/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_LB_YACC_H_INCLUDED
# define YY_YY_SRC_LB_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_IDENTIFIERS = 258,          /* TK_IDENTIFIERS  */
    TK_EVENTS = 259,               /* TK_EVENTS  */
    TK_NETWORK = 260,              /* TK_NETWORK  */
    TK_AUTOMATON = 261,            /* TK_AUTOMATON  */
    TK_STATE = 262,                /* TK_STATE  */
    TK_TRANS = 263,                /* TK_TRANS  */
    TK_FROM = 264,                 /* TK_FROM  */
    TK_SYN = 265,                  /* TK_SYN  */
    TK_LOC = 266,                  /* TK_LOC  */
    TK_RESULTS = 267,              /* TK_RESULTS  */
    TK_CONTINUOUS = 268,           /* TK_CONTINUOUS  */
    TK_DISCRETE = 269,             /* TK_DISCRETE  */
    TK_REACH = 270,                /* TK_REACH  */
    TK_PARTIAL = 271,              /* TK_PARTIAL  */
    TK_MIN = 272,                  /* TK_MIN  */
    TK_MAX = 273,                  /* TK_MAX  */
    TK_STATE_NUM = 274,            /* TK_STATE_NUM  */
    TK_NBR = 275,                  /* TK_NBR  */
    TK_REWARD = 276,               /* TK_REWARD  */
    TK_SUM_RW = 277,               /* TK_SUM_RW  */
    TK_PROD_RW = 278,              /* TK_PROD_RW  */
    TK_ID = 279,                   /* TK_ID  */
    TK_INTEGER = 280,              /* TK_INTEGER  */
    TK_REAL = 281,                 /* TK_REAL  */
    TK_EXPONENT = 282,             /* TK_EXPONENT  */
    TK_LEFT_BRACKET = 283,         /* TK_LEFT_BRACKET  */
    TK_RIGHT_BRACKET = 284,        /* TK_RIGHT_BRACKET  */
    TK_LEFT_PARENTHESIS = 285,     /* TK_LEFT_PARENTHESIS  */
    TK_RIGHT_PARENTHESIS = 286,    /* TK_RIGHT_PARENTHESIS  */
    TK_LEFT_SQUARE_BRACKET = 287,  /* TK_LEFT_SQUARE_BRACKET  */
    TK_RIGHT_SQUARE_BRACKET = 288, /* TK_RIGHT_SQUARE_BRACKET  */
    TK_SEMICOLON = 289,            /* TK_SEMICOLON  */
    TK_COMMA = 290,                /* TK_COMMA  */
    TK_ATTRIB = 291,               /* TK_ATTRIB  */
    TK_COLON = 292,                /* TK_COLON  */
    TK_POINT = 293,                /* TK_POINT  */
    TK_2DOTS = 294,                /* TK_2DOTS  */
    TK_DOTS = 295,                 /* TK_DOTS  */
    TK_SIMPLE = 296,               /* TK_SIMPLE  */
    TK_DOUBLE = 297,               /* TK_DOUBLE  */
    TK_PLUS = 298,                 /* TK_PLUS  */
    TK_PLUS_PLUS = 299,            /* TK_PLUS_PLUS  */
    TK_MINUS = 300,                /* TK_MINUS  */
    TK_MINUS_MINUS = 301,          /* TK_MINUS_MINUS  */
    TK_MULT = 302,                 /* TK_MULT  */
    TK_DIV = 303,                  /* TK_DIV  */
    TK_AND = 304,                  /* TK_AND  */
    TK_OR = 305,                   /* TK_OR  */
    TK_XOR = 306,                  /* TK_XOR  */
    TK_NOT = 307,                  /* TK_NOT  */
    TK_EQUAL = 308,                /* TK_EQUAL  */
    TK_UNEQUAL = 309,              /* TK_UNEQUAL  */
    TK_MAJOR = 310,                /* TK_MAJOR  */
    TK_MAJOR_EQUAL = 311,          /* TK_MAJOR_EQUAL  */
    TK_MINOR = 312,                /* TK_MINOR  */
    TK_MINOR_EQUAL = 313           /* TK_MINOR_EQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_LB_YACC_H_INCLUDED  */
