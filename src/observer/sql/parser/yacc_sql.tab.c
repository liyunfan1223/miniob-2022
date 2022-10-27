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
  YYSYMBOL_STAR = 72,                      /* STAR  */
  YYSYMBOL_STRING_V = 73,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_show_index = 77,                /* show_index  */
  YYSYMBOL_exit = 78,                      /* exit  */
  YYSYMBOL_help = 79,                      /* help  */
  YYSYMBOL_sync = 80,                      /* sync  */
  YYSYMBOL_begin = 81,                     /* begin  */
  YYSYMBOL_commit = 82,                    /* commit  */
  YYSYMBOL_rollback = 83,                  /* rollback  */
  YYSYMBOL_drop_table = 84,                /* drop_table  */
  YYSYMBOL_show_tables = 85,               /* show_tables  */
  YYSYMBOL_desc_table = 86,                /* desc_table  */
  YYSYMBOL_create_index = 87,              /* create_index  */
  YYSYMBOL_index_col_ID_list = 88,         /* index_col_ID_list  */
  YYSYMBOL_index_col_ID = 89,              /* index_col_ID  */
  YYSYMBOL_drop_index = 90,                /* drop_index  */
  YYSYMBOL_create_table = 91,              /* create_table  */
  YYSYMBOL_attr_def_list = 92,             /* attr_def_list  */
  YYSYMBOL_attr_def = 93,                  /* attr_def  */
  YYSYMBOL_number = 94,                    /* number  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_ID_get = 96,                    /* ID_get  */
  YYSYMBOL_insert = 97,                    /* insert  */
  YYSYMBOL_record_list = 98,               /* record_list  */
  YYSYMBOL_record = 99,                    /* record  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_set_value_list = 102,           /* set_value_list  */
  YYSYMBOL_sub_select = 103,               /* sub_select  */
  YYSYMBOL_sub_select_token = 104,         /* sub_select_token  */
  YYSYMBOL_sub_attr_list = 105,            /* sub_attr_list  */
  YYSYMBOL_sub_select_attr = 106,          /* sub_select_attr  */
  YYSYMBOL_sub_rel_list = 107,             /* sub_rel_list  */
  YYSYMBOL_sub_where = 108,                /* sub_where  */
  YYSYMBOL_sub_condition_list = 109,       /* sub_condition_list  */
  YYSYMBOL_type_conj = 110,                /* type_conj  */
  YYSYMBOL_sub_condition = 111,            /* sub_condition  */
  YYSYMBOL_delete = 112,                   /* delete  */
  YYSYMBOL_update = 113,                   /* update  */
  YYSYMBOL_update_set_list = 114,          /* update_set_list  */
  YYSYMBOL_update_set = 115,               /* update_set  */
  YYSYMBOL_select = 116,                   /* select  */
  YYSYMBOL_attr_list = 117,                /* attr_list  */
  YYSYMBOL_select_attr = 118,              /* select_attr  */
  YYSYMBOL_aggop = 119,                    /* aggop  */
  YYSYMBOL_inner_join_list = 120,          /* inner_join_list  */
  YYSYMBOL_on = 121,                       /* on  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_where = 123,                    /* where  */
  YYSYMBOL_condition_list = 124,           /* condition_list  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_group = 126,                    /* group  */
  YYSYMBOL_group_attr_list = 127,          /* group_attr_list  */
  YYSYMBOL_group_attr = 128,               /* group_attr  */
  YYSYMBOL_hc_list = 129,                  /* hc_list  */
  YYSYMBOL_having_condition = 130,         /* having_condition  */
  YYSYMBOL_order = 131,                    /* order  */
  YYSYMBOL_order_attr_list = 132,          /* order_attr_list  */
  YYSYMBOL_order_attr = 133,               /* order_attr  */
  YYSYMBOL_order_type = 134,               /* order_type  */
  YYSYMBOL_comOp = 135,                    /* comOp  */
  YYSYMBOL_load_data = 136                 /* load_data  */
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
#define YYLAST   443

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  346

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   171,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   196,   202,   207,   212,   218,   224,   230,   236,
     242,   248,   255,   261,   263,   266,   270,   276,   283,   292,
     294,   298,   309,   320,   331,   344,   347,   348,   349,   350,
     351,   355,   364,   371,   373,   375,   379,   384,   386,   388,
     391,   394,   397,   401,   405,   408,   418,   424,   426,   429,
     435,   441,   446,   448,   450,   456,   461,   466,   471,   476,
     481,   488,   490,   493,   497,   499,   504,   506,   512,   515,
     518,   523,   533,   541,   551,   560,   569,   579,   591,   601,
     610,   612,   614,   619,   625,   643,   645,   647,   652,   657,
     662,   667,   672,   677,   684,   687,   690,   693,   696,   700,
     702,   706,   708,   715,   717,   721,   723,   726,   728,   732,
     741,   750,   761,   771,   781,   792,   803,   812,   821,   823,
     825,   829,   831,   833,   837,   842,   849,   851,   854,   859,
     868,   877,   886,   895,   906,   908,   911,   913,   915,   919,
     924,   931,   934,   937,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   950,   951,   952,   953,   954,   958
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
  "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "show_index", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "index_col_ID_list", "index_col_ID", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "record_list", "record", "value_list", "value", "set_value_list",
  "sub_select", "sub_select_token", "sub_attr_list", "sub_select_attr",
  "sub_rel_list", "sub_where", "sub_condition_list", "type_conj",
  "sub_condition", "delete", "update", "update_set_list", "update_set",
  "select", "attr_list", "select_attr", "aggop", "inner_join_list", "on",
  "rel_list", "where", "condition_list", "condition", "group",
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
     325,   326,   327,   328
};
#endif

