#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"

namespace AST {
class astree {
    scope_node* root = nullptr;

public:
    template <typename NodeType, typename... t_args> base_ast_node* make_node(t_args && ... args){
        auto new_node = new NodeType(std::forward<t_args>(args)...);
        return new_node;
    }

    void set_root(scope_node* ptr) { root = ptr; }
};
}
