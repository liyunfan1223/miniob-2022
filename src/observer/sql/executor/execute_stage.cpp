/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/tables_join_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/order_operator.h"
#include "sql/operator/group_operator.h"
#include "sql/operator/subquery_predicate_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"
#include "sql/operator/exp_project_operator.h"

using namespace common;

//RC create_selection_executor(
//   Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
    case StmtType::SELECT: {
      try {
        do_select(sql_event);
      } catch (...) {
        const char *response = "FAILURE\n";
        session_event->set_response(response);
      }
    } break;
    case StmtType::INSERT: {
      do_insert(sql_event);
    } break;
    case StmtType::UPDATE: {
      try {
        do_update(sql_event);
      } catch (...) {
        const char *response = "FAILURE\n";
        session_event->set_response(response);
      }

    } break;
    case StmtType::DELETE: {
      do_delete(sql_event);
    } break;
    default: {
      LOG_WARN("should not happen. please implenment");
    } break;
    }
  } else {
    switch (sql->flag) {
    case SCF_HELP: {
      do_help(sql_event);
    } break;
    case SCF_CREATE_TABLE: {
      do_create_table(sql_event);
    } break;
    case SCF_CREATE_INDEX: {
      do_create_index(sql_event);
    } break;
    case SCF_SHOW_TABLES: {
      do_show_tables(sql_event);
    } break;
    case SCF_DESC_TABLE: {
      do_desc_table(sql_event);
    } break;

    case SCF_DROP_TABLE:
    case SCF_DROP_INDEX:
    case SCF_LOAD_DATA: {
      default_storage_stage_->handle_event(event);
    } break;
    case SCF_SYNC: {
      /*
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_BEGIN: {
      do_begin(sql_event);
      /*
      session_event->set_response("SUCCESS\n");
      */
    } break;
    case SCF_COMMIT: {
      do_commit(sql_event);
      /*
      Trx *trx = session->current_trx();
      RC rc = trx->commit();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_CLOG_SYNC: {
      do_clog_sync(sql_event);
    }
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
    } break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
    } break;
    case SCF_SHOW_INDEX: {
      // TODO
      do_show_index(sql_event);
    } break;
    case SCF_SELECT_NONTABLE: {
      try {
        do_select_nontable(sql_event);
      } catch (...) {
        const char *response = "FAILURE\n";
        session_event->set_response(response);
      }
    } break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_tuple_header(std::ostream &os, Operator &oper)
{
  Tuple * tuple = oper.current_tuple();
  const int cell_num = tuple->cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    tuple->cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }
    if (cell_spec->p_total_alias != nullptr) {
      os << cell_spec->p_total_alias;
    } else {
      switch (cell_spec->agg_type) {
        case AGG_AVG:
          os << "AVG(";
          break;
        case AGG_MIN:
          os << "MIN(";
          break;
        case AGG_MAX:
          os << "MAX(";
          break;
        case AGG_COUNT:
          os << "COUNT(";
          break;
        case AGG_SUM:
          os << "SUM(";
          break;
        default:
          break;
      }
      switch (cell_spec->func_type) {
        case FUNC_LENGTH:
          os << "LENGTH(";
          break;
        case FUNC_ROUND:
          os << "ROUND(";
          break;
        case FUNC_DATE:
          os << "DATE_FORMAT(";
          break;
        default:
          break;
      }
      if (cell_spec->alias()) {
        //      os << cell_spec->table_alias() << ".";
        os << cell_spec->alias();
      }

      if (cell_spec->agg_type != AGG_NONE || cell_spec->func_type != FUNC_NONE) {
        if (cell_spec->func_type == FUNC_ROUND && cell_spec->round_func_param != 0) {
          os << "," << cell_spec->round_func_param;
        }
        if (cell_spec->func_type == FUNC_DATE && cell_spec->date_func_param != nullptr) {
          os << "," << cell_spec->date_func_param;
        }
        os << ")";
      }
    }
  }
  if (cell_num > 0) {
    os << '\n';
  }
}

void print_tuple_header_multi_table(std::ostream &os, Operator &oper)
{
  Tuple * tuple = oper.current_tuple();
  const int cell_num = tuple->cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    tuple->cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }
    if (cell_spec->p_total_alias != nullptr) {
      os << cell_spec->p_total_alias;
    } else {
      switch (cell_spec->agg_type) {
        case AGG_AVG:
          os << "AVG(";
          break;
        case AGG_MIN:
          os << "MIN(";
          break;
        case AGG_MAX:
          os << "MAX(";
          break;
        case AGG_COUNT:
          os << "COUNT(";
          break;
        case AGG_SUM:
          os << "SUM(";
          break;
        default:
          break;
      }
      switch (cell_spec->func_type) {
        case FUNC_LENGTH:
          os << "LENGTH(";
          break;
        case FUNC_ROUND:
          os << "ROUND(";
          break;
        case FUNC_DATE:
          os << "DATE_FORMAT(";
          break;
        default:
          break;
      }
      if (cell_spec->alias()) {
        if (cell_spec->p_rel_alias != nullptr) {
          os << cell_spec->p_rel_alias << ".";
        } else if (cell_spec->table_alias() != nullptr) {
          os << cell_spec->table_alias() << ".";
        }
        os << cell_spec->alias();
      }
      if (cell_spec->agg_type != AGG_NONE || cell_spec->func_type != FUNC_NONE) {
        if (cell_spec->func_type == FUNC_ROUND && cell_spec->round_func_param != 0) {
          os << "," << cell_spec->round_func_param;
        }
        if (cell_spec->func_type == FUNC_DATE && cell_spec->date_func_param != nullptr) {
          os << "," << cell_spec->date_func_param;
        }
        os << ")";
      }
    }
  }

  if (cell_num > 0) {
    os << '\n';
  }
}

void tuple_to_string(std::ostream &os, const Tuple &tuple)
{
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;
  for (int i = 0; i < tuple.cell_num(); i++) {
    rc = tuple.cell_at(i, cell);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
      break;
    }

    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    cell.to_string(os);
  }
}

IndexScanOperator *try_to_create_index_scan_operator(FilterStmt *filter_stmt)
{
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  if (filter_units.empty() ) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;
  for (const FilterUnit * filter_unit : filter_units) {
    if (filter_unit->comp() == NOT_EQUAL) {
      continue;
    }

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
    	break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
    case EQUAL_TO:    { comp = EQUAL_TO; }    break;
    case LESS_EQUAL:  { comp = GREAT_THAN; }  break;
    case NOT_EQUAL:   { comp = NOT_EQUAL; }   break;
    case LESS_THAN:   { comp = GREAT_EQUAL; } break;
    case GREAT_EQUAL: { comp = LESS_THAN; }   break;
    case GREAT_THAN:  { comp = LESS_EQUAL; }  break;
    default: {
    	LOG_WARN("should not happen");
    }
    }
  }


  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {
  case EQUAL_TO: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;

  case LESS_EQUAL: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = true;
  } break;

  case LESS_THAN: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = false;
  } break;

  case GREAT_EQUAL: {
    left_cell = &value;
    left_inclusive = true;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  case GREAT_THAN: {
    left_cell = &value;
    left_inclusive = false;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  default: {
    LOG_WARN("should not happen. comp=%d", comp);
  } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index,
       left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}

RC add_projection(Db * db, std::vector<Table *> & tables, size_t attr_num, RelAttr * attributes, ProjectOperator *oper, std::unordered_map<std::string, char *> & rel_alias) {
  for (size_t i = 0; i < attr_num; i++) {
    auto & attr = attributes[i];
    if (attr.is_exp) {
      auto vec = parse_expression(attr.expression);
      for (auto & item : vec) {
        if (item->type == ATTR_ET) {
          Table * table = item->rel_attr->relation_name == nullptr ? tables[0] : db->find_table(item->rel_attr->relation_name);
          oper->add_projection(table, table->table_meta().field(item->rel_attr->attribute_name), item->rel_attr->aggType, rel_alias[std::string(table->name())], nullptr);
        }
      }
      continue;
    }
    // select *
    if (attr.relation_name == nullptr && 0 == strcmp(attr.attribute_name, "*")) {
      if (attr.aggType == AGG_COUNT) {
        oper->add_projection(nullptr, "*", AGG_COUNT, nullptr, attr.alias_name);
      } else if (attr.aggType == AGG_NONE) {
        for (int j = (int)tables.size() - 1; j >= 0; j--) {
          auto &table = tables[j];
          const TableMeta &table_meta = table->table_meta();
          const int field_num = table_meta.field_num();
          for (int k = table_meta.sys_field_num(); k < field_num; k++) {
            oper->add_projection(table, table_meta.field(k), attr.aggType, rel_alias[std::string(table->name())], nullptr);
          }
        }
      } else {
        return GENERIC_ERROR;
      }
    } else {
      Table * table = attr.relation_name == nullptr ? tables[0] : db->find_table(attr.relation_name);
      if (table == nullptr) {
        for (auto & item : rel_alias) {
          if (item.second != nullptr && 0 == strcmp(attr.relation_name, item.second)) {
            table = db->find_table(item.first.c_str());
            break;
          }
        }
      }
      // select id.*
      if (0 == strcmp(attr.attribute_name, "*")) {
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num();
        for (int j = table_meta.sys_field_num(); j < field_num; j++) {
          oper->add_projection(table, table_meta.field(j), attr.aggType, rel_alias[std::string(table->name())], nullptr);
        }
      } else {
        // select id.id
        if (table->table_meta().field(attr.attribute_name) == nullptr) {
          return RC::GENERIC_ERROR;
        }
        oper->add_projection(table, table->table_meta().field(attr.attribute_name), attr.aggType, rel_alias[std::string(table->name())], attr.alias_name);
      }
    }
  }
  return SUCCESS;
}

RC check_attr_in_group(size_t attr_num, RelAttr * attrs, size_t group_num, GroupAttr * groups)
{
  for (size_t i = 0; i < attr_num; i++) {
    RelAttr & attr = attrs[i];
    if (attr.is_agg) continue;
    if (attr.is_exp) continue;
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

RC replace_exists(Selects & selects) {
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
RC ExecuteStage::do_select_nontable(SQLStageEvent *sql_event)
{
  Selects & selects = sql_event->query()->sstr.selection;
  SessionEvent *session_event = sql_event->session_event();
  std::stringstream ss;
  for (size_t i = 0; i < selects.attr_num; i++) {
    RelAttr & rel = selects.attributes[i];
    if (i != 0) ss << " | ";

    if (rel.alias_name != nullptr) {
      ss << rel.alias_name;
    }
  }
  ss << std::endl;
  char tmp[100];
  for (size_t i = 0; i < selects.attr_num; i++) {
    RelAttr &rel = selects.attributes[i];
    if (i != 0) {
      ss << " | ";
    }
    switch (rel.func_type) {
      case FUNC_LENGTH: {
        if (rel.non_table_value->type != CHARS) {
          throw 0;
        }
        ss << std::to_string(strlen((char *)rel.non_table_value->data));
      } break;
      case FUNC_ROUND: {
        if (rel.non_table_value->type != FLOATS) {
          throw 0;
        }
        float val;
        if (rel.non_table_value->type == INTS) {
          val = *(int *)rel.non_table_value->data;
        } else if (rel.non_table_value->type == FLOATS) {
          val = *(float *)rel.non_table_value->data;
        }
        int digit = rel.round_func_param;
        int time = 1;
        for (int j = 1; j <= digit; j++) time *= 10;
        int total = val > 0 ? (int)(val * time + 0.5) : (int)(val * time - 0.5);
        if (time == 1) {
          ss << std::to_string(total / time);
        } else {
          ss << std::to_string(total / time) << "." << std::to_string(total % time);
        }
      } break;
      case FUNC_DATE: {
        if (rel.non_table_value->type != DATES) {
          throw 0;
        }
        if (rel.date_func_param == nullptr) {
          throw 0;
        }
        int y, m, d, val;
        val = *(int *)rel.non_table_value->data;
        y = val / 10000;
        m = val % 10000 / 100;
        d = val % 100;
        char * pattern = strdup(rel.date_func_param);
        int pattern_len = strlen(pattern);
        std::string res = "";
        for (int j = 0; j < pattern_len; j++) {
          if (pattern[j] != '%') {
            res += pattern[j];
          } else {
            j++;
            switch (pattern[j]) {
              case 'Y': {
                sprintf(tmp, "%d", y);
                res += std::string(tmp);
              } break;
              case 'y': {
                sprintf(tmp, "%02d", y % 100);
                res += std::string(tmp);
              } break;
              case 'M': {
                std::vector<std::string> month = {"January", "February", "March", "April", "May", "June", "July",
                "August", "September", "October", "November", "December"};
                res += month[m - 1];
              } break;
              case 'm': {
                sprintf(tmp, "%02d", m);
                res += std::string(tmp);
              } break;
              case 'D': {
                std::string suffix = "";
                if (d == 1 || d == 21 || d == 31) {
                  suffix = "st";
                } else if (d == 2 || d == 22) {
                  suffix = "ed";
                } else if (d == 3 || d == 23) {
                  suffix = "rd";
                } else suffix = "th";
                sprintf(tmp, "%d", d);
                res += std::string(tmp) + suffix;
              } break;
              case 'd': {
                sprintf(tmp, "%02d", d);
                res += std::string(tmp);
              }
            }
          }
        }
        ss << res;
      } break;
      default: {
      }
    }
  }
  ss << std::endl;
  session_event->set_response(ss.str());
  return SUCCESS;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  Selects & selects = sql_event->query()->sstr.selection;
  Db *db = session_event->session()->get_current_db();
  RC rc = RC::SUCCESS;

  replace_exists(selects);
  std::vector<TableScanOperator *> scan_opers;

  std::vector<Table *> tables;
  for (size_t i = 0; i < selects.relation_num; i++) {
    Table * t_db = db->find_table(selects.relations[i]);
    if (t_db == nullptr) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables.push_back(db->find_table(selects.relations[i]));
  }
  for (auto table : tables) {
    scan_opers.push_back(new TableScanOperator(table));
  }
  for (int i = 0; i < (int)selects.relation_num - 1; i++) {
    for (int j = i + 1; j < (int)selects.relation_num; j++) {
      if (selects.relations_alias[i] != nullptr && selects.relations_alias[j] != nullptr
          && strcmp(selects.relations_alias[i], selects.relations_alias[j]) == 0) {
        session_event->set_response("FAILURE\n");
        return RC::GENERIC_ERROR;
      }
    }
  }
  std::unordered_map<std::string, char *> rel_alias;
  for (size_t i = 0; i < selects.relation_num; i++) {
    rel_alias[std::string(selects.relations[i])] = selects.relations_alias[i];
  }

  SubqueryPredicateOperator pred_oper(selects.conditions, selects.condition_num, selects.relations[0], selects.relations_alias[0], db);
  pred_oper.add_child(scan_opers[0]);

  TablesJoinPredOperator join_pred_oper(scan_opers, select_stmt->filter_stmt(),
      selects.conditions, selects.condition_num, rel_alias);

  OrderOperator order_by_oper(selects.order_num, selects.order_attributes);
  if (scan_opers.size() == 1) {
    order_by_oper.add_child(&pred_oper);
  } else {
    order_by_oper.add_child(&join_pred_oper);
  }

  ProjectOperator project_oper;
  project_oper.add_child(&order_by_oper);
  rc = add_projection(db, tables, selects.attr_num, selects.attributes, &project_oper, rel_alias);
  if (rc != SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }
  Operator * tmp_oper = nullptr;
  Operator * output_oper = nullptr;

  bool has_agg = false;
  for (auto & item : project_oper.tuple_.speces_) {
    if (item->agg_type != AGG_NONE) {
      has_agg = true;
    }
  }

  GroupOperator groupOperator(selects.group_num, selects.group_attributes,
      selects.having_num, selects.having_conditions);
  groupOperator.add_child(&project_oper);
  if (has_agg) {
    rc = check_attr_in_group(selects.attr_num, selects.attributes, selects.group_num, selects.group_attributes);
    if (rc != SUCCESS) {
      session_event->set_response("FAILURE\n");
      return rc;
    }
    tmp_oper = &groupOperator;
  } else {
    tmp_oper = &project_oper;
  }


  ExpProjectOperator exp_oper(selects.attr_num, selects.attributes, tables, db, rel_alias);
  exp_oper.add_child(tmp_oper);

  output_oper = &exp_oper;
  rc = output_oper->open();
  std::stringstream ss;
  if (select_stmt->tables().size() != 1) {
    print_tuple_header_multi_table(ss, *output_oper);
  } else {
    print_tuple_header(ss, *output_oper);
  }
  while ((rc = output_oper->next()) == RC::SUCCESS) {
    Tuple * tuple = output_oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    tuple_to_string(ss, *tuple);
    ss << std::endl;
  }
  session_event->set_response(ss.str());
  rc = RC::SUCCESS;
  return rc;
}

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}

RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name,
			create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}
RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CreateIndex &create_index = sql_event->query()->sstr.create_index;
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  RC rc = table->create_index(nullptr, create_index.index_name, create_index.attribute_name, create_index.attr_num,create_index.is_unique);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}
RC ExecuteStage::do_show_index(SQLStageEvent *sql_event)
{
  const char * table_name = sql_event->query()->sstr.show_index.relation_name;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  Table *table = db->find_table(table_name);
  if (table==nullptr){
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::stringstream ss;
  std::string s;
  ss<<"Table | Non_unique | Key_name | Seq_in_index | Column_name"<<std::endl;
  s=table->get_index();
  ss<<s;
  session_event->set_response(ss.str().c_str());
  return RC::SUCCESS;
}
RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();
  Inserts & inserts = sql_event->query()->sstr.insertion;
  const char *table_name = inserts.relation_name;
  Table *table = db->find_table(table_name);
  //循环，有一个insert不成功需要回滚
//  RC rc = table->insert_record(trx, inserts.records[0].value_num, inserts.records[0].values);
  RC rc = RC::SUCCESS;
  //  insert_record 函数参数连带修改
  Record record;
  Record recordlist[inserts.record_num];
  int rollback_idx=0;
////判断是否有unique index，判断是否有和insert 相同的记录，passed unique insert
//  std::vector<Index *>  indexs=table->get_total_index();
//  int flag=0;
//  int index_need_check_position = -1;
//  for(Index * idx:indexs){
//    index_need_check_position++;
//    if ((int)idx->index_meta().is_unique()){
//      //judge whether records are not unique
//      const std::vector<std::string> &fields = idx->index_meta().field();
////     多索引的时候存在问题
//      LOG_INFO("Check unique index: %s, %s, %d", idx->index_meta().name(), idx->index_meta().field()[0].c_str(), index_need_check_position);
//        const char *left_key = static_cast<const char *>(inserts.records->values[index_need_check_position].data);
//        const char *right_key = static_cast<const char *>(inserts.records->values[index_need_check_position].data);
//        int left_len = 4;
//        int right_len = 4;
//        bool left_inclusive = true;
//        bool right_inclusive = true;
//        if (inserts.records->values[index_need_check_position].type == CHARS) {
//          left_len = left_key != nullptr ? strlen(left_key) : 0;
//          right_len = right_key != nullptr ? strlen(right_key) : 0;
//        }
//        IndexScanner *index_scanner = idx->create_scanner(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
//        RID rid;
//        RC rc2 = index_scanner->next_entry(&rid);
//        if (rc2 != RC::SUCCESS) {
//          continue;
//        } else {
//          session_event->set_response("FAILURE\n");
//          return RC::REPEATED_UNIQUE_VALUE;
//        }
//    }
//  }
  std::vector<Index *>  indexs=table->get_total_index();
  int flag=0;
  for(Index * idx:indexs){
    if ((int)idx->index_meta().is_unique()){
      //构造condition，调用ScanOperator
      //如果field包含update条件，那么用要修改的field属性进行查询。查得到，flag=1。
      const std::vector<std::string> &fields = idx->index_meta().field();
      int c_num=0;
      Condition c[20];
      for( std::string f:fields){
        //field是否在修改的值中
        for(int j =2;j<table->table_meta().field_num();j++){//table的前两个field不用看，是多余的
          if (strcmp(f.c_str(),table->table_meta().field(j)->name())==0){
            //            构造condition
            c[c_num].left_is_attr=1;    // TRUE if left-hand side is an attribute
            Value left_value;    // left-hand side value if left_is_attr = FALSE
            c[c_num].left_attr.attribute_name=const_cast<char *>(table->table_meta().field(j)->name());   // left-hand side attribute
            c[c_num].comp=EQUAL_TO;         // comparison operator
            c[c_num].right_is_attr=0;   // TRUE if right-hand side is an attribute
            c[c_num].right_value=inserts.records[0].values[j-2];
            if(c_num==0){
              c[c_num].conj=CONJ_FIRST;
            }else{
              c[c_num].conj=CONJ_AND;
            }
            c_num++;
          }
        }
      }
      //index 包含在update的修改范围内
      if (c_num==fields.size()){
        TableScanOperator scan_oper(table);
        SubqueryPredicateOperator spred_oper(c, c_num, table_name, db);
        spred_oper.add_child(&scan_oper);
        std::vector<Operator *> children;
        children.push_back(&spred_oper);
        if (children.size() != 1) {
          LOG_WARN("delete operator must has 1 child");
          session_event->set_response("FAILURE\n");
          return RC::INTERNAL;
        }

        Operator *child = children[0];
        RC rc = child->open();
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to open child operator: %s", strrc(rc));
          session_event->set_response("FAILURE\n");
          return rc;
        }
        while (RC::SUCCESS == (rc = child->next())) {
          Tuple *tuple = child->current_tuple();
          if (nullptr == tuple) {
            continue;
          }else{
            flag=1;
            break;
          }
        }
      }
    }
  }
  if(flag==1){
    session_event->set_response("FAILURE\n");
    return RC::REPEATED_UNIQUE_VALUE;
  }
  for (int i = 0; i < (int)inserts.record_num; i++) {
    rc= table->insert_record(trx, inserts.records[i].value_num, inserts.records[i].values, record);
//    记录所有成功的operation的地址。operations_是trx的private变量。调用table->rollback_insert()。在rollback之后要delete_operatoin。
//    考虑并发情况会更加复杂
    //  delete record会处理这个部分
    if (rc == RC::SUCCESS) {
      recordlist[i] = record;
    }else{
      rollback_idx=i;
      break;
    };

  }
  if (rc == RC::SUCCESS) {
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }
      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }
      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      session_event->set_response("SUCCESS\n");
    }
  } else {
    session_event->set_response("FAILURE\n");
    //回滚本次操作的record,operation暂时不变
    for (int j = 0; j < rollback_idx; j++) {
      table->delete_record(trx,&recordlist[j]);
    }

  }

  return rc;
}

RC ExecuteStage::do_update(SQLStageEvent * sql_event) //UpdateStmt *stmt, SessionEvent *session_event)
{
  UpdateStmt *stmt = (UpdateStmt *)sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();

//  Stmt *stmt = sql_event->stmt();
//  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }
  Updates & updates = sql_event->query()->sstr.update;

  UpdateStmt *update_stmt = (UpdateStmt *)stmt;
  Table *table = update_stmt->table();

  std::vector<const FieldMeta *> fields;
  std::vector<int> field_idxs;
  for (size_t i = 0; i < update_stmt->field_names().size(); i++) {
    const FieldMeta *field = table->table_meta().field(update_stmt->field_names()[i]);
    int field_idx = table->table_meta().find_field_index_by_name(update_stmt->field_names()[i]);
    fields.push_back(field);
    field_idxs.push_back(field_idx);
  }


  TableScanOperator scan_oper(update_stmt->table());

  SubqueryPredicateOperator spred_oper(updates.conditions, updates.condition_num, updates.relation_name, db);

  // pred_oper.add_child(&scan_oper);
  spred_oper.add_child(&scan_oper);

  std::vector<Operator *> children;
  // children.push_back(&pred_oper);
  children.push_back(&spred_oper);


  if (children.size() != 1) {
    LOG_WARN("delete operator must has 1 child");
    session_event->set_response("FAILURE\n");
    return RC::INTERNAL;
  }

  //unique cases：如果修改后会发生冲突，但本身找不到需要修改的记录，也是返回success
  Operator *child2 = children[0];
  RC rc_tag=RC::SUCCESS;
  RC rc2 = child2->open();
  if (rc2 != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc2));
    session_event->set_response("FAILURE\n");
    return rc2;
  }
  rc2=RC::SUCCESS;
  if (child2->next()!=RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc2 = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc2 != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc2;
      }

      rc2 = clog_manager->clog_append_record(clog_record);
      if (rc2 != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc2;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }

    return rc2;
  }

  //unique cases
  std::vector<Index *>  indexs=table->get_total_index();
  int flag=0;
  for(Index * idx:indexs){
    if ((int)idx->index_meta().is_unique()){
      //构造condition，调用ScanOperator
      //如果field包含update条件，那么用要修改的field属性进行查询。查得到，flag=1。
      const std::vector<std::string> &fields = idx->index_meta().field();
      int c_num=0;
      Condition c[20];
      for( std::string f:fields){
        //field是否在修改的值中
        for(int j =0;j<updates.attr_num;j++){
          if (strcmp(f.c_str(),updates.attribute_name[j])==0){
            //            构造condition
            c[c_num].left_is_attr=1;    // TRUE if left-hand side is an attribute
                                                                            // 1时，操作符左边是属性名，0时，是属性值
            Value left_value;    // left-hand side value if left_is_attr = FALSE
            c[c_num].left_attr.attribute_name=updates.attribute_name[j];   // left-hand side attribute
            c[c_num].comp=EQUAL_TO;         // comparison operator
            c[c_num].right_is_attr=0;   // TRUE if right-hand side is an attribute
                                                                            // 1时，操作符右边是属性名，0时，是属性值
                                                                            //          c[c_num].right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
            c[c_num].right_value=updates.value[j];
            if(c_num==0){
              c[c_num].conj=CONJ_FIRST;
            }else{
              c[c_num].conj=CONJ_AND;
            }
            c_num++;
          }
        }
      }
      //index 包含在update的修改范围内
      if (c_num==fields.size()){
        TableScanOperator scan_oper2(update_stmt->table());
        SubqueryPredicateOperator spred_oper2(c, c_num, updates.relation_name, db);
        spred_oper2.add_child(&scan_oper2);
        std::vector<Operator *> children2;
        children2.push_back(&spred_oper2);
        if (children2.size() != 1) {
          LOG_WARN("delete operator must has 1 child");
          session_event->set_response("FAILURE\n");
          return RC::INTERNAL;
        }

        Operator *child2 = children2[0];
        RC rc = child2->open();
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to open child operator: %s", strrc(rc));
          session_event->set_response("FAILURE\n");
          return rc;
        }
        while (RC::SUCCESS == (rc = child2->next())) {
          Tuple *tuple = child2->current_tuple();
          if (nullptr == tuple) {
            continue;
          }else{
            flag=1;
            break;
          }
        }
      }
    }
  }
  if(flag==1){
    session_event->set_response("FAILURE\n");
    return RC::REPEATED_UNIQUE_VALUE;
  }

  Operator *child = children[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    session_event->set_response("FAILURE\n");
    return rc;
  }

  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    rc = table->update_record(trx, &record,fields, update_stmt->values(), field_idxs, db);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    }
  }

  // end
  rc = RC::SUCCESS;
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }

  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;

  TableScanOperator scan_oper(delete_stmt->table());
  PredicateOperator pred_oper(delete_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      } 

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}
