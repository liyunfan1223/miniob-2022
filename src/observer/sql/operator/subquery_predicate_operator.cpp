//
// Created by MorphLing on 2022/10/22.
//

#include "subquery_predicate_operator.h"

#include "common/log/log.h"
#include "sql/operator/subquery_predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"

RC SubqueryPredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC SubqueryPredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate_by_cond(*tuple)) {
      return rc;
    }
  }
  return rc;
}

RC SubqueryPredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple * SubqueryPredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

RC SubqueryPredicateOperator::replace_exists(Selects & selects) {
  for (size_t i = 0; i < selects.condition_num; i++) {
    Condition & cond = selects.conditions[i];
    if (cond.comp == EXISTS_OP || cond.comp == NOT_EXISTS_OP) {
      cond.right_value.selects->attributes[0].is_agg = 1;
      cond.right_value.selects->attributes[0].aggType = AGG_COUNT;
      cond.right_value.selects->attributes[0].relation_name = nullptr;
      cond.right_value.selects->attributes[0].attribute_name = (char *)"*";
    }
    if (cond.comp == EXISTS_OP) {
      cond.comp = LESS_THAN;
    }
    if (cond.comp == NOT_EXISTS_OP) {
      cond.comp = EQUAL_TO;
    }
  }
  return SUCCESS;
}

RC SubqueryPredicateOperator::add_projection(Db * db, std::vector<Table *> & tables, size_t attr_num, RelAttr * attributes, ProjectOperator *oper) {
  for (size_t i = 0; i < attr_num; i++) {
    auto & attr = attributes[i];
    // select *
    if (attr.relation_name == nullptr && 0 == strcmp(attr.attribute_name, "*")) {
      if (attr.aggType == AGG_COUNT) {
        oper->add_projection(nullptr, "*", AGG_COUNT);
      } else if (attr.aggType == AGG_NONE) {
        for (int j = (int)tables.size() - 1; j >= 0; j--) {
          auto &table = tables[j];
          const TableMeta &table_meta = table->table_meta();
          const int field_num = table_meta.field_num();
          for (int k = table_meta.sys_field_num(); k < field_num; k++) {
            oper->add_projection(table, table_meta.field(k), attr.aggType);
          }
        }
      } else {
        return GENERIC_ERROR;
      }
    } else {
      Table * table = attr.relation_name == nullptr ? tables[0] : db->find_table(attr.relation_name);
      // select id.*
      if (0 == strcmp(attr.attribute_name, "*")) {
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num();
        for (int j = table_meta.sys_field_num(); j < field_num; j++) {
          oper->add_projection(table, table_meta.field(j), attr.aggType);
        }
      } else {
        // select id.id
        if (table->table_meta().field(attr.attribute_name) == nullptr) {
          return RC::GENERIC_ERROR;
        }
        oper->add_projection(table, table->table_meta().field(attr.attribute_name), attr.aggType);
      }
    }
  }
  return SUCCESS;
}

RC SubqueryPredicateOperator::check_attr_in_group(size_t attr_num, RelAttr * attrs, size_t group_num, GroupAttr * groups)
{
  for (size_t i = 0; i < attr_num; i++) {
    RelAttr & attr = attrs[i];
    if (attr.is_agg) continue;
    bool in_group = false;
    for (size_t j = 0; j < group_num; j++) {
      GroupAttr & group = groups[j];
      if ((strcmp(attr.attribute_name, group.attribute_name) == 0) &&
          ((attr.relation_name == nullptr && group.relation_name == nullptr) || (
                                                                                    attr.relation_name != nullptr && group.relation_name != nullptr && strcmp(attr.relation_name, group.relation_name) == 0))
      ) {
        in_group = true;
      }
    }
    if (!in_group) {
      return GENERIC_ERROR;
    }
  }
  return SUCCESS;
}

RC SubqueryPredicateOperator::execute_sub_query(std::vector<Tuple *> &parent_tuples,
    std::vector<const char *> &parent_rels, Selects *selects, TupleCell &ret_cell, Db * db_)
{
  RC rc = RC::SUCCESS;
  replace_exists(*selects);

  std::vector<TableScanOperator *> scan_opers;
  std::vector<Table *> tables;
  for (size_t i = 0; i < selects->relation_num; i++) {
    Table * t_db = db_->find_table(selects->relations[i]);
    if (t_db == nullptr) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables.push_back(db_->find_table(selects->relations[i]));
  }
  for (auto table : tables) {
    scan_opers.push_back(new TableScanOperator(table));
  }

  SubqueryPredicateOperator pred_oper(selects->conditions, selects->condition_num, tables[0]->name(), db_,
      parent_tuples, parent_rels);
  pred_oper.add_child(scan_opers[0]);

//  OrderOperator order_by_oper(selects->order_num, selects->order_attributes);
//
//  order_by_oper.add_child(&pred_oper);

  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);
  rc = add_projection(db_, tables, selects->attr_num, selects->attributes, &project_oper);
  if (rc != SUCCESS) {
//    session_event->set_response("FAILURE\n");
    return rc;
  }
  Operator * output_oper = nullptr;

  bool has_agg = false;
  for (size_t i = 0; i < selects->attr_num; i++) {
    if (selects->attributes[i].is_agg) {
      has_agg = true;
    }
  }

  GroupOperator groupOperator(selects->group_num, selects->group_attributes,
      selects->having_num, selects->having_conditions);
  groupOperator.add_child(&project_oper);
  if (has_agg) {
    rc = check_attr_in_group(selects->attr_num, selects->attributes, selects->group_num, selects->group_attributes);
    if (rc != SUCCESS) {
//      session_event->set_response("FAILURE\n");
      return rc;
    }
    output_oper = &groupOperator;
  } else {
    output_oper = &project_oper;
  }
  output_oper->open();
  std::vector<TupleCell *> res_cells;

  while ((rc = output_oper->next()) == RC::SUCCESS) {
    Tuple * tuple = output_oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    TupleCell * tmp_cell = new TupleCell();
    if (tuple->cell_num() > 1) {
      return GENERIC_ERROR;
    }
    tuple->cell_at(0, *tmp_cell);
    res_cells.push_back(tmp_cell);
  }
  if (has_agg || res_cells.size() == 1) {
    ret_cell = *res_cells[0];
  } else {
    ret_cell.is_set = 1;
    for (auto r : res_cells) {
      ret_cell.set_cells.push_back(r);
    }
  }

  return RC::SUCCESS;
}

