#pragma once

#include <memory>
#include "base_ast_node.hpp"
#include "scope_node.hpp"
#include <vector>


namespace AST {
    class astree final{
        scope_node* root = nullptr;
        std::vector<std::unique_ptr<base_ast_node>> node_storage;

    public:
        astree() : root(new scope_node()) {
            node_storage.push_back(std::unique_ptr<scope_node>(root));
        }

        template <typename NodeType, typename... t_args> auto make_node(t_args && ... args){
            auto new_node_un_ptr = std::make_unique<NodeType>(std::forward<t_args>(args)...);
            auto new_node_ptr = new_node_un_ptr.get();
            node_storage.push_back(std::move(new_node_un_ptr));
            return new_node_ptr;
        }

        void set_root(scope_node* ptr) noexcept {root = ptr; }
        auto get_root() const noexcept { return root; }
    };
}
