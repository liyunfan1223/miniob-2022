//
// Created by MorphLing on 2022/10/29.
//

#include "exp_project_operator.h"


RC ExpProjectOperator::open()
{
  RC rc = children_[0]->open();
  return rc;
}

RC ExpProjectOperator::next()
{
  RC rc = children_[0]->next();
  if (rc != SUCCESS) {
    return rc;
  }
  tuple_.tuple_cells_.clear();
  for (int i = 0; i < (int32_t)tuple_.speces_.size(); i++) {
    tuple_.set_tuple_cells(i, children_[0]->current_tuple());
  }
  return RC::SUCCESS;
}

RC ExpProjectOperator::close()
{
  RC rc = children_[0]->close();
  return rc;
}
Tuple *ExpProjectOperator::current_tuple()
{
  return &tuple_;
}
