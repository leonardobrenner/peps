/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/lb/glc.y"

//====================================================================================//
//                                                                                    //
//                           Parser and Semantic Analysis                             //
//                                                                                    //
//====================================================================================//
//  This File:   glc.y                       Tool: YACC                               //
//  Software:    PEPS                        Advisor: Paulof@inf.pucrs.br             //
//  Doc:                                                                              //
//====================================================================================//
//  Creation:    01/Mar/02                   by: lbrenner@inf.pucrs.br                //
//  Last Change: 07/Nov/02                   by: lbrenner@inf.pucrs.br                //
//====================================================================================//
//  YACC is a general-purpose parser generator that converts a context-free grammar   //
// a C program.In this module are make the actions to generate the internal SAN's     //
// tables and the others functionalities of this textual interface for PEPS.          //
//====================================================================================//
#include "sanfile.h"

//====================================================================================//
//                                   Global variables                                 //
//====================================================================================//

NET *net; // Network structure
DOM *dom; // Dominion structure
EDIC *edic; // Events dictionary

inf2pos itop;  // Used to convert of infix operator expression form
               //   to postfix operator expression form 

FUNC *t_ident; // Auxiliar table to identifiers

aut_st    replic_map;      // replication map to perform lump

int not_error = 1;

int tour; // Set the times that the parser was called, the first to count the number
          // of automatas, the number of states, the number of transitions and others
int n_aut; // Number of automatons in network, this counter is increased in the first 
           // pass to alloc the automaton structure in second pass
int n_state; // Number of states in each automaton
int n_trans; // Number of transitions in each state
int n_mst; // Number of master events
int n_sync; // Number of synchronizing events
int n_local; // Number of local events
int n_events; // Number of events (local and synchronizing)
int aut_group; // Automaton group number 
//====================================================================================//
//                                      Variables                                     //
//====================================================================================//

char temp[MAX_AUTOMATON_NAME];
char tmp[FUNCTION], tmp1[FUNCTION];  // Variables used to grouping characters
char fnc[FUNCTION]; // Variable to store the functions
char fname[MAX_FUNC_NAME];
char event_name[MAX_EVENT_NAME];
char i1n[MAX_FUNC_NAME];
char i2n[MAX_FUNC_NAME];

int with_id, sum_or_prod;
int r_t;
double v_tmp;
int i_tmp;
int i1, i2, iv, ia, di, dl;
int from_dst, f_t;
int event_type;
int event_rate;
int event_mst;
int queue_p, queue_m;

char aut_replic[MAX_AUTOMATON_NAME];
char state_queue[MAX_STATE_NAME];
char aux_dst[MAX_STATE_NAME];
int aut; // current automaton index
int replic; // number of replics
int state; // current state index
int queue; // queue
int trans; // transition
int mst; // master event
int synch; // synchronizing event
int local; // local event
int **mat_trans; // This matrix store the number of transitions of each automaton-state


//====================================================================================//
//                                   Parser variables                                 //
//====================================================================================//

extern int yynerrs;  // Variable of the YACC generator to count the number of errors.  
extern int yylineno;        // Variable of the YACC generator to count the current line

extern int yylex(void); // Get the next token
extern void yyrestart(FILE *input_file);
extern char *yytext; 
extern FILE *yyin; // Input file


//====================================================================================//
//                                   Function errors                                  //
//====================================================================================//
//  These functions analysis which error occurred and put the error into a message    //
// more specific.                                                                     //
//====================================================================================//


//====================================================================================
// Function that YACC use to put sintatic message errors                      
//====================================================================================
extern void yyerror(char *s)
{
  yynerrs++; 
  not_error = 0;
  Sintatic_Error(yynerrs, yylineno, s, yytext);
}

//====================================================================================
// Function to put semantic error messages 
//====================================================================================
void type_error(const char* error_number)
{
  yynerrs++;
  not_error = 0;
  Semantic_Error_YACC(yynerrs, yylineno, yytext, error_number);
}


void alloc_mat_aut(int aaut)
{
  mat_trans = new int*[aaut];  
}

void alloc_mat_state(int aaut, int sstate)
{
  mat_trans[aaut] = new int[sstate];  
  for(int i=0; i<sstate; i++)
    mat_trans[aaut][i] = 0;
}


#line 211 "./src/lb/yacc.C"

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

