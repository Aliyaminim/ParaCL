#pragma once

#include "tree.hpp"
//#include <string>

namespace AST {
    class variable_node : public base_ast_node {

        //std::string name;
        int value;

    public:
        variable_node(base_ast_node *parent, Node_name a, int x) :
            base_ast_node{parent, a}, value(x) {}

        variable_node(base_ast_node *parent, Node_name a) :
            base_ast_node{parent, a} {}

        int value_() const { return value; }
    };
}

// b = 2
// a = b + 1 + 2
// print a