#define YYPACT_NINF (-271)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-128)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -271,   273,  -271,   148,   156,   202,   -44,   176,    39,    18,
      70,    40,   110,   115,   124,   128,   171,   153,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,   130,   132,   133,
     136,   264,  -271,  -271,  -271,  -271,  -271,   183,  -271,   166,
     202,   197,   214,   226,   184,  -271,   162,   163,   196,  -271,
    -271,  -271,  -271,  -271,   195,   223,   209,   244,   245,   202,
     198,   199,  -271,   -49,  -271,  -271,   200,   234,   233,   -15,
     201,   206,   211,  -271,  -271,  -271,  -271,   221,    91,   253,
     286,   161,     7,   292,   222,   257,   233,   -15,   268,  -271,
     280,   122,   291,   271,   302,  -271,   239,  -271,  -271,    -4,
     294,   318,   161,  -271,  -271,    36,  -271,  -271,   -15,   175,
     319,  -271,   317,   206,   326,  -271,  -271,  -271,  -271,  -271,
     105,    -3,   265,   266,   233,   329,    10,   175,  -271,  -271,
    -271,  -271,  -271,   330,    -4,   161,  -271,  -271,   285,   175,
     262,   323,     6,  -271,  -271,  -271,   299,   280,   346,   295,
     301,  -271,   300,  -271,   355,    -3,   338,   302,   322,  -271,
    -271,   175,    57,   358,   364,   207,    -4,  -271,  -271,  -271,
     175,  -271,   313,  -271,  -271,  -271,  -271,  -271,  -271,    72,
    -271,  -271,  -271,   327,    71,    82,  -271,   381,  -271,  -271,
    -271,   376,  -271,    -3,   391,  -271,    36,   221,  -271,   342,
     343,    57,  -271,  -271,  -271,   341,   368,  -271,   367,   207,
     383,  -271,  -271,   323,  -271,  -271,  -271,  -271,  -271,  -271,
     372,  -271,  -271,  -271,  -271,  -271,     6,  -271,    13,   348,
     399,  -271,   207,   334,    14,  -271,   109,   101,   335,  -271,
     336,   378,   347,    13,    15,  -271,  -271,  -271,   340,   302,
     375,    94,   394,   384,  -271,  -271,    13,   345,   212,  -271,
     349,    60,  -271,    15,   302,  -271,    20,  -271,  -271,   350,
    -271,   351,  -271,  -271,   290,   288,   400,  -271,   212,    15,
    -271,   352,  -271,  -271,  -271,  -271,  -271,   127,   398,  -271,
     212,   353,   175,   120,  -271,  -271,    34,   314,   323,    20,
    -271,  -271,   323,  -271,   138,   406,  -271,   356,   141,   155,
    -271,   175,   323,   357,   323,   323,  -271,  -271,   389,  -271,
    -271,   175,   407,   175,   169,   359,  -271,   323,  -271,   401,
    -271,  -271,   175,   361,  -271,  -271
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
       0,     0,   114,   115,   116,   117,   118,   109,   108,     0,
     105,     0,     0,     0,     0,    25,     0,     0,     0,    26,
      27,    28,    24,    23,     0,     0,     0,     0,     0,   105,
       0,     0,   107,     0,    31,    30,     0,     0,   125,   100,
       0,     0,     0,    29,    37,   106,   110,   119,     0,     0,
       0,    53,    88,     0,     0,     0,   125,   100,     0,    51,
      39,     0,     0,     0,   123,   112,     0,   111,    22,    57,
       0,     0,    53,    89,    90,     0,   126,    98,   100,     0,
       0,   101,     0,     0,     0,    46,    47,    48,    49,    50,
      42,    33,     0,     0,   125,     0,    67,     0,    64,    60,
      61,    62,    63,     0,    57,    53,    52,    55,     0,     0,
       0,     0,    88,   102,   103,    99,     0,    39,     0,     0,
       0,    44,     0,    36,     0,    33,   121,   123,   138,   113,
      71,     0,    67,     0,     0,    72,    57,    56,    59,    54,
       0,   136,     0,   164,   165,   166,   167,   168,   169,     0,
     170,   172,   174,   176,     0,     0,   128,     0,    40,    38,
      45,     0,    43,    33,     0,    34,     0,   119,   124,     0,
     154,    67,    68,    66,    65,     0,    76,    75,     0,    72,
       0,    58,   137,     0,   171,   173,   175,   177,   131,   129,
     132,   130,   178,    41,    35,    32,    88,   120,   141,     0,
       0,    69,    72,     0,    81,    74,     0,     0,     0,   122,
       0,   144,   139,   141,   156,   104,    73,    77,     0,   123,
      84,     0,     0,     0,   133,   134,   141,     0,   146,   143,
       0,   163,   155,   156,   123,    82,    88,    70,    79,     0,
      78,     0,   142,   145,     0,     0,     0,   140,   146,   156,
     162,     0,   161,   159,   158,    83,    85,     0,     0,   135,
     146,     0,     0,     0,   147,   157,   163,     0,     0,    88,
      80,   148,     0,   152,     0,     0,   160,     0,     0,     0,
      87,     0,     0,     0,     0,     0,    93,    91,    94,    92,
     153,     0,     0,     0,     0,     0,   149,     0,   151,     0,
      95,    96,     0,     0,   150,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -154,   269,  -271,  -271,   270,   309,
    -271,  -271,  -271,  -271,   -95,   324,   -24,  -115,  -165,  -271,
    -271,  -206,   218,  -271,  -271,   126,  -176,  -271,  -271,  -271,
     -89,   344,  -271,   -34,   395,  -174,   230,  -271,  -162,   -48,
    -146,   235,  -271,  -160,   189,  -270,   158,  -271,  -246,   170,
     137,  -149,  -271
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   164,   165,    30,    31,   124,   100,
     201,   130,   101,    32,   111,   112,   143,   144,   173,   174,
     175,   218,   219,   260,   277,   296,   115,   309,    33,    34,
      96,    97,    35,    49,    50,    51,   104,   207,   134,    93,
     116,   152,   210,   252,   253,   287,   288,   240,   272,   273,
     293,   194,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     151,   220,   195,    94,   154,   208,   196,   212,   121,  -127,
    -127,   205,   136,   245,   137,   162,    72,   147,   304,   170,
      88,   172,   176,    89,  -127,    52,   136,   294,   171,   153,
     311,   250,   258,   270,   181,    85,   256,   -86,  -127,   113,
     113,   220,    55,   305,   290,   220,   241,    56,   120,   234,
     179,  -127,   136,   113,    95,   138,   211,   172,  -127,  -127,
    -127,  -127,   139,   140,   141,   222,   163,   142,   220,   138,
     290,   114,   114,   136,   247,   171,   139,   140,   141,   229,
     231,   142,   251,   259,   271,   114,   168,   136,   291,   292,
     249,   151,   148,   269,   286,   138,   172,   275,   136,   149,
     297,    57,   139,   140,   141,   150,   282,   142,   105,    58,
     286,   278,   295,    59,   286,   292,   138,   136,    60,   106,
     178,   159,   279,   139,   140,   141,   286,    61,   142,   224,
     138,    62,   264,   297,   225,   226,   302,   139,   140,   141,
     228,   138,   142,   136,   125,   126,   127,   128,   139,   140,
     141,   230,   221,   142,    37,   322,    38,   136,   318,   319,
     138,   160,    39,   321,    40,   161,   323,   139,   140,   141,
     263,   136,   142,   331,    63,   333,   334,   109,   261,   110,
     129,   262,   308,    53,    54,   136,   138,   313,   342,   314,
      64,   136,   315,   139,   140,   141,   307,    71,   142,    65,
     138,    66,    67,   327,   329,    68,   330,   139,   140,   141,
     326,    70,   142,    73,   138,    76,   336,    74,   338,   340,
      41,   139,   140,   141,   328,   215,   142,   344,   138,    75,
      79,    77,    78,    80,   138,   139,   140,   141,   339,    81,
     142,   139,   140,   141,    82,   284,   142,    83,    84,    42,
      43,    44,    45,    46,    42,    43,    44,    45,    46,    42,
      43,    44,    45,    46,    91,    92,   103,    86,    87,    90,
     107,    47,    98,     2,    48,    99,   216,     3,     4,   217,
     102,   285,     5,     6,     7,     8,     9,    10,    11,   108,
     182,    95,    12,    13,    14,   117,   119,   122,   123,    15,
      16,   183,   184,   185,   186,   187,   188,   131,   135,    17,
     109,    42,    43,    44,    45,    46,   301,   132,   189,   190,
     133,   146,   155,   156,   191,   192,   193,   183,   184,   185,
     186,   187,   188,    47,   166,   167,    48,    42,    43,    44,
      45,    46,   317,   158,   189,   190,   169,   177,   180,   199,
     191,   192,   193,   183,   184,   185,   186,   187,   188,   285,
     202,   200,   183,   184,   185,   186,   187,   188,   197,   163,
     189,   190,   204,   206,   209,   213,   191,   192,   193,   189,
     190,   214,   223,   227,   232,   191,   192,   193,    42,    43,
      44,    45,    46,   233,   235,   238,   243,   239,   244,   246,
     248,   254,   255,   257,   265,   251,   267,   276,   268,   274,
     216,   280,   281,   217,   283,   310,   303,   335,   271,   298,
     299,   306,   312,   324,   337,   325,   332,   198,   341,   343,
     345,   203,   157,   242,   145,   320,    69,   237,   118,   266,
     289,   236,   300,   316
};

