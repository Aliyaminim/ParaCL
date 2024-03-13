#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"

namespace AST {
    class print_stmt : public base_ast_node {
        //
        value_expression *out_ = nullptr;

    public:
        print_stmt(scope_node *parent, Node_name a, value_expression* out) :
            base_ast_node{parent, a}, out_(out) {}

        VAL_TYPE process_node() override;
    };
}