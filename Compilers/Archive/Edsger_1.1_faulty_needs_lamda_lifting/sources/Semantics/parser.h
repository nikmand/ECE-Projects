/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_for = 258,
    T_if = 259,
    T_new = 260,
    T_delete = 261,
    T_else = 262,
    T_void = 263,
    T_byref = 264,
    T_break = 265,
    T_continue = 266,
    T_return = 267,
    T_id = 268,
    T_type = 269,
    T_double_plus = 270,
    T_times_eq = 271,
    T_div_eq = 272,
    T_mod_eq = 273,
    T_plus_eq = 274,
    T_minus_eq = 275,
    T_true = 276,
    T_false = 277,
    T_NULL = 278,
    T_int_const = 279,
    T_char_const = 280,
    T_double_const = 281,
    T_string_literal = 282,
    T_be = 283,
    T_le = 284,
    T_ee = 285,
    T_ne = 286,
    T_umbershant_and = 287,
    T_umbershant_or = 288,
    T_double_minus = 289,
    Then = 290,
    Pointer = 291,
    TypeCast = 292,
    Prefix = 293,
    UNARY = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 84 "parser.y" /* yacc.c:1909  */

	struct {
		char name[256];
		int counter;
		double d;
		char c;
		int isStatement;
               	Type type;
		struct dec_node *dec_head;
		struct dec_node *dec_tail;
		int dec_index ;
		int by_ref_idx ;
		bool dynamic;  
		bool rv ;
		bool has_return;
		bool null_const;
		struct type_node *head;
		struct type_node *tail;
		bool has_reference; /* for array comparison */
		SymbolEntry *reference;
	}general ;

#line 117 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