#include "yacc.H"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_IDENTIFIERS = 3,             /* TK_IDENTIFIERS  */
  YYSYMBOL_TK_EVENTS = 4,                  /* TK_EVENTS  */
  YYSYMBOL_TK_NETWORK = 5,                 /* TK_NETWORK  */
  YYSYMBOL_TK_AUTOMATON = 6,               /* TK_AUTOMATON  */
  YYSYMBOL_TK_STATE = 7,                   /* TK_STATE  */
  YYSYMBOL_TK_TRANS = 8,                   /* TK_TRANS  */
  YYSYMBOL_TK_FROM = 9,                    /* TK_FROM  */
  YYSYMBOL_TK_SYN = 10,                    /* TK_SYN  */
  YYSYMBOL_TK_LOC = 11,                    /* TK_LOC  */
  YYSYMBOL_TK_RESULTS = 12,                /* TK_RESULTS  */
  YYSYMBOL_TK_CONTINUOUS = 13,             /* TK_CONTINUOUS  */
  YYSYMBOL_TK_DISCRETE = 14,               /* TK_DISCRETE  */
  YYSYMBOL_TK_REACH = 15,                  /* TK_REACH  */
  YYSYMBOL_TK_PARTIAL = 16,                /* TK_PARTIAL  */
  YYSYMBOL_TK_MIN = 17,                    /* TK_MIN  */
  YYSYMBOL_TK_MAX = 18,                    /* TK_MAX  */
  YYSYMBOL_TK_STATE_NUM = 19,              /* TK_STATE_NUM  */
  YYSYMBOL_TK_NBR = 20,                    /* TK_NBR  */
  YYSYMBOL_TK_REWARD = 21,                 /* TK_REWARD  */
  YYSYMBOL_TK_SUM_RW = 22,                 /* TK_SUM_RW  */
  YYSYMBOL_TK_PROD_RW = 23,                /* TK_PROD_RW  */
  YYSYMBOL_TK_ID = 24,                     /* TK_ID  */
  YYSYMBOL_TK_INTEGER = 25,                /* TK_INTEGER  */
  YYSYMBOL_TK_REAL = 26,                   /* TK_REAL  */
  YYSYMBOL_TK_EXPONENT = 27,               /* TK_EXPONENT  */
  YYSYMBOL_TK_LEFT_BRACKET = 28,           /* TK_LEFT_BRACKET  */
  YYSYMBOL_TK_RIGHT_BRACKET = 29,          /* TK_RIGHT_BRACKET  */
  YYSYMBOL_TK_LEFT_PARENTHESIS = 30,       /* TK_LEFT_PARENTHESIS  */
  YYSYMBOL_TK_RIGHT_PARENTHESIS = 31,      /* TK_RIGHT_PARENTHESIS  */
  YYSYMBOL_TK_LEFT_SQUARE_BRACKET = 32,    /* TK_LEFT_SQUARE_BRACKET  */
  YYSYMBOL_TK_RIGHT_SQUARE_BRACKET = 33,   /* TK_RIGHT_SQUARE_BRACKET  */
  YYSYMBOL_TK_SEMICOLON = 34,              /* TK_SEMICOLON  */
  YYSYMBOL_TK_COMMA = 35,                  /* TK_COMMA  */
  YYSYMBOL_TK_ATTRIB = 36,                 /* TK_ATTRIB  */
  YYSYMBOL_TK_COLON = 37,                  /* TK_COLON  */
  YYSYMBOL_TK_POINT = 38,                  /* TK_POINT  */
  YYSYMBOL_TK_2DOTS = 39,                  /* TK_2DOTS  */
  YYSYMBOL_TK_DOTS = 40,                   /* TK_DOTS  */
  YYSYMBOL_TK_SIMPLE = 41,                 /* TK_SIMPLE  */
  YYSYMBOL_TK_DOUBLE = 42,                 /* TK_DOUBLE  */
  YYSYMBOL_TK_PLUS = 43,                   /* TK_PLUS  */
  YYSYMBOL_TK_PLUS_PLUS = 44,              /* TK_PLUS_PLUS  */
  YYSYMBOL_TK_MINUS = 45,                  /* TK_MINUS  */
  YYSYMBOL_TK_MINUS_MINUS = 46,            /* TK_MINUS_MINUS  */
  YYSYMBOL_TK_MULT = 47,                   /* TK_MULT  */
  YYSYMBOL_TK_DIV = 48,                    /* TK_DIV  */
  YYSYMBOL_TK_AND = 49,                    /* TK_AND  */
  YYSYMBOL_TK_OR = 50,                     /* TK_OR  */
  YYSYMBOL_TK_XOR = 51,                    /* TK_XOR  */
  YYSYMBOL_TK_NOT = 52,                    /* TK_NOT  */
  YYSYMBOL_TK_EQUAL = 53,                  /* TK_EQUAL  */
  YYSYMBOL_TK_UNEQUAL = 54,                /* TK_UNEQUAL  */
  YYSYMBOL_TK_MAJOR = 55,                  /* TK_MAJOR  */
  YYSYMBOL_TK_MAJOR_EQUAL = 56,            /* TK_MAJOR_EQUAL  */
  YYSYMBOL_TK_MINOR = 57,                  /* TK_MINOR  */
  YYSYMBOL_TK_MINOR_EQUAL = 58,            /* TK_MINOR_EQUAL  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_start = 60,                     /* start  */
  YYSYMBOL_blk_id = 61,                    /* blk_id  */
  YYSYMBOL_blk_int_id = 62,                /* blk_int_id  */
  YYSYMBOL_63_1 = 63,                      /* $@1  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_blk_int_id2 = 65,               /* blk_int_id2  */
  YYSYMBOL_blk_events = 66,                /* blk_events  */
  YYSYMBOL_blk_int_ev = 67,                /* blk_int_ev  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_69_4 = 69,                      /* $@4  */
  YYSYMBOL_70_5 = 70,                      /* $@5  */
  YYSYMBOL_71_6 = 71,                      /* $@6  */
  YYSYMBOL_blk_int_ev2 = 72,               /* blk_int_ev2  */
  YYSYMBOL_event_replic = 73,              /* event_replic  */
  YYSYMBOL_int_event_replic = 74,          /* int_event_replic  */
  YYSYMBOL_75_7 = 75,                      /* $@7  */
  YYSYMBOL_rate = 76,                      /* rate  */
  YYSYMBOL_int_rate = 77,                  /* int_rate  */
  YYSYMBOL_semi_colon = 78,                /* semi_colon  */
  YYSYMBOL_blk_exp_dom = 79,               /* blk_exp_dom  */
  YYSYMBOL_blk_def_dom = 80,               /* blk_def_dom  */
  YYSYMBOL_81_8 = 81,                      /* $@8  */
  YYSYMBOL_82_9 = 82,                      /* $@9  */
  YYSYMBOL_blk_exp = 83,                   /* blk_exp  */
  YYSYMBOL_blk_exp2 = 84,                  /* blk_exp2  */
  YYSYMBOL_list_exp = 85,                  /* list_exp  */
  YYSYMBOL_exp = 86,                       /* exp  */
  YYSYMBOL_87_10 = 87,                     /* $@10  */
  YYSYMBOL_88_11 = 88,                     /* $@11  */
  YYSYMBOL_elem = 89,                      /* elem  */
  YYSYMBOL_90_12 = 90,                     /* $@12  */
  YYSYMBOL_91_13 = 91,                     /* $@13  */
  YYSYMBOL_92_14 = 92,                     /* $@14  */
  YYSYMBOL_93_15 = 93,                     /* $@15  */
  YYSYMBOL_op_rw = 94,                     /* op_rw  */
  YYSYMBOL_dominion = 95,                  /* dominion  */
  YYSYMBOL_interval = 96,                  /* interval  */
  YYSYMBOL_interval_1 = 97,                /* interval_1  */
  YYSYMBOL_98_16 = 98,                     /* $@16  */
  YYSYMBOL_99_17 = 99,                     /* $@17  */
  YYSYMBOL_id_stat = 100,                  /* id_stat  */
  YYSYMBOL_id_replic = 101,                /* id_replic  */
  YYSYMBOL_102_18 = 102,                   /* $@18  */
  YYSYMBOL_replic = 103,                   /* replic  */
  YYSYMBOL_104_19 = 104,                   /* $@19  */
  YYSYMBOL_105_20 = 105,                   /* $@20  */
  YYSYMBOL_number = 106,                   /* number  */
  YYSYMBOL_op_unary = 107,                 /* op_unary  */
  YYSYMBOL_op_bin = 108,                   /* op_bin  */
  YYSYMBOL_reach = 109,                    /* reach  */
  YYSYMBOL_110_21 = 110,                   /* $@21  */
  YYSYMBOL_111_22 = 111,                   /* $@22  */
  YYSYMBOL_t_reach = 112,                  /* t_reach  */
  YYSYMBOL_blk_net = 113,                  /* blk_net  */
  YYSYMBOL_114_23 = 114,                   /* $@23  */
  YYSYMBOL_115_24 = 115,                   /* $@24  */
  YYSYMBOL_model_type = 116,               /* model_type  */
  YYSYMBOL_blk_autom = 117,                /* blk_autom  */
  YYSYMBOL_118_25 = 118,                   /* $@25  */
  YYSYMBOL_119_26 = 119,                   /* $@26  */
  YYSYMBOL_120_27 = 120,                   /* $@27  */
  YYSYMBOL_121_28 = 121,                   /* $@28  */
  YYSYMBOL_blk_autom2 = 122,               /* blk_autom2  */
  YYSYMBOL_blk_state = 123,                /* blk_state  */
  YYSYMBOL_124_29 = 124,                   /* $@29  */
  YYSYMBOL_125_30 = 125,                   /* $@30  */
  YYSYMBOL_126_31 = 126,                   /* $@31  */
  YYSYMBOL_blk_state2 = 127,               /* blk_state2  */
  YYSYMBOL_blk_from = 128,                 /* blk_from  */
  YYSYMBOL_129_32 = 129,                   /* $@32  */
  YYSYMBOL_130_33 = 130,                   /* $@33  */
  YYSYMBOL_blk_from_replic = 131,          /* blk_from_replic  */
  YYSYMBOL_132_34 = 132,                   /* $@34  */
  YYSYMBOL_blk_trans = 133,                /* blk_trans  */
  YYSYMBOL_134_35 = 134,                   /* $@35  */
  YYSYMBOL_135_36 = 135,                   /* $@36  */
  YYSYMBOL_blk_trans2 = 136,               /* blk_trans2  */
  YYSYMBOL_dst_state = 137,                /* dst_state  */
  YYSYMBOL_138_37 = 138,                   /* $@37  */
  YYSYMBOL_dst_replic = 139,               /* dst_replic  */
  YYSYMBOL_140_38 = 140,                   /* $@38  */
  YYSYMBOL_blk_type_trans = 141,           /* blk_type_trans  */
  YYSYMBOL_142_39 = 142,                   /* $@39  */
  YYSYMBOL_143_40 = 143,                   /* $@40  */
  YYSYMBOL_blk_type_trans2 = 144,          /* blk_type_trans2  */
  YYSYMBOL_e_replic = 145,                 /* e_replic  */
  YYSYMBOL_146_41 = 146,                   /* $@41  */
  YYSYMBOL_blk_prob = 147,                 /* blk_prob  */
  YYSYMBOL_prob = 148,                     /* prob  */
  YYSYMBOL_blk_replic = 149,               /* blk_replic  */
  YYSYMBOL_replic_number = 150,            /* replic_number  */
  YYSYMBOL_151_42 = 151,                   /* $@42  */
  YYSYMBOL_blk_queue = 152,                /* blk_queue  */
  YYSYMBOL_queue_number = 153,             /* queue_number  */
  YYSYMBOL_154_43 = 154,                   /* $@43  */
  YYSYMBOL_blk_reward = 155,               /* blk_reward  */
  YYSYMBOL_reward_number = 156,            /* reward_number  */
  YYSYMBOL_blk_res = 157,                  /* blk_res  */
  YYSYMBOL_158_44 = 158,                   /* $@44  */
  YYSYMBOL_blk_def_res = 159,              /* blk_def_res  */
  YYSYMBOL_160_45 = 160,                   /* $@45  */
  YYSYMBOL_161_46 = 161,                   /* $@46  */
  YYSYMBOL_signal = 162,                   /* signal  */
  YYSYMBOL_dots = 163,                     /* dots  */
  YYSYMBOL_aut_list = 164,                 /* aut_list  */
  YYSYMBOL_list_member = 165,              /* list_member  */
  YYSYMBOL_aut_dom = 166,                  /* aut_dom  */
  YYSYMBOL_aut_dom_int = 167               /* aut_dom_int  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  109
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


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
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   174,   175,   180,   190,   179,   194,   195,
     203,   208,   213,   207,   217,   222,   216,   228,   229,   233,
     234,   238,   238,   246,   259,   260,   264,   282,   298,   299,
     306,   307,   324,   325,   324,   336,   340,   344,   345,   349,
     351,   348,   353,   357,   358,   359,   360,   361,   366,   372,
     376,   371,   399,   399,   428,   428,   450,   454,   455,   459,
     474,   476,   485,   487,   484,   492,   493,   497,   497,   508,
     509,   508,   511,   515,   516,   517,   521,   525,   529,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   555,   557,   555,   567,   568,   576,
     577,   576,   582,   583,   593,   597,   612,   623,   592,   631,
     632,   641,   646,   670,   640,   691,   692,   698,   702,   697,
     713,   718,   717,   721,   730,   742,   729,   774,   775,   780,
     779,   806,   823,   845,   867,   890,   917,   916,   921,   925,
     926,   925,  1056,  1057,  1062,  1061,  1066,  1070,  1071,  1075,
    1149,  1252,  1253,  1257,  1257,  1278,  1304,  1305,  1309,  1309,
    1335,  1367,  1368,  1372,  1382,  1408,  1408,  1414,  1421,  1413,
    1428,  1438,  1439,  1440,  1444,  1445,  1449,  1450,  1454,  1455,
    1459,  1460,  1464,  1465
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
  "\"end of file\"", "error", "\"invalid token\"", "TK_IDENTIFIERS",
  "TK_EVENTS", "TK_NETWORK", "TK_AUTOMATON", "TK_STATE", "TK_TRANS",
  "TK_FROM", "TK_SYN", "TK_LOC", "TK_RESULTS", "TK_CONTINUOUS",
  "TK_DISCRETE", "TK_REACH", "TK_PARTIAL", "TK_MIN", "TK_MAX",
  "TK_STATE_NUM", "TK_NBR", "TK_REWARD", "TK_SUM_RW", "TK_PROD_RW",
  "TK_ID", "TK_INTEGER", "TK_REAL", "TK_EXPONENT", "TK_LEFT_BRACKET",
  "TK_RIGHT_BRACKET", "TK_LEFT_PARENTHESIS", "TK_RIGHT_PARENTHESIS",
  "TK_LEFT_SQUARE_BRACKET", "TK_RIGHT_SQUARE_BRACKET", "TK_SEMICOLON",
  "TK_COMMA", "TK_ATTRIB", "TK_COLON", "TK_POINT", "TK_2DOTS", "TK_DOTS",
  "TK_SIMPLE", "TK_DOUBLE", "TK_PLUS", "TK_PLUS_PLUS", "TK_MINUS",
  "TK_MINUS_MINUS", "TK_MULT", "TK_DIV", "TK_AND", "TK_OR", "TK_XOR",
  "TK_NOT", "TK_EQUAL", "TK_UNEQUAL", "TK_MAJOR", "TK_MAJOR_EQUAL",
  "TK_MINOR", "TK_MINOR_EQUAL", "$accept", "start", "blk_id", "blk_int_id",
  "$@1", "$@2", "blk_int_id2", "blk_events", "blk_int_ev", "$@3", "$@4",
  "$@5", "$@6", "blk_int_ev2", "event_replic", "int_event_replic", "$@7",
  "rate", "int_rate", "semi_colon", "blk_exp_dom", "blk_def_dom", "$@8",
  "$@9", "blk_exp", "blk_exp2", "list_exp", "exp", "$@10", "$@11", "elem",
  "$@12", "$@13", "$@14", "$@15", "op_rw", "dominion", "interval",
  "interval_1", "$@16", "$@17", "id_stat", "id_replic", "$@18", "replic",
  "$@19", "$@20", "number", "op_unary", "op_bin", "reach", "$@21", "$@22",
  "t_reach", "blk_net", "$@23", "$@24", "model_type", "blk_autom", "$@25",
  "$@26", "$@27", "$@28", "blk_autom2", "blk_state", "$@29", "$@30",
  "$@31", "blk_state2", "blk_from", "$@32", "$@33", "blk_from_replic",
  "$@34", "blk_trans", "$@35", "$@36", "blk_trans2", "dst_state", "$@37",
  "dst_replic", "$@38", "blk_type_trans", "$@39", "$@40",
  "blk_type_trans2", "e_replic", "$@41", "blk_prob", "prob", "blk_replic",
  "replic_number", "$@42", "blk_queue", "queue_number", "$@43",
  "blk_reward", "reward_number", "blk_res", "$@44", "blk_def_res", "$@45",
  "$@46", "signal", "dots", "aut_list", "list_member", "aut_dom",
  "aut_dom_int", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-226)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,    -9,    28,    41,  -226,  -226,  -226,    -3,    38,    29,
    -226,  -226,  -226,  -226,    57,    56,  -226,    49,    52,    54,
      78,  -226,    12,  -226,  -226,  -226,  -226,  -226,    61,    70,
      72,    75,  -226,    75,  -226,  -226,  -226,  -226,    62,    76,
    -226,  -226,  -226,    74,  -226,  -226,    91,    -5,  -226,    62,
      77,    77,    73,    80,    62,    62,    62,  -226,  -226,    79,
    -226,    81,    84,  -226,    -9,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,    79,  -226,    -4,   -14,   -14,    10,
    -226,  -226,  -226,    82,    85,    87,    81,    75,  -226,  -226,
    -226,  -226,  -226,    35,  -226,  -226,    62,  -226,    75,  -226,
    -226,    86,  -226,    26,    88,  -226,  -226,    88,  -226,  -226,
      89,    90,    93,    62,  -226,  -226,  -226,  -226,  -226,    75,
      96,  -226,  -226,    97,  -226,  -226,  -226,    35,  -226,    92,
     100,    95,    95,  -226,    62,  -226,  -226,    35,  -226,  -226,
    -226,    91,    99,  -226,    60,   102,  -226,    -3,    -3,   104,
    -226,    75,    98,   117,  -226,  -226,  -226,    35,   106,   127,
    -226,  -226,  -226,  -226,  -226,  -226,   118,  -226,  -226,  -226,
     128,  -226,   100,   130,    80,   122,  -226,   102,  -226,  -226,
    -226,  -226,   124,    69,   150,  -226,  -226,   125,  -226,  -226,
      35,  -226,   135,   151,   136,  -226,   138,  -226,  -226,   131,
    -226,   104,    71,   134,   133,  -226,  -226,  -226,  -226,   137,
      -2,   158,   142,  -226,    35,  -226,  -226,  -226,  -226,   140,
      43,  -226,  -226,  -226,   158,   143,  -226,  -226,   139,   150,
     141,   151,  -226,     3,  -226,  -226,  -226,  -226,  -226,   147,
    -226,   148,  -226,  -226,   144,   145,  -226,  -226,   152,   153,
    -226,  -226,  -226,  -226,   149,   158,   146,   155,  -226,  -226,
    -226,  -226,  -226,   154,   156,    34,   152,  -226,  -226,  -226,
     159,  -226,  -226,  -226
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     5,     3,     1,     0,    98,     0,
      14,    11,    10,    97,     0,     0,     6,     0,     0,     0,
       0,    94,    52,    15,    12,    99,   165,     2,     0,     0,
       0,     0,    49,     0,    54,    74,    73,    75,    52,     0,
      76,    77,    78,     0,    30,    31,    42,     0,    56,    52,
      20,    20,     0,   170,    52,    52,    52,    67,    48,    61,
      47,    72,     0,    32,     9,    92,    93,    81,    82,    79,
      80,    89,    90,    91,    83,    84,    85,    86,    87,    88,
      35,    39,    57,    58,     0,    44,     0,     0,     0,     0,
     167,   166,    95,    38,     0,     0,    72,     0,    50,    60,
      69,    55,    43,     0,     8,     7,    52,    53,    66,    23,
      21,     0,    26,     0,   177,    25,    27,   177,   103,   102,
       0,     0,     0,    52,    36,    45,    46,    68,    62,     0,
       0,   174,   175,     0,    40,    59,    65,     0,    19,     0,
     181,    29,    29,   100,    52,    96,    37,     0,    51,    70,
      33,    42,     0,    24,     0,   179,    28,    18,    18,     0,
     168,     0,     0,     0,    41,    22,   182,     0,     0,     0,
     176,    17,    16,    13,   104,   101,     0,    63,    71,    34,
       0,   180,   181,     0,   170,     0,   183,   179,   105,   169,
      64,   178,   152,     0,     0,   155,   153,     0,   111,   106,
       0,   151,     0,   120,     0,   112,     0,   107,   154,   157,
     117,   110,     0,   162,   123,   109,   108,   160,   158,     0,
     173,     0,     0,   118,     0,   156,   164,   171,   172,     0,
       0,   124,   113,   121,     0,     0,   161,   163,     0,   116,
       0,   120,   159,     0,   115,   114,   122,   119,   129,     0,
     132,     0,   133,   131,     0,   138,   135,   134,     0,     0,
     130,   139,   125,   136,   146,   128,     0,     0,   140,   127,
     126,   137,   144,   148,     0,     0,   143,   145,   150,   149,
       0,   142,   141,   147
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,    42,  -226,  -226,  -226,  -226,   175,  -226,
    -226,  -226,  -226,    25,   157,  -226,  -226,   103,    83,    44,
    -226,  -226,  -226,  -226,   -19,   -51,  -226,    36,  -226,  -226,
     -43,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   101,  -226,
    -226,  -226,   -31,  -226,   105,  -226,  -226,   -87,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   -18,  -226,
    -226,  -226,  -226,  -226,   -47,  -226,  -226,  -226,  -226,   -46,
    -226,  -226,  -226,  -226,  -225,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,   -82,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
      13,  -226,  -226,  -226,  -133,    94,    11,    17,  -226
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     5,     9,    22,   105,     8,   171,    18,
      51,    17,    50,   172,    87,   111,   137,   114,   115,   157,
      43,    44,   103,   163,    93,    94,   124,    80,   106,   151,
      46,    59,   129,    47,    61,    84,   107,    98,    99,   147,
     185,   135,    58,    96,   101,   130,   162,    48,    49,    81,
      14,    28,   122,    15,    20,    52,   159,   120,   175,   183,
     192,   203,   211,   216,   199,   202,   209,   239,   245,   207,
     214,   234,   223,   240,   232,   238,   265,   270,   254,   255,
     260,   266,   262,   264,   273,   282,   268,   274,   276,   280,
     194,   197,   200,   213,   219,   224,   221,   229,    27,    53,
      91,   121,   176,   230,   133,   141,   170,   155,   168
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     116,   116,    60,    45,   152,    95,    85,    10,    11,   241,
     112,    35,    36,    37,   161,     4,   113,    82,    83,    62,
     109,   110,   226,   118,   119,     1,   116,   248,     6,    29,
      30,    31,    32,    33,   180,    92,    34,    35,    36,    37,
     269,   227,    38,   228,    39,     7,   249,   250,   251,   252,
     112,    35,    36,    37,    13,    40,   253,    41,   278,    35,
      36,    37,    19,   134,    42,    16,   128,   204,    35,    36,
      37,    21,   146,    23,   131,   132,    24,   136,    25,    29,
      30,    31,    32,    33,   166,   167,    34,    35,    36,    37,
      26,   235,    38,   195,   196,   217,   218,    54,   148,    57,
      55,    63,    56,    89,    90,    40,   104,    41,    64,    86,
     174,    97,   140,   100,    42,   102,   125,   123,   126,   138,
     143,   149,   150,   153,   165,   160,   144,   145,   154,   156,
     177,   178,    65,    66,    67,   181,    68,   169,    69,    70,
      71,    72,    73,   237,    74,    75,    76,    77,    78,    79,
     179,   182,   184,   186,   188,   190,   193,   198,   201,   205,
     206,   208,   210,   212,   220,   222,   231,   233,   242,   243,
     225,   236,   256,   257,   246,   258,   261,   259,   263,   271,
     272,   267,    12,   173,   275,   108,   158,   164,   279,   277,
     283,   117,   244,   215,   281,   247,   139,   189,   191,   187,
       0,   127,     0,     0,     0,     0,     0,     0,    88,     0,
       0,   142
};

static const yytype_int16 yycheck[] =
{
      87,    88,    33,    22,   137,    56,    49,    10,    11,   234,
      24,    25,    26,    27,   147,    24,    30,    22,    23,    38,
      24,    25,    24,    13,    14,     3,   113,    24,     0,    17,
      18,    19,    20,    21,   167,    54,    24,    25,    26,    27,
     265,    43,    30,    45,    32,     4,    43,    44,    45,    46,
      24,    25,    26,    27,    16,    43,    53,    45,    24,    25,
      26,    27,     5,   106,    52,    36,    97,   200,    25,    26,
      27,    15,   123,    24,    39,    40,    24,   108,    24,    17,
      18,    19,    20,    21,    24,    25,    24,    25,    26,    27,
      12,   224,    30,    24,    25,    24,    25,    36,   129,    24,
      30,    25,    30,    30,    24,    43,    64,    45,    34,    32,
       6,    32,    24,    32,    52,    31,    31,    35,    31,    33,
      31,    25,    25,    31,    25,   144,    36,    34,    28,    34,
     161,    33,    41,    42,    43,    29,    45,    35,    47,    48,
      49,    50,    51,   230,    53,    54,    55,    56,    57,    58,
      33,    24,    34,    25,    24,    33,    32,     7,    33,    24,
       9,    25,    24,    32,    30,    32,     8,    25,    25,    30,
      33,    31,    25,    25,    33,    31,    24,    32,    25,    33,
      25,    32,     7,   158,    30,    84,   142,   151,   275,    33,
      31,    88,   239,   211,   276,   241,   113,   184,   187,   182,
      -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,   117
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    60,    61,    24,    62,     0,     4,    66,    63,
      10,    11,    67,    16,   109,   112,    36,    70,    68,     5,
     113,    15,    64,    24,    24,    24,    12,   157,   110,    17,
      18,    19,    20,    21,    24,    25,    26,    27,    30,    32,
      43,    45,    52,    79,    80,    83,    89,    92,   106,   107,
      71,    69,   114,   158,    36,    30,    30,    24,   101,    90,
     101,    93,    83,    25,    34,    41,    42,    43,    45,    47,
      48,    49,    50,    51,    53,    54,    55,    56,    57,    58,
      86,   108,    22,    23,    94,    89,    32,    73,    73,    30,
      24,   159,    83,    83,    84,    84,   102,    32,    96,    97,
      32,   103,    31,    81,    62,    65,    87,    95,    97,    24,
      25,    74,    24,    30,    76,    77,   106,    76,    13,    14,
     116,   160,   111,    35,    85,    31,    31,   103,   101,    91,
     104,    39,    40,   163,    89,   100,   101,    75,    33,    77,
      24,   164,   164,    31,    36,    34,    84,    98,   101,    25,
      25,    88,   163,    31,    28,   166,    34,    78,    78,   115,
      83,   163,   105,    82,    86,    25,    24,    25,   167,    35,
     165,    67,    72,    72,     6,   117,   161,   101,    33,    33,
     163,    29,    24,   118,    34,    99,    25,   166,    24,   159,
      33,   165,   119,    32,   149,    24,    25,   150,     7,   123,
     151,    33,   124,   120,   163,    24,     9,   128,    25,   125,
      24,   121,    32,   152,   129,   117,   122,    24,    25,   153,
      30,   155,    32,   131,   154,    33,    24,    43,    45,   156,
     162,     8,   133,    25,   130,   163,    31,   106,   134,   126,
     132,   133,    25,    30,   123,   127,    33,   128,    24,    43,
      44,    45,    46,    53,   137,   138,    25,    25,    31,    32,
     139,    24,   141,    25,   142,   135,   140,    32,   145,   133,
     136,    33,    25,   143,   146,    30,   147,    33,    24,   106,
     148,   141,   144,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    63,    64,    62,    65,    65,
      66,    68,    69,    67,    70,    71,    67,    72,    72,    73,
      73,    75,    74,    74,    76,    76,    77,    77,    78,    78,
      79,    79,    81,    82,    80,    83,    84,    85,    85,    87,
      88,    86,    86,    89,    89,    89,    89,    89,    89,    90,
      91,    89,    92,    89,    93,    89,    89,    94,    94,    95,
      96,    96,    98,    99,    97,   100,   100,   102,   101,   104,
     105,   103,   103,   106,   106,   106,   107,   107,   107,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   110,   111,   109,   112,   112,   114,
     115,   113,   116,   116,   118,   119,   120,   121,   117,   122,
     122,   124,   125,   126,   123,   127,   127,   129,   130,   128,
     128,   132,   131,   131,   134,   135,   133,   136,   136,   138,
     137,   137,   137,   137,   137,   137,   140,   139,   139,   142,
     143,   141,   144,   144,   146,   145,   145,   147,   147,   148,
     148,   149,   149,   151,   150,   150,   152,   152,   154,   153,
     153,   155,   155,   156,   156,   158,   157,   160,   161,   159,
     159,   162,   162,   162,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     0,     0,     0,     7,     1,     0,
       2,     0,     0,     9,     0,     0,     9,     1,     0,     3,
       0,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       1,     1,     0,     0,     7,     2,     2,     2,     0,     0,
       0,     5,     0,     3,     2,     4,     4,     2,     2,     0,
       0,     5,     0,     3,     0,     3,     1,     1,     1,     2,
       1,     0,     0,     0,     7,     1,     0,     0,     3,     0,
       0,     5,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     7,     1,     0,     0,
       0,     8,     1,     1,     0,     0,     0,     0,    10,     1,
       0,     0,     0,     0,     9,     1,     0,     0,     0,     7,
       0,     0,     4,     0,     0,     0,     8,     1,     0,     0,
       3,     1,     1,     1,     2,     2,     0,     4,     0,     0,
       0,     6,     1,     0,     0,     4,     0,     3,     0,     1,
       1,     3,     0,     0,     4,     1,     3,     0,     0,     4,
       1,     3,     0,     2,     1,     0,     3,     0,     0,     7,
       0,     1,     1,     0,     1,     1,     3,     0,     4,     0,
       3,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
      yychar = yylex ();
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
  case 5: /* $@1: %empty  */
