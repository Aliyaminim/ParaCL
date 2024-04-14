#pragma once

#include "base_ast_node.hpp"

namespace AST {
    class number_expr : public base_expr_node {
        VAL_TYPE value;
    public:
        explicit number_expr(VAL_TYPE v) : base_expr_node(base_expr_node_type::NUMBER_EXPR), value(v) {}

        VAL_TYPE get_value() const noexcept { return value; }

        virtual ~number_expr() {}
    };
}
