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

#pragma once

#include "sql/operator/operator.h"

class FilterStmt;

/**
 * PredicateOperator 用于单个表中的记录过滤
 * 如果是多个表数据过滤，比如join条件的过滤，需要设计新的predicate或者扩展:w
 */
class PredicateOperator : public Operator
{
public:
  PredicateOperator(FilterStmt *filter_stmt)
      : filter_stmt_(filter_stmt)
  {}
  PredicateOperator(FilterStmt *filter_stmt,
      Condition *conditions, size_t condition_num, const char * rel_name)
    : filter_stmt_(filter_stmt), conditions_(conditions), condition_num_(condition_num), rel_name_(rel_name)
  {

  }

  virtual ~PredicateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
  //int tuple_cell_num() const override;
  //RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  bool do_predicate(Tuple &tuple);
  bool do_predicate_by_cond(Tuple &tuple);
  // 遇到子查询 调用该函数 返回 ret_cell
  RC execute_sub_query(std::vector<Tuple *> & parent_tuples, std::vector<const char *> & parent_rels, Selects * selects, TupleCell & ret_cell);
private:
  FilterStmt *filter_stmt_ = nullptr;
  Condition * conditions_;
  size_t condition_num_;
  std::vector<Tuple *> parent_tuples_;
  std::vector<const char *> parent_rel_;
  const char * rel_name_;
};
