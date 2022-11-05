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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"
#include<string>
#include<string>
#include<cstring>
#include<algorithm>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name,  std::vector<FieldMeta *> fields, size_t is_unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  unique_=is_unique;
  for (int i=0;i<fields.size();i++) {
    field_.push_back(fields[i]->name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  //列间用逗号分隔
  std::string f="";
  for (int i=0;i<field_.size();i++){
    if (i!=field_.size()-1) {
      f = f + field_[i] + ",";
    }else{
      f = f + field_[i];
    }
  }

  json_value[FIELD_FIELD_NAME] = f;
  json_value[FIELD_UNIQUE] = std::to_string(unique_);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  std::string f=field_value.asCString();
  std::size_t previous = 0;
  std::size_t current = f.find(","); //列间是用逗号分隔的
  std::vector<std::string> elems;
  while (current != std::string::npos) {
    if (current > previous) {
      elems.push_back(f.substr(previous, current - previous));
    }
    previous = current + 1;
    current = f.find(",", previous);
  }
  if (previous != f.size()) {
    elems.push_back(f.substr(previous));
  }
  std::vector<FieldMeta *>  fields;
  for (auto i=0;i<elems.size();i++){
    const FieldMeta *field = table.field(elems[i].c_str());
    fields.push_back((FieldMeta *)field);
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  return     index.init(name_value.asCString(), fields,std::stoi(unique.asCString()));

}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const std::vector<std::string> IndexMeta::field() const
{
//  std::string s="";
//  for(int i=0;i<attr_num;i++){
//    s+=field_[i];
//    if(i==attr_num-1) break;
//    s+= ",";
//  }
  return field_;
}
size_t IndexMeta::is_unique() const{
  return unique_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" ;
  for(int i=0;i<attr_num;i++){
    os << field_[i];
    if(i==attr_num-1) break;
    os << ",";
  }
}