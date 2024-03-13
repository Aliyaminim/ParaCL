#pragma once

#include "tree.hpp"
//#include "value_expressions.hpp"

namespace AST {
    class number_expr : public base_ast_node {

        VAL_TYPE value;

    public:
        number_expr(base_ast_node* parent_operation, Node_name a, int && x) :
            base_ast_node{parent_operation, a}
        {
            value = x;
        }

        VAL_TYPE value_() const { return value; }

        VAL_TYPE process_node() override;
    };
}
