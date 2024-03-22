#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"

namespace AST {
    class if_stmt : public base_stmt_node {
        base_expr_node* condition = nullptr;
        scope_node* true_scope = nullptr;
        scope_node* else_scope = nullptr;
    public:
        if_stmt(base_expr_node* cond_, scope_node* true_scope_, scope_node* else_scope_) : base_stmt_node(base_stmt_node_type::IF_STMT),
            condition(cond_), true_scope(true_scope_), else_scope(else_scope_) {}

        if_stmt(base_expr_node* cond_, scope_node* true_scope_) : base_stmt_node(base_stmt_node_type::IF_STMT),
            condition(cond_), true_scope(true_scope_) {}

        base_expr_node* get_condition() const noexcept {
            return condition;
        }

        scope_node* get_true_scope() const noexcept {
            return true_scope;
        }

        scope_node* get_else_scope() const noexcept {
            return else_scope;
        }
    };
}
