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
  size_t attr_length;
  Selects sub_selects[MAX_NUM];
  size_t sub_select_num;
  Value set_values[MAX_NUM];
  size_t set_num;
  Conjunction conj[MAX_NUM];
  size_t conj_num;
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



#line 142 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_DATE_STR = 68,                  /* DATE_STR  */
  YYSYMBOL_ID = 69,                        /* ID  */
  YYSYMBOL_PATH = 70,                      /* PATH  */
  YYSYMBOL_SSS = 71,                       /* SSS  */
  YYSYMBOL_EXPRESSION = 72,                /* EXPRESSION  */
  YYSYMBOL_STAR = 73,                      /* STAR  */
  YYSYMBOL_STRING_V = 74,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command = 77,                   /* command  */
  YYSYMBOL_show_index = 78,                /* show_index  */
  YYSYMBOL_exit = 79,                      /* exit  */
  YYSYMBOL_help = 80,                      /* help  */
  YYSYMBOL_sync = 81,                      /* sync  */
  YYSYMBOL_begin = 82,                     /* begin  */
  YYSYMBOL_commit = 83,                    /* commit  */
  YYSYMBOL_rollback = 84,                  /* rollback  */
  YYSYMBOL_drop_table = 85,                /* drop_table  */
  YYSYMBOL_show_tables = 86,               /* show_tables  */
  YYSYMBOL_desc_table = 87,                /* desc_table  */
  YYSYMBOL_create_index = 88,              /* create_index  */
  YYSYMBOL_index_col_ID_list = 89,         /* index_col_ID_list  */
  YYSYMBOL_index_col_ID = 90,              /* index_col_ID  */
  YYSYMBOL_drop_index = 91,                /* drop_index  */
  YYSYMBOL_create_table = 92,              /* create_table  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_number = 95,                    /* number  */
  YYSYMBOL_type = 96,                      /* type  */
  YYSYMBOL_ID_get = 97,                    /* ID_get  */
  YYSYMBOL_insert = 98,                    /* insert  */
  YYSYMBOL_record_list = 99,               /* record_list  */
  YYSYMBOL_record = 100,                   /* record  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_set_value_list = 103,           /* set_value_list  */
  YYSYMBOL_sub_select = 104,               /* sub_select  */
  YYSYMBOL_sub_select_token = 105,         /* sub_select_token  */
  YYSYMBOL_sub_attr_list = 106,            /* sub_attr_list  */
  YYSYMBOL_sub_select_attr = 107,          /* sub_select_attr  */
  YYSYMBOL_sub_rel_list = 108,             /* sub_rel_list  */
  YYSYMBOL_sub_where = 109,                /* sub_where  */
  YYSYMBOL_sub_condition_list = 110,       /* sub_condition_list  */
  YYSYMBOL_type_conj = 111,                /* type_conj  */
  YYSYMBOL_sub_condition = 112,            /* sub_condition  */
  YYSYMBOL_delete = 113,                   /* delete  */
  YYSYMBOL_update = 114,                   /* update  */
  YYSYMBOL_update_set_list = 115,          /* update_set_list  */
  YYSYMBOL_update_set = 116,               /* update_set  */
  YYSYMBOL_select = 117,                   /* select  */
  YYSYMBOL_attr_list = 118,                /* attr_list  */
  YYSYMBOL_select_attr_or_expression = 119, /* select_attr_or_expression  */
  YYSYMBOL_select_attr = 120,              /* select_attr  */
  YYSYMBOL_aggop = 121,                    /* aggop  */
  YYSYMBOL_inner_join_list = 122,          /* inner_join_list  */
  YYSYMBOL_on = 123,                       /* on  */
  YYSYMBOL_rel_list = 124,                 /* rel_list  */
  YYSYMBOL_where = 125,                    /* where  */
  YYSYMBOL_condition_list = 126,           /* condition_list  */
  YYSYMBOL_condition = 127,                /* condition  */
  YYSYMBOL_value_or_expression = 128,      /* value_or_expression  */
  YYSYMBOL_group = 129,                    /* group  */
  YYSYMBOL_group_attr_list = 130,          /* group_attr_list  */
  YYSYMBOL_group_attr = 131,               /* group_attr  */
  YYSYMBOL_hc_list = 132,                  /* hc_list  */
  YYSYMBOL_having_condition = 133,         /* having_condition  */
  YYSYMBOL_order = 134,                    /* order  */
  YYSYMBOL_order_attr_list = 135,          /* order_attr_list  */
  YYSYMBOL_order_attr = 136,               /* order_attr  */
  YYSYMBOL_order_type = 137,               /* order_type  */
  YYSYMBOL_comOp = 138,                    /* comOp  */
  YYSYMBOL_load_data = 139                 /* load_data  */
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
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  350

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   170,   170,   172,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   197,   203,   208,   213,   219,   225,   231,   237,
     243,   249,   256,   262,   264,   267,   271,   277,   284,   293,
     295,   299,   310,   321,   332,   345,   348,   349,   350,   351,
     352,   356,   365,   372,   374,   376,   380,   385,   387,   389,
     392,   395,   398,   402,   406,   409,   419,   425,   427,   430,
     436,   442,   447,   449,   451,   457,   462,   467,   472,   477,
     482,   489,   491,   494,   498,   500,   505,   507,   513,   516,
     519,   524,   534,   542,   552,   561,   570,   580,   592,   602,
     611,   613,   615,   620,   626,   641,   643,   645,   650,   653,
     660,   665,   670,   675,   680,   685,   692,   695,   698,   701,
     704,   708,   710,   714,   716,   723,   725,   729,   731,   734,
     736,   740,   749,   758,   769,   779,   789,   800,   811,   820,
     831,   834,   840,   842,   844,   848,   850,   852,   856,   861,
     868,   870,   873,   878,   887,   896,   905,   914,   925,   927,
     930,   932,   934,   938,   943,   950,   953,   956,   960,   961,
     962,   963,   964,   965,   966,   967,   968,   969,   970,   971,
     972,   973,   977
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
  "HAVING", "IN", "EXISTS", "IS", "OR", "NUMBER", "FLOAT", "DATE_STR",
  "ID", "PATH", "SSS", "EXPRESSION", "STAR", "STRING_V", "$accept",
  "commands", "command", "show_index", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "index_col_ID_list", "index_col_ID", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "record_list", "record", "value_list", "value",
  "set_value_list", "sub_select", "sub_select_token", "sub_attr_list",
  "sub_select_attr", "sub_rel_list", "sub_where", "sub_condition_list",
  "type_conj", "sub_condition", "delete", "update", "update_set_list",
  "update_set", "select", "attr_list", "select_attr_or_expression",
  "select_attr", "aggop", "inner_join_list", "on", "rel_list", "where",
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
     325,   326,   327,   328,   329
};
#endif

