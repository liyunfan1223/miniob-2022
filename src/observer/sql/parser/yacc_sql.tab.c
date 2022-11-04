/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
  FuncType func_type;
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
  size_t is_unique;
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



#line 149 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_ON = 35,                        /* ON  */
  YYSYMBOL_LOAD = 36,                      /* LOAD  */
  YYSYMBOL_DATA = 37,                      /* DATA  */
  YYSYMBOL_INFILE = 38,                    /* INFILE  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_INNER = 45,                     /* INNER  */
  YYSYMBOL_JOIN = 46,                      /* JOIN  */
  YYSYMBOL_MAX = 47,                       /* MAX  */
  YYSYMBOL_MIN = 48,                       /* MIN  */
  YYSYMBOL_COUNT = 49,                     /* COUNT  */
  YYSYMBOL_AVG = 50,                       /* AVG  */
  YYSYMBOL_SUM = 51,                       /* SUM  */
  YYSYMBOL_GROUP = 52,                     /* GROUP  */
  YYSYMBOL_BY = 53,                        /* BY  */
  YYSYMBOL_ORDER = 54,                     /* ORDER  */
  YYSYMBOL_ASC = 55,                       /* ASC  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_LIKE = 57,                      /* LIKE  */
  YYSYMBOL_TEXT_T = 58,                    /* TEXT_T  */
  YYSYMBOL_NULL_TOKEN = 59,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 60,                  /* NULLABLE  */
  YYSYMBOL_HAVING = 61,                    /* HAVING  */
  YYSYMBOL_IN = 62,                        /* IN  */
  YYSYMBOL_EXISTS = 63,                    /* EXISTS  */
  YYSYMBOL_IS = 64,                        /* IS  */
  YYSYMBOL_OR = 65,                        /* OR  */
  YYSYMBOL_AS = 66,                        /* AS  */
  YYSYMBOL_LENGTH = 67,                    /* LENGTH  */
  YYSYMBOL_ROUND = 68,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 69,               /* DATE_FORMAT  */
  YYSYMBOL_UNIQUE = 70,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_DATE_STR = 73,                  /* DATE_STR  */
  YYSYMBOL_ID = 74,                        /* ID  */
  YYSYMBOL_PATH = 75,                      /* PATH  */
  YYSYMBOL_SSS = 76,                       /* SSS  */
  YYSYMBOL_EXPRESSION = 77,                /* EXPRESSION  */
  YYSYMBOL_STAR = 78,                      /* STAR  */
  YYSYMBOL_STRING_V = 79,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command = 82,                   /* command  */
  YYSYMBOL_show_index = 83,                /* show_index  */
  YYSYMBOL_exit = 84,                      /* exit  */
  YYSYMBOL_help = 85,                      /* help  */
  YYSYMBOL_sync = 86,                      /* sync  */
  YYSYMBOL_begin = 87,                     /* begin  */
  YYSYMBOL_commit = 88,                    /* commit  */
  YYSYMBOL_rollback = 89,                  /* rollback  */
  YYSYMBOL_drop_table = 90,                /* drop_table  */
  YYSYMBOL_show_tables = 91,               /* show_tables  */
  YYSYMBOL_desc_table = 92,                /* desc_table  */
  YYSYMBOL_create_index = 93,              /* create_index  */
  YYSYMBOL_unique_or_not = 94,             /* unique_or_not  */
  YYSYMBOL_index_col_ID_list = 95,         /* index_col_ID_list  */
  YYSYMBOL_index_col_ID = 96,              /* index_col_ID  */
  YYSYMBOL_drop_index = 97,                /* drop_index  */
  YYSYMBOL_create_table = 98,              /* create_table  */
  YYSYMBOL_attr_def_list = 99,             /* attr_def_list  */
  YYSYMBOL_attr_def = 100,                 /* attr_def  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_ID_get = 103,                   /* ID_get  */
  YYSYMBOL_insert = 104,                   /* insert  */
  YYSYMBOL_record_list = 105,              /* record_list  */
  YYSYMBOL_record = 106,                   /* record  */
  YYSYMBOL_value_list = 107,               /* value_list  */
  YYSYMBOL_value = 108,                    /* value  */
  YYSYMBOL_set_value_list = 109,           /* set_value_list  */
  YYSYMBOL_sub_select = 110,               /* sub_select  */
  YYSYMBOL_sub_select_token = 111,         /* sub_select_token  */
  YYSYMBOL_sub_attr_list = 112,            /* sub_attr_list  */
  YYSYMBOL_sub_select_attr = 113,          /* sub_select_attr  */
  YYSYMBOL_sub_rel_list = 114,             /* sub_rel_list  */
  YYSYMBOL_sub_rel_item = 115,             /* sub_rel_item  */
  YYSYMBOL_sub_where = 116,                /* sub_where  */
  YYSYMBOL_sub_condition_list = 117,       /* sub_condition_list  */
  YYSYMBOL_type_conj = 118,                /* type_conj  */
  YYSYMBOL_sub_condition = 119,            /* sub_condition  */
  YYSYMBOL_delete = 120,                   /* delete  */
  YYSYMBOL_update = 121,                   /* update  */
  YYSYMBOL_update_set_list = 122,          /* update_set_list  */
  YYSYMBOL_update_set = 123,               /* update_set  */
  YYSYMBOL_select_non_table = 124,         /* select_non_table  */
  YYSYMBOL_select = 125,                   /* select  */
  YYSYMBOL_attr_list = 126,                /* attr_list  */
  YYSYMBOL_select_attr_or_expression = 127, /* select_attr_or_expression  */
  YYSYMBOL_select_attr = 128,              /* select_attr  */
  YYSYMBOL_select_nontable_attr_list = 129, /* select_nontable_attr_list  */
  YYSYMBOL_select_nontable_attr = 130,     /* select_nontable_attr  */
  YYSYMBOL_funcop = 131,                   /* funcop  */
  YYSYMBOL_aggop = 132,                    /* aggop  */
  YYSYMBOL_alias_or_not = 133,             /* alias_or_not  */
  YYSYMBOL_inner_join_list = 134,          /* inner_join_list  */
  YYSYMBOL_on = 135,                       /* on  */
  YYSYMBOL_rel_list = 136,                 /* rel_list  */
  YYSYMBOL_rel_item = 137,                 /* rel_item  */
  YYSYMBOL_where = 138,                    /* where  */
  YYSYMBOL_condition_list = 139,           /* condition_list  */
  YYSYMBOL_condition = 140,                /* condition  */
  YYSYMBOL_value_or_expression = 141,      /* value_or_expression  */
  YYSYMBOL_group = 142,                    /* group  */
  YYSYMBOL_group_attr_list = 143,          /* group_attr_list  */
  YYSYMBOL_group_attr = 144,               /* group_attr  */
  YYSYMBOL_hc_list = 145,                  /* hc_list  */
  YYSYMBOL_having_condition = 146,         /* having_condition  */
  YYSYMBOL_order = 147,                    /* order  */
  YYSYMBOL_order_attr_list = 148,          /* order_attr_list  */
  YYSYMBOL_order_attr = 149,               /* order_attr  */
  YYSYMBOL_order_type = 150,               /* order_type  */
  YYSYMBOL_comOp = 151,                    /* comOp  */
  YYSYMBOL_load_data = 152                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   546

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  207
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  438

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   182,   182,   184,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   212,   218,   223,   228,   234,   240,   246,
     252,   258,   264,   271,   279,   282,   285,   287,   290,   294,
     300,   307,   316,   318,   322,   333,   344,   355,   368,   371,
     372,   373,   374,   375,   379,   388,   395,   397,   399,   403,
     408,   410,   412,   415,   418,   421,   425,   429,   432,   442,
     448,   450,   453,   459,   464,   469,   471,   476,   481,   486,
     491,   496,   501,   508,   510,   516,   519,   522,   526,   528,
     533,   535,   541,   544,   547,   552,   562,   570,   580,   589,
     598,   608,   620,   630,   639,   641,   643,   648,   654,   669,
     688,   690,   695,   698,   705,   710,   715,   720,   725,   730,
     735,   740,   745,   750,   760,   772,   774,   779,   785,   799,
     802,   805,   811,   814,   817,   820,   823,   829,   832,   835,
     839,   841,   846,   848,   853,   855,   860,   865,   870,   877,
     879,   883,   885,   889,   898,   907,   918,   928,   938,   950,
     960,   968,   978,   989,   998,  1009,  1012,  1018,  1020,  1022,
    1026,  1028,  1030,  1034,  1039,  1046,  1048,  1051,  1056,  1065,
    1074,  1083,  1092,  1103,  1105,  1108,  1110,  1112,  1116,  1121,
    1128,  1131,  1134,  1138,  1139,  1140,  1141,  1142,  1143,  1144,
    1145,  1146,  1147,  1148,  1149,  1150,  1151,  1155
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "INNER", "JOIN", "MAX", "MIN", "COUNT", "AVG", "SUM", "GROUP", "BY",
  "ORDER", "ASC", "NOT", "LIKE", "TEXT_T", "NULL_TOKEN", "NULLABLE",
  "HAVING", "IN", "EXISTS", "IS", "OR", "AS", "LENGTH", "ROUND",
  "DATE_FORMAT", "UNIQUE", "NUMBER", "FLOAT", "DATE_STR", "ID", "PATH",
  "SSS", "EXPRESSION", "STAR", "STRING_V", "$accept", "commands",
  "command", "show_index", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "unique_or_not", "index_col_ID_list", "index_col_ID", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "record_list", "record", "value_list", "value",
  "set_value_list", "sub_select", "sub_select_token", "sub_attr_list",
  "sub_select_attr", "sub_rel_list", "sub_rel_item", "sub_where",
  "sub_condition_list", "type_conj", "sub_condition", "delete", "update",
  "update_set_list", "update_set", "select_non_table", "select",
  "attr_list", "select_attr_or_expression", "select_attr",
  "select_nontable_attr_list", "select_nontable_attr", "funcop", "aggop",
  "alias_or_not", "inner_join_list", "on", "rel_list", "rel_item", "where",
  "condition_list", "condition", "value_or_expression", "group",
  "group_attr_list", "group_attr", "hc_list", "having_condition", "order",
  "order_attr_list", "order_attr", "order_type", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334
};
#endif