#line 180 "./src/lb/glc.y"
    { strcpy(fname,(char *) yytext);
      if(tour==1){
	    itop.reset(); 
	    ia = -1; 	
	  }
	  if(tour==4){
        itop.reset();  	
	    ia = -1; 	
      }
	}
#line 1594 "./src/lb/yacc.C"
    break;

  case 6: /* $@2: %empty  */
#line 190 "./src/lb/glc.y"
              {itop.reset();}
#line 1600 "./src/lb/yacc.C"
    break;

  case 11: /* $@3: %empty  */
#line 208 "./src/lb/glc.y"
        { if(tour==1)
	    n_events++;
	  event_type = 0;
	}
#line 1609 "./src/lb/yacc.C"
    break;

  case 12: /* $@4: %empty  */
#line 213 "./src/lb/glc.y"
        { strcpy(fname,(char*)yytext);
	  di = dl = 0;
	}
#line 1617 "./src/lb/yacc.C"
    break;

  case 14: /* $@5: %empty  */
#line 217 "./src/lb/glc.y"
        { if(tour==1)
	    n_events++;
	  event_type = 1;
	}
#line 1626 "./src/lb/yacc.C"
    break;

  case 15: /* $@6: %empty  */
#line 222 "./src/lb/glc.y"
  { strcpy(fname,(char*)yytext);
    di = dl = 0;
  }
