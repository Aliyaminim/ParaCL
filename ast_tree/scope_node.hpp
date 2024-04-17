#pragma once

#include "base_ast_node.hpp"
#include "symbol_table.hpp"
#include <vector>

namespace AST {
    class scope_node : public base_ast_node {
        std::vector<base_ast_node*> container_stmts;
        scope_node* parent_scope;
        Symbol_table symtab;
    public:
        explicit scope_node(std::vector<base_ast_node*> c, scope_node* p_sc = nullptr) : base_ast_node(base_ast_node_type::SCOPE),
            container_stmts(c), parent_scope(p_sc) {}
        explicit scope_node(scope_node* p_sc = nullptr) : base_ast_node(base_ast_node_type::SCOPE), parent_scope(p_sc) {}

        scope_node* get_parent_scope() const noexcept { return parent_scope; }
        void set_parent_scope(scope_node* p) noexcept { parent_scope = p; }
        void set_stmts(std::vector<base_ast_node*> cont) { container_stmts = cont; }

        std::vector<base_ast_node*>* get_container() {return &container_stmts;};

        scope_node* find_var(std::string_view name) {
            auto curr_scope = this;
            do {
                if(curr_scope->contains(name))
                    return curr_scope;
                curr_scope = curr_scope->parent_scope;
            } while(curr_scope);

            return nullptr;
        }

        bool contains(std::string_view name) const { return symtab.contains(name); }

        void set(std::string_view name, VAL_TYPE val) { symtab[name] = val; }

        void declare(std::string_view name) {
            auto var_scope = find_var(name);
            if(!var_scope) {
                symtab.add(name);
            }
        }

        VAL_TYPE& get_var_value(std::string_view name) { return symtab[name]; }

        virtual ~scope_node() {}

    };
}