#define YYPACT_NINF (-355)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-152)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -355,   343,  -355,     4,    15,   382,   -60,    90,    92,    94,
     110,    72,   175,   180,   210,   220,   226,   162,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,   147,  -355,
     228,   169,   171,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,    22,  -355,  -355,   229,  -355,   230,   237,   244,   259,
     260,   215,  -355,   190,   199,   240,  -355,  -355,  -355,  -355,
    -355,   238,   262,   201,   277,   278,   -34,   213,  -355,  -355,
     382,   270,   138,   290,   159,   -31,  -355,  -355,   231,   273,
     274,    -5,   242,   239,   286,  -355,  -355,    41,  -355,  -355,
     229,   306,   250,   230,   311,  -355,    -1,  -355,  -355,  -355,
    -355,    20,  -355,    96,    14,   312,   327,    12,    57,   328,
     261,   294,   274,    -5,   305,  -355,   318,   146,   264,  -355,
    -355,   266,    98,   323,  -355,   236,  -355,   236,   178,   325,
     329,   333,    41,   236,   271,    41,   236,    41,   275,    41,
    -355,   185,   334,   341,    12,  -355,  -355,    62,  -355,  -355,
      -5,   236,   356,  -355,   355,   239,   348,  -355,  -355,  -355,
    -355,  -355,    29,   350,   293,  -355,   250,   340,   178,  -355,
    -355,  -355,    99,  -355,   359,   352,  -355,   361,   145,  -355,
     370,  -355,   373,  -355,   236,   374,   185,    12,  -355,  -355,
     330,   236,   376,   387,   332,  -355,  -355,    54,   422,  -355,
    -355,  -355,   331,   318,   401,   335,   349,  -355,     6,  -355,
     323,   363,   274,  -355,   336,  -355,   333,   385,    42,    41,
      41,   236,    41,    41,   185,  -355,  -355,  -355,   236,  -355,
     339,   344,   345,  -355,  -355,  -355,  -355,  -355,  -355,   263,
    -355,  -355,  -355,   378,    84,  -355,   108,   414,  -355,  -355,
    -355,   418,  -355,   362,  -355,   420,     6,  -355,   364,   390,
      41,   359,   365,    18,   426,  -355,  -355,   427,  -355,  -355,
    -355,  -355,    75,   417,   422,  -355,  -355,  -355,  -355,  -355,
    -355,   424,  -355,  -355,  -355,     6,   450,  -355,   419,   402,
     403,  -355,  -355,   124,   440,    41,   393,    41,    41,   422,
     394,   395,   143,   396,  -355,  -355,    62,   340,     7,   421,
     468,   398,  -355,   365,   441,  -355,   458,  -355,  -355,   115,
     459,   460,   452,  -355,  -355,    54,  -355,   407,   454,   428,
       7,     9,  -355,  -355,   323,    19,  -355,    41,  -355,   422,
     422,   409,  -355,     7,   413,   249,  -355,   416,     1,  -355,
       9,  -355,  -355,   196,  -355,   425,   423,  -355,  -355,  -355,
     191,   358,   472,  -355,   249,     9,  -355,   429,  -355,  -355,
    -355,   384,   422,    19,   477,   478,   249,   430,   236,   119,
    -355,  -355,     8,   431,   212,   218,  -355,   432,   433,  -355,
     422,  -355,   125,   479,  -355,   422,  -355,  -355,   467,  -355,
     469,   470,   236,   422,   434,   422,   243,   435,   436,   437,
    -355,   236,   482,   236,   473,  -355,  -355,   483,   485,  -355,
     422,  -355,   438,  -355,  -355,   236,  -355,  -355
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,    22,     4,    18,     0,    35,
       0,     0,     0,   132,   133,   134,   135,   136,   129,   130,
     131,   137,   113,   114,   110,   112,   125,     0,     0,     0,
       0,     0,    26,     0,     0,     0,    27,    28,    29,    25,
      24,     0,     0,     0,     0,     0,     0,     0,   138,   116,
       0,     0,     0,     0,     0,     0,    32,    31,     0,     0,
     149,   104,     0,     0,     0,    30,    40,   137,   115,   139,
     110,     0,     0,   125,     0,   108,    70,    67,    63,    64,
      65,     0,    66,     0,     0,     0,     0,    56,    92,     0,
       0,     0,   149,   104,     0,    54,    42,     0,     0,   117,
     111,     0,   146,   144,   126,     0,    74,     0,    70,     0,
       0,     0,   137,     0,     0,   137,     0,   137,     0,   137,
      23,    60,     0,     0,    56,    93,    94,     0,   150,   102,
     104,     0,     0,   105,     0,     0,     0,    49,    50,    51,
      52,    53,    45,     0,     0,   147,     0,   140,    70,    71,
      69,    68,   137,    77,    75,     0,   121,     0,     0,   127,
       0,   119,     0,   118,     0,     0,    60,    56,    55,    58,
       0,     0,     0,     0,     0,   166,   165,    92,     0,   106,
     107,   103,     0,    42,     0,     0,     0,    47,    36,   148,
     144,     0,   149,    72,     0,    78,     0,     0,     0,   137,
     137,     0,   137,   137,    60,    59,    62,    57,     0,   163,
       0,     0,     0,   193,   194,   195,   196,   197,   198,     0,
     199,   201,   203,   205,     0,   152,     0,     0,    43,    41,
      48,     0,    46,     0,    39,     0,    36,   145,     0,   167,
     137,    75,     0,     0,     0,   123,   122,     0,   128,   120,
      61,   164,     0,     0,     0,   200,   202,   204,   206,   155,
     153,   156,   154,   207,    44,    36,     0,    37,   142,     0,
     183,    79,    76,    85,    83,   137,     0,   137,   137,     0,
       0,     0,     0,     0,    38,    33,     0,   140,   170,     0,
       0,     0,    86,     0,    88,    81,     0,    80,   124,     0,
       0,     0,     0,   157,   158,    92,   141,     0,   173,   168,
     170,   185,   109,    87,   144,    92,    73,   137,   160,     0,
       0,     0,   143,   170,     0,   175,   172,     0,   192,   184,
     185,    84,    89,     0,    82,     0,     0,   159,   171,   174,
       0,     0,     0,   169,   175,   185,   191,     0,   190,   188,
     187,     0,     0,    92,     0,     0,   175,     0,     0,     0,
     176,   186,   192,     0,     0,     0,    91,     0,     0,   177,
       0,   181,     0,     0,   189,     0,    97,    95,    98,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,     0,     0,     0,     0,    99,   100,     0,     0,   178,
       0,   180,     0,   161,   162,     0,   101,   179
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,  -355,
    -355,  -355,  -355,  -355,  -355,  -254,   251,  -355,  -355,   300,
     351,  -355,  -355,  -355,  -355,  -148,   366,  -141,   -84,  -105,
    -355,  -355,   246,   289,  -355,   197,  -355,   136,  -243,  -355,
    -355,  -355,   -32,   404,  -355,  -355,   439,   442,  -355,   443,
     444,   129,    -4,   -81,   204,  -355,  -218,   347,  -117,  -203,
     209,  -247,  -355,  -314,   192,  -354,   157,  -355,  -341,   173,
     139,  -205,  -355
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   265,   266,    30,    31,   166,
     126,   261,   172,   127,    32,   153,   154,   195,   206,   139,
     140,   141,   227,   184,   324,   304,   346,   362,   157,   383,
      33,    34,   122,   123,    35,    36,    81,    54,    55,    83,
      56,    57,   372,    79,   222,   317,   177,   133,   119,   158,
     207,   208,   300,   339,   340,   373,   374,   320,   359,   360,
     379,   254,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     113,    58,   267,   256,   255,   162,   199,   290,   136,   292,
      38,   376,   297,   120,    59,   106,   129,   137,   376,   380,
     390,    41,   138,    42,   263,   337,   356,   357,   151,   377,
     152,   147,   399,   179,   391,   305,   -90,   142,   143,   368,
      97,   314,   148,   114,    98,   215,   306,   115,   144,   237,
      76,   113,   155,   178,   138,   236,   378,  -151,   107,   187,
    -151,   186,   190,   378,   189,   333,   191,   196,   193,   121,
     108,   109,   110,   223,    39,   112,    58,   210,   106,   312,
     264,   338,   348,   358,   156,   216,  -151,   155,    77,   217,
     155,   163,   309,   280,   138,    62,    78,    60,    61,  -151,
     106,   225,   363,   310,   329,   269,  -151,    77,  -151,  -151,
     234,  -151,   196,   145,   146,    78,   273,   239,   200,   156,
     274,   107,   156,    63,   106,   201,   361,   224,   209,   202,
     203,   106,   352,   108,   109,   110,   204,   185,   112,   205,
     363,    64,   413,   107,   365,   366,    65,   277,   275,   276,
     196,   278,   279,   414,   281,   108,   109,   110,   289,   106,
     112,   205,   230,   231,   174,    77,   388,   107,   167,   168,
     169,   170,   175,    78,   107,   106,   394,   395,    66,   108,
     109,   110,   291,    67,   112,   205,   108,   109,   110,   301,
     321,   112,   205,   402,   106,   412,   137,   403,   322,    71,
     416,   106,   107,   194,   171,    48,    49,    50,   421,   101,
     423,   104,   106,    68,   108,   109,   110,   332,   107,   112,
     205,    72,   185,    69,   325,   435,   327,   328,   106,    70,
     108,   109,   110,   111,   106,   112,    73,   107,    43,    44,
      45,    46,    47,    74,   107,    75,    88,    80,    82,   108,
     109,   110,   106,    84,   112,   107,   108,   109,   110,   106,
      85,   112,    86,    87,    89,   371,   364,   108,   109,   110,
     381,   107,   112,    90,    91,    94,    92,   107,    93,   382,
      95,    96,   370,   108,   109,   110,   406,    99,   112,   108,
     109,   110,   408,   105,   112,   107,    43,    44,    45,    46,
      47,   102,   107,   117,   401,   116,   118,   108,   109,   110,
     407,   409,   112,   125,   108,   109,   110,   424,   124,   112,
     285,   128,   131,   371,   132,   286,   287,   135,   420,   149,
     150,   159,   425,   161,   164,   121,   165,   429,   173,   431,
     111,   176,   180,     2,   198,   188,   181,     3,     4,   192,
     151,   437,     5,     6,     7,     8,     9,    10,    11,   211,
     242,   212,    12,    13,    14,   214,   218,   219,   228,    15,
      16,   243,   244,   245,   246,   247,   248,   226,   229,    17,
      43,    44,    45,    46,    47,   221,   387,   232,   249,   250,
     233,   235,   240,   238,   251,   252,   253,   243,   244,   245,
     246,   247,   248,   241,   259,   257,   260,   182,   262,   268,
     270,   183,   393,   282,   249,   250,   272,   293,   283,   284,
     251,   252,   253,   243,   244,   245,   246,   247,   248,    43,
      44,    45,    46,    47,   288,   294,   264,   296,   298,   303,
     249,   250,   299,   307,   308,   311,   251,   252,   253,    48,
      49,    50,   313,   315,   316,   318,    51,   319,   323,    52,
      53,   243,   244,   245,   246,   247,   248,   326,   330,   331,
     334,   342,   343,   345,   341,   347,   349,   350,   249,   250,
     351,   338,   354,   367,   251,   252,   253,   369,   389,   355,
     358,   385,   384,   397,   398,   417,   415,   418,   419,   430,
     433,   432,   434,   392,   400,   405,   410,   411,   422,   426,
     427,   428,   436,   258,   295,   271,   213,   302,   197,   396,
     344,   336,   100,   220,   160,   335,   103,   386,     0,   353,
     375,   404,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     0,     0,     0,   134
};

