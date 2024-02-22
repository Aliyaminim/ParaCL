%language "c++"
%skeleton "lalr1.cc"
%require "3.5"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{

//forward declaration
namespace yy { class Driver; }
}

%code {
#include "driver.hpp"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval, Driver* driver) {
    return driver->yylex(yylval);

}
}
}

%defines
%define api.token.raw
%define api.parser.class { parser }
%define api.token.constructor
%define api.namespace { yy }
%define parse.error simple
%define api.token.prefix {TOKEN_}

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

program : stmts
;

stmts : %empty
      | stmts stmt
;

stmt  : SCOLON
;

%%
