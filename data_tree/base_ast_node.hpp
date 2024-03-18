#pragma once

using VAL_TYPE = int;
#include "node_types.hpp"

namespace AST {
    class base_ast_node {
        base_ast_node_type ast_type;
    public:
        base_ast_node(base_ast_node_type t) : ast_type(t) {}
        virtual ~base_ast_node() {}

        base_ast_node_type get_ast_type(){
            return ast_type;
        }
    };

    class base_expr_node: public base_ast_node {
        base_expr_node_type ex_type;
    public:
        base_expr_node(base_expr_node_type ex_t) : base_ast_node(base_ast_node_type::EXPR), ex_type(ex_t) {}
        base_expr_node_type get_expr_type(){
            return ex_type;
        }
        virtual ~base_expr_node() {}
    };

    class base_stmt_node: public base_ast_node {
        base_stmt_node_type ex_type;
    public:
        base_stmt_node(base_stmt_node_type ex_t) : base_ast_node(base_ast_node_type::STMT), ex_type(ex_t) {}
        base_stmt_node_type get_expr_type(){
            return ex_type;
        }
        virtual ~base_stmt_node() {}
    };
}
