#pragma once

#include "tree.hpp"
#include "binary_operations.hpp"
#include "number_node.hpp"

namespace AST {
    class value_expression : public base_ast_node {

        std::vector<binary_operation * > container;

        VAL_TYPE value;
        bool calculated = false;

    public:
        value_expression(base_ast_node *parent, Node_name a) :
            base_ast_node{parent, a} {}
        
        binary_operation* add_binary_operand(binary_operation* x){
            if (not calculated){
                container.push_back(x);
                return x;
            }
            return nullptr;
        }

        void add_value(number_node * X){
            value = X->process_node();
            calculated = true;
        }

        VAL_TYPE process_node() override;
    };
}

// b = 2+3
// a = b + 1 + 2
// print a