#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"
#include "deque" //only insertion occurs


namespace AST {
    class astree {
        scope_node* root = nullptr;
        std::deque<base_ast_node*> node_storage;

    public:
        astree() : root(new scope_node()) {}
        template <typename NodeType, typename... t_args> auto make_node(t_args && ... args){
            auto new_node = new NodeType(std::forward<t_args>(args)...);
            node_storage.push_back(new_node);
            return new_node;
        }

        void set_root(scope_node* ptr) {root = ptr; }
        auto get_root() { return root; }
    };
}
