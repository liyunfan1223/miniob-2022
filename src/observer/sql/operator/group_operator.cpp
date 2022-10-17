//
// Created by MorphLing on 2022/10/15.
//

#include "group_operator.h"
#include <algorithm>

RC GroupOperator::open()
{
  Operator * child = children_[0];
  child->open();

  ProjectTuple * projectTuple = static_cast<ProjectTuple *>(child->current_tuple());
  tuple_.speces_ = projectTuple->speces_;
  while(child->next() != RECORD_EOF) {
    Tuple * tuple = child->current_tuple();
    auto joinTuple = static_cast<ProjectTuple *>(tuple);
    all_tuples_.push_back(new ProjectTuple(*joinTuple));
  }
  std::sort(all_tuples_.begin(), all_tuples_.end(), [&](Tuple * t1, Tuple * t2) {
    for (size_t i = 0; i < group_num_; i++) {
      auto &groupAttr = group_attributes_[i];
      TupleCell tc1, tc2;
      t1->find_cell(groupAttr.relation_name, groupAttr.attribute_name, tc1);
      t2->find_cell(groupAttr.relation_name, groupAttr.attribute_name, tc2);
      int res = tc1.compare(tc2);
      if (res != 0) {
        return res < 0;
      }
    }
    return false;
  });
  return SUCCESS;
}

bool GroupOperator::in_group(Tuple *t1, Tuple *t2)
{
  for (size_t i = 0; i < group_num_; i++) {
    auto & orderAttr = group_attributes_[i];
    TupleCell tc1, tc2;
    t1->find_cell(orderAttr.relation_name, orderAttr.attribute_name, tc1);
    t2->find_cell(orderAttr.relation_name, orderAttr.attribute_name, tc2);
    int res = tc1.compare(tc2);
    if (res != 0) {
      return false;
    }
  }
  return true;
}

RC GroupOperator::next()
{
  if (current_tuple_count_ >= (int32_t) all_tuples_.size()) {
    return RC::RECORD_EOF;
  }
  std::vector<Tuple *> tmp_tuples_;
  tmp_tuples_.push_back(all_tuples_[current_tuple_count_++]);
  while (current_tuple_count_ < (int32_t) all_tuples_.size() &&
      in_group(all_tuples_[current_tuple_count_ - 1], all_tuples_[current_tuple_count_])) {
    tmp_tuples_.push_back(all_tuples_[current_tuple_count_++]);
  }
  tuple_.tuple_cells_.clear();
  for (int i = 0; i < (int32_t)tuple_.speces_.size(); i++) {
    tuple_.set_tuple_cells(i, tmp_tuples_);
  }

  return RC::SUCCESS;
}

RC GroupOperator::close()
{
  return children_[0]->close();
}

Tuple *GroupOperator::current_tuple()
{
  return &tuple_;
}