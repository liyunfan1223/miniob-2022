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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC PredicateOperator::next()
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

    if (do_predicate(*tuple)) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple * PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

bool PredicateOperator::do_predicate(Tuple &tuple)
{
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp) {
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      if (left_cell.condition_satisfy(comp, right_cell) == 0) {
        return false;
      }
    }
  }
  return true;
}

RC PredicateOperator::execute_sub_query(std::vector<Tuple *> &parent_tuples, std::vector<const char *> &parent_rels, Selects *selects, TupleCell &ret_cell)
{
  return RC::UNIMPLENMENT;
}

bool PredicateOperator::do_predicate_by_cond(Tuple &tuple)
{
  for (size_t i = 0; i < condition_num_; i++) {
    Condition & cond = conditions_[i];
    TupleCell tc_left, tc_right;
    CompOp compOp = cond.comp;

    if (cond.left_is_attr) {
      RelAttr & relAttr = cond.left_attr;
      tuple.find_cell(relAttr.relation_name, relAttr.attribute_name, tc_left);
    } else {
      Value & value = cond.left_value;
      if (value.is_sub_select) {
        parent_tuples_.push_back(&tuple);
        parent_rel_.push_back(rel_name_);
        execute_sub_query(parent_tuples_, parent_rel_, value.selects, tc_left);
        parent_tuples_.pop_back();
        parent_rel_.pop_back();
      } else {
        tc_left.set_type(value.type);
        tc_left.set_data((char *)value.data);
        if (value.type == CHARS) {
          tc_left.set_length(strlen((char *)value.data));
        }
      }
    }

    if (cond.right_is_attr) {
      RelAttr & relAttr = cond.right_attr;
      tuple.find_cell(relAttr.relation_name, relAttr.attribute_name, tc_right);
    } else {
      Value & value = cond.right_value;
      if (value.is_sub_select) {
        parent_tuples_.push_back(&tuple);
        parent_rel_.push_back(rel_name_);
        execute_sub_query(parent_tuples_, parent_rel_, value.selects, tc_right);
        parent_tuples_.pop_back();
        parent_rel_.pop_back();
      } else {
        tc_right.set_type(value.type);
        tc_right.set_data((char *)value.data);
        if (value.type == CHARS) {
          tc_right.set_length(strlen((char *)value.data));
        }
      }
    }

    // 对 in 和 not in 特殊处理
    if (!cond.right_is_attr && cond.right_value.is_set) {
        bool in = false;
        for (size_t i = 0; i < (size_t)cond.right_value.set_length; i++) {
          auto val = cond.right_value.set_values[i];
          TupleCell tmp_cell;
          tmp_cell.set_type(val.type);
          tmp_cell.set_data((char *)val.data);
          if (tc_left.condition_satisfy(EQUAL_TO, tmp_cell)) {
            in = true;
          }
        }
        if (compOp == IN_OP && !in) return false;
        if (compOp == NOT_IN_OP && in) return false;
    } else {
      if (!tc_left.condition_satisfy(compOp, tc_right)) {
        return false;
      }
    }
  }
  return true;
}
// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
