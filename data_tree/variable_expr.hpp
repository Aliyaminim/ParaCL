#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"
#include <string>

namespace AST {
    class variable_expr : public base_expr_node {
        std::string name_;
        VAL_TYPE value;
        scope_node* curr_scope;
    public:
        explicit variable_expr(std::string nm, scope_node* curr_sc_) : base_expr_node(base_expr_node_type::VAR_EXPR),
            name_(nm), curr_scope(curr_sc_) {}

        VAL_TYPE get_value(){
            return value;
        }

        void set_value(VAL_TYPE res){                   // поместить в private
            value = res;
            return;
        }

        const std::string &name() const noexcept {
            return name_;
        }

        scope_node* get_scope() { return curr_scope->find_var(name_); }

    };
}