#define YYPACT_NINF (-256)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-130)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -256,   274,  -256,   138,   211,    70,   -52,    71,    20,    15,
      68,   -15,   123,   135,   144,   167,   176,   100,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,  -256,    83,   113,   136,
     137,   291,  -256,  -256,  -256,  -256,  -256,   141,  -256,  -256,
     161,    70,  -256,   212,   226,   228,   201,  -256,   164,   165,
     215,  -256,  -256,  -256,  -256,  -256,   203,   234,   216,   249,
     250,    70,   200,   206,  -256,   116,  -256,  -256,   208,   251,
     248,    12,   219,   213,   223,  -256,  -256,  -256,  -256,   252,
       3,   282,   305,   207,    22,   306,   242,   279,   248,    12,
     292,  -256,   304,   238,   307,   278,   317,  -256,   267,  -256,
    -256,   -10,   321,   341,   207,  -256,  -256,    34,  -256,  -256,
      12,   205,   345,  -256,   343,   213,   330,  -256,  -256,  -256,
    -256,  -256,    99,    14,   281,   293,   248,   356,     0,   205,
    -256,  -256,  -256,  -256,  -256,   357,   -10,   207,  -256,  -256,
     298,   205,   263,  -256,  -256,    30,   326,  -256,  -256,  -256,
     311,   304,   372,   310,   322,  -256,   316,  -256,   367,    14,
     351,   317,   335,  -256,  -256,   205,   142,   379,   380,   149,
     -10,  -256,  -256,  -256,   205,  -256,   329,  -256,  -256,  -256,
    -256,  -256,  -256,    51,  -256,  -256,  -256,   346,    64,  -256,
      82,   396,  -256,  -256,  -256,   383,  -256,    14,   398,  -256,
      34,   252,  -256,   350,   352,   142,  -256,  -256,  -256,   115,
     376,  -256,   374,   149,   391,  -256,  -256,   326,  -256,  -256,
    -256,  -256,  -256,  -256,   381,  -256,  -256,  -256,  -256,  -256,
      30,  -256,    16,   355,   407,  -256,   149,   342,    23,  -256,
     134,   109,   347,  -256,   348,   384,   353,    16,    42,  -256,
    -256,  -256,   349,   317,   387,   166,   403,   393,  -256,  -256,
      16,   354,   265,  -256,   358,   117,  -256,    42,   317,  -256,
     -12,  -256,  -256,   359,  -256,   360,  -256,  -256,   344,   289,
     399,  -256,   265,    42,  -256,   361,  -256,  -256,  -256,  -256,
    -256,   171,   405,  -256,   265,   362,   205,   147,  -256,  -256,
      -3,   315,   326,   -12,  -256,  -256,   326,  -256,   174,   408,
    -256,   363,   177,   188,  -256,   205,   326,   364,   326,   326,
    -256,  -256,   406,  -256,  -256,   205,   409,   205,   199,   366,
    -256,   326,  -256,   410,  -256,  -256,   205,   368,  -256,  -256
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,    18,     0,     0,     0,
       0,     0,   116,   117,   118,   119,   120,   111,   109,   110,
       0,   105,   108,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
       0,   105,     0,     0,   107,     0,    31,    30,     0,     0,
     127,   100,     0,     0,     0,    29,    37,   106,   112,   121,
       0,     0,     0,    53,    88,     0,     0,     0,   127,   100,
       0,    51,    39,     0,     0,     0,   125,   114,     0,   113,
      22,    57,     0,     0,    53,    89,    90,     0,   128,    98,
     100,     0,     0,   101,     0,     0,     0,    46,    47,    48,
      49,    50,    42,    33,     0,     0,   127,     0,    67,     0,
      64,    60,    61,    62,    63,     0,    57,    53,    52,    55,
       0,     0,     0,   141,   140,    88,     0,   102,   103,    99,
       0,    39,     0,     0,     0,    44,     0,    36,     0,    33,
     123,   125,   142,   115,    71,     0,    67,     0,     0,    72,
      57,    56,    59,    54,     0,   138,     0,   168,   169,   170,
     171,   172,   173,     0,   174,   176,   178,   180,     0,   130,
       0,     0,    40,    38,    45,     0,    43,    33,     0,    34,
       0,   121,   126,     0,   158,    67,    68,    66,    65,     0,
      76,    75,     0,    72,     0,    58,   139,     0,   175,   177,
     179,   181,   133,   131,   134,   132,   182,    41,    35,    32,
      88,   122,   145,     0,     0,    69,    72,     0,    81,    74,
       0,     0,     0,   124,     0,   148,   143,   145,   160,   104,
      73,    77,     0,   125,    84,     0,     0,     0,   135,   136,
     145,     0,   150,   147,     0,   167,   159,   160,   125,    82,
      88,    70,    79,     0,    78,     0,   146,   149,     0,     0,
       0,   144,   150,   160,   166,     0,   165,   163,   162,    83,
      85,     0,     0,   137,   150,     0,     0,     0,   151,   161,
     167,     0,     0,    88,    80,   152,     0,   156,     0,     0,
     164,     0,     0,     0,    87,     0,     0,     0,     0,     0,
      93,    91,    94,    92,   157,     0,     0,     0,     0,     0,
     153,     0,   155,     0,    95,    96,     0,     0,   154,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,   -83,   258,  -256,  -256,   275,   314,
    -256,  -256,  -256,  -256,  -101,   328,  -135,  -111,  -164,  -256,
    -256,  -209,   222,  -256,  -256,   129,  -173,  -256,  -256,  -256,
     -84,   365,  -256,   -32,   402,  -256,  -176,   233,  -256,  -169,
      -7,  -151,   235,  -174,  -256,  -228,   192,  -182,   159,  -256,
    -255,   175,   140,  -155,  -256
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   168,   169,    30,    31,   126,   102,
     205,   132,   103,    32,   113,   114,   145,   154,   177,   178,
     179,   222,   223,   264,   281,   300,   117,   313,    33,    34,
      98,    99,    35,    50,    51,    52,    53,   106,   211,   136,
      95,   118,   155,   156,   214,   256,   257,   291,   292,   244,
     276,   277,   297,   198,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     146,   200,   212,   224,   199,   -86,   138,   294,   139,   174,
     158,   182,   216,   149,   249,   123,   138,    54,   175,    74,
     107,   115,   298,    57,   233,  -129,   235,   176,   180,   273,
      96,   108,   166,  -129,   254,   146,   157,   260,   309,    87,
     185,   262,   286,   224,    58,   225,   183,   224,  -129,   140,
     138,   245,   296,   116,    60,   115,   141,   142,   143,   140,
     274,   144,  -129,   115,   215,   176,   141,   142,   143,   146,
     224,   144,   251,   226,  -129,  -129,  -129,   268,    55,    56,
     138,    97,  -129,   167,  -129,   255,   209,   116,    41,   253,
     150,   122,   263,   140,   279,   116,   290,   151,   138,    59,
     141,   142,   143,   152,   176,   144,   153,   301,   228,   299,
     308,   275,   290,   229,   230,   163,   290,    42,    43,    44,
      45,    46,   315,   140,   238,   138,    61,   294,   290,   172,
     141,   142,   143,   232,   306,   144,   153,    66,    62,    47,
     301,   140,    48,    49,    37,   295,    38,    63,   141,   142,
     143,   234,    67,   144,   153,   164,   322,   323,   138,   165,
     175,   325,    42,    43,    44,    45,    46,   219,   140,    72,
      64,   335,   296,   337,   338,   141,   142,   143,   267,    65,
     144,   153,    68,   282,   220,    90,   346,   138,   221,    91,
     312,   326,    73,   138,   283,   317,    42,    43,    44,    45,
      46,   140,   327,   265,   138,    69,    70,   266,   141,   142,
     143,   331,   333,   144,   334,   138,   318,    39,   220,    40,
     319,   138,   221,   111,   340,   112,   342,   344,    75,    76,
     140,    77,    78,    79,    80,   348,   140,   141,   142,   143,
     311,    82,   144,   141,   142,   143,   330,   140,   144,    81,
      83,    84,    85,    86,   141,   142,   143,   332,   140,   144,
     127,   128,   129,   130,   140,   141,   142,   143,   343,    88,
     144,   141,   142,   143,     2,    89,   144,    92,     3,     4,
      94,    93,   101,     5,     6,     7,     8,     9,    10,    11,
     100,   186,   104,    12,    13,    14,   131,   105,   288,   109,
      15,    16,   187,   188,   189,   190,   191,   192,   110,   119,
      17,    97,    42,    43,    44,    45,    46,   305,   121,   193,
     194,   124,   125,   133,   134,   195,   196,   197,   187,   188,
     189,   190,   191,   192,   289,   135,   137,   111,    42,    43,
      44,    45,    46,   321,   148,   193,   194,   162,   159,   160,
     170,   195,   196,   197,   187,   188,   189,   190,   191,   192,
      47,   184,   171,    48,    49,   187,   188,   189,   190,   191,
     192,   193,   194,   173,   181,   203,   204,   195,   196,   197,
     201,   206,   193,   194,   208,   167,   210,   213,   195,   196,
     197,    42,    43,    44,    45,    46,   217,   218,   227,   236,
     237,   239,   231,   242,   247,   248,   243,   250,   258,   252,
     259,   261,   271,   289,   272,   307,   269,   255,   278,   280,
     284,   285,   314,   287,   207,   328,   341,   275,   302,   303,
     310,   316,   329,   336,   339,   345,   202,   349,   347,   161,
     147,   246,   324,    71,   241,   240,   270,   304,     0,   293,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120
};

