//
// Created by Administrator on 2022/10/15.
//

#ifndef MINIDB_UPDATE_OPERATOR_H
#define MINIDB_UPDATE_OPERATOR_H

#endif  // MINIDB_UPDATE_OPERATOR_H

#pragma once


#include "operator.h"
#include "../expr/tuple.h"
#include "../../rc.h"

class UpdateStmt;

class UpdateOperator : public Operator
{
public:
  UpdateOperator(UpdateStmt *update_stmt)
      : update_stmt_(update_stmt)
  {}

  virtual ~UpdateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override {
    return nullptr;
  }
  //int tuple_cell_num() const override
  //RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override
private:
  UpdateStmt *update_stmt_ = nullptr;
};