static const yytype_int16 yycheck[] =
{
      84,     5,   220,   208,   207,   122,   154,   254,     9,   256,
       6,    10,   266,    18,    74,    16,    97,    18,    10,   360,
     374,     6,   106,     8,    18,    18,   340,    18,    16,    28,
      18,    17,   386,   138,   375,    17,    17,    17,    18,   353,
      74,   295,    28,    74,    78,    16,    28,    78,    28,   197,
      28,   135,    33,   137,   138,   196,    55,     3,    59,   143,
       3,   142,   146,    55,   145,   312,   147,   151,   149,    74,
      71,    72,    73,   178,    70,    76,    80,   161,    16,   284,
      74,    74,   329,    74,    65,    56,    32,    33,    66,    60,
      33,   123,    17,   234,   178,     3,    74,     7,     8,    45,
      16,   182,   345,    28,   309,   222,    52,    66,    54,    52,
     194,    54,   196,    17,    18,    74,    74,   201,    56,    65,
      78,    59,    65,    29,    16,    63,   344,    28,   160,    67,
      68,    16,   335,    71,    72,    73,    74,   141,    76,    77,
     383,    31,    17,    59,   349,   350,    74,   231,   229,   230,
     234,   232,   233,    28,   238,    71,    72,    73,    74,    16,
      76,    77,    17,    18,    66,    66,   371,    59,    22,    23,
      24,    25,    74,    74,    59,    16,   381,   382,     3,    71,
      72,    73,    74,     3,    76,    77,    71,    72,    73,   270,
      66,    76,    77,    74,    16,   400,    18,    78,    74,    37,
     405,    16,    59,    18,    58,    67,    68,    69,   413,    80,
     415,    82,    16,     3,    71,    72,    73,    74,    59,    76,
      77,    74,   226,     3,   305,   430,   307,   308,    16,     3,
      71,    72,    73,    74,    16,    76,     8,    59,    47,    48,
      49,    50,    51,    74,    59,    74,    31,    18,    18,    71,
      72,    73,    16,    16,    76,    59,    71,    72,    73,    16,
      16,    76,     3,     3,    74,    74,   347,    71,    72,    73,
      74,    59,    76,    74,    34,    74,    38,    59,    16,   363,
       3,     3,    33,    71,    72,    73,    74,    74,    76,    71,
      72,    73,    74,     3,    76,    59,    47,    48,    49,    50,
      51,    31,    59,    30,   388,    74,    32,    71,    72,    73,
     394,   395,    76,    74,    71,    72,    73,    74,    76,    76,
      57,    35,    16,    74,    74,    62,    63,    16,   412,    17,
       3,     3,   416,    39,    29,    74,    18,   421,    74,   423,
      74,    18,    17,     0,     3,    74,    17,     4,     5,    74,
      16,   435,     9,    10,    11,    12,    13,    14,    15,     3,
      28,     6,    19,    20,    21,    17,    16,    74,    16,    26,
      27,    39,    40,    41,    42,    43,    44,    18,    17,    36,
      47,    48,    49,    50,    51,    45,    28,    17,    56,    57,
      17,    17,    16,    63,    62,    63,    64,    39,    40,    41,
      42,    43,    44,    16,     3,    74,    71,    74,    59,    46,
      74,    78,    28,    74,    56,    57,    31,     3,    74,    74,
      62,    63,    64,    39,    40,    41,    42,    43,    44,    47,
      48,    49,    50,    51,    56,    17,    74,    17,    74,    74,
      56,    57,    52,    17,    17,    28,    62,    63,    64,    67,
      68,    69,    28,     3,    35,    53,    74,    54,    18,    77,
      78,    39,    40,    41,    42,    43,    44,    74,    74,    74,
      74,     3,    74,    32,    53,    17,    17,    17,    56,    57,
      28,    74,    28,    74,    62,    63,    64,    74,    16,    61,
      74,    68,    67,    16,    16,    28,    17,    28,    28,    17,
      17,    28,    17,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,   213,   263,   226,   165,   271,   152,   383,
     323,   317,    80,   176,   120,   316,    82,   370,    -1,   337,
     357,   392,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,   103
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      97,    98,   104,   120,   121,   124,   125,   152,     6,    70,
      94,     6,     8,    47,    48,    49,    50,    51,    67,    68,
      69,    74,    77,    78,   127,   128,   130,   131,   132,    74,
       7,     8,     3,    29,    31,    74,     3,     3,     3,     3,
       3,    37,    74,     8,    74,    74,    28,    66,    74,   133,
      18,   126,    18,   129,    16,    16,     3,     3,    31,    74,
      74,    34,    38,    16,    74,     3,     3,    74,    78,    74,
     127,   131,    31,   130,   131,     3,    16,    59,    71,    72,
      73,    74,    76,   108,    74,    78,    74,    30,    32,   138,
      18,    74,   122,   123,    76,    74,   100,   103,    35,   133,
     126,    16,    74,   137,   129,    16,     9,    18,   108,   109,
     110,   111,    17,    18,    28,    17,    18,    17,    28,    17,
       3,    16,    18,   105,   106,    33,    65,   118,   139,     3,
     123,    39,   138,   122,    29,    18,    99,    22,    23,    24,
      25,    58,   102,    74,    66,    74,    18,   136,   108,   109,
      17,    17,    74,    78,   113,   132,   133,   108,    74,   133,
     108,   133,    74,   133,    18,   107,   108,   106,     3,   105,
      56,    63,    67,    68,    74,    77,   108,   140,   141,   122,
     108,     3,     6,   100,    17,    16,    56,    60,    16,    74,
     137,    45,   134,   109,    28,   133,    18,   112,    16,    17,
      17,    18,    17,    17,   108,    17,   107,   105,    63,   108,
      16,    16,    28,    39,    40,    41,    42,    43,    44,    56,
      57,    62,    63,    64,   151,   139,   151,    74,    99,     3,
      71,   101,    59,    18,    74,    95,    96,   136,    46,   138,
      74,   113,    31,    74,    78,   133,   133,   108,   133,   133,
     107,   108,    74,    74,    74,    57,    62,    63,    56,    74,
     141,    74,   141,     3,    17,    96,    17,    95,    74,    52,
     142,   133,   112,    74,   115,    17,    28,    17,    17,    17,
      28,    28,   151,    28,    95,     3,    35,   135,    53,    54,
     147,    66,    74,    18,   114,   133,    74,   133,   133,   151,
      74,    74,    74,   141,    74,   140,   134,    18,    74,   143,
     144,    53,     3,    74,   115,    32,   116,    17,   141,    17,
      17,    28,   139,   144,    28,    61,   143,    18,    74,   148,
     149,   136,   117,   118,   133,   151,   151,    74,   143,    74,
      33,    74,   132,   145,   146,   149,    10,    28,    55,   150,
     148,    74,   108,   119,    67,    68,   146,    28,   151,    16,
     145,   148,    74,    28,   151,   151,   117,    16,    16,   145,
      74,   108,    74,    78,   150,    74,    74,   108,    74,   108,
      74,    74,   151,    17,    28,    17,   151,    28,    28,    28,
     108,   151,    74,   151,    74,   108,    74,    74,    74,   108,
      17,   108,    28,    17,    17,   151,    74,   108
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    94,    95,    95,    95,    96,
      97,    98,    99,    99,   100,   100,   100,   100,   101,   102,
     102,   102,   102,   102,   103,   104,   105,   105,   105,   106,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     109,   109,   109,   110,   111,   112,   112,   113,   113,   113,
     113,   113,   113,   114,   114,   115,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   119,
     119,   119,   120,   121,   122,   122,   122,   123,   124,   125,
     126,   126,   127,   127,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   129,   129,   130,   130,   131,
     131,   131,   132,   132,   132,   132,   132,   133,   133,   133,
     134,   134,   135,   135,   136,   136,   137,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141,   142,   142,   142,
     143,   143,   143,   144,   144,   145,   145,   145,   146,   146,
     146,   146,   146,   147,   147,   148,   148,   148,   149,   149,
     150,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   152
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     2,     2,     2,     2,     2,     2,
       4,     3,     3,    10,     0,     1,     0,     2,     3,     1,
       4,     8,     0,     3,     5,     2,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     6,     0,     3,     2,     3,
       0,     3,     2,     1,     1,     1,     1,     1,     3,     3,
       0,     2,     3,     7,     1,     0,     3,     1,     2,     4,
       5,     5,     7,     0,     3,     1,     2,     3,     0,     2,
       0,     3,     0,     1,     1,     3,     3,     3,     3,     5,
       5,     7,     5,     6,     0,     2,     3,     3,     4,    11,
       0,     3,     1,     1,     1,     3,     2,     4,     5,     5,
       7,     5,     7,     7,     9,     0,     3,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     2,
       0,     5,     0,     3,     0,     3,     1,     2,     3,     0,
       2,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       6,    13,    13,     2,     3,     1,     1,     0,     3,     5,
       0,     3,     2,     1,     3,     0,     2,     3,     6,     8,
       6,     3,     5,     0,     3,     0,     3,     2,     2,     4,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 23: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 212 "yacc_sql.y"
                                 {
	CONTEXT->ssql->flag=SCF_SHOW_INDEX;
	show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1630 "yacc_sql.tab.c"
    break;

  case 24: /* exit: EXIT SEMICOLON  */
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1638 "yacc_sql.tab.c"
    break;

  case 25: /* help: HELP SEMICOLON  */
#line 223 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1646 "yacc_sql.tab.c"
    break;

  case 26: /* sync: SYNC SEMICOLON  */
#line 228 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1654 "yacc_sql.tab.c"
    break;

  case 27: /* begin: TRX_BEGIN SEMICOLON  */
#line 234 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1662 "yacc_sql.tab.c"
    break;

  case 28: /* commit: TRX_COMMIT SEMICOLON  */
#line 240 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1670 "yacc_sql.tab.c"
    break;

  case 29: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 246 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1678 "yacc_sql.tab.c"
    break;

  case 30: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 252 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1687 "yacc_sql.tab.c"
    break;

  case 31: /* show_tables: SHOW TABLES SEMICOLON  */
#line 258 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1695 "yacc_sql.tab.c"
    break;

  case 32: /* desc_table: DESC ID SEMICOLON  */
#line 264 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1704 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE unique_or_not INDEX ID ON ID LBRACE index_col_ID_list RBRACE SEMICOLON  */
#line 272 "yacc_sql.y"
    {
	CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
	create_index_multi_rel_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), CONTEXT->is_unique);
    }
