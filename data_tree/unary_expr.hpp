#pragma once

#include "base_ast_node.hpp"
#include "node_types.hpp"

namespace AST {
    class unary_expr : public base_expr_node {
        unary_oper un_type;
        base_expr_node* value;
    public:
        explicit unary_expr(unary_oper t, base_expr_node* v = nullptr) : base_expr_node(base_expr_node_type::UNARY_EXPR), un_type(t), value(v) {}

        unary_oper get_un_type(){
            return un_type;
        }

        base_expr_node* get_rhs(){
            return value;
        }
    };
}
