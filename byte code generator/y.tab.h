
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 68 "syntax.y"

	#include <vector>
	using namespace std;



/* Line 1676 of yacc.c  */
#line 47 "y.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     int_word = 258,
     bool_word = 259,
     float_word = 260,
     if_word = 261,
     else_word = 262,
     while_word = 263,
     IDENTIFIER = 264,
     INT = 265,
     REAL = 266,
     BOOL = 267,
     ARTHOP = 268,
     RELOP = 269,
     BOOLOP = 270,
     ASSIGN = 271,
     SEMICOLON = 272,
     LEFTBRACKET = 273,
     RIGHTBRACKET = 274,
     LEFTCURLY = 275,
     RIGHTCURLY = 276
   };
#endif
/* Tokens.  */
#define int_word 258
#define bool_word 259
#define float_word 260
#define if_word 261
#define else_word 262
#define while_word 263
#define IDENTIFIER 264
#define INT 265
#define REAL 266
#define BOOL 267
#define ARTHOP 268
#define RELOP 269
#define BOOLOP 270
#define ASSIGN 271
#define SEMICOLON 272
#define LEFTBRACKET 273
#define RIGHTBRACKET 274
#define LEFTCURLY 275
#define RIGHTCURLY 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 75 "syntax.y"

    int intVal;
    float floatVal;
    int boolVal;
    char* id;
    char* op;
    int exType;
    struct {
		vector<int> *trueList, *falseList;
	} boolEx;
	struct {
		vector<int> *nextList;
	} stmt;
    int primType;



/* Line 1676 of yacc.c  */
#line 124 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