static const yytype_int16 yycheck[] =
{
     111,   156,   171,   179,   155,    17,    16,    10,    18,     9,
     121,   146,   176,   114,   223,    99,    16,    69,    18,    51,
      17,    33,   277,     3,   198,     3,   200,   138,   139,   257,
      18,    28,    18,     3,    18,   146,   120,   246,   293,    71,
     151,    18,   270,   219,    29,   180,   147,   223,    18,    59,
      16,   215,    55,    65,    69,    33,    66,    67,    68,    59,
      18,    71,    32,    33,   175,   176,    66,    67,    68,   180,
     246,    71,   227,   184,    52,    45,    54,   251,     7,     8,
      16,    69,    52,    69,    54,    69,   169,    65,    18,   240,
      56,    98,    69,    59,   263,    65,   272,    63,    16,    31,
      66,    67,    68,    69,   215,    71,    72,   280,    57,   278,
     292,    69,   288,    62,    63,    16,   292,    47,    48,    49,
      50,    51,   304,    59,   207,    16,     3,    10,   304,   136,
      66,    67,    68,    69,   289,    71,    72,    37,     3,    69,
     313,    59,    72,    73,     6,    28,     8,     3,    66,    67,
      68,    69,    69,    71,    72,    56,   311,   312,    16,    60,
      18,   316,    47,    48,    49,    50,    51,    18,    59,    28,
       3,   326,    55,   328,   329,    66,    67,    68,    69,     3,
      71,    72,    69,    17,    69,    69,   341,    16,    73,    73,
     301,    17,    31,    16,    28,   306,    47,    48,    49,    50,
      51,    59,    28,    69,    16,    69,    69,    73,    66,    67,
      68,   322,   323,    71,   325,    16,    69,     6,    69,     8,
      73,    16,    73,    16,   335,    18,   337,   338,    16,     3,
      59,     3,    31,    69,    69,   346,    59,    66,    67,    68,
      69,    38,    71,    66,    67,    68,    69,    59,    71,    34,
      16,    35,     3,     3,    66,    67,    68,    69,    59,    71,
      22,    23,    24,    25,    59,    66,    67,    68,    69,    69,
      71,    66,    67,    68,     0,    69,    71,    69,     4,     5,
      32,    30,    69,     9,    10,    11,    12,    13,    14,    15,
      71,    28,    69,    19,    20,    21,    58,    45,    33,    17,
      26,    27,    39,    40,    41,    42,    43,    44,     3,     3,
      36,    69,    47,    48,    49,    50,    51,    28,    39,    56,
      57,    29,    18,    16,    46,    62,    63,    64,    39,    40,
      41,    42,    43,    44,    69,    18,    69,    16,    47,    48,
      49,    50,    51,    28,     3,    56,    57,    17,     3,     6,
      69,    62,    63,    64,    39,    40,    41,    42,    43,    44,
      69,    63,    69,    72,    73,    39,    40,    41,    42,    43,
      44,    56,    57,    17,    17,     3,    66,    62,    63,    64,
      69,    59,    56,    57,    17,    69,    35,    52,    62,    63,
      64,    47,    48,    49,    50,    51,    17,    17,    69,     3,
      17,     3,    56,    53,    28,    31,    54,    16,    53,    28,
       3,    69,    28,    69,    61,    16,    69,    69,    69,    32,
      17,    28,    17,    69,   166,    17,    17,    69,    69,    69,
      69,    69,    69,    69,    28,    69,   161,    69,    28,   125,
     112,   219,   313,    41,   211,   210,   254,   288,    -1,   274,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      91,    92,    98,   113,   114,   117,   139,     6,     8,     6,
       8,    18,    47,    48,    49,    50,    51,    69,    72,    73,
     118,   119,   120,   121,    69,     7,     8,     3,    29,    31,
      69,     3,     3,     3,     3,     3,    37,    69,    69,    69,
      69,   119,    28,    31,   118,    16,     3,     3,    31,    69,
      69,    34,    38,    16,    35,     3,     3,   118,    69,    69,
      69,    73,    69,    30,    32,   125,    18,    69,   115,   116,
      71,    69,    94,    97,    69,    45,   122,    17,    28,    17,
       3,    16,    18,    99,   100,    33,    65,   111,   126,     3,
     116,    39,   125,   115,    29,    18,    93,    22,    23,    24,
      25,    58,    96,    16,    46,    18,   124,    69,    16,    18,
      59,    66,    67,    68,    71,   101,   102,   100,     3,    99,
      56,    63,    69,    72,   102,   127,   128,   115,   102,     3,
       6,    94,    17,    16,    56,    60,    18,    69,    89,    90,
      69,    69,   125,    17,     9,    18,   102,   103,   104,   105,
     102,    17,   101,    99,    63,   102,    28,    39,    40,    41,
      42,    43,    44,    56,    57,    62,    63,    64,   138,   126,
     138,    69,    93,     3,    66,    95,    59,    90,    17,    89,
      35,   123,   124,    52,   129,   102,   103,    17,    17,    18,
      69,    73,   106,   107,   121,   101,   102,    69,    57,    62,
      63,    56,    69,   128,    69,   128,     3,    17,    89,     3,
     127,   122,    53,    54,   134,   103,   107,    28,    31,   106,
      16,   138,    28,   126,    18,    69,   130,   131,    53,     3,
     106,    69,    18,    69,   108,    69,    73,    69,   128,    69,
     131,    28,    61,   130,    18,    69,   135,   136,    69,   124,
      32,   109,    17,    28,    17,    28,   130,    69,    33,    69,
     121,   132,   133,   136,    10,    28,    55,   137,   135,   124,
     110,   111,    69,    69,   133,    28,   138,    16,   132,   135,
      69,    69,   102,   112,    17,   132,    69,   102,    69,    73,
     137,    28,   138,   138,   110,   138,    17,    28,    17,    69,
      69,   102,    69,   102,   102,   138,    69,   138,   138,    28,
     102,    17,   102,    69,   102,    69,   138,    28,   102,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    89,    89,    90,    91,    92,    93,
      93,    94,    94,    94,    94,    95,    96,    96,    96,    96,
      96,    97,    98,    99,    99,    99,   100,   101,   101,   101,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   103,
     104,   105,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   108,   108,   108,   109,   109,   110,   110,   111,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   113,   114,
     115,   115,   115,   116,   117,   118,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   120,   121,   121,   121,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   128,   129,   129,   129,   130,   130,   130,   131,   131,
     132,   132,   132,   133,   133,   133,   133,   133,   134,   134,
     135,   135,   135,   136,   136,   137,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     2,     2,     2,     2,     2,     4,
       3,     3,     9,     0,     2,     3,     1,     4,     8,     0,
       3,     5,     2,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     6,     0,     3,     2,     3,     0,     3,     2,
       1,     1,     1,     1,     1,     3,     3,     0,     2,     3,
       5,     1,     0,     3,     2,     1,     1,     3,     4,     4,
       6,     0,     2,     3,     0,     2,     0,     3,     0,     1,
       1,     3,     3,     3,     3,     5,     5,     7,     5,     6,
       0,     2,     3,     3,    10,     0,     3,     2,     1,     1,
       1,     1,     3,     4,     4,     6,     1,     1,     1,     1,
       1,     0,     5,     0,     3,     0,     3,     0,     2,     0,
       3,     3,     3,     3,     3,     5,     5,     7,     2,     3,
       1,     1,     0,     3,     5,     0,     3,     2,     1,     3,
       0,     2,     3,     6,     8,     6,     3,     5,     0,     3,
       0,     3,     2,     2,     4,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
       1,     2,     8
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
  case 22: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 197 "yacc_sql.y"
                                 {
	CONTEXT->ssql->flag=SCF_SHOW_INDEX;
	show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1555 "yacc_sql.tab.c"
    break;

  case 23: /* exit: EXIT SEMICOLON  */
#line 203 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1563 "yacc_sql.tab.c"
    break;

  case 24: /* help: HELP SEMICOLON  */
#line 208 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1571 "yacc_sql.tab.c"
    break;

  case 25: /* sync: SYNC SEMICOLON  */
#line 213 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1579 "yacc_sql.tab.c"
    break;

  case 26: /* begin: TRX_BEGIN SEMICOLON  */
#line 219 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1587 "yacc_sql.tab.c"
    break;

  case 27: /* commit: TRX_COMMIT SEMICOLON  */
#line 225 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1595 "yacc_sql.tab.c"
    break;

  case 28: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 231 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1603 "yacc_sql.tab.c"
    break;

  case 29: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 237 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1612 "yacc_sql.tab.c"
    break;

  case 30: /* show_tables: SHOW TABLES SEMICOLON  */
#line 243 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1620 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 249 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1629 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE index_col_ID_list RBRACE SEMICOLON  */
#line 257 "yacc_sql.y"
    {
	CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
	create_index_multi_rel_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string));
    }
