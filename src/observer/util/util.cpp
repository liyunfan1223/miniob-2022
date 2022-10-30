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
// Created by wangyunlai on 2022/9/28
//

#include "util/util.h"


std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

int get_exp_element(const char * expression, int st, int ed, std::vector<ExpElement *> & vec)
{
  static AggType agg_type = AGG_NONE;

  if (ed < st) return -1;
  ExpElement exp_element;
  exp_element.type = VALUE_ET;
  char * str_element = (char *)malloc((ed - st + 2) * sizeof(char));
  int len = ed - st + 1;
  str_element[len] = '\0';
  memcpy(str_element, expression + st, len);

  std::string target(str_element);

  int dot_pos = -1;
  for (int i = st; i <= ed; i++) {
    if ( (expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z') || expression[i] == '_') {
      exp_element.type = ATTR_ET;
    }
    if (expression[i] == '.') {
      dot_pos = i - st;
    }
  }
  if (exp_element.type == VALUE_ET) {
    if (dot_pos != -1) {
      float val = atof(str_element);
      exp_element.value = new Value();
      exp_element.value->type = FLOATS;
      exp_element.value->data = new float(val);
    } else {
      int val = atoi(str_element);
      exp_element.value = new Value();
      exp_element.value->type = INTS;
      exp_element.value->data = new int(val);
    }
  } else {
    exp_element.rel_attr = new RelAttr();
    if (strcmp(target.c_str(), "avg") == 0 || strcmp(target.c_str(), "AVG") == 0) {
      agg_type = AGG_AVG;
      return -1;
    } else if (strcmp(target.c_str(), "max") == 0 || strcmp(target.c_str(), "MAX") == 0) {
      agg_type = AGG_MAX;
      return -1;
    } else if (strcmp(target.c_str(), "min") == 0 || strcmp(target.c_str(), "MIN") == 0) {
      agg_type = AGG_MIN;
      return -1;
    } else if (strcmp(target.c_str(), "sum") == 0 || strcmp(target.c_str(), "SUM") == 0) {
      agg_type = AGG_SUM;
      return -1;
    } else if (strcmp(target.c_str(), "count") == 0 || strcmp(target.c_str(), "COUNT") == 0) {
      agg_type = AGG_COUNT;
      return -1;
    } else {
      if (dot_pos == -1) {
        exp_element.rel_attr->relation_name = nullptr;
        exp_element.rel_attr->attribute_name = strdup(str_element);
        exp_element.rel_attr->aggType = agg_type;
        if (agg_type != AGG_NONE) {
          exp_element.rel_attr->is_agg = 1;
          agg_type = AGG_NONE;
        }
      } else {
        exp_element.rel_attr->relation_name = strdup((char *)target.substr(0, dot_pos).c_str());
        exp_element.rel_attr->attribute_name = strdup((char *)target.substr(dot_pos + 1, len - dot_pos).c_str());
        exp_element.rel_attr->aggType = agg_type;
        if (agg_type != AGG_NONE) {
          exp_element.rel_attr->is_agg = 1;
          agg_type = AGG_NONE;
        }
      }
    }
  }

  vec.push_back(new ExpElement(exp_element));
  return 0;
}

std::vector<ExpElement *> parse_expression(const char * expression)
{
  int len = strlen(expression);
  int last_idx = 0;
  std::vector<ExpElement *> vec;
//  int last_extend_minus = -1;
  std::vector<int> last_extend_minus;
  int brace_level = 0;
  for (int i = 0; i < len; i++) {
    switch (expression[i]) {
      case '(': {
        get_exp_element(expression, last_idx, i - 1, vec);
        ExpElement exp_element;
        exp_element.type=LBRACE_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
        brace_level++;
      } break;
      case ')': {
        get_exp_element(expression, last_idx, i - 1, vec);
        ExpElement exp_element;
        exp_element.type = RBRACE_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
        if (last_extend_minus.size() && brace_level == last_extend_minus.back()) {
          ExpElement exp_element2;
          exp_element2.type = RBRACE_ET;
          vec.push_back(new ExpElement (exp_element2));
          last_extend_minus.pop_back();
        }
        brace_level--;
      } break;
      case '+': {
        get_exp_element(expression, last_idx, i - 1, vec);

        if (last_extend_minus.size() && brace_level == last_extend_minus.back()) {
          ExpElement exp_element2;
          exp_element2.type = RBRACE_ET;
          vec.push_back(new ExpElement (exp_element2));
          last_extend_minus.pop_back();
        }

        ExpElement exp_element;
        exp_element.type = PLUS_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
      } break;
      case '-': {
        if (i == 0 || (get_exp_element(expression, last_idx, i - 1, vec) == -1 && expression[i - 1] != ')')) {
          last_extend_minus.push_back(brace_level);
          ExpElement exp_element;
          exp_element.type = LBRACE_ET;
          vec.push_back(new ExpElement (exp_element));

          ExpElement exp_element2;
          exp_element2.type = VALUE_ET;
          Value *value = new Value;
          value->type = INTS;
          value->data = new int(0);
          exp_element2.value = value;
          vec.push_back(new ExpElement (exp_element2));
        } else if (last_extend_minus.size() && brace_level == last_extend_minus.back()) {
          ExpElement exp_element2;
          exp_element2.type = RBRACE_ET;
          vec.push_back(new ExpElement (exp_element2));
          last_extend_minus.pop_back();
        }

        ExpElement exp_element;
        exp_element.type = MINUS_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
      } break;
      case '*': {
        get_exp_element(expression, last_idx, i - 1, vec);
        if (last_extend_minus.size() && brace_level == last_extend_minus.back()) {
          ExpElement exp_element2;
          exp_element2.type = RBRACE_ET;
          vec.push_back(new ExpElement (exp_element2));
          last_extend_minus.pop_back();
        }
        ExpElement exp_element;
        exp_element.type = MUL_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
      } break;
      case '/': {
        get_exp_element(expression, last_idx, i - 1, vec);
        if (last_extend_minus.size() && brace_level == last_extend_minus.back()) {
          ExpElement exp_element2;
          exp_element2.type = RBRACE_ET;
          vec.push_back(new ExpElement (exp_element2));
          last_extend_minus.pop_back();
        }
        ExpElement exp_element;
        exp_element.type = DIVIDE_ET;
        vec.push_back(new ExpElement (exp_element));
        last_idx = i + 1;
      }
      default: {}
    }
  }
  get_exp_element(expression, last_idx, len - 1, vec);
  return vec;
}

void get_tuple_cell_for_exp(std::vector<ExpElement *> & vec, Tuple & tuple, TupleCell & ret)
{
  // 中缀表达式 to 前缀表达式
  std::vector<ExpElement *> stack;
  std::vector<ExpElement *> res;
  for (auto it = vec.rbegin(); it != vec.rend(); it++) {
    auto item = *it;
    switch (item->type) {
      case VALUE_ET:
      case ATTR_ET: {
        res.push_back(item);
      } break;
      case RBRACE_ET: {
        stack.push_back(item);
      } break;
      case LBRACE_ET: {
        while(stack.back()->type != RBRACE_ET) {
          res.push_back(stack.back());
          stack.pop_back();
        }
        stack.pop_back();
      } break;
      case PLUS_ET:
      case MINUS_ET: {
        while(stack.size() && (stack.back()->type == DIVIDE_ET || stack.back()->type == MUL_ET) ) {
          res.push_back(stack.back());
          stack.pop_back();
        }
        stack.push_back(item);
      } break;
      case DIVIDE_ET:
      case MUL_ET: {
        stack.push_back(item);
      } break;
    }
  }
  while(stack.size()) {
    res.push_back(stack.back());
    stack.pop_back();
  }

  std::vector<float> f_vec;
  for (auto item : res) {
    switch (item->type) {
      case VALUE_ET: {
        if (item->value->type == INTS) {
          f_vec.push_back(*(int *)item->value->data);
        } else if (item->value->type == FLOATS) {
          f_vec.push_back(*(float *)item->value->data);
        }
      } break;
      case ATTR_ET: {
        TupleCell tmp_cell;
        tuple.find_cell_agg(item->rel_attr->relation_name, item->rel_attr->attribute_name, tmp_cell, item->rel_attr->aggType);
        if (tmp_cell.attr_type() == INTS) {
          f_vec.push_back(*(int *)tmp_cell.data());
        } else if (tmp_cell.attr_type() == FLOATS) {
          f_vec.push_back(*(float *)tmp_cell.data());
        }
      } break;
      case PLUS_ET: {
        auto item1 = f_vec.back();
        f_vec.pop_back();
        auto item2 = f_vec.back();
        f_vec.pop_back();
        f_vec.push_back(item1 + item2);
      } break;
      case MINUS_ET: {
        auto item1 = f_vec.back();
        f_vec.pop_back();
        auto item2 = f_vec.back();
        f_vec.pop_back();
        f_vec.push_back(item1 - item2);
      } break;
      case DIVIDE_ET: {
        auto item1 = f_vec.back();
        f_vec.pop_back();
        auto item2 = f_vec.back();
        f_vec.pop_back();
        // 被除数=0 返回 NULL
        if (item2 == 0) {
          ret.set_type(NULL_T);
          return;
        }
        f_vec.push_back(item1 / item2);
      } break;
      case MUL_ET: {
        auto item1 = f_vec.back();
        f_vec.pop_back();
        auto item2 = f_vec.back();
        f_vec.pop_back();
        f_vec.push_back(item1 * item2);
      } break;
      default:
        break;
    }
  }
  assert(f_vec.size() == 1);
  ret.set_type(FLOATS);
  ret.set_data((char *)(new float(f_vec[0])));
}
