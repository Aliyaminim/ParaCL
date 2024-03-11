#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"

namespace AST {
    class unary_operation : public base_ast_node {

        value_expression * value;

    public:
        unary_operation(base_ast_node *parent, Node_name a, value_expression* x) :
            base_ast_node{parent, a}, value(x) {}

    };
}

// b = 2+3
// a = b + 1 + 2
// print a