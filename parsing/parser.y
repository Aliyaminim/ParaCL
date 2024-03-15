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
#include "data_tree/ast_nodes_include.hpp"

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
;

%type<AST::base_expr_node*>
    expr_stmt
    expr
    assign_expr
    logic_expr
    comp_expr
    arith_expr
    unary_expr
    primary_expr
;

%type<AST::base_stmt_node*>
    if_stmt
    while_stmt
;

%type<AST::scope_node*>
    scope
    close_brace
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

program: stmts {
    auto root = driver->make_node<AST::scope_node>($1);
    driver->set_ast_root(root);
    driver->set_curr_parsing_scope(root);
}
;

stmts: stmts stmt { $$ = std::move($1); $$.push_back($2); }
| %empty {}
;

stmt: expr_stmt { $$ = $1; }
| PRINT expr SCOLON { $$ = driver->make_node<AST::print_stmt>($2); }
| scope { $$ = $1; }
| while_stmt { $$ = $1; }
| if_stmt { $$ = $1; }
;

expr_stmt: expr SCOLON { $$ = $1; }
;

scope: open_brace stmts close_brace { $$ = $3->set_stmts($2); }
;

open_brace: LBRACE {
    auto sc = driver->make_node<AST::scope_node>();
    sc.set_parent_scope(driver->get_curr_parsing_scope());
    driver->set_curr_parsing_scope(sc);
}
;

close_brace: RBRACE {
    $$ = driver->get_curr_parsing_scope();
    driver->reset_curr_parsing_scope();
}
;

while_stmt: WHILE LPAREN expr RPAREN stmt {
    auto block = driver->make_node<AST::scope_node>(std::vector{$5});
    $$ = driver->make_node<AST::while_stmt>($3, block);
}
;

if_stmt: IF LPAREN expr RPAREN stmt %prec THEN {
    auto true_block = driver->make_node<AST::scope_node>(std::vector{$5});
    $$ = driver->make_node<AST::if_stmt>($3, true_block);
}
| IF LPAREN expr RPAREN stmt ELSE stmt {
    auto true_block = driver->make_node<AST::scope_node>(std::vector{$5});
    auto else_block = driver->make_node<AST::scope_node>(std::vector{$7});
    $$ = driver->make_node<AST::if_stmt>($3, true_block, else_block);
}
;

expr: assign_expr { $$ = $1; }
| logic_expr { $$ = $1; }
;

assign_expr: VAR ASSIGN assign_expr { $$ = $3; auto left = AST::variable_expr{$1}; $$->add_var(left); }
| VAR ASSIGN logic_expr { auto left = AST::variable_node{$1}; $$ = driver->make_node<AST::assignment_node>(left, $3); }
;

logic_expr: logic_expr AND comp_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_AND, $1, $3); }
| logic_expr OR comp_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_OR, $1, $3); }
| comp_expr { $$ = $1; }
;

comp_expr: comp_expr EQUAL arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_EQU, $1, $3); }
| comp_expr NOT_EQUAL arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_NEQU, $1, $3); }
| comp_expr LESS arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_LESS, $1, $3); }
| comp_expr LESS_EQ arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_LESS_EQU, $1, $3); }
| comp_expr GREATER arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_GREATER, $1, $3); }
| comp_expr GREATER_EQ arith_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_GREATER_EQU, $1, $3); }
| arith_expr { $$ = $1; }
;

arith_expr: arith_expr PLUS unary_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_ADD, $1, $3); }
| arith_expr MINUS unary_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_SUB, $1, $3); }
| arith_expr MULTIPLY unary_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_MUL, $1, $3); }
| arith_expr DIVIDE unary_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_DIV, $1, $3); }
| arith_expr MODULUS unary_expr { $$ = driver->make_node<AST::binary_expr>(AST::binary_oper::BINARY_MOD, $1, $3); }
| unary_expr { $$ = $1; }
;

unary_expr: MINUS  primary_expr %prec UMINUS { $$ = driver->make_node<AST::unary_expr>(AST::unary_oper::UNARY_MINUS, $2); }
| PLUS  primary_expr %prec UPLUS { $$ = driver->make_node<AST::unary_expr>(AST::unary_oper::UNARY_PLUS, $2); }
| NOT primary_expr %prec NOT { $$ = driver->make_node<AST::unary_expr>(AST::unary_oper::UNARY_NOT, $2); }
| primary_expr { $$ = $1; }
;

primary_expr: LPAREN expr RPAREN { $$ = $2; }
| NUMBER { $$ = driver->make_node<AST::number_expr>($1); }
| VAR   { $$ = driver->make_node<AST::variable_expr>($1); }
| QMARK { $$ = driver->make_node<AST::read_expr>(); }
;

%%

void yy::parser::error(const std::string &msg) {
  std::cout << "Error occurred on line "  << curr_line  << std::endl;
  #ifdef DEBUG
    std::cout << "Maybe parsed wrongly number: " << debugg_num << std::endl;
  #endif
  throw std::runtime_error{msg};
}
