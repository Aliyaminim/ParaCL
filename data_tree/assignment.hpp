#pragma once

#include "variable_node.hpp"
#include "value_expressions.hpp"

namespace AST {
    class assignment_node : public binary_operation {

    public:
        assignment_node(base_ast_node *parent, Node_name a, variable_node* l, value_expression* r) :
            binary_operation{parent, a, l, r} {}
        VAL_TYPE process_node() override;
    };
}