#line 1634 "./src/lb/yacc.C"
    break;

  case 21: /* $@7: %empty  */
#line 238 "./src/lb/glc.y"
               {di = atol((char*) yytext); }
#line 1640 "./src/lb/yacc.C"
    break;

  case 22: /* int_event_replic: TK_INTEGER $@7 dots TK_INTEGER  */
#line 239 "./src/lb/glc.y"
    { dl = atol((char*) yytext); 
      n_events+= dl-di;
      if((dl-di)<0){
        Semantic_Error(fname, Parser_114);
        not_error = 0;
      }
    }
#line 1652 "./src/lb/yacc.C"
    break;

  case 23: /* int_event_replic: TK_ID  */
#line 247 "./src/lb/glc.y"
    { if(dom->get_name((char *) yytext)>=0){
        di = dom->get_first((char *) yytext);
        dl = dom->get_last((char *) yytext);
        n_events+= dl-di;        
      }
      else {
        type_error(Parser_01);
      }
    }
#line 1666 "./src/lb/yacc.C"
    break;

  case 26: /* int_rate: TK_ID  */
#line 265 "./src/lb/glc.y"
    { if(tour==4){
        if(net->get_ident_name((char *) yytext)<0){
          type_error(Parser_01);
        }
        else{
          if(dl-di<=0){
            edic->put_event(fname,event_type, "0", net->get_ident_name((char*)yytext));
          }
          else{
            for(int i=di; i<=dl; i++){
              sprintf(event_name, "%s[%d]", fname,i);
              edic->put_event(event_name,event_type, "0", net->get_ident_name((char*)yytext));
            }
          }
        }
      }
    }
#line 1688 "./src/lb/yacc.C"
    break;

  case 27: /* int_rate: number  */
#line 283 "./src/lb/glc.y"
    { if(tour==4){
        if(dl-di<=0){
          edic->put_event(fname,event_type, (char*)yytext, -1);
        }
        else{
          for(int i=di; i<=dl; i++){
            sprintf(event_name, "%s[%d]", fname,i);
            edic->put_event(event_name,event_type, (char*)yytext, -1);
          }
        }
      }
    }
#line 1705 "./src/lb/yacc.C"
    break;

  case 31: /* blk_exp_dom: blk_exp  */
#line 308 "./src/lb/glc.y"
    { if(tour==1){
    	itop.get_func(fnc);
        itop.reset();
	    t_ident->put_name(fname);
        t_ident->put_exp(fnc);
      }
      if(tour==4){
		itop.get_func(fnc);
        itop.reset();
	    net->put_ident_name(fname);
        net->put_ident_exp(fnc);
      }
    }
#line 1723 "./src/lb/yacc.C"
    break;

  case 32: /* $@8: %empty  */
#line 324 "./src/lb/glc.y"
                                      {di = atol((char*)yytext);}
#line 1729 "./src/lb/yacc.C"
    break;

  case 33: /* $@9: %empty  */
#line 325 "./src/lb/glc.y"
    { dl = atol((char*)yytext);
      dom->put_name(fname);
      if(dom->put_dom(di, dl)<0){
        Semantic_Error(fname, Parser_114);
        not_error = 0;
      }
    }
#line 1741 "./src/lb/yacc.C"
    break;

  case 39: /* $@10: %empty  */
#line 349 "./src/lb/glc.y"
    { itop.put_op((char*) yytext);}
#line 1747 "./src/lb/yacc.C"
    break;

  case 40: /* $@11: %empty  */
#line 351 "./src/lb/glc.y"
    { itop.put_elem();}
