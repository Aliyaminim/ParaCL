#pragma once

#include "base_ast_node.hpp"
#include <vector>

namespace AST {
class scope_node : public base_ast_node {
    std::vector<base_ast_node*> container_stmts;
    base_ast_node* parent_scope;
public:
    explicit scope_node(std::vector<base_ast_node*> c, base_ast_node* p_sc = nullptr) :
        container_stmts(c), parent_scope(p_sc)
};
}
