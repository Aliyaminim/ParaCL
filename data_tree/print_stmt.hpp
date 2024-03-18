#pragma once

#include "base_ast_node.hpp"

namespace AST {
    class print_stmt : public base_expr_node {
        base_expr_node *out;

    public:
        explicit print_stmt(base_expr_node* out_ = nullptr) : base_expr_node(base_expr_node_type::READ_EXPR), out(out_) {}

        base_expr_node* out_(){ return out; }
    };
}
