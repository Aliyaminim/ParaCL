#pragma once

#include "base_ast_node.hpp"
#include <vector>

namespace AST {
    class scope_node : public base_ast_node {
        std::vector<base_ast_node*> container_stmts;
        scope_node* parent_scope;
    public:
        explicit scope_node(std::vector<base_ast_node*> c, scope_node* p_sc = nullptr) :
            container_stmts(c), parent_scope(p_sc) {}
        scope_node() = default;

        scope_node* get_parent_scope() { return parent_scope; }
        void set_parent_scope(scope_node* p) { parent_scope = p; }
        void set_stmts(std::vector<base_ast_node*> cont) { container_stmts = cont; }
    };
}
