//
// Created by Clouds on 2022/9/24.
//

#pragma once

#include "sql/operator/operator.h"
#include "sql/operator/table_scan_operator.h"

class FilterStmt;

class TablesJoinOperator: public Operator
{
public:
  TablesJoinOperator(std::vector<TableScanOperator*> scan_opers, FilterStmt *filter_stmt)
  :scan_opers_(scan_opers), filter_stmt_(filter_stmt)
  {
    field_lengths_.push_back(0);
    current_index_ = 0;
    field_length_ = 0;
    total_index_ = 1;
  }

  virtual ~TablesJoinOperator() {
      for (auto scan_oper : scan_opers_) {
        delete scan_oper;
      }
      scan_opers_.clear();

      for (auto vec_record: records_) {
        for (auto record: vec_record) {
          delete record;
        }
        vec_record.clear();
      }
      records_.clear();
  };

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
private:
  RC cartesian_product_dfs_(int table_index);
  bool do_predicate_( std::vector<Record *> &records , int record_length);
  int32_t get_field_index_(FieldExpr * fieldExpr);
  std::vector<TableScanOperator*> scan_opers_;
  int32_t current_index_;
  int32_t total_index_;
  int32_t field_length_;
  std::vector<int32_t> field_lengths_;
  std::vector<std::pair<int32_t, int32_t>> index_mul_;
  std::vector<std::vector<Record *>> records_;
  std::vector<std::vector<Record *>> product_records_;
  std::vector<Record *> current_records_;
  JoinTuple tuple_;
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};
