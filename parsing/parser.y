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
%left QMARK
%left OR
%left AND
%left NOT
%left MINUS PLUS
%left MULTIPLY DIVIDE
%precedence UMINUS
/* nonassoc UMINUS*/
%right THEN ELSE


%start program

%%

program: %empty
| stmts
;

stmts: stmts stmt
| stmt
;

stmt: assignment
| printing
| scope
;

assignment: VAR ASSIGN expr SCOLON
| VAR ASSIGN assignment
;

printing: PRINT expr SCOLON
;

scope: LBRACE program RBRACE
;

expr: arithmetic_expr
;

arithmetic_expr: arithmetic_expr PLUS term
| arithmetic_expr MINUS term
| term
;

term: term MULTIPLY primary
| term DIVIDE primary
| primary
;

primary:    LPAREN expr RPAREN
            | NUMBER
            | VAR
            | QMARK
;

%%

void yy::parser::error(const std::string &msg) {
  std::cout << "Error occurred on line" << std::endl;
  throw std::runtime_error{msg};
}
