#pragma once

using VAL_TYPE = int;
#include "node_types.hpp"

namespace AST {
    class base_ast_node {
        base_ast_node_type ast_type;
    public:
        base_ast_node() {}
        virtual ~base_ast_node() {}

        base_ast_node_type get_ast_type(){
            return ast_type;
        }
    };

    class base_expr_node: public base_ast_node {
        base_expr_node_type ex_type;
    public:
        base_expr_node_type get_expr_type(){
            return ex_type;
        }
    };

    class base_stmt_node: public base_ast_node {
        base_stmt_node_type ex_type;
    public:
        base_stmt_node_type get_expr_type(){
            return ex_type;
        }
    };
}