#line 1713 "yacc_sql.tab.c"
    break;

  case 34: /* unique_or_not: %empty  */
#line 279 "yacc_sql.y"
                {
    	CONTEXT->is_unique = 0;
    }
#line 1721 "yacc_sql.tab.c"
    break;

  case 35: /* unique_or_not: UNIQUE  */
#line 282 "yacc_sql.y"
             {
    	CONTEXT->is_unique = 1;
    }
#line 1729 "yacc_sql.tab.c"
    break;

  case 37: /* index_col_ID_list: index_col_ID index_col_ID_list  */
#line 287 "yacc_sql.y"
                                     {

    }
#line 1737 "yacc_sql.tab.c"
    break;

  case 38: /* index_col_ID_list: COMMA index_col_ID index_col_ID_list  */
#line 290 "yacc_sql.y"
                                           {
    }
#line 1744 "yacc_sql.tab.c"
    break;

  case 39: /* index_col_ID: ID  */
#line 294 "yacc_sql.y"
       {
    	create_index_append_attr_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1752 "yacc_sql.tab.c"
    break;

  case 40: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 301 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1761 "yacc_sql.tab.c"
    break;

  case 41: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 308 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1773 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 318 "yacc_sql.y"
                                   {    }
#line 1779 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 323 "yacc_sql.y"
        {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
#line 1794 "yacc_sql.tab.c"
    break;

  case 45: /* attr_def: ID_get type  */
#line 334 "yacc_sql.y"
        {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), CONTEXT->attr_length);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
#line 1809 "yacc_sql.tab.c"
    break;

  case 46: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 345 "yacc_sql.y"
        {
    		AttrInfo attribute;
    		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), CONTEXT->attr_length);
    		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
    		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
    		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
    		CONTEXT->value_length++;
    	}
