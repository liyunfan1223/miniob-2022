
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  size_t record_length;
  InsertRecord records[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  CompOp comps[MAX_NUM];
  size_t comp_num;
  char id[MAX_NUM];
  OrderType order_type;
  AggType agg_type;
  size_t attr_length;
  Selects sub_selects[MAX_NUM];
  size_t sub_select_num;
  Value set_values[MAX_NUM];
  size_t set_num;
  Conjunction conj[MAX_NUM];
  size_t conj_num;
  char * rel[MAX_NUM];
  char * rel_alias[MAX_NUM];
  size_t rel_num;
  char * alias_stack[MAX_NUM];
  size_t alias_stack_pt;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.record_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
        INNER
        JOIN
        MAX
        MIN
        COUNT
        AVG
        SUM
        GROUP
        BY
        ORDER
        ASC
        NOT
        LIKE
        TEXT_T
        NULL_TOKEN
        NULLABLE
        HAVING
        IN
        EXISTS
        IS
        OR
        AS

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> DATE_STR
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> EXPRESSION
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
	| show_index
    ;

show_index:
    SHOW INDEX FROM ID SEMICOLON {
	CONTEXT->ssql->flag=SCF_SHOW_INDEX;
	show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
    };

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE index_col_ID_list RBRACE SEMICOLON
    {
	CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
	create_index_multi_rel_init(&CONTEXT->ssql->sstr.create_index, $3, $5);
    }
    ;
index_col_ID_list:
    /* empty */
    | index_col_ID index_col_ID_list {

    }
    | COMMA index_col_ID index_col_ID_list {
    }
    ;
index_col_ID:
    ID {
    	create_index_append_attr_name(&CONTEXT->ssql->sstr.create_index, $1);
    }
    ;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
	{
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $4);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
    |ID_get type
	{
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, CONTEXT->attr_length);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
	|ID_get type NOT NULL_TOKEN
    	{
    		AttrInfo attribute;
    		attr_info_init(&attribute, CONTEXT->id, $2, CONTEXT->attr_length);
    		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
    		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
    		CONTEXT->value_length++;
    	}
    |ID_get type NULLABLE
	{
		AttrInfo attribute;
		nullable_attr_info_init(&attribute, CONTEXT->id, $2, CONTEXT->attr_length);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; CONTEXT->attr_length = 4; }
       | STRING_T { $$=CHARS; CONTEXT->attr_length = 40; }
       | FLOAT_T { $$=FLOATS; CONTEXT->attr_length = 4; }
       | DATE_T { $$=DATES; CONTEXT->attr_length = 4; }
       | TEXT_T { $$=TEXTS; CONTEXT->attr_length = 4096; }
       ;

ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES record_list SEMICOLON
    {
      CONTEXT->ssql->flag=SCF_INSERT;//"insert";
      inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->records, CONTEXT->record_length);
      //临时变量清零
      CONTEXT->record_length = 0;
    }
record_list:
    /* empty */
    | COMMA record record_list {
    }
    | record record_list {
    }
    ;
record:
    LBRACE value_list RBRACE {
    	insert_record_init(&CONTEXT->records[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
    	CONTEXT->value_length=0;
    }
    ;
value_list:
    /* empty */
    | COMMA value value_list  {
    }
    | value value_list {
    }
value:
    NUMBER {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
    }
    |FLOAT {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
    }
    |DATE_STR {
    		$1 = substr($1,1,strlen($1)-2);
		value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
    }
    |SSS {
		$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
    }
    |NULL_TOKEN {
    		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
    | LBRACE sub_select RBRACE {
    	// printf("MAKE VALUE FOR SUB_SELECTS\n");
    	value_init_sub_select(&CONTEXT->values[CONTEXT->value_length++], &CONTEXT->sub_selects[CONTEXT->sub_select_num]);
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].attr_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].relation_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].condition_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].group_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].order_num=0;
    	CONTEXT->sub_select_num--;
    }
    | LBRACE set_value_list RBRACE {
	value_init_set(&CONTEXT->values[CONTEXT->value_length++], CONTEXT->set_values, CONTEXT->set_num);
	CONTEXT->set_num = 0;
    }
    ;