bool SubqueryPredicateOperator::do_predicate_by_cond(Tuple &tuple)
{
  bool result = true;
  for (size_t i = 0; i < condition_num_; i++) {
    Condition & cond = conditions_[i];
    TupleCell tc_left, tc_right;
    CompOp compOp = cond.comp;

    if (cond.left_is_attr) {
      RelAttr & relAttr = cond.left_attr;
      if (relAttr.relation_name == nullptr || strcmp(rel_name_, relAttr.relation_name) == 0) {
        tuple.find_cell(relAttr.relation_name, relAttr.attribute_name, tc_left);
      } else {
        for (int i = 0; i < (int)parent_rel_.size(); i++) {
          if (strcmp(relAttr.relation_name, parent_rel_[i]) == 0) {
            parent_tuples_[i]->find_cell(relAttr.relation_name, relAttr.attribute_name, tc_left);
            break;
          }
        }
      }
    } else {
      Value & value = cond.left_value;
      if (value.type == EXPRESSION_T) {
        std::vector<ExpElement *> vec = parse_expression(value.expression);
        get_tuple_cell_for_exp(vec, tuple, tc_left);
      } else {
        if (value.is_sub_select) {
          parent_tuples_.push_back(&tuple);
          parent_rel_.push_back(rel_name_);
          if (execute_sub_query(parent_tuples_, parent_rel_, value.selects, tc_left, db_) != SUCCESS) {
            throw 0;
          }
          parent_tuples_.pop_back();
          parent_rel_.pop_back();
        } else {
          if (value.is_null) {
            tc_left.set_type(NULL_T);
          } else {
            tc_left.set_type(value.type);
            tc_left.set_data((char *)value.data);
            if (value.type == CHARS) {
              tc_left.set_length(strlen((char *)value.data));
            }
          }
        }
      }
    }

    if (cond.right_is_attr) {
      RelAttr & relAttr = cond.right_attr;
      if (relAttr.relation_name == nullptr || strcmp(rel_name_, relAttr.relation_name) == 0) {
        tuple.find_cell(relAttr.relation_name, relAttr.attribute_name, tc_right);
      } else {
        for (int j = 0; j < (int)parent_rel_.size(); j++) {
          if (strcmp(relAttr.relation_name, parent_rel_[j]) == 0) {
            parent_tuples_[j]->find_cell(relAttr.relation_name, relAttr.attribute_name, tc_right);
            break;
          }
        }
      }
    } else {
      Value & value = cond.right_value;
      if (value.type == EXPRESSION_T) {
        std::vector<ExpElement *> vec = parse_expression(value.expression);
        get_tuple_cell_for_exp(vec, tuple, tc_right);
      } else {
        if (value.is_sub_select) {
          parent_tuples_.push_back(&tuple);
          parent_rel_.push_back(rel_name_);
          if (execute_sub_query(parent_tuples_, parent_rel_, value.selects, tc_right, db_) != SUCCESS) {
            throw 0;
          }
          parent_tuples_.pop_back();
          parent_rel_.pop_back();
        } else if (value.is_set) { // 处理 set
          tc_right.is_set = 1;
          for (int j = 0; j < value.set_length; j++) {
            TupleCell * p_tmp_cell;
            p_tmp_cell = new TupleCell(value.set_values[j].type, (char *)value.set_values[j].data);
            tc_right.set_cells.push_back(p_tmp_cell);
          }
        } else {
          if (value.is_null) {
            tc_right.set_type(NULL_T);
          } else {
            tc_right.set_type(value.type);
            tc_right.set_data((char *)value.data);
            if (value.type == CHARS) {
              tc_right.set_length(strlen((char *)value.data));
            }
          }
        }
      }
    }

    bool now_result = tc_left.condition_satisfy(compOp, tc_right);
    switch (cond.conj) {
      case CONJ_FIRST: {
        result = now_result;
      } break;
      case CONJ_AND: {
        result = result && now_result;
      } break;
      case CONJ_OR: {
        result = result || now_result;
      } break;
    }
  }
  return result;
}