#line 1753 "./src/lb/yacc.C"
    break;

  case 44: /* elem: op_unary elem  */
#line 358 "./src/lb/glc.y"
                   { itop.put_elem(); }
#line 1759 "./src/lb/yacc.C"
    break;

  case 45: /* elem: TK_MIN TK_LEFT_PARENTHESIS blk_exp2 TK_RIGHT_PARENTHESIS  */
#line 359 "./src/lb/glc.y"
                                                              { itop.put_elem("min");}
#line 1765 "./src/lb/yacc.C"
    break;

  case 46: /* elem: TK_MAX TK_LEFT_PARENTHESIS blk_exp2 TK_RIGHT_PARENTHESIS  */
#line 360 "./src/lb/glc.y"
                                                              { itop.put_elem("max");}
#line 1771 "./src/lb/yacc.C"
    break;

  case 47: /* elem: TK_REWARD id_replic  */
#line 362 "./src/lb/glc.y"
    { strcpy(tmp,"% "); 
      sprintf(tmp,"%s%s ",tmp,tmp1);
      itop.put_elem(tmp);
    }
#line 1780 "./src/lb/yacc.C"
    break;

  case 48: /* elem: TK_STATE_NUM id_replic  */
#line 367 "./src/lb/glc.y"
    { strcpy(tmp, "@ ");
      sprintf(tmp,"%s%s ",tmp,tmp1);
      itop.put_elem(tmp);
    }
#line 1789 "./src/lb/yacc.C"
    break;

  case 49: /* $@12: %empty  */
#line 372 "./src/lb/glc.y"
    { strcpy(tmp, "@$ ");
      i1 = i2 = 0;
    }
#line 1797 "./src/lb/yacc.C"
    break;

  case 50: /* $@13: %empty  */
#line 376 "./src/lb/glc.y"
    { if(i1>i2 && tour==4){
        Semantic_Error(fname, Parser_105);
        not_error = 0;
      }
    }
#line 1807 "./src/lb/yacc.C"
    break;

  case 51: /* elem: TK_NBR $@12 interval $@13 id_replic  */
#line 382 "./src/lb/glc.y"
    { strcpy(temp,tmp1); 
      if(tour==1){
        sprintf(tmp,"%s%s %s %s ", tmp, temp, i1n, i2n);
        itop.put_elem(tmp);
      }
      if(tour==4){
        sprintf(tmp,"%s%s %d %d ", tmp, temp, i1, i2);
        itop.put_elem(tmp);
        if(net->get_name(temp, i1, i2)==-1){
          Semantic_Warning(fname, temp, Parser_103);
        }
        if(net->get_name(temp, i1, i2)==0){
          Semantic_Warning(fname, temp, Parser_104);
        }
      } 

    }
#line 1829 "./src/lb/yacc.C"
    break;

  case 52: /* $@14: %empty  */
#line 399 "./src/lb/glc.y"
     { tmp[0]='\0';
       i1 = i2 = 0;
    }
#line 1837 "./src/lb/yacc.C"
    break;

  case 53: /* elem: $@14 op_rw dominion  */
#line 403 "./src/lb/glc.y"
    { if(i1>i2 && tour==4){
        Semantic_Error(fname, Parser_105);
        not_error = 0;
      } 
      if(with_id){
        if(sum_or_prod)
    	  strcpy(tmp1,"%S ");
        else strcpy(tmp1,"%P ");
      }
      else{
        if(sum_or_prod)
          strcpy(tmp1,"%$ ");
        else
          strcpy(tmp1,"%# ");
      }
      if(tour==1){
        sprintf(tmp1,"%s%s %s %s ",tmp1, temp, i1n, i2n);
        itop.put_elem(tmp1);
      }
      if(tour==4){
        sprintf(tmp1,"%s%s %d %d ",tmp1, temp, i1, i2);
        itop.put_elem(tmp1);
      }
      
    }
#line 1867 "./src/lb/yacc.C"
    break;

  case 54: /* $@15: %empty  */
#line 428 "./src/lb/glc.y"
           {strcpy(tmp1, (char*) yytext);}
#line 1873 "./src/lb/yacc.C"
    break;

  case 55: /* elem: TK_ID $@15 replic  */
#line 430 "./src/lb/glc.y"
    { if(tour==4 || tour==1){
        if(net->get_name(tmp1, ia)>=0){
          sprintf(tmp1,"%d ", net->get_name(tmp1, ia)); 
        }
        else{
          if(net->get_name(tmp1)>=0){
            sprintf(tmp1,"%d ", net->get_name(tmp1));
          }
          else{
            if(t_ident->get_name(tmp1)<0){
              strcat(tmp1," ");          
            }
            else{
              t_ident->get_exp(tmp1,tmp1); 
            }
          }
        }
        itop.put_elem(tmp1); 
      }
    }
#line 1898 "./src/lb/yacc.C"
    break;

  case 56: /* elem: number  */
#line 450 "./src/lb/glc.y"
            { itop.put_elem((char*) yytext);}
#line 1904 "./src/lb/yacc.C"
    break;

  case 57: /* op_rw: TK_SUM_RW  */
#line 454 "./src/lb/glc.y"
              {sum_or_prod = 1; }
#line 1910 "./src/lb/yacc.C"
    break;

  case 58: /* op_rw: TK_PROD_RW  */
#line 455 "./src/lb/glc.y"
                {sum_or_prod = 0;}
#line 1916 "./src/lb/yacc.C"
    break;

  case 59: /* dominion: interval_1 id_stat  */
#line 460 "./src/lb/glc.y"
    { strcpy(temp,tmp1); 
      if(tour==4 && with_id==1){
        if(net->get_name(temp, i1, i2)==-1){
          Semantic_Warning(fname, temp, Parser_103);
        }
        if(net->get_name(temp, i1, i2)==0){
          Semantic_Warning(fname, temp, Parser_104);
        }
      } 
    }
#line 1931 "./src/lb/yacc.C"
    break;

  case 61: /* interval: %empty  */
#line 476 "./src/lb/glc.y"
    { if(tour==4){
        i1 = 0;
        i2 = net->get_net_n_aut()-1;
      }
    }
#line 1941 "./src/lb/yacc.C"
    break;

  case 62: /* $@16: %empty  */
#line 485 "./src/lb/glc.y"
              { i1 = net->get_name(tmp1); strcpy(i1n,tmp1); tmp1[0] = '\0'; }
#line 1947 "./src/lb/yacc.C"
    break;

  case 63: /* $@17: %empty  */
#line 487 "./src/lb/glc.y"
              { i2 = net->get_name(tmp1); strcpy(i2n,tmp1); tmp1[0] = '\0'; }
#line 1953 "./src/lb/yacc.C"
    break;

  case 65: /* id_stat: id_replic  */
#line 492 "./src/lb/glc.y"
              {with_id = 1;}
#line 1959 "./src/lb/yacc.C"
    break;

  case 66: /* id_stat: %empty  */
#line 493 "./src/lb/glc.y"
      {with_id = 0;}
#line 1965 "./src/lb/yacc.C"
    break;

  case 67: /* $@18: %empty  */
#line 497 "./src/lb/glc.y"
          {strcpy(tmp1,(char*) yytext);}
#line 1971 "./src/lb/yacc.C"
    break;

  case 68: /* id_replic: TK_ID $@18 replic  */
#line 499 "./src/lb/glc.y"
    { if(tour==4){
    	if(net->get_name(tmp1)>=0){
          ia = net->get_name(tmp1);
        }
      }
    }
#line 1982 "./src/lb/yacc.C"
    break;

  case 69: /* $@19: %empty  */
#line 508 "./src/lb/glc.y"
                           {strcat(tmp1,(char*) yytext);}
#line 1988 "./src/lb/yacc.C"
    break;

  case 70: /* $@20: %empty  */
#line 509 "./src/lb/glc.y"
               {strcat(tmp1,(char*) yytext);}
#line 1994 "./src/lb/yacc.C"
    break;

  case 71: /* replic: TK_LEFT_SQUARE_BRACKET $@19 TK_INTEGER $@20 TK_RIGHT_SQUARE_BRACKET  */
#line 510 "./src/lb/glc.y"
                            {strcat(tmp1,(char*) yytext);}
#line 2000 "./src/lb/yacc.C"
    break;

  case 76: /* op_unary: TK_PLUS  */
#line 522 "./src/lb/glc.y"
    { itop.put_elem("1");
      itop.put_op("*");
    }
#line 2008 "./src/lb/yacc.C"
    break;

  case 77: /* op_unary: TK_MINUS  */
#line 526 "./src/lb/glc.y"
    { itop.put_elem("-1");
      itop.put_op("*");
    }
#line 2016 "./src/lb/yacc.C"
    break;

  case 78: /* op_unary: TK_NOT  */
#line 529 "./src/lb/glc.y"
            { itop.put_op((char*) yytext);}
#line 2022 "./src/lb/yacc.C"
    break;

  case 94: /* $@21: %empty  */
#line 555 "./src/lb/glc.y"
                        {itop.reset(); ia = -1; strcpy(fname,(char *) yytext);}
#line 2028 "./src/lb/yacc.C"
    break;

  case 95: /* $@22: %empty  */
#line 557 "./src/lb/glc.y"
    { if(tour==4){
    	itop.get_func(fnc);
        itop.reset();
        net->put_reach_exp(fnc);
      }
    }
#line 2039 "./src/lb/yacc.C"
    break;

  case 97: /* t_reach: TK_PARTIAL  */
#line 567 "./src/lb/glc.y"
               {r_t = 1; PRF::prf.partial_rss();}
#line 2045 "./src/lb/yacc.C"
    break;

  case 98: /* t_reach: %empty  */
#line 568 "./src/lb/glc.y"
     {r_t = 0; PRF::prf.full_rss();}
#line 2051 "./src/lb/yacc.C"
    break;

  case 99: /* $@23: %empty  */
#line 576 "./src/lb/glc.y"
                     { net->put_net_name((char*) yytext);}
#line 2057 "./src/lb/yacc.C"
    break;

  case 100: /* $@24: %empty  */
