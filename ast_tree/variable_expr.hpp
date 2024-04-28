#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"
#include <string_view>

namespace AST {
    class variable_expr : public base_expr_node {
        std::string name_;
        scope_node* curr_scope;
        //value is owned by symbol table
    public:
        explicit variable_expr(std::string nm, scope_node* curr_sc_) : base_expr_node(base_expr_node_type::VAR_EXPR),
            name_(nm), curr_scope(curr_sc_) {}

        std::string_view get_name() const noexcept {
            return name_;
        }

        VAL_TYPE& get_value() {
            return curr_scope->get_var_value(name_);
        }

        virtual ~variable_expr() {}
    };
}
