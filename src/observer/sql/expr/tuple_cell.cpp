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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
  case INTS: {
    os << *(int *)data_;
  } break;
  case FLOATS: {
    float v = *(float *)data_;
    os << double2string(v);
  } break;
  case CHARS: {
    for (int i = 0; i < length_; i++) {
      if (data_[i] == '\0') {
        break;
      }
      os << data_[i];
    }
  } break;
  case DATES: {
    int val = *(int *)data_;
    int y, m, d;
    y = val / 10000;
    m = val % 10000 / 100;
    d = val % 100;
    char * output = (char *)malloc(sizeof(char) * 20);
    sprintf(output, "%04d-%02d-%02d", y, m, d);
    os << output;
  } break;
  case NULL_T: {
    os << "NULL";
  } break;
  default: {
    LOG_WARN("unsupported attr type: %d", attr_type_);
  } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
    case INTS: return compare_int(this->data_, other.data_);
    case FLOATS: return compare_float(this->data_, other.data_);
    case CHARS: return compare_string(this->data_, this->length_, other.data_, other.length_);
    case DATES: return compare_int(this->data_, other.data_);
    case NULL_T: return 0;
    default: {
      LOG_WARN("unsupported type: %d", this->attr_type_);
    }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) { //this是表格定义的
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  }else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) { //this是表格定义的
    float this_data = (float) *(int *)data_;
    float other_data = atof((char *)other.data_);
    return compare_float(&this_data, &other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = atof((char *)other.data_);
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {//more cases
    float this_data = atof((char *)data_);
    float other_data = (float) *(int *)other.data_;
    return compare_float(&this_data, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = atof((char *)data_);
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ != NULL_T && other.attr_type_ == NULL_T) {
    return 1;
  } else if (this->attr_type_ == NULL_T && other.attr_type_ != NULL_T) {
    return -1;
  }
  LOG_WARN("not supported");
  return -1; // TODO return rc?
}

int TupleCell::not_equal(const TupleCell &other) const
{
  if (this->attr_type_ == NULL_T || other.attr_type() == NULL_T) {
    return 0;
  }
  return this->compare(other) != 0;
}

int TupleCell::satisfy_in(const TupleCell &other) const
{
  if (this->attr_type_ == NULL_T || other.attr_type() == NULL_T) {
    return 0;
  }
  return this->compare(other) == 0;
}

int TupleCell::satisfy_not_in(const TupleCell &other) const
{
  if (this->attr_type_ == NULL_T || other.attr_type() == NULL_T) {
    return 0;
  }
  return this->compare(other) != 0;
}

bool TupleCell::is_match(const char * str, const char * pattern, size_t pattern_length)
{
  size_t str_length = strlen(str);
  bool match_dp[str_length + 1][pattern_length + 1];
  memset(match_dp, 0, sizeof(match_dp));
  match_dp[0][0] = 1;
  for (size_t i = 0; i <= str_length; i++) {
    for (size_t j = 1; j <= pattern_length; j++) {
      switch (pattern[j - 1]) {
        case '%': {
          for (size_t k = 0; k <= i; k++) {
            if (match_dp[k][j - 1] == 1) {
              match_dp[i][j] = 1;
            }
          }
        } break;
        case '_': {
          if (i >= 1) {
            match_dp[i][j] = match_dp[i - 1][j - 1];
          }
        } break;
        default: {
          if (i >= 1 && pattern[j - 1] == str[i - 1]) {
            match_dp[i][j] = match_dp[i - 1][j - 1];
          }
        }
      }
    }
  }
  return match_dp[str_length][pattern_length];
}

int TupleCell::condition_satisfy(CompOp comp, const TupleCell & other) const
{
  const int compare = this->compare(other);
  int filter_result = 0;
  switch (comp) {
    case EQUAL_TO: {
      if (other.is_set) {
        throw 0;
      }
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = (0 == compare);
      }
    } break;
    case LESS_EQUAL: {
      if (other.is_set) {
        throw 0;
      }if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = (compare <= 0);
      }
    } break;
    case NOT_EQUAL: {
      if (other.is_set) {
        throw 0;
      }
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = this->not_equal(other);
      }
    } break;
    case LESS_THAN: {
      if (other.is_set) {
        throw 0;
      }
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = (compare < 0);
      }
    } break;
    case GREAT_EQUAL: {
      if (other.is_set) {
        throw 0;
      }
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = (compare >= 0);
      }
    } break;
    case GREAT_THAN: {
      if (other.is_set) {
        throw 0;
      }
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = (compare > 0);
      }
    } break;
    case LIKE_TO: {
      assert(this->attr_type() == other.attr_type() && this->attr_type() == CHARS);
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = is_match(this->data(), other.data(), other.length());
      }
    } break;
    case NOT_LIKE_TO: {
      assert(this->attr_type() == other.attr_type() && this->attr_type() == CHARS);
      if (other.attr_type() == NULL_T || this->attr_type() == NULL_T) {
        filter_result = 0;
      } else {
        filter_result = !is_match(this->data(), other.data(), other.length());
      }
    } break;
    case IN_OP: {
      if (other.is_set) {
        for (auto &tupleCell : other.set_cells) {
          if (this->satisfy_in(*tupleCell)) {
            filter_result = 1;
          }
        }
      } else {
        if (this->satisfy_in(other)) {
          filter_result = 1;
        }
      }
    } break;
    case NOT_IN_OP: {
      filter_result = 1;
      if (other.is_set) {
        for (auto & tupleCell : other.set_cells) {
          if (!this->satisfy_not_in(*tupleCell)) {
            filter_result = 0;
          }
        }
      } else {
        if (!this->satisfy_not_in(other)) {
          filter_result = 0;
        }
      }
    } break;
    case IS_OP: {
      assert(other.attr_type() == NULL_T);
      if (this->attr_type() == NULL_T) {
        filter_result = 1;
      }
    } break;
    case IS_NOT_OP: {
      assert(other.attr_type() == NULL_T);
      if (this->attr_type() != NULL_T) {
        filter_result = 1;
      }
    } break;
    default: {
      assert(false); // unimplemented
    }
  }
  return filter_result;
}