%language "c++"
%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define api.parser.class { parser }
%define api.namespace { yy }
%define api.token.prefix {TOKEN_}
%define parse.lac full
%define parse.error verbose
%define parse.trace

%code requires
{
#include <iostream>
#include <stdexcept>
//forward declaration
namespace yy { class Driver; }
}

%code {
#include "driver.hpp"

namespace yy {
parser::symbol_type yylex(Driver* driver) { return driver->yylex(); }
}

}

%param {yy::Driver* driver}

%token
    IF      "if"
    ELSE    "else"
    WHILE   "while"
    PRINT   "print"
;
%token
    QMARK   "?"
    LPAREN   "("
    RPAREN   ")"
    LBRACE   "{"
    RBRACE   "}"
    SCOLON  ";"
    COLON    ":"
    COMMA    ","
;
%token
    PLUS        "+"
    MINUS       "-"
    MULTIPLY    "*"
    DIVIDE      "/"
    MODULUS     "%"
    ASSIGN      "="
;

%token
    EQUAL       "=="
    NOT_EQUAL   "!="
    GREATER     ">"
    LESS        "<"
    GREATER_EQ  ">="
    LESS_EQ     "<="
    OR          "||"
    AND         "&&"
    NOT         "!"
    EOF 0       "end of file"
;

%token <int> NUMBER
%token <std::string> VAR

%right ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_EQ GREATER GREATER_EQ EQUAL NOT_EQUAL
%left MINUS PLUS
%left MULTIPLY DIVIDE MODULUS
%nonassoc UPLUS UMINUS

%precedence THEN
%precedence ELSE

%start program

%%

program: stmts
;

stmts: stmts stmt
| %empty
;

stmt: expr_stmt
| PRINT expr SCOLON
| scope
| while_stmt
| if_stmt
;

expr_stmt: expr SCOLON
;

scope: LBRACE stmts RBRACE
;

while_stmt: WHILE LPAREN expr RPAREN stmt
;

if_stmt: IF LPAREN expr RPAREN stmt %prec THEN
| IF LPAREN expr RPAREN stmt ELSE stmt
;

expr: assign_expr
| logic_expr
;

assign_expr: VAR ASSIGN assign_expr
| VAR ASSIGN logic_expr
;

logic_expr: logic_expr AND comp_expr
| logic_expr OR comp_expr
| comp_expr
;

comp_expr: comp_expr EQUAL arith_expr
| comp_expr NOT_EQUAL arith_expr
| comp_expr LESS arith_expr
| comp_expr LESS_EQ arith_expr
| comp_expr GREATER arith_expr
| comp_expr GREATER_EQ arith_expr
| arith_expr
;

arith_expr: arith_expr PLUS unary_expr
| arith_expr MINUS unary_expr
| arith_expr MULTIPLY unary_expr
| arith_expr DIVIDE unary_expr
| arith_expr MODULUS unary_expr
| unary_expr
;

unary_expr: MINUS  primary_expr %prec UMINUS
| PLUS  primary_expr %prec UPLUS
| NOT primary_expr %prec NOT
| primary_expr
;

primary_expr: LPAREN expr RPAREN
| NUMBER
| VAR
| QMARK
;

%%

void yy::parser::error(const std::string &msg) {
  std::cout << "Error occurred on line" << std::endl;
  throw std::runtime_error{msg};
}
