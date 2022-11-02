//
// Created by MorphLing on 2022/11/1.
//

#include "function_operator.h"

RC FunctionOperator::open()
{
  RC rc = children_[0]->open();
  return rc;
}

RC FunctionOperator::next()
{
  children_[0]->next();
  children_[0]->current_tuple();
  return LOCKED_SHAREDCACHE;
}

RC FunctionOperator::close()
{
  return LOCKED_SHAREDCACHE;
}

Tuple *FunctionOperator::current_tuple()
{
  return nullptr;
}
