#pragma once

#include "base_ast_node.hpp"

namespace AST {
    class print_stmt : public base_stmt_node {
        base_expr_node *out;

    public:
        explicit print_stmt(base_expr_node* out_ = nullptr) : base_stmt_node(base_stmt_node_type::PRINT_STMT), out(out_) {}

        base_expr_node* out_() const noexcept { return out; }
    };
}