static const yytype_int16 yycheck[] =
{
     115,   175,   151,    18,   119,   167,   152,   172,    97,     3,
       3,   165,    16,   219,    18,    18,    50,   112,   288,     9,
      69,   136,   137,    72,    18,    69,    16,   273,    18,   118,
     300,    18,    18,    18,   149,    69,   242,    17,    32,    33,
      33,   215,     3,   289,    10,   219,   211,    29,    96,   203,
     145,    45,    16,    33,    69,    59,   171,   172,    52,    52,
      54,    54,    66,    67,    68,   180,    69,    71,   242,    59,
      10,    65,    65,    16,   223,    18,    66,    67,    68,   194,
     195,    71,    69,    69,    69,    65,   134,    16,    28,    55,
     236,   206,    56,   253,   268,    59,   211,   259,    16,    63,
     276,    31,    66,    67,    68,    69,   266,    71,    17,    69,
     284,    17,   274,     3,   288,    55,    59,    16,     3,    28,
     144,    16,    28,    66,    67,    68,   300,     3,    71,    57,
      59,     3,   247,   309,    62,    63,   285,    66,    67,    68,
      69,    59,    71,    16,    22,    23,    24,    25,    66,    67,
      68,    69,   176,    71,     6,    17,     8,    16,   307,   308,
      59,    56,     6,   312,     8,    60,    28,    66,    67,    68,
      69,    16,    71,   322,     3,   324,   325,    16,    69,    18,
      58,    72,   297,     7,     8,    16,    59,   302,   337,    69,
      37,    16,    72,    66,    67,    68,    69,    31,    71,    69,
      59,    69,    69,   318,   319,    69,   321,    66,    67,    68,
      69,    28,    71,    16,    59,    31,   331,     3,   333,   334,
      18,    66,    67,    68,    69,    18,    71,   342,    59,     3,
      34,    69,    69,    38,    59,    66,    67,    68,    69,    16,
      71,    66,    67,    68,    35,    33,    71,     3,     3,    47,
      48,    49,    50,    51,    47,    48,    49,    50,    51,    47,
      48,    49,    50,    51,    30,    32,    45,    69,    69,    69,
      17,    69,    71,     0,    72,    69,    69,     4,     5,    72,
      69,    69,     9,    10,    11,    12,    13,    14,    15,     3,
      28,    69,    19,    20,    21,     3,    39,    29,    18,    26,
      27,    39,    40,    41,    42,    43,    44,    16,    69,    36,
      16,    47,    48,    49,    50,    51,    28,    46,    56,    57,
      18,     3,     3,     6,    62,    63,    64,    39,    40,    41,
      42,    43,    44,    69,    69,    69,    72,    47,    48,    49,
      50,    51,    28,    17,    56,    57,    17,    17,    63,     3,
      62,    63,    64,    39,    40,    41,    42,    43,    44,    69,
      59,    66,    39,    40,    41,    42,    43,    44,    69,    69,
      56,    57,    17,    35,    52,    17,    62,    63,    64,    56,
      57,    17,    69,    56,     3,    62,    63,    64,    47,    48,
      49,    50,    51,    17,     3,    53,    28,    54,    31,    16,
      28,    53,     3,    69,    69,    69,    28,    32,    61,    69,
      69,    17,    28,    72,    69,    17,    16,    28,    69,    69,
      69,    69,    69,    17,    17,    69,    69,   157,    69,    28,
      69,   162,   123,   215,   110,   309,    41,   207,    94,   250,
     270,   206,   284,   306
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      90,    91,    97,   112,   113,   116,   136,     6,     8,     6,
       8,    18,    47,    48,    49,    50,    51,    69,    72,   117,
     118,   119,    69,     7,     8,     3,    29,    31,    69,     3,
       3,     3,     3,     3,    37,    69,    69,    69,    69,   118,
      28,    31,   117,    16,     3,     3,    31,    69,    69,    34,
      38,    16,    35,     3,     3,   117,    69,    69,    69,    72,
      69,    30,    32,   123,    18,    69,   114,   115,    71,    69,
      93,    96,    69,    45,   120,    17,    28,    17,     3,    16,
      18,    98,    99,    33,    65,   110,   124,     3,   115,    39,
     123,   114,    29,    18,    92,    22,    23,    24,    25,    58,
      95,    16,    46,    18,   122,    69,    16,    18,    59,    66,
      67,    68,    71,   100,   101,    99,     3,    98,    56,    63,
      69,   101,   125,   114,   101,     3,     6,    93,    17,    16,
      56,    60,    18,    69,    88,    89,    69,    69,   123,    17,
       9,    18,   101,   102,   103,   104,   101,    17,   100,    98,
      63,   101,    28,    39,    40,    41,    42,    43,    44,    56,
      57,    62,    63,    64,   135,   135,   124,    69,    92,     3,
      66,    94,    59,    89,    17,    88,    35,   121,   122,    52,
     126,   101,   102,    17,    17,    18,    69,    72,   105,   106,
     119,   100,   101,    69,    57,    62,    63,    56,    69,   101,
      69,   101,     3,    17,    88,     3,   125,   120,    53,    54,
     131,   102,   106,    28,    31,   105,    16,   135,    28,   124,
      18,    69,   127,   128,    53,     3,   105,    69,    18,    69,
     107,    69,    72,    69,   101,    69,   128,    28,    61,   127,
      18,    69,   132,   133,    69,   122,    32,   108,    17,    28,
      17,    28,   127,    69,    33,    69,   119,   129,   130,   133,
      10,    28,    55,   134,   132,   122,   109,   110,    69,    69,
     130,    28,   135,    16,   129,   132,    69,    69,   101,   111,
      17,   129,    69,   101,    69,    72,   134,    28,   135,   135,
     109,   135,    17,    28,    17,    69,    69,   101,    69,   101,
     101,   135,    69,   135,   135,    28,   101,    17,   101,    69,
     101,    69,   135,    28,   101,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    88,    88,    89,    90,    91,    92,
      92,    93,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    96,    97,    98,    98,    98,    99,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   102,
     103,   104,   105,   105,   105,   106,   106,   106,   106,   106,
     106,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   112,   113,
     114,   114,   114,   115,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   126,   126,
     126,   127,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   132,   133,
     133,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   136
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
       3,     4,     4,     6,     1,     1,     1,     1,     1,     0,
       5,     0,     3,     0,     3,     0,     2,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     2,     3,     0,     3,
       5,     0,     3,     2,     1,     3,     0,     2,     3,     6,
       8,     6,     3,     5,     0,     3,     0,     3,     2,     2,
       4,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     1,     2,     8
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
#line 196 "yacc_sql.y"
                                 {
	CONTEXT->ssql->flag=SCF_SHOW_INDEX;
	show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1544 "yacc_sql.tab.c"
    break;

  case 23: /* exit: EXIT SEMICOLON  */
#line 202 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1552 "yacc_sql.tab.c"
    break;

  case 24: /* help: HELP SEMICOLON  */
#line 207 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1560 "yacc_sql.tab.c"
    break;

  case 25: /* sync: SYNC SEMICOLON  */
#line 212 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1568 "yacc_sql.tab.c"
    break;

  case 26: /* begin: TRX_BEGIN SEMICOLON  */
#line 218 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1576 "yacc_sql.tab.c"
    break;

  case 27: /* commit: TRX_COMMIT SEMICOLON  */
#line 224 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1584 "yacc_sql.tab.c"
    break;

  case 28: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 230 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1592 "yacc_sql.tab.c"
    break;

  case 29: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 236 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1601 "yacc_sql.tab.c"
    break;

  case 30: /* show_tables: SHOW TABLES SEMICOLON  */
#line 242 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1609 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 248 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1618 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE index_col_ID_list RBRACE SEMICOLON  */
#line 256 "yacc_sql.y"
    {
	CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
	create_index_multi_rel_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string));
    }
