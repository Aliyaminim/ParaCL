#pragma once

#include "base_ast_node.hpp"

namespace AST {
    class read_expr : public base_expr_node {
        VAL_TYPE input; //may be unnecessary
    public:
        void set_input(VAL_TYPE in) { input = in; }
    };
}