#pragma once

#include "base_ast_node.hpp"

namespace AST {
    class read_expr : public base_expr_node {
    public:
        read_expr(): base_expr_node(base_expr_node_type::READ_EXPR) {}
        virtual ~read_expr() {}
    };
}