#line 1824 "yacc_sql.tab.c"
    break;

  case 47: /* attr_def: ID_get type NULLABLE  */
#line 356 "yacc_sql.y"
        {
		AttrInfo attribute;
		nullable_attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), CONTEXT->attr_length);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
#line 1839 "yacc_sql.tab.c"
    break;

  case 48: /* number: NUMBER  */
#line 368 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1845 "yacc_sql.tab.c"
    break;

  case 49: /* type: INT_T  */
#line 371 "yacc_sql.y"
              { (yyval.number)=INTS; CONTEXT->attr_length = 4; }
#line 1851 "yacc_sql.tab.c"
    break;

  case 50: /* type: STRING_T  */
#line 372 "yacc_sql.y"
                  { (yyval.number)=CHARS; CONTEXT->attr_length = 40; }
#line 1857 "yacc_sql.tab.c"
    break;

  case 51: /* type: FLOAT_T  */
#line 373 "yacc_sql.y"
                 { (yyval.number)=FLOATS; CONTEXT->attr_length = 4; }
#line 1863 "yacc_sql.tab.c"
    break;

  case 52: /* type: DATE_T  */
#line 374 "yacc_sql.y"
                { (yyval.number)=DATES; CONTEXT->attr_length = 4; }
#line 1869 "yacc_sql.tab.c"
    break;

  case 53: /* type: TEXT_T  */
#line 375 "yacc_sql.y"
                { (yyval.number)=CHARS; CONTEXT->attr_length = 4096; }
#line 1875 "yacc_sql.tab.c"
    break;

  case 54: /* ID_get: ID  */
#line 380 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1884 "yacc_sql.tab.c"
    break;

  case 55: /* insert: INSERT INTO ID VALUES record_list SEMICOLON  */
#line 389 "yacc_sql.y"
    {
      CONTEXT->ssql->flag=SCF_INSERT;//"insert";
      inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-3].string), CONTEXT->records, CONTEXT->record_length);
      //临时变量清零
      CONTEXT->record_length = 0;
    }
#line 1895 "yacc_sql.tab.c"
    break;

  case 57: /* record_list: COMMA record record_list  */
#line 397 "yacc_sql.y"
                               {
    }
#line 1902 "yacc_sql.tab.c"
    break;

  case 58: /* record_list: record record_list  */
#line 399 "yacc_sql.y"
                         {
    }
#line 1909 "yacc_sql.tab.c"
    break;

  case 59: /* record: LBRACE value_list RBRACE  */
#line 403 "yacc_sql.y"
                             {
    	insert_record_init(&CONTEXT->records[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
    	CONTEXT->value_length=0;
    }
#line 1918 "yacc_sql.tab.c"
    break;

  case 61: /* value_list: COMMA value value_list  */
#line 410 "yacc_sql.y"
                              {
    }
#line 1925 "yacc_sql.tab.c"
    break;

  case 62: /* value_list: value value_list  */
#line 412 "yacc_sql.y"
                       {
    }
#line 1932 "yacc_sql.tab.c"
    break;

  case 63: /* value: NUMBER  */
#line 415 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
    }
#line 1940 "yacc_sql.tab.c"
    break;

  case 64: /* value: FLOAT  */
#line 418 "yacc_sql.y"
           {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
    }
#line 1948 "yacc_sql.tab.c"
    break;

  case 65: /* value: DATE_STR  */
#line 421 "yacc_sql.y"
              {
    		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1957 "yacc_sql.tab.c"
    break;

  case 66: /* value: SSS  */
#line 425 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1966 "yacc_sql.tab.c"
    break;

  case 67: /* value: NULL_TOKEN  */
#line 429 "yacc_sql.y"
                {
    		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1974 "yacc_sql.tab.c"
    break;

  case 68: /* value: LBRACE sub_select RBRACE  */
#line 432 "yacc_sql.y"
                               {
    	// printf("MAKE VALUE FOR SUB_SELECTS\n");
    	value_init_sub_select(&CONTEXT->values[CONTEXT->value_length++], &CONTEXT->sub_selects[CONTEXT->sub_select_num]);
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].attr_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].relation_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].condition_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].group_num=0;
    	CONTEXT->sub_selects[CONTEXT->sub_select_num].order_num=0;
    	CONTEXT->sub_select_num--;
    }
#line 1989 "yacc_sql.tab.c"
    break;

  case 69: /* value: LBRACE set_value_list RBRACE  */
#line 442 "yacc_sql.y"
                                   {
	value_init_set(&CONTEXT->values[CONTEXT->value_length++], CONTEXT->set_values, CONTEXT->set_num);
	CONTEXT->set_num = 0;
    }
#line 1998 "yacc_sql.tab.c"
    break;

  case 71: /* set_value_list: value set_value_list  */
