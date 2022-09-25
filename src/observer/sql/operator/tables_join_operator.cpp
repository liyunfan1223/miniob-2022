//
// Created by Clouds on 2022/9/24.
//

#include "tables_join_operator.h"
#include "table_scan_operator.h"

RC TablesJoinOperator::open()
{
  for (auto it = scan_opers_.rbegin(); it != scan_opers_.rend(); it++)
  {
    auto &scan_oper = *it;
    std::vector<Record *> table_records;
    RC rc = scan_oper->open();
    if (rc == RC::SUCCESS) {
      while (scan_oper->next() == RC::SUCCESS) {
        auto tuple = static_cast<RowTuple*>(scan_oper->current_tuple());
        table_records.push_back(new Record(tuple->record().rid(), tuple->record().data()));
      }
      tuple_.add_schema(scan_oper->table(), scan_oper->table()->table_meta().field_metas());
      tuple_.add_sum(tuple_length_);
      tuple_length_ += scan_oper->table()->table_meta().field_num();
      record_length_ += table_records.size();
      index_mul_.push_back({(int32_t)table_records.size(), total_index_});
      total_index_ *= table_records.size();
      records_.push_back(table_records);
    } else {
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC TablesJoinOperator::next()
{
  if (current_index_ >= total_index_) {
    return RC::RECORD_EOF;
  }
  current_records_.clear();
  for (int32_t table_index = 0; table_index < (int32_t) records_.size(); table_index++)
  {
    auto current_row = records_[table_index];
    auto new_record = current_row[get_row_index_(table_index)];
    current_records_.push_back(new_record);
  }
  current_index_++;
  return RC::SUCCESS;
}

RC TablesJoinOperator::close()
{
  RC rc = RC::SUCCESS;
  for (auto scan_oper : scan_opers_) {
    if ((rc = scan_oper->close()) != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}

Tuple * TablesJoinOperator::current_tuple()
{
  tuple_.set_records(&current_records_);
  return &tuple_;
}

int32_t TablesJoinOperator::get_row_index_(int32_t table_num) {
  return (current_index_ / index_mul_[table_num].second) % index_mul_[table_num].first;
}