#line 1638 "yacc_sql.tab.c"
    break;

  case 34: /* index_col_ID_list: index_col_ID index_col_ID_list  */
#line 264 "yacc_sql.y"
                                     {

    }
#line 1646 "yacc_sql.tab.c"
    break;

  case 35: /* index_col_ID_list: COMMA index_col_ID index_col_ID_list  */
#line 267 "yacc_sql.y"
                                           {
    }
#line 1653 "yacc_sql.tab.c"
    break;

  case 36: /* index_col_ID: ID  */
#line 271 "yacc_sql.y"
       {
    	create_index_append_attr_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1661 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 278 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1670 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 285 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1682 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 295 "yacc_sql.y"
                                   {    }
#line 1688 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 300 "yacc_sql.y"
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
#line 1703 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 311 "yacc_sql.y"
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
#line 1718 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 322 "yacc_sql.y"
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
#line 1733 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 333 "yacc_sql.y"
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
#line 1748 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 345 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1754 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 348 "yacc_sql.y"
              { (yyval.number)=INTS; CONTEXT->attr_length = 4; }
#line 1760 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 349 "yacc_sql.y"
                  { (yyval.number)=CHARS; CONTEXT->attr_length = 40; }
#line 1766 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 350 "yacc_sql.y"
                 { (yyval.number)=FLOATS; CONTEXT->attr_length = 4; }
#line 1772 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 351 "yacc_sql.y"
                { (yyval.number)=DATES; CONTEXT->attr_length = 4; }
#line 1778 "yacc_sql.tab.c"
    break;

  case 50: /* type: TEXT_T  */
#line 352 "yacc_sql.y"
                { (yyval.number)=TEXTS; CONTEXT->attr_length = 4096; }
#line 1784 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 357 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1793 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES record_list SEMICOLON  */
#line 366 "yacc_sql.y"
    {
      CONTEXT->ssql->flag=SCF_INSERT;//"insert";
      inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-3].string), CONTEXT->records, CONTEXT->record_length);
      //临时变量清零
      CONTEXT->record_length = 0;
    }