#line 1627 "yacc_sql.tab.c"
    break;

  case 34: /* index_col_ID_list: index_col_ID index_col_ID_list  */
#line 263 "yacc_sql.y"
                                     {

    }
#line 1635 "yacc_sql.tab.c"
    break;

  case 35: /* index_col_ID_list: COMMA index_col_ID index_col_ID_list  */
#line 266 "yacc_sql.y"
                                           {
    }
#line 1642 "yacc_sql.tab.c"
    break;

  case 36: /* index_col_ID: ID  */
#line 270 "yacc_sql.y"
       {
    	create_index_append_attr_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1650 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 277 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1659 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 284 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1671 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 294 "yacc_sql.y"
                                   {    }
#line 1677 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 299 "yacc_sql.y"
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
#line 1692 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 310 "yacc_sql.y"
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
#line 1707 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 321 "yacc_sql.y"
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
#line 1722 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 332 "yacc_sql.y"
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
#line 1737 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 344 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1743 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 347 "yacc_sql.y"
              { (yyval.number)=INTS; CONTEXT->attr_length = 4; }
#line 1749 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 348 "yacc_sql.y"
                  { (yyval.number)=CHARS; CONTEXT->attr_length = 40; }
#line 1755 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 349 "yacc_sql.y"
                 { (yyval.number)=FLOATS; CONTEXT->attr_length = 4; }
#line 1761 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 350 "yacc_sql.y"
                { (yyval.number)=DATES; CONTEXT->attr_length = 4; }
#line 1767 "yacc_sql.tab.c"
    break;

  case 50: /* type: TEXT_T  */
#line 351 "yacc_sql.y"
                { (yyval.number)=TEXTS; CONTEXT->attr_length = 4096; }
#line 1773 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 356 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1782 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES record_list SEMICOLON  */
#line 365 "yacc_sql.y"
    {
      CONTEXT->ssql->flag=SCF_INSERT;//"insert";
      inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-3].string), CONTEXT->records, CONTEXT->record_length);
      //临时变量清零
      CONTEXT->record_length = 0;
    }
