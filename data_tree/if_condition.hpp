#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"
#include "scope_node.hpp"

namespace AST {
    class if_condition_node : public base_ast_node {

        value_expression * condition;
        scope_node * scope_;

    public:
        if_condition_node(scope_node* parentx , value_expression* cond, scope_node* scp, Node_name a) :
            base_ast_node{parentx, a}, condition(cond), scope_(scp) {}
        
        
    };
}
