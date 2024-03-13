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
#include "data_tree/tree_nodes_include.hpp"

//forward declaration
namespace yy { class Driver; }
#ifdef DEBUG
    extern int debugg_num;
#endif
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

%type<std::vector<AST::base_ast_node*>>
    stmts
;

%type<AST::base_ast_node*>
    stmt
    expr_stmt
    expr
    assign_expr
    logic_expr
    comp_expr
    arith_expr
    unary_expr
    primary_expr
;

%type<AST::if_condition_node*>
    if_stmt
;

%type<AST::scope_node*>
    scope
;

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

program: stmts { auto head = driver.make_node<AST::scope_node>($1); driver.ast_->set_root(head);}
;

stmts: stmts stmt { $$ = std::move($1); $$.push_back($2); }
| %empty {}
;

stmt: expr_stmt { $$ = $1; }
| PRINT expr SCOLON { $$ = driver.make_node<func_node_print>(functional_oper::FUNC_PRINT, $2); }
| scope { $$ = $1; }
| while_stmt {  }
| if_stmt { $$ = nullptr; }
| SCOLON { $$ = nullptr; }
;

expr_stmt: expr SCOLON { $$ = $1; }
;

scope: LBRACE stmts RBRACE { $$ = driver.make_node<AST::scope_node>($2); }
;

while_stmt: WHILE LPAREN expr RPAREN stmt
;

if_stmt: IF LPAREN expr RPAREN stmt %prec THEN
| IF LPAREN expr RPAREN stmt ELSE stmt
;

expr: assign_expr { $$ = $1; }
| logic_expr { $$ = $1; }
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

arith_expr: arith_expr PLUS unary_expr { $$ = driver.make_node<binary_operation>(binary_calculus_oper::BINARY_ADD, $1, $3); }
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

primary_expr: LPAREN expr RPAREN { $$ = $2; }
| NUMBER { $$ = driver.make_node<number_node>(terminal_nodes::INT, $1); }
| VAR   { }
| QMARK
;

%%

void yy::parser::error(const std::string &msg) {
  std::cout << "Error occurred on line "  << curr_line  << std::endl;
  #ifdef DEBUG
    std::cout << "Maybe parsed wrongly number: " << debugg_num << std::endl;
  #endif
  throw std::runtime_error{msg};
}