#line 450 "yacc_sql.y"
                           {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 2006 "yacc_sql.tab.c"
    break;

  case 72: /* set_value_list: COMMA value set_value_list  */
#line 453 "yacc_sql.y"
                                 {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 2014 "yacc_sql.tab.c"
    break;

  case 73: /* sub_select: sub_select_token sub_select_attr sub_attr_list FROM sub_rel_item sub_rel_list sub_where  */
#line 459 "yacc_sql.y"
                                                                                            {
    }
#line 2021 "yacc_sql.tab.c"
    break;

  case 74: /* sub_select_token: SELECT  */
#line 464 "yacc_sql.y"
           {
	CONTEXT->sub_select_num++;
    }
#line 2029 "yacc_sql.tab.c"
    break;

  case 76: /* sub_attr_list: COMMA sub_select_attr sub_attr_list  */
#line 471 "yacc_sql.y"
                                          {
    }
#line 2036 "yacc_sql.tab.c"
    break;

  case 77: /* sub_select_attr: STAR  */
#line 476 "yacc_sql.y"
         {
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2046 "yacc_sql.tab.c"
    break;

  case 78: /* sub_select_attr: ID alias_or_not  */
#line 481 "yacc_sql.y"
                      {
        RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2056 "yacc_sql.tab.c"
    break;

  case 79: /* sub_select_attr: ID DOT ID alias_or_not  */
#line 486 "yacc_sql.y"
                             {
        RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2066 "yacc_sql.tab.c"
    break;

  case 80: /* sub_select_attr: aggop LBRACE STAR RBRACE alias_or_not  */
#line 491 "yacc_sql.y"
                                            {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2076 "yacc_sql.tab.c"
    break;

  case 81: /* sub_select_attr: aggop LBRACE ID RBRACE alias_or_not  */
#line 496 "yacc_sql.y"
                                          {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, (yyvsp[-2].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2086 "yacc_sql.tab.c"
    break;

  case 82: /* sub_select_attr: aggop LBRACE ID DOT ID RBRACE alias_or_not  */
#line 501 "yacc_sql.y"
                                                 {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2096 "yacc_sql.tab.c"
    break;

  case 84: /* sub_rel_list: COMMA sub_rel_item rel_list  */
#line 510 "yacc_sql.y"
                                  {

    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 85: /* sub_rel_item: ID  */
#line 516 "yacc_sql.y"
       {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[0].string), NULL);
    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 86: /* sub_rel_item: ID ID  */
#line 519 "yacc_sql.y"
            {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-1].string), (yyvsp[0].string));
    }
#line 2120 "yacc_sql.tab.c"
    break;

  case 87: /* sub_rel_item: ID AS ID  */
#line 522 "yacc_sql.y"
               {
	selects_append_relation_alias(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-2].string), (yyvsp[0].string));
    }
#line 2128 "yacc_sql.tab.c"
    break;

  case 89: /* sub_where: WHERE sub_condition_list  */
#line 528 "yacc_sql.y"
                               {
	printf("2\n");
    }
#line 2136 "yacc_sql.tab.c"
    break;

  case 91: /* sub_condition_list: type_conj sub_condition sub_condition_list  */
#line 535 "yacc_sql.y"
                                                 {

    }
#line 2144 "yacc_sql.tab.c"
    break;

  case 92: /* type_conj: %empty  */
#line 541 "yacc_sql.y"
                {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_FIRST;
    }
#line 2152 "yacc_sql.tab.c"
    break;

  case 93: /* type_conj: AND  */
#line 544 "yacc_sql.y"
          {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_AND;
    }
#line 2160 "yacc_sql.tab.c"
    break;

  case 94: /* type_conj: OR  */
#line 547 "yacc_sql.y"
         {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_OR;
    }
#line 2168 "yacc_sql.tab.c"
    break;

  case 95: /* sub_condition: ID comOp value  */
#line 553 "yacc_sql.y"
    {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	// printf("CONTEXT->sub_select_num: %d\n", CONTEXT->sub_select_num);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2182 "yacc_sql.tab.c"
    break;

  case 96: /* sub_condition: value comOp value  */
#line 562 "yacc_sql.y"
                       {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2195 "yacc_sql.tab.c"
    break;

  case 97: /* sub_condition: ID comOp ID  */
#line 570 "yacc_sql.y"
                 {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2210 "yacc_sql.tab.c"
    break;

  case 98: /* sub_condition: value comOp ID  */
#line 580 "yacc_sql.y"
                    {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2224 "yacc_sql.tab.c"
    break;

  case 99: /* sub_condition: ID DOT ID comOp value  */
#line 589 "yacc_sql.y"
                           {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2238 "yacc_sql.tab.c"
    break;

  case 100: /* sub_condition: value comOp ID DOT ID  */
#line 598 "yacc_sql.y"
                           {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2253 "yacc_sql.tab.c"
    break;

  case 101: /* sub_condition: ID DOT ID comOp ID DOT ID  */
#line 608 "yacc_sql.y"
                               {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2267 "yacc_sql.tab.c"
    break;

  case 102: /* delete: DELETE FROM ID where SEMICOLON  */
#line 621 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2279 "yacc_sql.tab.c"
    break;

  case 103: /* update: UPDATE ID SET update_set_list where SEMICOLON  */
#line 631 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string),
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2290 "yacc_sql.tab.c"
    break;

  case 105: /* update_set_list: update_set update_set_list  */
#line 641 "yacc_sql.y"
                                 {
    }
#line 2297 "yacc_sql.tab.c"
    break;

  case 106: /* update_set_list: COMMA update_set update_set_list  */
#line 643 "yacc_sql.y"
                                       {
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 107: /* update_set: ID EQ value  */
#line 648 "yacc_sql.y"
                {
        Value *value = &CONTEXT->values[--CONTEXT->value_length];
    	updates_append_attr_and_value(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), value);
    }
#line 2313 "yacc_sql.tab.c"
    break;

  case 108: /* select_non_table: SELECT select_nontable_attr select_nontable_attr_list SEMICOLON  */
#line 654 "yacc_sql.y"
                                                                    {
	for (int i = (int)CONTEXT->rel_num - 1; i >= 0; i--) {
	    selects_append_relation_alias(&CONTEXT->ssql->sstr.selection, CONTEXT->rel[i], CONTEXT->rel_alias[i]);
       	}
       	CONTEXT->ssql->flag=SCF_SELECT_NONTABLE;//"select";
	// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;
	//临时变量清零
	CONTEXT->condition_length=0;
	CONTEXT->from_length=0;
	CONTEXT->select_length=0;
	CONTEXT->value_length = 0;
    }
#line 2330 "yacc_sql.tab.c"
    break;

  case 109: /* select: SELECT select_attr_or_expression attr_list FROM rel_item rel_list inner_join_list where group order SEMICOLON  */
#line 670 "yacc_sql.y"
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
#line 2351 "yacc_sql.tab.c"
    break;

  case 111: /* attr_list: COMMA select_attr_or_expression attr_list  */
#line 690 "yacc_sql.y"
                                                {
    }
#line 2358 "yacc_sql.tab.c"
    break;

  case 112: /* select_attr_or_expression: select_attr  */
#line 695 "yacc_sql.y"
                {

    }
#line 2366 "yacc_sql.tab.c"
    break;

  case 113: /* select_attr_or_expression: EXPRESSION  */
#line 698 "yacc_sql.y"
                 {
    	RelAttr attr;
    	relation_attr_exp_init(&attr, (yyvsp[0].string));
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2376 "yacc_sql.tab.c"
    break;

  case 114: /* select_attr: STAR  */
#line 705 "yacc_sql.y"
         {  
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2386 "yacc_sql.tab.c"
    break;

  case 115: /* select_attr: ID DOT STAR  */
#line 710 "yacc_sql.y"
                  {
    	RelAttr attr;
    	relation_attr_init(&attr, (yyvsp[-2].string), "*");
     	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2396 "yacc_sql.tab.c"
    break;

  case 116: /* select_attr: ID alias_or_not  */
#line 715 "yacc_sql.y"
                      {
        RelAttr attr;
	relation_attr_alias_init(&attr, NULL, (yyvsp[-1].string), CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2406 "yacc_sql.tab.c"
    break;

  case 117: /* select_attr: ID DOT ID alias_or_not  */
#line 720 "yacc_sql.y"
                             {
        RelAttr attr;
	relation_attr_alias_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2416 "yacc_sql.tab.c"
    break;

  case 118: /* select_attr: aggop LBRACE STAR RBRACE alias_or_not  */
#line 725 "yacc_sql.y"
                                            {
	RelAttr attr;
	relation_attr_aggr_alias_init(&attr, NULL, "*", CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2426 "yacc_sql.tab.c"
    break;

  case 119: /* select_attr: aggop LBRACE ID RBRACE alias_or_not  */
#line 730 "yacc_sql.y"
                                          {
    	RelAttr attr;
    	relation_attr_aggr_alias_init(&attr, NULL, (yyvsp[-2].string), CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2436 "yacc_sql.tab.c"
    break;

  case 120: /* select_attr: aggop LBRACE ID DOT ID RBRACE alias_or_not  */
#line 735 "yacc_sql.y"
                                                 {
    	RelAttr attr;
    	relation_attr_aggr_alias_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), CONTEXT->agg_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt]);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2446 "yacc_sql.tab.c"
    break;

  case 121: /* select_attr: funcop LBRACE ID RBRACE alias_or_not  */
#line 740 "yacc_sql.y"
                                           {
	RelAttr attr;
    	relation_attr_func_alias_init(&attr, NULL, (yyvsp[-2].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, NULL);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2456 "yacc_sql.tab.c"
    break;

  case 122: /* select_attr: funcop LBRACE ID DOT ID RBRACE alias_or_not  */
#line 745 "yacc_sql.y"
                                                  {
	RelAttr attr;
    	relation_attr_func_alias_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, NULL);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2466 "yacc_sql.tab.c"
    break;

  case 123: /* select_attr: funcop LBRACE ID COMMA value RBRACE alias_or_not  */
#line 750 "yacc_sql.y"
                                                       {
	RelAttr attr;
	Value value = CONTEXT->values[--CONTEXT->value_length];
	if (value.type == INTS) {
    	    relation_attr_func_alias_init(&attr, NULL, (yyvsp[-4].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], *(int *)value.data, NULL);
    	} else if (value.type == CHARS) {
    	    relation_attr_func_alias_init(&attr, NULL, (yyvsp[-4].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, (char *)value.data);
    	}
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2481 "yacc_sql.tab.c"
    break;

  case 124: /* select_attr: funcop LBRACE ID DOT ID COMMA value RBRACE alias_or_not  */
#line 760 "yacc_sql.y"
                                                              {
	RelAttr attr;
	Value value = CONTEXT->values[--CONTEXT->value_length];
	if (value.type == INTS) {
	    relation_attr_func_alias_init(&attr, (yyvsp[-6].string), (yyvsp[-4].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], *(int *)value.data, NULL);
	} else if (value.type == CHARS) {
	    relation_attr_func_alias_init(&attr, (yyvsp[-6].string), (yyvsp[-4].string), CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, (char *)value.data);
	}
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2496 "yacc_sql.tab.c"
    break;

  case 126: /* select_nontable_attr_list: COMMA select_nontable_attr select_nontable_attr_list  */
#line 774 "yacc_sql.y"
                                                           {
    }
#line 2503 "yacc_sql.tab.c"
    break;

  case 127: /* select_nontable_attr: funcop LBRACE value RBRACE alias_or_not  */
#line 779 "yacc_sql.y"
                                            {
    	RelAttr attr;
    	Value value2 = CONTEXT->values[--CONTEXT->value_length];
       	relation_attr_nontable_func_alias_init(&attr, CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, NULL, &value2);
       	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2514 "yacc_sql.tab.c"
    break;

  case 128: /* select_nontable_attr: funcop LBRACE value COMMA value RBRACE alias_or_not  */
#line 785 "yacc_sql.y"
                                                          {
    	RelAttr attr;
    	Value value = CONTEXT->values[--CONTEXT->value_length];
    	Value value2 = CONTEXT->values[--CONTEXT->value_length];
    	if (value.type == INTS) {
       	    relation_attr_nontable_func_alias_init(&attr, CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], *(int *)value.data, NULL, &value2);
       	} else if (value.type == CHARS) {
       	    relation_attr_nontable_func_alias_init(&attr, CONTEXT->func_type, CONTEXT->alias_stack[--CONTEXT->alias_stack_pt], 0, (char *)value.data, &value2);
       	}
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2530 "yacc_sql.tab.c"
    break;

  case 129: /* funcop: LENGTH  */
#line 799 "yacc_sql.y"
           {
	CONTEXT->func_type = FUNC_LENGTH;
    }
#line 2538 "yacc_sql.tab.c"
    break;

  case 130: /* funcop: ROUND  */
#line 802 "yacc_sql.y"
            {
	CONTEXT->func_type = FUNC_ROUND;
    }
#line 2546 "yacc_sql.tab.c"
    break;

  case 131: /* funcop: DATE_FORMAT  */
#line 805 "yacc_sql.y"
                  {
	CONTEXT->func_type = FUNC_DATE;
    }
#line 2554 "yacc_sql.tab.c"
    break;

  case 132: /* aggop: MAX  */
#line 811 "yacc_sql.y"
        {
	CONTEXT->agg_type = AGG_MAX;
    }
#line 2562 "yacc_sql.tab.c"
    break;

  case 133: /* aggop: MIN  */
#line 814 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_MIN;
    }
#line 2570 "yacc_sql.tab.c"
    break;

  case 134: /* aggop: COUNT  */
#line 817 "yacc_sql.y"
            {
	CONTEXT->agg_type = AGG_COUNT;
    }
#line 2578 "yacc_sql.tab.c"
    break;

  case 135: /* aggop: AVG  */
#line 820 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_AVG;
    }
#line 2586 "yacc_sql.tab.c"
    break;

  case 136: /* aggop: SUM  */
#line 823 "yacc_sql.y"
          {
    	CONTEXT->agg_type = AGG_SUM;
    }
#line 2594 "yacc_sql.tab.c"
    break;

  case 137: /* alias_or_not: %empty  */
#line 829 "yacc_sql.y"
                {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = NULL;
    }
#line 2602 "yacc_sql.tab.c"
    break;

  case 138: /* alias_or_not: ID  */
#line 832 "yacc_sql.y"
         {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = strdup((yyvsp[0].string));
    }
#line 2610 "yacc_sql.tab.c"
    break;

  case 139: /* alias_or_not: AS ID  */
#line 835 "yacc_sql.y"
            {
	CONTEXT->alias_stack[CONTEXT->alias_stack_pt++] = strdup((yyvsp[0].string));
    }
#line 2618 "yacc_sql.tab.c"
    break;

  case 141: /* inner_join_list: INNER JOIN ID on inner_join_list  */
#line 841 "yacc_sql.y"
                                       {
	selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 2626 "yacc_sql.tab.c"
    break;

  case 143: /* on: ON condition condition_list  */
#line 848 "yacc_sql.y"
                                  {
	// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
    }
#line 2634 "yacc_sql.tab.c"
    break;

  case 145: /* rel_list: COMMA rel_item rel_list  */
#line 855 "yacc_sql.y"
                              {
    }
#line 2641 "yacc_sql.tab.c"
    break;

  case 146: /* rel_item: ID  */
#line 860 "yacc_sql.y"
       {
	CONTEXT->rel[CONTEXT->rel_num] = strdup((yyvsp[0].string));
	CONTEXT->rel_alias[CONTEXT->rel_num++] = NULL;
        // selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
#line 2651 "yacc_sql.tab.c"
    break;

  case 147: /* rel_item: ID ID  */
#line 865 "yacc_sql.y"
            {
        CONTEXT->rel[CONTEXT->rel_num] = strdup((yyvsp[-1].string));
        CONTEXT->rel_alias[CONTEXT->rel_num++] = strdup((yyvsp[0].string));
      	// selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
#line 2661 "yacc_sql.tab.c"
    break;

  case 148: /* rel_item: ID AS ID  */
#line 870 "yacc_sql.y"
               {
        CONTEXT->rel[CONTEXT->rel_num] = strdup((yyvsp[-2].string));
        CONTEXT->rel_alias[CONTEXT->rel_num++] = strdup((yyvsp[0].string));
	// selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
    }
#line 2671 "yacc_sql.tab.c"
    break;

  case 150: /* where: WHERE condition_list  */
#line 879 "yacc_sql.y"
                           {

    }
#line 2679 "yacc_sql.tab.c"
    break;

  case 152: /* condition_list: type_conj condition condition_list  */
#line 885 "yacc_sql.y"
                                         {
    }
#line 2686 "yacc_sql.tab.c"
    break;

  case 153: /* condition: ID comOp value_or_expression  */
#line 890 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2699 "yacc_sql.tab.c"
    break;

  case 154: /* condition: value_or_expression comOp value_or_expression  */
#line 899 "yacc_sql.y"
    {
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2712 "yacc_sql.tab.c"
    break;

  case 155: /* condition: ID comOp ID  */
#line 908 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2727 "yacc_sql.tab.c"
    break;

  case 156: /* condition: value_or_expression comOp ID  */
#line 919 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2741 "yacc_sql.tab.c"
    break;

  case 157: /* condition: ID DOT ID comOp value_or_expression  */
#line 929 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2755 "yacc_sql.tab.c"
    break;

  case 158: /* condition: value_or_expression comOp ID DOT ID  */
#line 939 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	// condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2771 "yacc_sql.tab.c"
    break;

  case 159: /* condition: ID DOT ID comOp ID DOT ID  */
#line 951 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2785 "yacc_sql.tab.c"
    break;

  case 160: /* condition: LENGTH LBRACE ID RBRACE comOp value_or_expression  */
#line 960 "yacc_sql.y"
                                                        {
	RelAttr left_attr;
	relation_attr_func_alias_init(&left_attr, NULL, (yyvsp[-3].string), FUNC_LENGTH, NULL, NULL, NULL);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2798 "yacc_sql.tab.c"
    break;

  case 161: /* condition: LENGTH LBRACE ID DOT ID RBRACE comOp LENGTH LBRACE ID DOT ID RBRACE  */
#line 968 "yacc_sql.y"
                                                                           {
    	RelAttr left_attr;
	relation_attr_func_alias_init(&left_attr, (yyvsp[-10].string), (yyvsp[-8].string), FUNC_LENGTH, NULL, NULL, NULL);
	RelAttr right_attr;
	relation_attr_func_alias_init(&right_attr, (yyvsp[-3].string), (yyvsp[-1].string), FUNC_LENGTH, NULL, NULL, NULL);

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2813 "yacc_sql.tab.c"
    break;

  case 162: /* condition: ROUND LBRACE ID DOT ID RBRACE comOp ROUND LBRACE ID DOT ID RBRACE  */
#line 978 "yacc_sql.y"
                                                                         {
        RelAttr left_attr;
    	relation_attr_func_alias_init(&left_attr, (yyvsp[-10].string), (yyvsp[-8].string), FUNC_ROUND, NULL, NULL, NULL);
    	RelAttr right_attr;
    	relation_attr_func_alias_init(&right_attr, (yyvsp[-3].string), (yyvsp[-1].string), FUNC_ROUND, NULL, NULL, NULL);

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
        }
#line 2828 "yacc_sql.tab.c"
    break;

  case 163: /* condition: EXISTS value  */
#line 989 "yacc_sql.y"
                   {
	Value left_value;
	value_init_integer(&left_value, 0);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2842 "yacc_sql.tab.c"
    break;

  case 164: /* condition: NOT EXISTS value  */
#line 998 "yacc_sql.y"
                       {
    	Value left_value;
        value_init_integer(&left_value, 0);
    	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

    	Condition condition;
    	condition_conj_init(&condition, NOT_EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2856 "yacc_sql.tab.c"
    break;

  case 165: /* value_or_expression: value  */
#line 1009 "yacc_sql.y"
          {

    }
#line 2864 "yacc_sql.tab.c"
    break;

  case 166: /* value_or_expression: EXPRESSION  */
#line 1012 "yacc_sql.y"
                 {
	// $1 = substr($1,1,strlen($1)-2);
	value_init_expression(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 2873 "yacc_sql.tab.c"
    break;

  case 168: /* group: GROUP BY group_attr_list  */
#line 1020 "yacc_sql.y"
                               {
    }
#line 2880 "yacc_sql.tab.c"
    break;

  case 169: /* group: GROUP BY group_attr_list HAVING hc_list  */
#line 1022 "yacc_sql.y"
                                              {

    }
#line 2888 "yacc_sql.tab.c"
    break;

  case 171: /* group_attr_list: COMMA group_attr group_attr_list  */
#line 1028 "yacc_sql.y"
                                       {
    }
#line 2895 "yacc_sql.tab.c"
    break;

  case 172: /* group_attr_list: group_attr group_attr_list  */
#line 1030 "yacc_sql.y"
                                 {
    }
#line 2902 "yacc_sql.tab.c"
    break;

  case 173: /* group_attr: ID  */
#line 1034 "yacc_sql.y"
       {
        GroupAttr group_attr;
	group_attr_init(&group_attr, NULL, (yyvsp[0].string));
	group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2912 "yacc_sql.tab.c"
    break;

  case 174: /* group_attr: ID DOT ID  */
#line 1039 "yacc_sql.y"
                {
        GroupAttr group_attr;
        group_attr_init(&group_attr, (yyvsp[-2].string), (yyvsp[0].string));
        group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2922 "yacc_sql.tab.c"
    break;

  case 176: /* hc_list: having_condition hc_list  */
#line 1048 "yacc_sql.y"
                               {

    }
#line 2930 "yacc_sql.tab.c"
    break;

  case 177: /* hc_list: AND having_condition hc_list  */
#line 1051 "yacc_sql.y"
                                   {
    }
#line 2937 "yacc_sql.tab.c"
    break;

  case 178: /* having_condition: aggop LBRACE ID RBRACE comOp value  */
#line 1056 "yacc_sql.y"
                                       {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2951 "yacc_sql.tab.c"
    break;

  case 179: /* having_condition: aggop LBRACE ID DOT ID RBRACE comOp value  */
#line 1065 "yacc_sql.y"
                                                {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2965 "yacc_sql.tab.c"
    break;

  case 180: /* having_condition: aggop LBRACE STAR RBRACE comOp value  */
#line 1074 "yacc_sql.y"
                                           {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, "*", CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2979 "yacc_sql.tab.c"
    break;

  case 181: /* having_condition: ID comOp value  */
#line 1083 "yacc_sql.y"
                     {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2993 "yacc_sql.tab.c"
    break;

  case 182: /* having_condition: ID DOT ID comOp value  */
#line 1092 "yacc_sql.y"
                            {
        RelAttr left_attr;
        relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 3007 "yacc_sql.tab.c"
    break;

  case 184: /* order: ORDER BY order_attr_list  */
#line 1105 "yacc_sql.y"
                               {
    }
#line 3014 "yacc_sql.tab.c"
    break;

  case 186: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 1110 "yacc_sql.y"
                                       {
    }
#line 3021 "yacc_sql.tab.c"
    break;

  case 187: /* order_attr_list: order_attr order_attr_list  */
#line 1112 "yacc_sql.y"
                                 {
    }
#line 3028 "yacc_sql.tab.c"
    break;

  case 188: /* order_attr: ID order_type  */
#line 1116 "yacc_sql.y"
                  {
        OrderAttr order_attr;
	order_attr_init(&order_attr, NULL, (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 3038 "yacc_sql.tab.c"
    break;

  case 189: /* order_attr: ID DOT ID order_type  */
#line 1121 "yacc_sql.y"
                           {
        OrderAttr order_attr;
	order_attr_init(&order_attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 3048 "yacc_sql.tab.c"
    break;

  case 190: /* order_type: ASC  */
#line 1128 "yacc_sql.y"
        {
    	CONTEXT->order_type = OrderAsc;
    }
#line 3056 "yacc_sql.tab.c"
    break;

  case 191: /* order_type: DESC  */
#line 1131 "yacc_sql.y"
           {
    	CONTEXT->order_type = OrderDesc;
    }
#line 3064 "yacc_sql.tab.c"
    break;

  case 192: /* order_type: %empty  */
#line 1134 "yacc_sql.y"
                  {
    	CONTEXT->order_type = OrderAsc;
    }
#line 3072 "yacc_sql.tab.c"
    break;

  case 193: /* comOp: EQ  */
#line 1138 "yacc_sql.y"
       { CONTEXT->comps[CONTEXT->comp_num++] = EQUAL_TO; }
#line 3078 "yacc_sql.tab.c"
    break;

  case 194: /* comOp: LT  */
#line 1139 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_THAN; }
#line 3084 "yacc_sql.tab.c"
    break;

  case 195: /* comOp: GT  */
#line 1140 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_THAN; }
#line 3090 "yacc_sql.tab.c"
    break;

  case 196: /* comOp: LE  */
#line 1141 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_EQUAL; }
#line 3096 "yacc_sql.tab.c"
    break;

  case 197: /* comOp: GE  */
#line 1142 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_EQUAL; }
#line 3102 "yacc_sql.tab.c"
    break;

  case 198: /* comOp: NE  */
#line 1143 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EQUAL; }
#line 3108 "yacc_sql.tab.c"
    break;

  case 199: /* comOp: LIKE  */
#line 1144 "yacc_sql.y"
           { CONTEXT->comps[CONTEXT->comp_num++] = LIKE_TO; }
#line 3114 "yacc_sql.tab.c"
    break;

  case 200: /* comOp: NOT LIKE  */
#line 1145 "yacc_sql.y"
               { CONTEXT->comps[CONTEXT->comp_num++] = NOT_LIKE_TO; }
#line 3120 "yacc_sql.tab.c"
    break;

  case 201: /* comOp: IN  */
#line 1146 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IN_OP; }
#line 3126 "yacc_sql.tab.c"
    break;

  case 202: /* comOp: NOT IN  */
#line 1147 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = NOT_IN_OP; }
#line 3132 "yacc_sql.tab.c"
    break;

  case 203: /* comOp: EXISTS  */
#line 1148 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = EXISTS_OP; }
#line 3138 "yacc_sql.tab.c"
    break;

  case 204: /* comOp: NOT EXISTS  */
#line 1149 "yacc_sql.y"
                 { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EXISTS_OP; }
#line 3144 "yacc_sql.tab.c"
    break;

  case 205: /* comOp: IS  */
#line 1150 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IS_OP; }
#line 3150 "yacc_sql.tab.c"
    break;

  case 206: /* comOp: IS NOT  */
#line 1151 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = IS_NOT_OP; }
#line 3156 "yacc_sql.tab.c"
    break;

  case 207: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1156 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3165 "yacc_sql.tab.c"
    break;


#line 3169 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1161 "yacc_sql.y"

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