#line 577 "./src/lb/glc.y"
                                                        { aut = 0; }
#line 2063 "./src/lb/yacc.C"
    break;

  case 102: /* model_type: TK_DISCRETE  */
#line 582 "./src/lb/glc.y"
                   { net->put_net_model(DISCRETE);}
#line 2069 "./src/lb/yacc.C"
    break;

  case 103: /* model_type: TK_CONTINUOUS  */
#line 583 "./src/lb/glc.y"
                       {net->put_net_model(CONTINUOUS);}
#line 2075 "./src/lb/yacc.C"
    break;

  case 104: /* $@25: %empty  */
#line 593 "./src/lb/glc.y"
    { if(tour==1)
        n_aut++;
    }
#line 2083 "./src/lb/yacc.C"
    break;

  case 105: /* $@26: %empty  */
#line 597 "./src/lb/glc.y"
    { replic = 1;
      strcpy(fname,(char*)yytext);
      if(tour==2){
        n_state = 0;
        if(!net->put_aut_name(aut, (char*) yytext)){
          type_error(Parser_03);
        }
        replic_map.put(aut, aut_group);
        aut++;
      }
      if(tour>=3){
        state = 0;
      }
    }
#line 2102 "./src/lb/yacc.C"
    break;

  case 106: /* $@27: %empty  */
#line 612 "./src/lb/glc.y"
    { if(tour==2){
        for(int i=1;i<=replic;i++){
          if(!net->put_aut_n_state(aut-i, n_state)){
            not_error = 0;
          }
          alloc_mat_state(aut-i, n_state);
        }
        aut_group++;
      }
    }
#line 2117 "./src/lb/yacc.C"
    break;

  case 107: /* $@28: %empty  */
#line 623 "./src/lb/glc.y"
    { if(tour>=3){
        aut+= replic;
      }
    }
#line 2126 "./src/lb/yacc.C"
    break;

  case 111: /* $@29: %empty  */
#line 641 "./src/lb/glc.y"
    { if(tour==2)
        n_state++;
      f_t = 0;
    }
#line 2135 "./src/lb/yacc.C"
    break;

  case 112: /* $@30: %empty  */
#line 646 "./src/lb/glc.y"
    { strcpy(fname,(char*)yytext);
      if(tour==3){
        n_trans = 0;
        if(t_ident->get_name((char*) yytext)>0){
          type_error(Parser_06);
        }
        for(int i=0; i<replic; i++){
          if(!net->put_state_name(aut+i, state, (char*) yytext)){
            type_error(Parser_05);
          }
          net->put_state_reward(aut+i, state, state);
        }
        state++;
        queue = 1;
      }	
      if(tour>=4){
        state++;
        queue = 1;	
        trans = 0;
      }
      queue_p = 0;
      queue_m = 0;
    }
#line 2163 "./src/lb/yacc.C"
    break;

  case 113: /* $@31: %empty  */
#line 670 "./src/lb/glc.y"
    { if(tour==3){
        for(int i=0;i<replic;i++){    
          for(int j=1;j<=queue;j++){
            mat_trans[aut+i][state-j] = n_trans;
            if(queue_p>0 && queue_p>=j && queue>1)
              mat_trans[aut+i][state-j]--;
            if(queue_m<0 && ((queue-j)<abs(queue_m))&& queue>1){
              mat_trans[aut+i][state-j]--;
            }
          }
        }
        
      }
      if(tour>=4){
        state+=queue-1;
      }
    }
#line 2185 "./src/lb/yacc.C"
    break;

  case 117: /* $@32: %empty  */
#line 698 "./src/lb/glc.y"
    { strcpy(temp,(char*)yytext);
      f_t = 1;
    }
#line 2193 "./src/lb/yacc.C"
    break;

  case 118: /* $@33: %empty  */
#line 702 "./src/lb/glc.y"
    { if(tour>=3){
        from_dst = net->get_name(temp,aut);
        if(from_dst<0){
          yynerrs++;
          not_error = 0;
          Semantic_Error_YACC(yynerrs, yylineno, temp, Parser_100);
          from_dst = 0;
        }
      }
    }
#line 2208 "./src/lb/yacc.C"
    break;

  case 121: /* $@34: %empty  */
#line 718 "./src/lb/glc.y"
    { sprintf(temp,"%s[%s]",temp,(char*)yytext);
     }
#line 2215 "./src/lb/yacc.C"
    break;

  case 124: /* $@35: %empty  */
#line 730 "./src/lb/glc.y"
    { if (tour==3){
        n_trans++;
        if(f_t)
          for(int i=0;i<replic;i++){    
            mat_trans[aut+i][from_dst]++;
          }
      }
      n_mst = 0;
      n_sync = 0;
      n_local = 0;  
    }
#line 2231 "./src/lb/yacc.C"
    break;

  case 125: /* $@36: %empty  */
#line 742 "./src/lb/glc.y"
    { if(tour==4){
        if(f_t==0){
     	for(int i=0; i<replic; i++){
      	  for(int j=abs(queue_m); j<(queue-queue_p); j++){	
              if(!net->put_event_n_mst(aut+i, state+j-1, n_mst))
                not_error = 0;
              if(!net->put_event_n_sync(aut+i, state+j-1, n_sync))
                not_error = 0;
              if(!net->put_event_n_local(aut+i, state+j-1, n_local))
                not_error = 0;
//              cout << "aloc(" << aut+i << "," << state+j-1 << "): m(" << n_mst << ") - s(" << n_sync <<  ") - l(" << n_local << ")\n";
            }
          }
        }
        else{
      	for(int i=0; i<replic; i++){
            if(!net->put_event_n_mst(aut+i, from_dst, n_mst))
              not_error = 0;
            if(!net->put_event_n_sync(aut+i, from_dst, n_sync))
              not_error = 0;
            if(!net->put_event_n_local(aut+i, from_dst, n_local))
              not_error = 0;
//              cout << "+aloc(" << aut+i << "," << from_dst << "): m(" << n_mst << ") - s(" << n_sync <<  ") - l(" << n_local << ")\n";

          }
        }
      }
    }
#line 2264 "./src/lb/yacc.C"
    break;

  case 129: /* $@37: %empty  */
#line 780 "./src/lb/glc.y"
    {if(tour>=4)
  	 sprintf(aux_dst,"%s",(char*) yytext);
    }
#line 2272 "./src/lb/yacc.C"
    break;

  case 130: /* dst_state: TK_ID $@37 dst_replic  */
#line 784 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){
          for(int i=0; i<replic; i++){
            for(int j=0; j<queue; j++){	
              from_dst = net->put_trans_dst(aut+i,state+j-1,1,aux_dst);
              if(from_dst<0){
                type_error(Parser_100); 
              }  
            }
          }
        }
        else{
          for(int i=0; i<replic; i++){
            if(net->put_from_dst(aut+i,from_dst,aux_dst)<0){
              type_error(Parser_100); 
            }  
          }
        }
        queue_p = 0;
        queue_m = 0;
      }
    }
#line 2299 "./src/lb/yacc.C"
    break;

  case 131: /* dst_state: TK_EQUAL  */
#line 807 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){
          for(int i=0; i<replic; i++){
            for(int j=0; j<queue; j++){	
        	  net->put_trans_dst(aut+i,state+j-1,4,(char*) yytext);
        	  from_dst = state-1;
            }
          }
        }
        else{
          type_error(Parser_115); 
        }
        queue_p = 0;
        queue_m = 0;
      }
    }
#line 2320 "./src/lb/yacc.C"
    break;

  case 132: /* dst_state: TK_PLUS_PLUS  */
#line 824 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){   
          for(int i=0; i<replic; i++){
            for(int j=0; j<queue-1; j++){	
              from_dst = net->put_trans_dst(aut+i,state+j-1,2,(char*) yytext);
              if(from_dst<0){
                type_error(Parser_101); 
              }  
            }
          }
          if(queue==1){
            type_error(Parser_101); 
          }
        }
        else{
          type_error(Parser_115); 
        }
        queue_m = 0;        
      }
      queue_p = 1;
    }
#line 2346 "./src/lb/yacc.C"
    break;

  case 133: /* dst_state: TK_MINUS_MINUS  */
#line 846 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){
          for(int i=0; i<replic; i++){
            for(int j=1; j<queue; j++){	
              from_dst = net->put_trans_dst(aut+i,state+j-1,3,(char*) yytext);
              if(from_dst<0){
                type_error(Parser_101); 
              }  
            }
          }
          if(queue==1){
            type_error(Parser_101); 
          }
        }
        else{
          type_error(Parser_115); 
        }
        queue_p = 0;                
      }
      queue_m = -1;
    }
#line 2372 "./src/lb/yacc.C"
    break;

  case 134: /* dst_state: TK_MINUS TK_INTEGER  */
#line 868 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){
          for(int i=0; i<replic; i++){
            for(int j=atol((char*)yytext); j<queue; j++){	
          	sprintf(aux_dst,"-%s",(char*) yytext);
              from_dst = net->put_trans_dst(aut+i,state+j-1,5,aux_dst);
              if(from_dst<0){
                type_error(Parser_101); 
              }  
            }
          }
          if(queue==1){
            type_error(Parser_101); 
          }          
        }
        else{
          type_error(Parser_115); 
        }
        queue_p = 0;
      }
      queue_m = - atol((char*) yytext);
    }
#line 2399 "./src/lb/yacc.C"
    break;

  case 135: /* dst_state: TK_PLUS TK_INTEGER  */
#line 891 "./src/lb/glc.y"
    { if(tour>=4){
        if(f_t==0){
          for(int i=0; i<replic; i++){
            for(int j=0; j<queue-atol((char*)yytext); j++){	
          	sprintf(aux_dst,"-%s",(char*) yytext);
              from_dst = net->put_trans_dst(aut+i,state+j-1,5,aux_dst);
              if(from_dst<0){
                type_error(Parser_101); 
              }  
            }
          }
          if(queue==1){
            type_error(Parser_101); 
          }          
        }
        else{
          type_error(Parser_115); 
        }
        queue_m = 0;
      }
      queue_p = atol((char*) yytext);
    }
