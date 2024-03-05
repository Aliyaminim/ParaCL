#pragma once

#include "tree.hpp"

namespace AST {
    class number_node : public base_ast_node {

        int value;

    public:
        number_node(base_ast_node *parent, Node_name a, int x) :
            base_ast_node{parent, a}, value(x) {}

        int value_() const { return value; }
    };
}