#line 1804 "yacc_sql.tab.c"
    break;

  case 54: /* record_list: COMMA record record_list  */
#line 374 "yacc_sql.y"
                               {
    }
#line 1811 "yacc_sql.tab.c"
    break;

  case 55: /* record_list: record record_list  */
#line 376 "yacc_sql.y"
                         {
    }
#line 1818 "yacc_sql.tab.c"
    break;

  case 56: /* record: LBRACE value_list RBRACE  */
#line 380 "yacc_sql.y"
                             {
    	insert_record_init(&CONTEXT->records[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
    	CONTEXT->value_length=0;
    }
#line 1827 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 387 "yacc_sql.y"
                              {
    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: value value_list  */
#line 389 "yacc_sql.y"
                       {
    }
#line 1841 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 392 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
    }
#line 1849 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 395 "yacc_sql.y"
           {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
    }
#line 1857 "yacc_sql.tab.c"
    break;

  case 62: /* value: DATE_STR  */
#line 398 "yacc_sql.y"
              {
    		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1866 "yacc_sql.tab.c"
    break;

  case 63: /* value: SSS  */
#line 402 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1875 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULL_TOKEN  */
#line 406 "yacc_sql.y"
                {
    		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1883 "yacc_sql.tab.c"
    break;

  case 65: /* value: LBRACE sub_select RBRACE  */
#line 409 "yacc_sql.y"
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
#line 1898 "yacc_sql.tab.c"
    break;

  case 66: /* value: LBRACE set_value_list RBRACE  */
#line 419 "yacc_sql.y"
                                   {
	value_init_set(&CONTEXT->values[CONTEXT->value_length++], CONTEXT->set_values, CONTEXT->set_num);
	CONTEXT->set_num = 0;
    }
#line 1907 "yacc_sql.tab.c"
    break;

  case 68: /* set_value_list: value set_value_list  */
#line 427 "yacc_sql.y"
                           {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 1915 "yacc_sql.tab.c"
    break;

  case 69: /* set_value_list: COMMA value set_value_list  */
#line 430 "yacc_sql.y"
                                 {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 1923 "yacc_sql.tab.c"
    break;

  case 70: /* sub_select: sub_select_token sub_attr_list FROM sub_rel_list sub_where  */
#line 436 "yacc_sql.y"
                                                               {

    }
#line 1931 "yacc_sql.tab.c"
    break;

  case 71: /* sub_select_token: SELECT  */
#line 442 "yacc_sql.y"
           {
	CONTEXT->sub_select_num++;
    }
#line 1939 "yacc_sql.tab.c"
    break;

  case 73: /* sub_attr_list: COMMA sub_select_attr sub_attr_list  */
#line 449 "yacc_sql.y"
                                          {
    }
#line 1946 "yacc_sql.tab.c"
    break;

  case 74: /* sub_attr_list: sub_select_attr sub_attr_list  */
#line 451 "yacc_sql.y"
                                    {

    }
#line 1954 "yacc_sql.tab.c"
    break;

  case 75: /* sub_select_attr: STAR  */
#line 457 "yacc_sql.y"
         {
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1964 "yacc_sql.tab.c"
    break;

  case 76: /* sub_select_attr: ID  */
#line 462 "yacc_sql.y"
         {
        RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1974 "yacc_sql.tab.c"
    break;

  case 77: /* sub_select_attr: ID DOT ID  */
#line 467 "yacc_sql.y"
                {
        RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1984 "yacc_sql.tab.c"
    break;

  case 78: /* sub_select_attr: aggop LBRACE STAR RBRACE  */
#line 472 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1994 "yacc_sql.tab.c"
    break;

  case 79: /* sub_select_attr: aggop LBRACE ID RBRACE  */
#line 477 "yacc_sql.y"
                             {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2004 "yacc_sql.tab.c"
    break;

  case 80: /* sub_select_attr: aggop LBRACE ID DOT ID RBRACE  */
#line 482 "yacc_sql.y"
                                    {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2014 "yacc_sql.tab.c"
    break;

  case 82: /* sub_rel_list: ID rel_list  */
#line 491 "yacc_sql.y"
                  {
	selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-1].string));
    }
#line 2022 "yacc_sql.tab.c"
    break;

  case 83: /* sub_rel_list: COMMA ID rel_list  */
#line 494 "yacc_sql.y"
                        {
    	selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-1].string));
    }
#line 2030 "yacc_sql.tab.c"
    break;

  case 85: /* sub_where: WHERE sub_condition_list  */
#line 500 "yacc_sql.y"
                               {
	printf("2\n");
    }
#line 2038 "yacc_sql.tab.c"
    break;

  case 87: /* sub_condition_list: type_conj sub_condition sub_condition_list  */
#line 507 "yacc_sql.y"
                                                 {

    }
#line 2046 "yacc_sql.tab.c"
    break;

  case 88: /* type_conj: %empty  */
#line 513 "yacc_sql.y"
                {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_FIRST;
    }
#line 2054 "yacc_sql.tab.c"
    break;

  case 89: /* type_conj: AND  */
#line 516 "yacc_sql.y"
          {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_AND;
    }
#line 2062 "yacc_sql.tab.c"
    break;

  case 90: /* type_conj: OR  */
#line 519 "yacc_sql.y"
         {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_OR;
    }
#line 2070 "yacc_sql.tab.c"
    break;

  case 91: /* sub_condition: ID comOp value  */
#line 525 "yacc_sql.y"
    {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	// printf("CONTEXT->sub_select_num: %d\n", CONTEXT->sub_select_num);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2084 "yacc_sql.tab.c"
    break;

  case 92: /* sub_condition: value comOp value  */
#line 534 "yacc_sql.y"
                       {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2097 "yacc_sql.tab.c"
    break;

  case 93: /* sub_condition: ID comOp ID  */
#line 542 "yacc_sql.y"
                 {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 94: /* sub_condition: value comOp ID  */
#line 552 "yacc_sql.y"
                    {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2126 "yacc_sql.tab.c"
    break;

  case 95: /* sub_condition: ID DOT ID comOp value  */
#line 561 "yacc_sql.y"
                           {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2140 "yacc_sql.tab.c"
    break;

  case 96: /* sub_condition: value comOp ID DOT ID  */
#line 570 "yacc_sql.y"
                           {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2155 "yacc_sql.tab.c"
    break;

  case 97: /* sub_condition: ID DOT ID comOp ID DOT ID  */
#line 580 "yacc_sql.y"
                               {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2169 "yacc_sql.tab.c"
    break;

  case 98: /* delete: DELETE FROM ID where SEMICOLON  */
#line 593 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2181 "yacc_sql.tab.c"
    break;

  case 99: /* update: UPDATE ID SET update_set_list where SEMICOLON  */
#line 603 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string),
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2192 "yacc_sql.tab.c"
    break;

  case 101: /* update_set_list: update_set update_set_list  */
#line 613 "yacc_sql.y"
                                 {
    }
#line 2199 "yacc_sql.tab.c"
    break;

  case 102: /* update_set_list: COMMA update_set update_set_list  */
#line 615 "yacc_sql.y"
                                       {
    }
#line 2206 "yacc_sql.tab.c"
    break;

  case 103: /* update_set: ID EQ value  */
#line 620 "yacc_sql.y"
                {
        Value *value = &CONTEXT->values[--CONTEXT->value_length];
    	updates_append_attr_and_value(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), value);
    }
#line 2215 "yacc_sql.tab.c"
    break;

  case 104: /* select: SELECT attr_list FROM ID inner_join_list rel_list where group order SEMICOLON  */
#line 627 "yacc_sql.y"
    {
	// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
	selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string));
	selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
	CONTEXT->ssql->flag=SCF_SELECT;//"select";
	// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;
	//临时变量清零
	CONTEXT->condition_length=0;
	CONTEXT->from_length=0;
	CONTEXT->select_length=0;
	CONTEXT->value_length = 0;
    }
#line 2232 "yacc_sql.tab.c"
    break;

  case 106: /* attr_list: COMMA select_attr_or_expression attr_list  */
#line 643 "yacc_sql.y"
                                                {
    }
#line 2239 "yacc_sql.tab.c"
    break;

  case 107: /* attr_list: select_attr_or_expression attr_list  */
#line 645 "yacc_sql.y"
                                          {
    }
#line 2246 "yacc_sql.tab.c"
    break;

  case 108: /* select_attr_or_expression: select_attr  */
#line 650 "yacc_sql.y"
                {

    }
#line 2254 "yacc_sql.tab.c"
    break;

  case 109: /* select_attr_or_expression: EXPRESSION  */
#line 653 "yacc_sql.y"
                 {
    	RelAttr attr;
    	relation_attr_exp_init(&attr, (yyvsp[0].string));
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2264 "yacc_sql.tab.c"
    break;

  case 110: /* select_attr: STAR  */
#line 660 "yacc_sql.y"
         {  
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2274 "yacc_sql.tab.c"
    break;

  case 111: /* select_attr: ID  */
#line 665 "yacc_sql.y"
         {
        RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2284 "yacc_sql.tab.c"
    break;

  case 112: /* select_attr: ID DOT ID  */
#line 670 "yacc_sql.y"
                {
        RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2294 "yacc_sql.tab.c"
    break;

  case 113: /* select_attr: aggop LBRACE STAR RBRACE  */
#line 675 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 114: /* select_attr: aggop LBRACE ID RBRACE  */
#line 680 "yacc_sql.y"
                             {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2314 "yacc_sql.tab.c"
    break;

  case 115: /* select_attr: aggop LBRACE ID DOT ID RBRACE  */
#line 685 "yacc_sql.y"
                                    {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 116: /* aggop: MAX  */
#line 692 "yacc_sql.y"
        {
	CONTEXT->agg_type = AGG_MAX;
    }
#line 2332 "yacc_sql.tab.c"
    break;

  case 117: /* aggop: MIN  */
#line 695 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_MIN;
    }
#line 2340 "yacc_sql.tab.c"
    break;

  case 118: /* aggop: COUNT  */
#line 698 "yacc_sql.y"
            {
	CONTEXT->agg_type = AGG_COUNT;
    }
#line 2348 "yacc_sql.tab.c"
    break;

  case 119: /* aggop: AVG  */
#line 701 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_AVG;
    }
#line 2356 "yacc_sql.tab.c"
    break;

  case 120: /* aggop: SUM  */
#line 704 "yacc_sql.y"
          {
    	CONTEXT->agg_type = AGG_SUM;
    }
#line 2364 "yacc_sql.tab.c"
    break;

  case 122: /* inner_join_list: INNER JOIN ID on inner_join_list  */
#line 710 "yacc_sql.y"
                                       {
	selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 2372 "yacc_sql.tab.c"
    break;

  case 124: /* on: ON condition condition_list  */
#line 716 "yacc_sql.y"
                                  {
	// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
    }
#line 2380 "yacc_sql.tab.c"
    break;

  case 126: /* rel_list: COMMA ID rel_list  */
#line 725 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2388 "yacc_sql.tab.c"
    break;

  case 128: /* where: WHERE condition_list  */
#line 731 "yacc_sql.y"
                           {
    }
#line 2395 "yacc_sql.tab.c"
    break;

  case 130: /* condition_list: type_conj condition condition_list  */
#line 736 "yacc_sql.y"
                                         {
    }
#line 2402 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID comOp value_or_expression  */
#line 741 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2415 "yacc_sql.tab.c"
    break;

  case 132: /* condition: value_or_expression comOp value_or_expression  */
#line 750 "yacc_sql.y"
    {
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2428 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID comOp ID  */
#line 759 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2443 "yacc_sql.tab.c"
    break;

  case 134: /* condition: value_or_expression comOp ID  */
#line 770 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2457 "yacc_sql.tab.c"
    break;

  case 135: /* condition: ID DOT ID comOp value_or_expression  */
#line 780 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2471 "yacc_sql.tab.c"
    break;

  case 136: /* condition: value_or_expression comOp ID DOT ID  */
#line 790 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2486 "yacc_sql.tab.c"
    break;

  case 137: /* condition: ID DOT ID comOp ID DOT ID  */
#line 801 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2500 "yacc_sql.tab.c"
    break;

  case 138: /* condition: EXISTS value  */
#line 811 "yacc_sql.y"
                   {
	Value left_value;
	value_init_integer(&left_value, 0);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2514 "yacc_sql.tab.c"
    break;

  case 139: /* condition: NOT EXISTS value  */
#line 820 "yacc_sql.y"
                       {
    	Value left_value;
        value_init_integer(&left_value, 0);
    	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

    	Condition condition;
    	condition_conj_init(&condition, NOT_EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2528 "yacc_sql.tab.c"
    break;

  case 140: /* value_or_expression: value  */
#line 831 "yacc_sql.y"
          {

    }
#line 2536 "yacc_sql.tab.c"
    break;

  case 141: /* value_or_expression: EXPRESSION  */
#line 834 "yacc_sql.y"
                 {
	// $1 = substr($1,1,strlen($1)-2);
	value_init_expression(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 2545 "yacc_sql.tab.c"
    break;

  case 143: /* group: GROUP BY group_attr_list  */
#line 842 "yacc_sql.y"
                               {
    }
#line 2552 "yacc_sql.tab.c"
    break;

  case 144: /* group: GROUP BY group_attr_list HAVING hc_list  */
#line 844 "yacc_sql.y"
                                              {

    }
#line 2560 "yacc_sql.tab.c"
    break;

  case 146: /* group_attr_list: COMMA group_attr group_attr_list  */
#line 850 "yacc_sql.y"
                                       {
    }
#line 2567 "yacc_sql.tab.c"
    break;

  case 147: /* group_attr_list: group_attr group_attr_list  */
#line 852 "yacc_sql.y"
                                 {
    }
#line 2574 "yacc_sql.tab.c"
    break;

  case 148: /* group_attr: ID  */
#line 856 "yacc_sql.y"
       {
        GroupAttr group_attr;
	group_attr_init(&group_attr, NULL, (yyvsp[0].string));
	group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2584 "yacc_sql.tab.c"
    break;

  case 149: /* group_attr: ID DOT ID  */
#line 861 "yacc_sql.y"
                {
        GroupAttr group_attr;
        group_attr_init(&group_attr, (yyvsp[-2].string), (yyvsp[0].string));
        group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2594 "yacc_sql.tab.c"
    break;

  case 151: /* hc_list: having_condition hc_list  */
#line 870 "yacc_sql.y"
                               {

    }
#line 2602 "yacc_sql.tab.c"
    break;

  case 152: /* hc_list: AND having_condition hc_list  */
#line 873 "yacc_sql.y"
                                   {
    }
#line 2609 "yacc_sql.tab.c"
    break;

  case 153: /* having_condition: aggop LBRACE ID RBRACE comOp value  */
#line 878 "yacc_sql.y"
                                       {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2623 "yacc_sql.tab.c"
    break;

  case 154: /* having_condition: aggop LBRACE ID DOT ID RBRACE comOp value  */
#line 887 "yacc_sql.y"
                                                {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2637 "yacc_sql.tab.c"
    break;

  case 155: /* having_condition: aggop LBRACE STAR RBRACE comOp value  */
#line 896 "yacc_sql.y"
                                           {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, "*", CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2651 "yacc_sql.tab.c"
    break;

  case 156: /* having_condition: ID comOp value  */
#line 905 "yacc_sql.y"
                     {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2665 "yacc_sql.tab.c"
    break;

  case 157: /* having_condition: ID DOT ID comOp value  */
#line 914 "yacc_sql.y"
                            {
        RelAttr left_attr;
        relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2679 "yacc_sql.tab.c"
    break;

  case 159: /* order: ORDER BY order_attr_list  */
#line 927 "yacc_sql.y"
                               {
    }
#line 2686 "yacc_sql.tab.c"
    break;

  case 161: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 932 "yacc_sql.y"
                                       {
    }
#line 2693 "yacc_sql.tab.c"
    break;

  case 162: /* order_attr_list: order_attr order_attr_list  */
#line 934 "yacc_sql.y"
                                 {
    }
#line 2700 "yacc_sql.tab.c"
    break;

  case 163: /* order_attr: ID order_type  */
#line 938 "yacc_sql.y"
                  {
        OrderAttr order_attr;
	order_attr_init(&order_attr, NULL, (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2710 "yacc_sql.tab.c"
    break;

  case 164: /* order_attr: ID DOT ID order_type  */
#line 943 "yacc_sql.y"
                           {
        OrderAttr order_attr;
	order_attr_init(&order_attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2720 "yacc_sql.tab.c"
    break;

  case 165: /* order_type: ASC  */
#line 950 "yacc_sql.y"
        {
    	CONTEXT->order_type = OrderAsc;
    }
#line 2728 "yacc_sql.tab.c"
    break;

  case 166: /* order_type: DESC  */
#line 953 "yacc_sql.y"
           {
    	CONTEXT->order_type = OrderDesc;
    }
#line 2736 "yacc_sql.tab.c"
    break;

  case 167: /* order_type: %empty  */
#line 956 "yacc_sql.y"
                  {
    	CONTEXT->order_type = OrderAsc;
    }
#line 2744 "yacc_sql.tab.c"
    break;

  case 168: /* comOp: EQ  */
#line 960 "yacc_sql.y"
       { CONTEXT->comps[CONTEXT->comp_num++] = EQUAL_TO; }
#line 2750 "yacc_sql.tab.c"
    break;

  case 169: /* comOp: LT  */
#line 961 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_THAN; }
#line 2756 "yacc_sql.tab.c"
    break;

  case 170: /* comOp: GT  */
#line 962 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_THAN; }
#line 2762 "yacc_sql.tab.c"
    break;

  case 171: /* comOp: LE  */
#line 963 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_EQUAL; }
#line 2768 "yacc_sql.tab.c"
    break;

  case 172: /* comOp: GE  */
#line 964 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_EQUAL; }
#line 2774 "yacc_sql.tab.c"
    break;

  case 173: /* comOp: NE  */
#line 965 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EQUAL; }
#line 2780 "yacc_sql.tab.c"
    break;

  case 174: /* comOp: LIKE  */
#line 966 "yacc_sql.y"
           { CONTEXT->comps[CONTEXT->comp_num++] = LIKE_TO; }
#line 2786 "yacc_sql.tab.c"
    break;

  case 175: /* comOp: NOT LIKE  */
#line 967 "yacc_sql.y"
               { CONTEXT->comps[CONTEXT->comp_num++] = NOT_LIKE_TO; }
#line 2792 "yacc_sql.tab.c"
    break;

  case 176: /* comOp: IN  */
#line 968 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IN_OP; }
#line 2798 "yacc_sql.tab.c"
    break;

  case 177: /* comOp: NOT IN  */
#line 969 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = NOT_IN_OP; }
#line 2804 "yacc_sql.tab.c"
    break;

  case 178: /* comOp: EXISTS  */
#line 970 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = EXISTS_OP; }
#line 2810 "yacc_sql.tab.c"
    break;

  case 179: /* comOp: NOT EXISTS  */
#line 971 "yacc_sql.y"
                 { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EXISTS_OP; }
#line 2816 "yacc_sql.tab.c"
    break;

  case 180: /* comOp: IS  */
#line 972 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IS_OP; }
#line 2822 "yacc_sql.tab.c"
    break;

  case 181: /* comOp: IS NOT  */
#line 973 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = IS_NOT_OP; }
#line 2828 "yacc_sql.tab.c"
    break;

  case 182: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 978 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2837 "yacc_sql.tab.c"
    break;


#line 2841 "yacc_sql.tab.c"

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

#line 983 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
