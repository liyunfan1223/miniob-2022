//
// Created by MorphLing on 2022/10/29.
//

#pragma once

#include "sql/operator/operator.h"
#include "sql/expr/tuple.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/tables_join_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/order_operator.h"
#include "sql/operator/group_operator.h"
#include "sql/operator/subquery_predicate_operator.h"
#include "storage/common/db.h"
#include "util/util.h"

class ExpProjectOperator: public Operator {

public:
  ExpProjectOperator(){}
  ExpProjectOperator(size_t attr_num, RelAttr * attributes, std::vector<Table *> tables, Db * db, std::unordered_map<std::string, char *> & rel_alias):
    attr_num_(attr_num), attributes_(attributes)
  {
    for (size_t i = 0; i < attr_num; i++) {
      auto &attr = attributes[i];
      if (attr.is_exp) {
        add_exp_projection(nullptr, attr.expression, AGG_NONE);
        continue;
      }

      // select *
      if (attr.relation_name == nullptr && 0 == strcmp(attr.attribute_name, "*")) {
        if (attr.aggType == AGG_COUNT) {
          add_projection(nullptr, "*", AGG_COUNT, nullptr, attr.alias_name, attr.func_type, attr.round_func_param, attr.date_func_param);
        } else if (attr.aggType == AGG_NONE) {
          for (int j = (int)tables.size() - 1; j >= 0; j--) {
            auto &table = tables[j];
            const TableMeta &table_meta = table->table_meta();
            const int field_num = table_meta.field_num();
            for (int k = table_meta.sys_field_num(); k < field_num; k++) {
              add_projection(table, table_meta.field(k), attr.aggType, rel_alias[std::string(table->name())], nullptr, attr.func_type, attr.round_func_param, attr.date_func_param);
            }
          }
        }
      } else {
        Table *table = attr.relation_name == nullptr ? tables[0] : db->find_table(attr.relation_name);
        if (table == nullptr) {
          for (auto &item : rel_alias) {
            if (item.second != nullptr && 0 == strcmp(attr.relation_name, item.second)) {
              table = db->find_table(item.first.c_str());
              break;
            }
          }
        }
        // select id.*
        if (0 == strcmp(attr.attribute_name, "*")) {
          const TableMeta &table_meta = table->table_meta();
          const int field_num = table_meta.field_num();
          for (int j = table_meta.sys_field_num(); j < field_num; j++) {
            add_projection(table, table_meta.field(j), attr.aggType, rel_alias[std::string(table->name())], nullptr, attr.func_type, attr.round_func_param, attr.date_func_param);
          }
        } else {
          // select id.id
          add_projection(table,
              table->table_meta().field(attr.attribute_name),
              attr.aggType,
              rel_alias[std::string(table->name())],
              attr.alias_name,
              attr.func_type,
              attr.round_func_param, attr.date_func_param);
        }
      }
    }
  }
  virtual ~ExpProjectOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;
private:
  void add_projection(const Table *table, const FieldMeta *field_meta, AggType agg_type, char * p_alias, char * p_total_alias, FuncType func_type, int round_func_param,
                      char * date_func_param)
  {
    // 对单表来说，展示的(alias) 字段总是字段名称，
    // 对多表查询来说，展示的alias 需要带表名字
    TupleCellSpec *spec = new TupleCellSpec(new FieldExpr(table, field_meta));
    spec->set_table_alias(table->name());
    spec->set_alias(field_meta->name());
    spec->agg_type = agg_type;
    spec->attr_type = field_meta->type();
    spec->p_rel_alias = p_alias;
    spec->p_total_alias = p_total_alias;
    spec->func_type = func_type;
    spec->round_func_param = round_func_param;
    spec->date_func_param = date_func_param;
    tuple_.speces_.push_back(spec);
  }
  void add_projection(const char *table_name, const char *field_meta_name, AggType agg_type, char * p_alias, char * p_total_alias, FuncType func_type, int round_func_param,
      char * date_func_param)
  {
    // 对单表来说，展示的(alias) 字段总是字段名称，
    // 对多表查询来说，展示的alias 需要带表名字
    TupleCellSpec *spec = new TupleCellSpec();
    spec->set_table_alias(table_name);
    spec->set_alias(field_meta_name);
    spec->agg_type = agg_type;
    spec->p_rel_alias = p_alias;
    spec->p_total_alias = p_total_alias;
    spec->func_type = func_type;
    spec->round_func_param = round_func_param;
    spec->date_func_param = date_func_param;
    tuple_.speces_.push_back(spec);
  }
  void add_exp_projection(const char *table_name, const char *field_meta_name, AggType agg_type)
  {
    // 对单表来说，展示的(alias) 字段总是字段名称，
    // 对多表查询来说，展示的alias 需要带表名字
    TupleCellSpec *spec = new TupleCellSpec();
    spec->set_table_alias(table_name);
    spec->set_alias(field_meta_name);
    spec->agg_type = agg_type;
    spec->is_exp = 1;
    tuple_.speces_.push_back(spec);
  }
  ExpProjectTuple tuple_;
  size_t attr_num_;
  RelAttr * attributes_;
//  std::vector<TupleCellSpec *> speces_;
};