set_value_list:
    /* empty */
    | value set_value_list {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
    | COMMA value set_value_list {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
    ;

sub_select:
    sub_select_token sub_select_attr sub_attr_list FROM sub_rel_item sub_rel_list sub_where {
    }
    ;

sub_select_token:
    SELECT {
	CONTEXT->sub_select_num++;
    }
    ;

sub_attr_list:
    /* empty */
    | COMMA sub_select_attr sub_attr_list {
    }
    ;

sub_select_attr:
    STAR {
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    | ID alias_or_not {
        RelAttr attr;
	relation_attr_init(&attr, NULL, $1);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    | ID DOT ID alias_or_not {
        RelAttr attr;
	relation_attr_init(&attr, $1, $3);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    | aggop LBRACE STAR RBRACE alias_or_not {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    | aggop LBRACE ID RBRACE alias_or_not {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, $3, CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    | aggop LBRACE ID DOT ID RBRACE alias_or_not {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, $3, $5, CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
    ;

sub_rel_list:
    /* empty */
    | COMMA sub_rel_item rel_list {

    }
    ;

sub_rel_item:
    ID {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], $1, NULL);
    }
    | ID ID {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], $1, $2);
    }
    | ID AS ID {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], $1, $3);
    }

sub_where:
    /* empty */
    | WHERE sub_condition_list {
	printf("2\n");
    }
    ;

sub_condition_list:
    /* empty */
    | type_conj sub_condition sub_condition_list {

    }
    ;

type_conj:
    /* empty */ {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_FIRST;
    }
    | AND {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_AND;
    }
    | OR {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_OR;
    }

sub_condition:
    ID comOp value
    {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, $1);
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	// printf("CONTEXT->sub_select_num: %d\n", CONTEXT->sub_select_num);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |value comOp value {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |ID comOp ID {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, $1);
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, $3);

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |value comOp ID {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, $3);

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |ID DOT ID comOp value {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, $1, $3);
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |value comOp ID DOT ID {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	RelAttr right_attr;
    	relation_attr_init(&right_attr, $3, $5);

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    |ID DOT ID comOp ID DOT ID {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, $1, $3);
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, $5, $7);
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
    ;

delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET update_set_list where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, $2,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;

update_set_list:
    /* empty */
    | update_set update_set_list {
    }
    | COMMA update_set update_set_list {
    }
    ;

update_set:
    ID EQ value {
        Value *value = &CONTEXT->values[--CONTEXT->value_length];
    	updates_append_attr_and_value(&CONTEXT->ssql->sstr.update, $1, value);
    };

select:				/*  select 语句的语法解析树*/
    SELECT select_attr_or_expression attr_list FROM rel_item rel_list inner_join_list where group order SEMICOLON
    {
	// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
	// selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);
	for (int i = (int)CONTEXT->rel_num - 1; i >= 0; i--) {
	    selects_append_relation_alias(&CONTEXT->ssql->sstr.selection, CONTEXT->rel[i], CONTEXT->rel_alias[i]);
       	}

	selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
	CONTEXT->ssql->flag=SCF_SELECT;//"select";
	// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;
	//临时变量清零
	CONTEXT->condition_length=0;
	CONTEXT->from_length=0;
	CONTEXT->select_length=0;
	CONTEXT->value_length = 0;
    }
	;

attr_list:
    /* empty */
    | COMMA select_attr_or_expression attr_list {
    }
    ;

select_attr_or_expression:
    select_attr {

    }
    | EXPRESSION {
    	RelAttr attr;
    	relation_attr_exp_init(&attr, $1);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }

select_attr:
    STAR {  
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | ID DOT STAR {
    	RelAttr attr;
    	relation_attr_init(&attr, $1, "*");
     	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | ID alias_or_not {
        RelAttr attr;
	relation_attr_alias_init(&attr, NULL, $1, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | ID DOT ID alias_or_not {
        RelAttr attr;
	relation_attr_alias_init(&attr, $1, $3, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | aggop LBRACE STAR RBRACE alias_or_not {
	RelAttr attr;
	relation_attr_aggr_alias_init(&attr, NULL, "*", CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | aggop LBRACE ID RBRACE alias_or_not {
    	RelAttr attr;
    	relation_attr_aggr_alias_init(&attr, NULL, $3, CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | aggop LBRACE ID DOT ID RBRACE alias_or_not {
    	RelAttr attr;
    	relation_attr_aggr_alias_init(&attr, $3, $5, CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    ;
aggop:
    MAX {
	CONTEXT->agg_type = AGG_MAX;
    }
    | MIN {
	CONTEXT->agg_type = AGG_MIN;
    }
    | COUNT {
	CONTEXT->agg_type = AGG_COUNT;
    }
    | AVG {
	CONTEXT->agg_type = AGG_AVG;
    }
    | SUM {
    	CONTEXT->agg_type = AGG_SUM;
    }
    ;

alias_or_not:
    /* empty */ {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = NULL;
    }
    | ID {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = strdup($1);
    }
    | AS ID {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = strdup($2);
    }

inner_join_list:
    /* empty */
    | INNER JOIN ID on inner_join_list {
	selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
    }
    ;

on:
    /* empty */
    | ON condition condition_list {
	// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
    }
    ;

rel_list:
    /* empty */
    | COMMA rel_item rel_list {
    }
    ;

rel_item:
    ID {
	CONTEXT->rel[CONTEXT->rel_num] = strdup($1);
	CONTEXT->rel_alias[CONTEXT->rel_num++] = NULL;
        // selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
    | ID ID {
        CONTEXT->rel[CONTEXT->rel_num] = strdup($1);
        CONTEXT->rel_alias[CONTEXT->rel_num++] = strdup($2);
      	// selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
    | ID AS ID {
        CONTEXT->rel[CONTEXT->rel_num] = strdup($1);
        CONTEXT->rel_alias[CONTEXT->rel_num++] = strdup($3);
	// selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
    ;

where:
    /* empty */ 
    | WHERE condition_list {

    }
    ;
condition_list:
    /* empty */
    | type_conj condition condition_list {
    }
    ;
condition:
    ID comOp value_or_expression
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, $1);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	printf("WHERE FINISHED %d\n", CONTEXT->condition_length);
    }
    |value_or_expression comOp value_or_expression
    {
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |ID comOp ID
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, $1);
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, $3);

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |value_or_expression comOp ID
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, $3);

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |ID DOT ID comOp value_or_expression
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, $1, $3);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |value_or_expression comOp ID DOT ID
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	RelAttr right_attr;
	relation_attr_init(&right_attr, $3, $5);

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |ID DOT ID comOp ID DOT ID
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, $1, $3);
	RelAttr right_attr;
	relation_attr_init(&right_attr, $5, $7);
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    ;
    | EXISTS value {
	Value left_value;
	value_init_integer(&left_value, 0);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | NOT EXISTS value {
    	Value left_value;
        value_init_integer(&left_value, 0);
    	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

    	Condition condition;
    	condition_conj_init(&condition, NOT_EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }

value_or_expression:
    value {

    }
    | EXPRESSION {
	// $1 = substr($1,1,strlen($1)-2);
	value_init_expression(&CONTEXT->values[CONTEXT->value_length++], $1);
    }
    ;

group:
    /* empty */
    | GROUP BY group_attr_list {
    }
    | GROUP BY group_attr_list HAVING hc_list {

    }
    ;
group_attr_list:
    /* empty */
    | COMMA group_attr group_attr_list {
    }
    | group_attr group_attr_list {
    }
    ;
group_attr:
    ID {
        GroupAttr group_attr;
	group_attr_init(&group_attr, NULL, $1);
	group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
    | ID DOT ID {
        GroupAttr group_attr;
        group_attr_init(&group_attr, $1, $3);
        group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
    ;

hc_list:
    /* empty */
    | having_condition hc_list {

    }
    | AND having_condition hc_list {
    }
    ;

having_condition:
    aggop LBRACE ID RBRACE comOp value {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, $3, CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
    | aggop LBRACE ID DOT ID RBRACE comOp value {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, $3, $5, CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
    | aggop LBRACE STAR RBRACE comOp value {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, "*", CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
    | ID comOp value {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, $1);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
    | ID DOT ID comOp value {
        RelAttr left_attr;
        relation_attr_init(&left_attr, $1, $3);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }


order:
    /* empty */
    | ORDER BY order_attr_list {
    }
    ;
order_attr_list:
    /* empty */
    | COMMA order_attr order_attr_list {
    }
    | order_attr order_attr_list {
    }
    ;
order_attr:
    ID order_type {
        OrderAttr order_attr;
	order_attr_init(&order_attr, NULL, $1, CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
    | ID DOT ID order_type {
        OrderAttr order_attr;
	order_attr_init(&order_attr, $1, $3, CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
    ;
order_type:
    ASC {
    	CONTEXT->order_type = OrderAsc;
    }
    | DESC {
    	CONTEXT->order_type = OrderDesc;
    }
    | /* empty */ {
    	CONTEXT->order_type = OrderAsc;
    }
comOp:
    EQ { CONTEXT->comps[CONTEXT->comp_num++] = EQUAL_TO; }
    | LT { CONTEXT->comps[CONTEXT->comp_num++] = LESS_THAN; }
    | GT { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_THAN; }
    | LE { CONTEXT->comps[CONTEXT->comp_num++] = LESS_EQUAL; }
    | GE { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_EQUAL; }
    | NE { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EQUAL; }
    | LIKE { CONTEXT->comps[CONTEXT->comp_num++] = LIKE_TO; }
    | NOT LIKE { CONTEXT->comps[CONTEXT->comp_num++] = NOT_LIKE_TO; }
    | IN { CONTEXT->comps[CONTEXT->comp_num++] = IN_OP; }
    | NOT IN { CONTEXT->comps[CONTEXT->comp_num++] = NOT_IN_OP; }
    | EXISTS { CONTEXT->comps[CONTEXT->comp_num++] = EXISTS_OP; }
    | NOT EXISTS { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EXISTS_OP; }
    | IS { CONTEXT->comps[CONTEXT->comp_num++] = IS_OP; }
    | IS NOT { CONTEXT->comps[CONTEXT->comp_num++] = IS_NOT_OP; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
//	for (int i = 0; i < MAX_NUM; i++) {
//	    context.rel[i] = (char *)malloc(MAX_NUM * sizeof(char));
//	    context.rel_alias[i] = (char *)malloc(MAX_NUM * sizeof(char));
//	}
	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}