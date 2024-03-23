#pragma once

#include "base_ast_node.hpp"
#include "node_types.hpp"

namespace AST {
    class binary_expr : public base_expr_node {
        binary_oper bin_type;
        base_expr_node *lhs;
        base_expr_node *rhs;

    public:
        explicit binary_expr(binary_oper t, base_expr_node* l = nullptr, base_expr_node* r = nullptr) : base_expr_node(base_expr_node_type::BINARY_EXPR), bin_type(t),
            lhs(l), rhs(r) {}

        base_expr_node* get_lhs() const noexcept { return lhs; }
        base_expr_node* get_rhs() const noexcept { return rhs; }

        binary_oper get_bin_type() const noexcept {
            return bin_type;
        }
    };
}
