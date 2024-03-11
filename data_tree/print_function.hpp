#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"

namespace AST {
    struct func_node_print : public base_ast_node {
        //
        value_expression *out_ = nullptr;

        func_node_print(scope_node *parent, Node_name a, value_expression* out) :
            base_ast_node{parent, a}, out_(out) {}
        
        VAL_TYPE process_node() override;
    };
}