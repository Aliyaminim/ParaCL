#pragma once

#include "base_ast_node.hpp"
#include "variable_expr.hpp"
#include <vector>

namespace AST {
    class assignment_expr : public base_expr_node {
        std::vector<variable_expr*> lhs;
        base_expr_node* rhs;
    public:
        explicit assignment_expr(variable_expr* v, base_expr_node* r) : base_expr_node(base_expr_node_type::ASSIGNMENT), rhs(r) { lhs.push_back(v); }

        void add_var(variable_expr* var) {
            lhs.push_back(var);
        }

        base_expr_node* get_rhs(){ return rhs; }

        std::vector<variable_expr*>* get_lhs(){return &lhs;};

    };
}
