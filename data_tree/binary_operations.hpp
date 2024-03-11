#pragma once

#include "tree.hpp"

namespace AST {
    class binary_operation : protected base_ast_node {
        base_ast_node *lhs_ = nullptr;
        base_ast_node *rhs_ = nullptr;


    public:
        binary_operation(base_ast_node *parent, Node_name a, base_ast_node* f, base_ast_node* l) :
            base_ast_node{parent, a}, lhs_(f), rhs_(l) {}

        base_ast_node * get_lhs(){
            return lhs_;
        }

        base_ast_node * get_rhs(){
            return rhs_;
        }

        VAL_TYPE process_node() override;


    };
}

// b = 2
// a = b + 1 + 2
// print a