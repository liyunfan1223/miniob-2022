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
  if (first_next_ && (int32_t) all_tuples_.size() == 0) {
    first_next_ = 0;
    std::vector<Tuple *> tmp_tuples;
    tuple_.tuple_cells_.clear();
    for (int i = 0; i < (int32_t)tuple_.speces_.size(); i++) {
      tuple_.set_tuple_cells(i, tmp_tuples);
    }
    return RC::SUCCESS;
  }

  if (current_tuple_count_ >= (int32_t) all_tuples_.size()) {
    return RC::RECORD_EOF;
  }
  std::vector<Tuple *> tmp_tuples;
  tmp_tuples.push_back(all_tuples_[current_tuple_count_++]);
  while (current_tuple_count_ < (int32_t) all_tuples_.size() &&
      in_group(all_tuples_[current_tuple_count_ - 1], all_tuples_[current_tuple_count_])) {
    tmp_tuples.push_back(all_tuples_[current_tuple_count_++]);
  }
  tuple_.tuple_cells_.clear();
  for (int i = 0; i < (int32_t)tuple_.speces_.size(); i++) {
    tuple_.set_tuple_cells(i, tmp_tuples);
  }

  if (!do_having_predicate_(tmp_tuples)) {
    return next();
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

bool GroupOperator::do_having_predicate_(std::vector<Tuple *> & tmp_tuples)
{
  for (size_t i = 0; i < having_num_; i++) {
    TupleCell tc_left, tc_right;
    auto & cond = having_conditions_[i];
    if (cond.left_is_attr) {
//      GroupTuple tmp_group_tuple;
//      tmp_group_tuple.speces_ = tuple_.speces_;
//      int32_t idx = tuple_.
      if (strcmp(cond.left_attr.attribute_name, "*") == 0) {
        GroupTuple::get_count(true, 0, tmp_tuples, UNDEFINED, tc_left);
      } else {
        tuple_.find_cell(cond.left_attr.relation_name, cond.left_attr.attribute_name, tc_left);
      }
    } else {
      tc_left.set_type(cond.left_value.type);
      tc_left.set_data((char *)cond.left_value.data);
      if (cond.left_value.type == CHARS) {
        tc_left.set_length(strlen(tc_left.data()));
      }
    }

    if (cond.right_is_attr) {
      tuple_.find_cell(cond.right_attr.relation_name, cond.right_attr.attribute_name, tc_right);
    } else {
      tc_right.set_type(cond.right_value.type);
      tc_right.set_data((char *)cond.right_value.data);
      if (cond.right_value.type == CHARS) {
        tc_right.set_length(strlen(tc_right.data()));
      }
    }

    if (!tc_left.condition_satisfy(cond.comp, tc_right)) {
      return false;
    }
  }
  return true;
}