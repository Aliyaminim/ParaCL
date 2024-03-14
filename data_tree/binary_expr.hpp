#pragma once

#include "base_ast_node.hpp"
#include "node_types.hpp"

namespace AST {
class binary_expr : public base_expr_node {
    binary_oper type;
    base_expr_node *lhs_;
    base_expr_node *rhs_;

public:
    explicit binary_expr(binary_oper t, base_expr_node* l = nullptr, base_expr_node* l = nullptr) : type(t),
        lhs(l), rhs(r) {}

    base_expr_node* get_lhs(){ return lhs_; }
    base_expr_node* get_rhs(){ return rhs_; }
};
}