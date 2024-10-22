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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"

#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<Value> values, std::vector<const char *> field_names)
  : table_ (table), filter_stmt_(filter_stmt), values_(values), field_names_(field_names)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const Updates &update_sql, Stmt *&stmt)
{
  // TODO
  stmt = nullptr;
  const char *table_name = update_sql.relation_name;
  std::vector<const char *> field_names;
  std::vector<Value> values;
  Table *table = db->find_table(table_name);

  for (size_t i = 0; i < update_sql.attr_num; i++) {
    char *field_name = update_sql.attribute_name[i];

    if (nullptr == db || nullptr == table_name || nullptr == field_name) {
      LOG_WARN("invalid argument. db=%p, table_name=%p,field_name = %p", db, table_name, field_name);
      return RC::INVALID_ARGUMENT;
    }

    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    const FieldMeta *field = table->table_meta().field(field_name);
    if (nullptr == field) {
      LOG_WARN("no such field. db=%s, table_name=%s,field_name=%s ", db->name(), table_name, field_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    field_names.push_back(field_name);
  }
  for (size_t i = 0; i < update_sql.value_num; i++) {
    const Value value = update_sql.value[i];
    values.push_back(value);
//    const AttrType field_type = field->type();
//    const AttrType value_type = value.type;
    //  if (field_type != value_type) {
    //    LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
    //        table_name, field->name(), field_type, value_type);
    //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    //  }

  }
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, nullptr,
      update_sql.conditions, update_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // 检查过所有
  stmt = new UpdateStmt(table, filter_stmt, values, field_names);
  return RC::SUCCESS;


}
