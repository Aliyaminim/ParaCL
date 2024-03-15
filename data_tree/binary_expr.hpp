#pragma once

#include "base_ast_node.hpp"
#include "node_types.hpp"

namespace AST {
class binary_expr : public base_expr_node {
    binary_oper type;
    base_expr_node *lhs;
    base_expr_node *rhs;

public:
    explicit binary_expr(binary_oper t, base_expr_node* l = nullptr, base_expr_node* r = nullptr) : type(t),
        lhs(l), rhs(r) {}

    base_expr_node* get_lhs(){ return lhs; }
    base_expr_node* get_rhs(){ return rhs; }
};
}