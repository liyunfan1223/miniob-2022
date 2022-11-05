修改:
- sql/parser/lex_sql.l, sql/parser/yacc_sql.y 增加 ORDER BY ID [ASC/DESC] 解析逻辑
- sql/parser/parse_defs.h Selects 结构体增加 Order 相关属性 (order_num, order_attributes)
- sql/operator/order_operator.cpp, sql/operator/order_operator.h 排序算子
- sql/executor/execute_stage.cpp do_select 函数重构: 合并单表和多表查询
- sql/stmt/select_stmp.cpp create 函数: 修改表访问顺序（改为从后往前），解决 SELECT * 顺序问题

MySQL中使用Order by排序 遇到null值列的排序情况 https://blog.csdn.net/qq_43072106/article/details/122349629