#line 2426 "./src/lb/yacc.C"
    break;

  case 136: /* $@38: %empty  */
#line 917 "./src/lb/glc.y"
    { if(tour>=4)
        sprintf(aux_dst,"%s[%s]",aux_dst,(char*) yytext);
    }
#line 2434 "./src/lb/yacc.C"
    break;

  case 139: /* $@39: %empty  */
#line 925 "./src/lb/glc.y"
          {strcpy(event_name, (char*)yytext);}
#line 2440 "./src/lb/yacc.C"
    break;

  case 140: /* $@40: %empty  */
#line 926 "./src/lb/glc.y"
    { if(tour>=4){
        if(edic->get_type(event_name)<0){
          type_error(Parser_04);
      }
      else{
        event_type = edic->get_type(event_name);
        event_rate = edic->get_f_rate(event_name);
        if(event_rate<0){
          edic->get_rate(event_name, fname);
        }
        switch(event_type){
          case 0: if(tour==4) // local event
                    n_local++;
                  if(tour==5){
                    if(f_t==0){
                      for(int i=0; i<replic; i++){
      	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                          if(net->put_local_name(aut+i, state+j-1, event_name)==0){
                            type_error(Parser_112);
                          }
                  	    if((from_dst+j)==(state+j-1)){
                            net->put_local_rate(aut+i, state+j-1,  0, "0", -1);
                            cout << "Semantic Warning - " << event_name << " - (** " \
                                 << Parser_111 <<  " **)." \
                                 << endl;
                          }
                          else{
                            if(event_rate>=0){
                              net->put_local_rate(aut+i, state+j-1, 1, "0", event_rate);
                            }
                            else{
                              net->put_local_rate(aut+i, state+j-1, 0, fname, -1);
                            }
                          }
                        }
                      }
                    } 
                    else{
                      for(int i=0; i<replic; i++){
                        if(net->put_local_name(aut+i, from_dst, event_name)==0){
                          type_error(Parser_112);
                        }
                	    if(from_dst==net->get_name(aux_dst,aut+i)){
                          net->put_local_rate(aut+i, from_dst, 0, "0", -1);
                          cout << "Semantic Warning - " << event_name << " - (** " \
                               << Parser_111 <<  " **)." \
                               << endl;
                        }
                        else{
                          if(event_rate>=0){
                            net->put_local_rate(aut+i, from_dst, 1, "0", event_rate);
                          }
                          else{
                            net->put_local_rate(aut+i, from_dst, 0, fname, -1);
                          }
                        }
                      }
                    }
                  }
            break; 
          case 1: if(edic->get_mst(event_name)==aut || edic->get_mst(event_name)<0){ // synchronized event
                    if(tour==4)
                      n_mst++;
                      edic->put_mst(event_name, aut);                      
                    if(tour==5){
                      if(f_t==0){
                      	for(int i=0; i<replic; i++){
          	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                            if(net->put_mst_name(aut+i, state+j-1, event_name)==0){
                              type_error(Parser_112);
                            }
                            if(event_rate>=0){
                              net->put_mst_rate(aut+i, state+j-1, 1, "-1", event_rate);
                            }
                            else{
                              net->put_mst_rate(aut+i, state+j-1, 0, fname, -1);                          
                            }
                            event_mst = 1;
                          }
                        }
                      }
                      else{
                    	  for(int i=0; i<replic; i++){
                          if(net->put_mst_name(aut+i, from_dst, event_name)==0){
                            type_error(Parser_112);
                          }
                          if(event_rate>=0){
                            net->put_mst_rate(aut+i, from_dst, 1, "-1",event_rate);
                          }
                          else{
                            net->put_mst_rate(aut+i, from_dst, 0, fname, -1);                          
                          }
                          event_mst = 1;                    	  
                        }
                      }
                    }  
                  }
                  else{
                    if(tour==4)
                      n_sync++;
                    if(tour==5){
                      if(f_t==0){
                    	for(int i=0; i<replic; i++){ 
        	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                            if(net->put_sync_name(aut+i, state+j-1, event_name)==0){
                              type_error(Parser_112);
                            }            	
                            event_mst = 0;
                          }
                        }
                      }  
                      else{
                      	for(int i=0; i<replic; i++){ 
                          if(net->put_sync_name(aut+i, from_dst, event_name)==0){
                            type_error(Parser_112);
                          }            	
                          event_mst = 0;
                        }
                      }
                    }                  
                  }
            break;
          }
        }
      }
    }
#line 2571 "./src/lb/yacc.C"
    break;

  case 144: /* $@41: %empty  */
#line 1062 "./src/lb/glc.y"
    { if(tour>=4)
        sprintf(event_name,"%s[%s]",event_name,(char*) yytext);
    }
#line 2579 "./src/lb/yacc.C"
    break;

  case 149: /* prob: number  */
#line 1076 "./src/lb/glc.y"
    { switch(event_type){
        case 0: if(tour==5){
              	if(event_rate>=0){
              	  net->get_ident_exp(event_rate, fname);
              	}
              	sprintf(tmp1,"%s %s * ", yytext, fname);
              	if(net->get_ident_exp(tmp1)<0){
              	  net->put_ident_name("new_rate");
              	  net->put_ident_exp(tmp1);
              	}
              	if(f_t==0){
                	for(int i=0; i<replic; i++){
    	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                	    if((from_dst+j)==(state+j-1))
                          net->put_local_rate(aut+i, state+j-1, 0, "0", -1);
                        else
                          net->put_local_rate(aut+i, state+j-1, 1, (char *)yytext, net->get_ident_exp(tmp1));
                      }
                    }
                  }
                  else{
                    for(int i=0; i<replic; i++){
               	   if(from_dst==net->get_name(aux_dst,aut+i)){
                        net->put_local_rate(aut+i, from_dst, 0, "0", -1);
                      }
                      else{
                        net->put_local_rate(aut+i, from_dst, 1, (char *)yytext, net->get_ident_exp(tmp1));
                      }
                    }
                  }
                }
          break; 
        case 1: if(tour==5){
        	      if(edic->get_mst(event_name)==aut || edic->get_mst(event_name)<0){
                	if(event_rate>=0){
                	  net->get_ident_exp(event_rate, fname);                  
                	}
                	sprintf(tmp1,"%s %s *", yytext, fname);
                	if(net->get_ident_exp(tmp1)<0){
                	  net->put_ident_name("new_rate");
                	  net->put_ident_exp(tmp1);
                	}
                	if(f_t==0){
                  	for(int i=0; i<replic; i++){
      	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                  	    net->put_mst_rate(aut+i, state+j-1, 1, (char*) yytext, net->get_ident_exp(tmp1));
                        }
                      }
                    }
                    else{
                  	for(int i=0; i<replic; i++){
                	      net->put_mst_rate(aut+i, from_dst, 1, (char*) yytext, net->get_ident_exp(tmp1));
                      }
                    }
                  }
                  else{
                    if(f_t==0){
                  	for(int i=0; i<replic; i++){
    	                for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                          net->put_sync_prob(aut+i, state+j-1, 0, (char*) yytext, -1);
                        }
                      }
                    }
                    else{
                  	for(int i=0; i<replic; i++){
                        net->put_sync_prob(aut+i, from_dst, 0, (char*) yytext, -1);
                      }
                    }
                  }
                }
          break;
      }
    }
#line 2657 "./src/lb/yacc.C"
    break;

  case 150: /* prob: TK_ID  */
#line 1150 "./src/lb/glc.y"
    { switch(event_type){
        case 0: if(tour==5){
          	    if(net->get_ident_name((char *) yytext)<0){
          	      type_error(Parser_01);
          	    }
          	    else{
                	if(event_rate>=0){
              	    net->get_ident_exp(event_rate, fname);
              	  }
                	net->get_ident_exp((char*) yytext, tmp1);
              	  sprintf(tmp1,"%s %s * ", tmp1, fname);
                	if(net->get_ident_exp(tmp1)<0){
                	  net->put_ident_name("new_rate");
                	  net->put_ident_exp(tmp1);
              	  }
                    if(f_t==0){
                  	for(int i=0; i<replic; i++){
      	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                  	    if((from_dst+j)==(state+j-1))
                            net->put_local_rate(aut+i, state+j-1, 0, "0", -1);
                          else
                            net->put_local_rate(aut+i, state+j-1, 1, "0", net->get_ident_exp(tmp1));
                        }
                      }
                    }
                    else{
                  	for(int i=0; i<replic; i++){
                 	   if(from_dst==net->get_name(aux_dst,aut+i)){
                          net->put_local_rate(aut+i, from_dst, 0, "0", -1);
                        }
                        else{
                          net->put_local_rate(aut+i, from_dst, 1, "0", net->get_ident_exp(tmp1));
                        }
                      }
                    }
                  }
                }
          break; 
        case 1: if(tour==5){
                  if(edic->get_mst(event_name)==aut || edic->get_mst(event_name)<0){
          	      if(net->get_ident_name((char *) yytext)<0){
            	      type_error(Parser_01);
                    }
            	    else{
                  	if(event_rate>=0){
                	    net->get_ident_exp(event_rate, fname);
                	  }
                	  net->get_ident_exp((char*) yytext, tmp1);
                	  sprintf(tmp1,"%s %s *", tmp1, fname);
                  	if(net->get_ident_exp(tmp1)<0){
                  	  net->put_ident_name("new_rate");
                  	  net->put_ident_exp(tmp1);
                	  }
                	  if(f_t==0){
                    	for(int i=0; i<replic; i++){
      	                for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                    	    net->put_mst_rate(aut+i, state+j-1, 1, (char*) yytext, net->get_ident_exp(tmp1));
                          }
                        }
                      }
                      else{
                    	for(int i=0; i<replic; i++){
                  	    net->put_mst_rate(aut+i, from_dst, 1, (char*) yytext, net->get_ident_exp(tmp1));
                        }
                      }
                    }
                  }
                  else{
                    if(f_t==0){
                  	for(int i=0; i<replic; i++){
      	              for(int j=abs(queue_m); j<(queue-queue_p); j++){	
                  	    if(net->get_ident_name((char *) yytext)<0){
    	                    type_error(Parser_01);
                  	    }
                  	    else{
                            net->put_sync_prob(aut+i, state+j-1,  1, (char *) yytext, net->get_ident_name((char *) yytext));
                          }
                        } 
                      }
                    }
                    else{
                  	for(int i=0; i<replic; i++){
                	    if(net->get_ident_name((char *) yytext)<0){
  	                    type_error(Parser_01);
                	    }
                	    else{
                          net->put_sync_prob(aut+i, from_dst, 1, (char *) yytext, net->get_ident_name((char *) yytext));
                        }
                      }
                    } 
                  }
                }
          break;
      }
    }
