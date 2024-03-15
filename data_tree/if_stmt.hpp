#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"

namespace AST {
class if_stmt : public base_stmt_node {

    base_expr_node* condition = nullptr;
    scope_node* true_scope = nullptr;
    scope_node* else_scope = nullptr;

public:
    if_stmt(base_expr_node* cond_, scope_node* true_scope_, scope_node* else_scope_) :
        condition(cond_), true_scope(true_scope_), else_scope(else_scope_) {}

    if_stmt(base_expr_node* cond_, scope_node* true_scope_) :
        condition(cond_), true_scope(true_scope_) {}

};
}
