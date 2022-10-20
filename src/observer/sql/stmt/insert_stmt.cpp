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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include <cmath>

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

bool InsertStmt::check_date(int val)
{
  int y = val / 10000;
  int m = val % 10000 / 100;
  int d = val % 100;
  if (y < 1000 || y > 9999) return 0;
  if (m < 1 || m > 12) return 0;
  int mx_day; // mx_day记录当月最大天数
  if (m == 2) {
    if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) mx_day = 29; // 闰年
    else mx_day = 28;
  } else if (m <= 7) {
    if (m % 2 == 1) mx_day = 31;
    else mx_day = 30;
  } else if (m % 2 == 1) mx_day = 30;
  else mx_day = 31;
  if (d > mx_day) return 0;
  return 1;
}

RC InsertStmt::create(Db *db, Inserts &inserts, Stmt *&stmt)//change the definition of Inserts into non-const
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.records[0].value_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", 
             db, table_name, inserts.records[0].value_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  Value *values = inserts.records[0].values; //change the const type into non-const and change the value
  int value_num = inserts.records[0].value_num;
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    const AttrType field_type = field_meta->type();
    const AttrType value_type = values[i].type;
    if (field_type != value_type) { // TODO try to convert the value type to field type
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
               table_name, field_meta->name(), field_type, value_type);
      //here do the typecast
      switch(field_type){
        case INTS: {
          int old_value_type=values[i].type;
          values[i].type = INTS;
          if (old_value_type == FLOATS){
            int temp = (int)(*(float *)values[i].data + 0.5);
            *(int *)values[i].data = temp;
          } else if (value_type == CHARS) {  //字符串前缀是数字，或者字符串无数字为输出0的情况，atoi都可以实现。
            int temp = atoi((char *)values[i].data);
            *(int *)values[i].data = temp;
          } else {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        }
        case FLOATS:{
          int old_value_type=values[i].type;
          values[i].type = FLOATS;
          if (old_value_type == INTS) {
            float temp = (float) *(int *)values[i].data;
            *(float *)values[i].data = temp;
          } else if (value_type == CHARS) {  //字符串前缀是数字，或者字符串无数字为输出0的情况，atoi都可以实现。
            float temp = atof((char *)values[i].data);
            *(float *)values[i].data = temp;
          } else {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        }
        case CHARS:{//不带符号
          int old_value_type=values[i].type;
          values[i].type = CHARS;
          if (old_value_type == INTS) {
//            itoa(*(int *)values[i].data, (char *)values[i].data, 10);
            sprintf((char *)values[i].data,"%d",abs(*(int *)values[i].data));
          } else if (value_type == FLOATS) {
            sprintf((char *)values[i].data,"%g",fabs(*(float *)values[i].data));//%f会多小数位
//            ftoa(*(float *)values[i].data, (char *)values[i].data, 10);
          } else {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        }
      }
//      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    } else if (value_type == DATES) {
      int val = *(int *)values[i].data;
      if (!check_date(val)) {
        LOG_WARN("date type invalid. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::GENERIC_ERROR;
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
