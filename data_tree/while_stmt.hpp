#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"

namespace AST {
class while_stmt : public base_stmt_node {
    base_expr_node* condition = nullptr;
    scope_node* scope = nullptr;
public:
    explicit while_stmt(base_expr_node* cond_ = nullptr, scope_node* scope_ = nullptr) :
        condition(cond_), scope(scope_) {}
};
}