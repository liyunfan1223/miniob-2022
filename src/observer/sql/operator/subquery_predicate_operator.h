//
// Created by MorphLing on 2022/10/22.
//

#pragma once

#include "sql/operator/operator.h"
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
#include "storage/common/db.h"

class FilterStmt;

class SubqueryPredicateOperator: public Operator {
public:
  SubqueryPredicateOperator(Condition *conditions, size_t condition_num, const char * rel_name, Db * db)
      : conditions_(conditions), condition_num_(condition_num), rel_name_(rel_name), db_(db)
  {

  }
  SubqueryPredicateOperator(Condition *conditions, size_t condition_num, const char * rel_name, Db * db,
      std::vector<Tuple *> parent_tuples, std::vector<const char *> parent_rels)
      : conditions_(conditions), condition_num_(condition_num),
        parent_tuples_(parent_tuples), parent_rel_(parent_rels), rel_name_(rel_name), db_(db)
  {

  }
  virtual ~SubqueryPredicateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
  //int tuple_cell_num() const override;
  //RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  RC replace_exists(Selects & selects);
  RC add_projection(Db * db, std::vector<Table *> & tables, size_t attr_num, RelAttr * attributes, ProjectOperator *oper);
  RC check_attr_in_group(size_t attr_num, RelAttr * attrs, size_t group_num, GroupAttr * groups);
  bool do_predicate(Tuple &tuple);
  bool do_predicate_by_cond(Tuple &tuple);
  // 遇到子查询 调用该函数 返回 ret_cell
  RC execute_sub_query(std::vector<Tuple *> & parent_tuples, std::vector<const char *> & parent_rels, Selects * selects, TupleCell & ret_cell);
private:
  Condition * conditions_;
  size_t condition_num_;
  std::vector<Tuple *> parent_tuples_;
  std::vector<const char *> parent_rel_;
  const char * rel_name_;
  Db * db_ = nullptr;
};
