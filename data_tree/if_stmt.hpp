#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"
#include "scope_node.hpp"

namespace AST {
class if_stmt : public base_ast_node {

    value_expression* condition = nullptr;
    scope_node* true_scope = nullptr;
    scope_node* else_scope = nullptr;

public:
    if_stmt(value_expression* cond_, scope_node* true_scope_, scope_node* else_scope_) :
        condition(cond_), true_scope(true_scope_), else_scope(else_scope_) {}

    if_stmt(value_expression* cond_, scope_node* true_scope_) :
        condition(cond_), true_scope(true_scope_) {}

};
}
