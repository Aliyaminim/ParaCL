#pragma once

using VAL_TYPE = int;

namespace AST {
    class base_ast_node {
    public:
        base_ast_node() {}
        virtual ~base_ast_node() {}
    };

    class base_expr_node: public base_ast_node {};
    class base_stmt_node: public base_ast_node {};
}