#line 1793 "yacc_sql.tab.c"
    break;

  case 54: /* record_list: COMMA record record_list  */
#line 373 "yacc_sql.y"
                               {
    }
#line 1800 "yacc_sql.tab.c"
    break;

  case 55: /* record_list: record record_list  */
#line 375 "yacc_sql.y"
                         {
    }
#line 1807 "yacc_sql.tab.c"
    break;

  case 56: /* record: LBRACE value_list RBRACE  */
#line 379 "yacc_sql.y"
                             {
    	insert_record_init(&CONTEXT->records[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
    	CONTEXT->value_length=0;
    }
#line 1816 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 386 "yacc_sql.y"
                              {
    }
#line 1823 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: value value_list  */
#line 388 "yacc_sql.y"
                       {
    }
#line 1830 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 391 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
    }
#line 1838 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 394 "yacc_sql.y"
           {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
    }
#line 1846 "yacc_sql.tab.c"
    break;

  case 62: /* value: DATE_STR  */
#line 397 "yacc_sql.y"
              {
    		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1855 "yacc_sql.tab.c"
    break;

  case 63: /* value: SSS  */
#line 401 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1864 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULL_TOKEN  */
#line 405 "yacc_sql.y"
                {
    		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1872 "yacc_sql.tab.c"
    break;

  case 65: /* value: LBRACE sub_select RBRACE  */
#line 408 "yacc_sql.y"
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
#line 1887 "yacc_sql.tab.c"
    break;

  case 66: /* value: LBRACE set_value_list RBRACE  */
#line 418 "yacc_sql.y"
                                   {
	value_init_set(&CONTEXT->values[CONTEXT->value_length++], CONTEXT->set_values, CONTEXT->set_num);
	CONTEXT->set_num = 0;
    }
#line 1896 "yacc_sql.tab.c"
    break;

  case 68: /* set_value_list: value set_value_list  */
#line 426 "yacc_sql.y"
                           {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 1904 "yacc_sql.tab.c"
    break;

  case 69: /* set_value_list: COMMA value set_value_list  */
#line 429 "yacc_sql.y"
                                 {
	CONTEXT->set_values[CONTEXT->set_num++] = CONTEXT->values[--CONTEXT->value_length];
    }
#line 1912 "yacc_sql.tab.c"
    break;

  case 70: /* sub_select: sub_select_token sub_attr_list FROM sub_rel_list sub_where  */
#line 435 "yacc_sql.y"
                                                               {

    }
#line 1920 "yacc_sql.tab.c"
    break;

  case 71: /* sub_select_token: SELECT  */
#line 441 "yacc_sql.y"
           {
	CONTEXT->sub_select_num++;
    }
#line 1928 "yacc_sql.tab.c"
    break;

  case 73: /* sub_attr_list: COMMA sub_select_attr sub_attr_list  */
#line 448 "yacc_sql.y"
                                          {
    }
#line 1935 "yacc_sql.tab.c"
    break;

  case 74: /* sub_attr_list: sub_select_attr sub_attr_list  */
#line 450 "yacc_sql.y"
                                    {

    }
#line 1943 "yacc_sql.tab.c"
    break;

  case 75: /* sub_select_attr: STAR  */
#line 456 "yacc_sql.y"
         {
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1953 "yacc_sql.tab.c"
    break;

  case 76: /* sub_select_attr: ID  */
#line 461 "yacc_sql.y"
         {
        RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1963 "yacc_sql.tab.c"
    break;

  case 77: /* sub_select_attr: ID DOT ID  */
#line 466 "yacc_sql.y"
                {
        RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1973 "yacc_sql.tab.c"
    break;

  case 78: /* sub_select_attr: aggop LBRACE STAR RBRACE  */
#line 471 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1983 "yacc_sql.tab.c"
    break;

  case 79: /* sub_select_attr: aggop LBRACE ID RBRACE  */
#line 476 "yacc_sql.y"
                             {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 1993 "yacc_sql.tab.c"
    break;

  case 80: /* sub_select_attr: aggop LBRACE ID DOT ID RBRACE  */
#line 481 "yacc_sql.y"
                                    {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &attr);
    }
#line 2003 "yacc_sql.tab.c"
    break;

  case 82: /* sub_rel_list: ID rel_list  */
#line 490 "yacc_sql.y"
                  {
	selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-1].string));
    }
#line 2011 "yacc_sql.tab.c"
    break;

  case 83: /* sub_rel_list: COMMA ID rel_list  */
#line 493 "yacc_sql.y"
                        {
    	selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-1].string));
    }
#line 2019 "yacc_sql.tab.c"
    break;

  case 85: /* sub_where: WHERE sub_condition_list  */
#line 499 "yacc_sql.y"
                               {
	printf("2\n");
    }
#line 2027 "yacc_sql.tab.c"
    break;

  case 87: /* sub_condition_list: type_conj sub_condition sub_condition_list  */
#line 506 "yacc_sql.y"
                                                 {

    }
#line 2035 "yacc_sql.tab.c"
    break;

  case 88: /* type_conj: %empty  */
#line 512 "yacc_sql.y"
                {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_FIRST;
    }
#line 2043 "yacc_sql.tab.c"
    break;

  case 89: /* type_conj: AND  */
#line 515 "yacc_sql.y"
          {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_AND;
    }
#line 2051 "yacc_sql.tab.c"
    break;

  case 90: /* type_conj: OR  */
#line 518 "yacc_sql.y"
         {
	CONTEXT->conj[CONTEXT->conj_num++] = CONJ_OR;
    }
#line 2059 "yacc_sql.tab.c"
    break;

  case 91: /* sub_condition: ID comOp value  */
#line 524 "yacc_sql.y"
    {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	// printf("CONTEXT->sub_select_num: %d\n", CONTEXT->sub_select_num);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2073 "yacc_sql.tab.c"
    break;

  case 92: /* sub_condition: value comOp value  */
#line 533 "yacc_sql.y"
                       {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2086 "yacc_sql.tab.c"
    break;

  case 93: /* sub_condition: ID comOp ID  */
#line 541 "yacc_sql.y"
                 {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2101 "yacc_sql.tab.c"
    break;

  case 94: /* sub_condition: value comOp ID  */
#line 551 "yacc_sql.y"
                    {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2115 "yacc_sql.tab.c"
    break;

  case 95: /* sub_condition: ID DOT ID comOp value  */
#line 560 "yacc_sql.y"
                           {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
    	Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2129 "yacc_sql.tab.c"
    break;

  case 96: /* sub_condition: value comOp ID DOT ID  */
#line 569 "yacc_sql.y"
                           {
    	Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2144 "yacc_sql.tab.c"
    break;

  case 97: /* sub_condition: ID DOT ID comOp ID DOT ID  */
#line 579 "yacc_sql.y"
                               {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
    	Condition condition;
    	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
    	selects_append_condition(&CONTEXT->sub_selects[CONTEXT->sub_select_num], &condition);
    }
#line 2158 "yacc_sql.tab.c"
    break;

  case 98: /* delete: DELETE FROM ID where SEMICOLON  */
#line 592 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2170 "yacc_sql.tab.c"
    break;

  case 99: /* update: UPDATE ID SET update_set_list where SEMICOLON  */
#line 602 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string),
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2181 "yacc_sql.tab.c"
    break;

  case 101: /* update_set_list: update_set update_set_list  */
#line 612 "yacc_sql.y"
                                 {
    }
#line 2188 "yacc_sql.tab.c"
    break;

  case 102: /* update_set_list: COMMA update_set update_set_list  */
#line 614 "yacc_sql.y"
                                       {
    }
#line 2195 "yacc_sql.tab.c"
    break;

  case 103: /* update_set: ID EQ value  */
#line 619 "yacc_sql.y"
                {
        Value *value = &CONTEXT->values[--CONTEXT->value_length];
    	updates_append_attr_and_value(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), value);
    }
#line 2204 "yacc_sql.tab.c"
    break;

  case 104: /* select: SELECT attr_list FROM ID inner_join_list rel_list where group order SEMICOLON  */
#line 626 "yacc_sql.y"
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
#line 2224 "yacc_sql.tab.c"
    break;

  case 106: /* attr_list: COMMA select_attr attr_list  */
#line 645 "yacc_sql.y"
                                  {
    }
#line 2231 "yacc_sql.tab.c"
    break;

  case 107: /* attr_list: select_attr attr_list  */
#line 647 "yacc_sql.y"
                            {
    }
#line 2238 "yacc_sql.tab.c"
    break;

  case 108: /* select_attr: STAR  */
#line 652 "yacc_sql.y"
         {  
	RelAttr attr;
	relation_attr_init(&attr, NULL, "*");
 	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2248 "yacc_sql.tab.c"
    break;

  case 109: /* select_attr: ID  */
#line 657 "yacc_sql.y"
         {
        RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2258 "yacc_sql.tab.c"
    break;

  case 110: /* select_attr: ID DOT ID  */
#line 662 "yacc_sql.y"
                {
        RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2268 "yacc_sql.tab.c"
    break;

  case 111: /* select_attr: aggop LBRACE STAR RBRACE  */
#line 667 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_aggr_init(&attr, NULL, "*", CONTEXT->agg_type);
	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2278 "yacc_sql.tab.c"
    break;

  case 112: /* select_attr: aggop LBRACE ID RBRACE  */
#line 672 "yacc_sql.y"
                             {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, NULL, (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2288 "yacc_sql.tab.c"
    break;

  case 113: /* select_attr: aggop LBRACE ID DOT ID RBRACE  */
#line 677 "yacc_sql.y"
                                    {
    	RelAttr attr;
    	relation_attr_aggr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->agg_type);
    	selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2298 "yacc_sql.tab.c"
    break;

  case 114: /* aggop: MAX  */
#line 684 "yacc_sql.y"
        {
	CONTEXT->agg_type = AGG_MAX;
    }
#line 2306 "yacc_sql.tab.c"
    break;

  case 115: /* aggop: MIN  */
#line 687 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_MIN;
    }
#line 2314 "yacc_sql.tab.c"
    break;

  case 116: /* aggop: COUNT  */
#line 690 "yacc_sql.y"
            {
	CONTEXT->agg_type = AGG_COUNT;
    }
#line 2322 "yacc_sql.tab.c"
    break;

  case 117: /* aggop: AVG  */
#line 693 "yacc_sql.y"
          {
	CONTEXT->agg_type = AGG_AVG;
    }
#line 2330 "yacc_sql.tab.c"
    break;

  case 118: /* aggop: SUM  */
#line 696 "yacc_sql.y"
          {
    	CONTEXT->agg_type = AGG_SUM;
    }
#line 2338 "yacc_sql.tab.c"
    break;

  case 120: /* inner_join_list: INNER JOIN ID on inner_join_list  */
#line 702 "yacc_sql.y"
                                       {
	selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 2346 "yacc_sql.tab.c"
    break;

  case 122: /* on: ON condition condition_list  */
#line 708 "yacc_sql.y"
                                  {
	// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
    }
#line 2354 "yacc_sql.tab.c"
    break;

  case 124: /* rel_list: COMMA ID rel_list  */
#line 717 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2362 "yacc_sql.tab.c"
    break;

  case 126: /* where: WHERE condition_list  */
#line 723 "yacc_sql.y"
                           {
    }
#line 2369 "yacc_sql.tab.c"
    break;

  case 128: /* condition_list: type_conj condition condition_list  */
#line 728 "yacc_sql.y"
                                         {
    }
#line 2376 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID comOp value  */
#line 733 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2389 "yacc_sql.tab.c"
    break;

  case 130: /* condition: value comOp value  */
#line 742 "yacc_sql.y"
    {
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2402 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID comOp ID  */
#line 751 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2417 "yacc_sql.tab.c"
    break;

  case 132: /* condition: value comOp ID  */
#line 762 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2431 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID DOT ID comOp value  */
#line 772 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2445 "yacc_sql.tab.c"
    break;

  case 134: /* condition: value comOp ID DOT ID  */
#line 782 "yacc_sql.y"
    {
	Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 0, NULL, left_value, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2460 "yacc_sql.tab.c"
    break;

  case 135: /* condition: ID DOT ID comOp ID DOT ID  */
#line 793 "yacc_sql.y"
    {
	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
	RelAttr right_attr;
	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
	Condition condition;
	condition_conj_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 1, &right_attr, NULL, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2474 "yacc_sql.tab.c"
    break;

  case 136: /* condition: EXISTS value  */
#line 803 "yacc_sql.y"
                   {
	Value left_value;
	value_init_integer(&left_value, 0);
	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

	Condition condition;
	condition_conj_init(&condition, EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2488 "yacc_sql.tab.c"
    break;

  case 137: /* condition: NOT EXISTS value  */
#line 812 "yacc_sql.y"
                       {
    	Value left_value;
        value_init_integer(&left_value, 0);
    	Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

    	Condition condition;
    	condition_conj_init(&condition, NOT_EXISTS_OP, 0, NULL, &left_value, 0, NULL, right_value, CONTEXT->conj[--CONTEXT->conj_num]);
    	CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2502 "yacc_sql.tab.c"
    break;

  case 139: /* group: GROUP BY group_attr_list  */
#line 823 "yacc_sql.y"
                               {
    }
#line 2509 "yacc_sql.tab.c"
    break;

  case 140: /* group: GROUP BY group_attr_list HAVING hc_list  */
#line 825 "yacc_sql.y"
                                              {

    }
#line 2517 "yacc_sql.tab.c"
    break;

  case 142: /* group_attr_list: COMMA group_attr group_attr_list  */
#line 831 "yacc_sql.y"
                                       {
    }
#line 2524 "yacc_sql.tab.c"
    break;

  case 143: /* group_attr_list: group_attr group_attr_list  */
#line 833 "yacc_sql.y"
                                 {
    }
#line 2531 "yacc_sql.tab.c"
    break;

  case 144: /* group_attr: ID  */
#line 837 "yacc_sql.y"
       {
        GroupAttr group_attr;
	group_attr_init(&group_attr, NULL, (yyvsp[0].string));
	group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2541 "yacc_sql.tab.c"
    break;

  case 145: /* group_attr: ID DOT ID  */
#line 842 "yacc_sql.y"
                {
        GroupAttr group_attr;
        group_attr_init(&group_attr, (yyvsp[-2].string), (yyvsp[0].string));
        group_append_attribute(&CONTEXT->ssql->sstr.selection, &group_attr);
    }
#line 2551 "yacc_sql.tab.c"
    break;

  case 147: /* hc_list: having_condition hc_list  */
#line 851 "yacc_sql.y"
                               {

    }
#line 2559 "yacc_sql.tab.c"
    break;

  case 148: /* hc_list: AND having_condition hc_list  */
#line 854 "yacc_sql.y"
                                   {
    }
#line 2566 "yacc_sql.tab.c"
    break;

  case 149: /* having_condition: aggop LBRACE ID RBRACE comOp value  */
#line 859 "yacc_sql.y"
                                       {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2580 "yacc_sql.tab.c"
    break;

  case 150: /* having_condition: aggop LBRACE ID DOT ID RBRACE comOp value  */
#line 868 "yacc_sql.y"
                                                {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2594 "yacc_sql.tab.c"
    break;

  case 151: /* having_condition: aggop LBRACE STAR RBRACE comOp value  */
#line 877 "yacc_sql.y"
                                           {
        RelAttr left_attr;
        relation_attr_aggr_init(&left_attr, NULL, "*", CONTEXT->agg_type);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2608 "yacc_sql.tab.c"
    break;

  case 152: /* having_condition: ID comOp value  */
#line 886 "yacc_sql.y"
                     {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2622 "yacc_sql.tab.c"
    break;

  case 153: /* having_condition: ID DOT ID comOp value  */
#line 895 "yacc_sql.y"
                            {
        RelAttr left_attr;
        relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
        Condition condition;
        condition_init(&condition, CONTEXT->comps[--CONTEXT->comp_num], 1, &left_attr, NULL, 0, NULL, right_value);
        selects_append_having_condition(&CONTEXT->ssql->sstr.selection, &condition);
        CONTEXT->value_length = 0;
    }
#line 2636 "yacc_sql.tab.c"
    break;

  case 155: /* order: ORDER BY order_attr_list  */
#line 908 "yacc_sql.y"
                               {
    }
#line 2643 "yacc_sql.tab.c"
    break;

  case 157: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 913 "yacc_sql.y"
                                       {
    }
#line 2650 "yacc_sql.tab.c"
    break;

  case 158: /* order_attr_list: order_attr order_attr_list  */
#line 915 "yacc_sql.y"
                                 {
    }
#line 2657 "yacc_sql.tab.c"
    break;

  case 159: /* order_attr: ID order_type  */
#line 919 "yacc_sql.y"
                  {
        OrderAttr order_attr;
	order_attr_init(&order_attr, NULL, (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2667 "yacc_sql.tab.c"
    break;

  case 160: /* order_attr: ID DOT ID order_type  */
#line 924 "yacc_sql.y"
                           {
        OrderAttr order_attr;
	order_attr_init(&order_attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
	order_append_attribute(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2677 "yacc_sql.tab.c"
    break;

  case 161: /* order_type: ASC  */
#line 931 "yacc_sql.y"
        {
    	CONTEXT->order_type = OrderAsc;
    }
#line 2685 "yacc_sql.tab.c"
    break;

  case 162: /* order_type: DESC  */
#line 934 "yacc_sql.y"
           {
    	CONTEXT->order_type = OrderDesc;
    }
#line 2693 "yacc_sql.tab.c"
    break;

  case 163: /* order_type: %empty  */
#line 937 "yacc_sql.y"
                  {
    	CONTEXT->order_type = OrderAsc;
    }
#line 2701 "yacc_sql.tab.c"
    break;

  case 164: /* comOp: EQ  */
#line 941 "yacc_sql.y"
       { CONTEXT->comps[CONTEXT->comp_num++] = EQUAL_TO; }
#line 2707 "yacc_sql.tab.c"
    break;

  case 165: /* comOp: LT  */
#line 942 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_THAN; }
#line 2713 "yacc_sql.tab.c"
    break;

  case 166: /* comOp: GT  */
#line 943 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_THAN; }
#line 2719 "yacc_sql.tab.c"
    break;

  case 167: /* comOp: LE  */
#line 944 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = LESS_EQUAL; }
#line 2725 "yacc_sql.tab.c"
    break;

  case 168: /* comOp: GE  */
#line 945 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = GREAT_EQUAL; }
#line 2731 "yacc_sql.tab.c"
    break;

  case 169: /* comOp: NE  */
#line 946 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EQUAL; }
#line 2737 "yacc_sql.tab.c"
    break;

  case 170: /* comOp: LIKE  */
#line 947 "yacc_sql.y"
           { CONTEXT->comps[CONTEXT->comp_num++] = LIKE_TO; }
#line 2743 "yacc_sql.tab.c"
    break;

  case 171: /* comOp: NOT LIKE  */
#line 948 "yacc_sql.y"
               { CONTEXT->comps[CONTEXT->comp_num++] = NOT_LIKE_TO; }
#line 2749 "yacc_sql.tab.c"
    break;

  case 172: /* comOp: IN  */
#line 949 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IN_OP; }
#line 2755 "yacc_sql.tab.c"
    break;

  case 173: /* comOp: NOT IN  */
#line 950 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = NOT_IN_OP; }
#line 2761 "yacc_sql.tab.c"
    break;

  case 174: /* comOp: EXISTS  */
#line 951 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = EXISTS_OP; }
#line 2767 "yacc_sql.tab.c"
    break;

  case 175: /* comOp: NOT EXISTS  */
#line 952 "yacc_sql.y"
                 { CONTEXT->comps[CONTEXT->comp_num++] = NOT_EXISTS_OP; }
#line 2773 "yacc_sql.tab.c"
    break;

  case 176: /* comOp: IS  */
#line 953 "yacc_sql.y"
         { CONTEXT->comps[CONTEXT->comp_num++] = IS_OP; }
#line 2779 "yacc_sql.tab.c"
    break;

  case 177: /* comOp: IS NOT  */
#line 954 "yacc_sql.y"
             { CONTEXT->comps[CONTEXT->comp_num++] = IS_NOT_OP; }
#line 2785 "yacc_sql.tab.c"
    break;

  case 178: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 959 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2794 "yacc_sql.tab.c"
    break;


#line 2798 "yacc_sql.tab.c"

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

#line 964 "yacc_sql.y"

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
