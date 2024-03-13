#pragma once

#include "tree.hpp"
#include <vector>

namespace AST {
    class scope_node : public base_ast_node {

        base_ast_node *parent_scope = nullptr;

        std::vector<base_ast_node * > container;

    public:
        scope_node(base_ast_node *parent, Node_name & a) :
            base_ast_node{parent, a} {}

        void add_node(base_ast_node *primary){
            container.push_back(primary);
        }


    };
}
