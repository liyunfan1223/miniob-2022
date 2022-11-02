//
// Created by MorphLing on 2022/11/1.
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
#include "util/util.h"

class FunctionOperator: public Operator {
public:
  ~FunctionOperator() override = default;
  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
};
