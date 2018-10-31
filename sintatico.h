/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SINTATICO_H_INCLUDED
# define YY_YY_SINTATICO_H_INCLUDED
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
    T_PROGRAMA = 258,
    T_INICIO = 259,
    T_FIM = 260,
    T_FUNCAO = 261,
    T_FIMFUNCAO = 262,
    T_IDENTIF = 263,
    T_LEIA = 264,
    T_ESCREVA = 265,
    T_ENQTO = 266,
    T_FACA = 267,
    T_FIMENQTO = 268,
    T_PARA = 269,
    T_DE = 270,
    T_ATE = 271,
    T_PASSO = 272,
    T_FIMPARA = 273,
    T_SE = 274,
    T_ENTAO = 275,
    T_SENAO = 276,
    T_FIMSE = 277,
    T_ATRIB = 278,
    T_VEZES = 279,
    T_DIV = 280,
    T_MAIS = 281,
    T_MENOS = 282,
    T_MAIOR = 283,
    T_MENOR = 284,
    T_IGUAL = 285,
    T_E = 286,
    T_OU = 287,
    T_V = 288,
    T_F = 289,
    T_NUMERO = 290,
    T_NAO = 291,
    T_ABRE = 292,
    T_FECHA = 293,
    T_VETOR = 294,
    T_LOGICO = 295,
    T_INTEIRO = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTATICO_H_INCLUDED  */