#line 2757 "./src/lb/yacc.C"
    break;

  case 153: /* $@42: %empty  */
#line 1257 "./src/lb/glc.y"
               {di = atol((char*) yytext);}
#line 2763 "./src/lb/yacc.C"
    break;

  case 154: /* replic_number: TK_INTEGER $@42 dots TK_INTEGER  */
#line 1258 "./src/lb/glc.y"
    { dl = atol((char*) yytext);
      replic = dl - di+1;
      if(replic<1){
        Semantic_Error(fname, Parser_114);
        not_error = 0;
      }
      if(tour==1){
        n_aut+= replic - 1;
      }
      if(tour==2){
        aut--;
        net->get_aut_name(aut, temp);
        for(int i=di;i<=dl;i++){
          sprintf(aut_replic,"%s[%d]",temp,i);
          net->put_aut_name(aut, aut_replic);
          replic_map.put(aut, aut_group);
          aut++;
        }
      }
    }
#line 2788 "./src/lb/yacc.C"
    break;

  case 155: /* replic_number: TK_ID  */
#line 1279 "./src/lb/glc.y"
    { if(dom->get_name((char *) yytext)>=0){
        di = dom->get_first((char *) yytext);
        dl = dom->get_last((char *) yytext);
        replic = dl-di+1;
        if(tour==1){
          n_aut+= replic-1;
        }
        if(tour==2){
          aut--;
          net->get_aut_name(aut, temp);
          for(int i=di;i<=dl;i++){
            sprintf(aut_replic,"%s[%d]",temp,i);
            net->put_aut_name(aut, aut_replic);
            replic_map.put(aut, aut_group);
            aut++;
          }
        }
      }
      else {
        type_error(Parser_01);
      }
    }
#line 2815 "./src/lb/yacc.C"
    break;

  case 158: /* $@43: %empty  */
#line 1309 "./src/lb/glc.y"
               {di = atol((char*) yytext);}
#line 2821 "./src/lb/yacc.C"
    break;

  case 159: /* queue_number: TK_INTEGER $@43 dots TK_INTEGER  */
#line 1310 "./src/lb/glc.y"
    { dl = atol((char*) yytext);
      queue = dl - di+1;
      if(queue<1){
        Semantic_Error(fname, Parser_114);
        not_error = 0;
      }
      if(tour==2){
        n_state+= queue-1;
      }
      if(tour==3){
        state--;
        net->get_state_name(aut, state, temp);
        for(int i=di;i<=dl;i++){
          sprintf(state_queue,"%s[%d]",temp,i);
          if(t_ident->get_name(state_queue)>0){
            type_error(Parser_06);
          }
          for(int j=0; j<replic; j++){
            net->put_state_name(aut+j, state, state_queue);
            net->put_state_reward(aut+j, state, state);
          }
          state++;
        }
      }
    }
#line 2851 "./src/lb/yacc.C"
    break;

  case 160: /* queue_number: TK_ID  */
#line 1336 "./src/lb/glc.y"
    { if(dom->get_name((char *) yytext)>=0){
        di = dom->get_first((char *) yytext);
        dl = dom->get_last((char *) yytext);
        queue = dl - di+1;
        if(tour==2){
          n_state+= queue-1;
        }
        if(tour==3){
          state--;
          net->get_state_name(aut, state, temp);
          for(int i=di;i<=dl;i++){
            sprintf(state_queue,"%s[%d]",temp,i);
            if(t_ident->get_name(state_queue)>0){
              type_error(Parser_06);
            }
            for(int j=0; j<replic; j++){
              net->put_state_name(aut+j, state, state_queue);
              net->put_state_reward(aut+j, state, state);
            }
            state++;
          }
        }
      }
      else {
        type_error(Parser_01);
      }
    }
#line 2883 "./src/lb/yacc.C"
    break;

  case 163: /* reward_number: signal number  */
#line 1373 "./src/lb/glc.y"
    { strcat(temp, (char*) yytext);
      if(tour==3){
        for(int i=0; i<replic;i++){
          for(int j=0; j<queue; j++){
    	    net->put_state_reward(aut+i,state-1-j,atof(temp));
    	  }
        }
      }   	
    }
#line 2897 "./src/lb/yacc.C"
    break;

  case 164: /* reward_number: TK_ID  */
#line 1383 "./src/lb/glc.y"
    { if(t_ident->get_name((char *) yytext)>=0){
    	if(t_ident->exp_value(t_ident->get_name((char *) yytext), &v_tmp)){
          if(tour==3){
            for(int i=0; i<replic;i++){
              for(int j=0; j<queue; j++){
    	        net->put_state_reward(aut+i,state-1-j,v_tmp);
    	      }
            }
          }
        }
        else{
          type_error(Parser_02);
        }
      }
      else{
        type_error(Parser_01);
      }   	
    }
#line 2920 "./src/lb/yacc.C"
    break;

  case 165: /* $@44: %empty  */
#line 1408 "./src/lb/glc.y"
               {itop.reset(); }
#line 2926 "./src/lb/yacc.C"
    break;

  case 167: /* $@45: %empty  */
#line 1414 "./src/lb/glc.y"
    { if(tour==4){
    	net->put_result_name((char *) yytext);
	    strcpy(fname,(char *) yytext);    	
	    ia = -1;
      }
    }
#line 2937 "./src/lb/yacc.C"
    break;

  case 168: /* $@46: %empty  */
#line 1421 "./src/lb/glc.y"
    { if(tour==4){
    	itop.get_func(fnc);
        itop.reset();
        net->put_result_exp(fnc);
      }
    }
#line 2948 "./src/lb/yacc.C"
    break;

  case 171: /* signal: TK_PLUS  */
#line 1438 "./src/lb/glc.y"
            {strcpy(temp, "");}
#line 2954 "./src/lb/yacc.C"
    break;

  case 172: /* signal: TK_MINUS  */
#line 1439 "./src/lb/glc.y"
              {strcpy(temp, "-");}
#line 2960 "./src/lb/yacc.C"
    break;

  case 173: /* signal: %empty  */
#line 1440 "./src/lb/glc.y"
     {strcpy(temp, "");}
#line 2966 "./src/lb/yacc.C"
    break;


#line 2970 "./src/lb/yacc.C"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
  ++yynerrs;

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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1467 "./src/lb/glc.y"



void Init_Variables()
{
  yylineno = 0;
}


//int main()
//void Compile_Network(peps_name name, const char* path_, const char* results_path_)
void Compile_Network(const peps_name san_level_name, const peps_name des_level_name)
{ 
  peps_name n_tmp;
  peps_name n_tmp1;

  net = new NET;
  t_ident = new FUNC;
  dom = new DOM;
  edic = new EDIC;

  sprintf(n_tmp, "%s.san", san_level_name);

  n_aut = 0;
  aut = 0;
  state = 0;
  tour = 0;
  n_events = 0;

  t_ident->alloc(2); // auxiliar table to identifiers
  dom->alloc(1); // auxiliar table to dominion
  net->reset();
   
  Init_Variables();
  tour++; // first pass
  yyin = fopen(n_tmp, "r");
  yyparse();
  fclose(yyin);


  if(not_error){
    aut_group = 0;
    not_error = net->put_net_n_aut(n_aut); // alloc n_aut automata
    replic_map.create(n_aut); // create replic map to n_aut automata    
    alloc_mat_aut(n_aut); // alloc matrix to store automata-state
    edic->put_n_event(n_events);
    Init_Variables();
    net->reset();    
    tour++; // second pass
    yyin = fopen(n_tmp, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
  }

  if(not_error){
    Init_Variables();
    net->reset();
    tour++; // third pass
    yyin = fopen(n_tmp, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    if(!net->put_net_n_ident(2))// alloc n_ident identifiers structure
      not_error = 0; 
    if(!net->put_net_n_result(2)) // alloc n_result results structure
      not_error = 0; 

    for(int i=0; i<net->get_net_n_aut(); i++){
      for(int j=0; j<net->get_aut_n_state(i); j++){
        if(!net->put_state_n_trans(i, j, mat_trans[i][j]))
          not_error = 0;
      }
    }
  }

  if(not_error){
    Init_Variables();
    net->reset();
    tour++; // fourth pass
    yyin = fopen(n_tmp, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    if(!net->rm_ident_cnst()){
      not_error = 0;
    }
    if(!net->rm_reach_cnst()){
      not_error = 0;     
    }        
    if(!net->rm_result_cnst()){
      not_error = 0;     
    }
  }

  if(not_error){
    Init_Variables();
    net->reset();
    tour++; // fifth pass
    yyin = fopen(n_tmp, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
  }

  if(not_error){
    strcpy(n_tmp, des_level_name);  	
    net->put2file_des(n_tmp);
    net->put2file_dic(n_tmp);
    net->put2file_tft(n_tmp);
    if(!r_t){
      net->put2file_fct(n_tmp);
      cout << endl;
    }
    else{
      if(!Exists_File(n_tmp, fct_file)){
        net->put2file_fct(n_tmp);
        cout << " (partial reachable state space)\n";
      }
      else{
        cout << " :-) existing file '" << n_tmp << ".fct ' used as reachable state space\n";  
      }
    } 
    net->put2file_res(n_tmp);
  } 

  itop.reset();

  if(net)
    delete net;
  if(t_ident)
    delete t_ident;
  if(dom)
    delete dom;
  if(edic)
    delete edic;

  if(!not_error)
    exit(1);
}
