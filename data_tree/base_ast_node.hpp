#pragma once

using VAL_TYPE = int;

namespace AST {
    class base_ast_node {
    public:
        base_ast_node() {}
        virtual ~base_ast_node() {}
    };

    class base_expr_node: public base_ast_node {
        base_expr_node_type t;
    public:
        base_expr_node_type get_type(){
            return t;
        }
    };
    
    class base_stmt_node: public base_ast_node {
        base_stmt_node_type t;
    public:
        base_stmt_node_type get_type(){
            return t;
        }
    };
}