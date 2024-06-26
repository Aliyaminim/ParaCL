#pragma once

#include "base_ast_node.hpp"
#include "variable_expr.hpp"
#include "scope_node.hpp"
#include <vector>
#include <cassert>

namespace AST {
    class assignment_expr : public base_expr_node {
        std::vector<variable_expr*> lhs;
        base_expr_node* rhs;
        scope_node* curr_scope;
    public:
        assignment_expr(variable_expr* v, base_expr_node* r, scope_node* curr_sc_) :
            base_expr_node(base_expr_node_type::ASSIGNMENT), rhs(r), curr_scope(curr_sc_)
        {   lhs.push_back(v);
            curr_scope->declare(v->get_name());
        }

        void add_var(variable_expr* var) {
            lhs.push_back(var);
            curr_scope->declare(var->get_name());
        }

        void define(VAL_TYPE value) {
            for (auto var : lhs) {
                curr_scope->define(var->get_name(), value);
            }
        }

        base_expr_node* get_rhs() const noexcept { return rhs; }

        const std::vector<variable_expr*>& get_lhs() const noexcept { return lhs; };

        virtual ~assignment_expr() {}
    };
}
