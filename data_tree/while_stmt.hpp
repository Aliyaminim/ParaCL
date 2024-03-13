#pragma once

#include "tree.hpp"
#include "value_expressions.hpp"
#include "scope_node.hpp"

namespace AST {
class while_stmt : public base_ast_node {

    value_expression* condition = nullptr;
    scope_node* scope = nullptr;

public:
    while_stmt(value_expression* cond_, scope_node* scope_) :
        condition(cond_), scope(scope_) {}

};
}