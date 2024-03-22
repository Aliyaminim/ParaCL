#pragma once

namespace AST{
    enum class binary_oper {
        BINARY_ADD,
        BINARY_SUB,
        BINARY_MUL,
        BINARY_DIV,
        BINARY_MOD,
        BINARY_EQU,
        BINARY_NEQU,
        BINARY_GREATER,
        BINARY_LESS,
        BINARY_GREATER_EQU,
        BINARY_LESS_EQU,
        BINARY_OR,
        BINARY_AND     // Остались битовые операторы(+ бит сдвига) и запятая
    };

    enum class unary_oper {
        UNARY_PLUS,
        UNARY_MINUS,
        UNARY_NOT,
        UNARY_DOUBLE_MINUS,
        UNARY_DOUBLE_PLUS,      // Запятая
    };

    enum class base_expr_node_type {
        ASSIGNMENT,
        BINARY_EXPR,
        UNARY_EXPR,
        NUMBER_EXPR,
        VAR_EXPR,
        READ_EXPR,
    };

    enum class base_stmt_node_type {
        IF_STMT,
        WHILE_STMT,
        PRINT_STMT,
    };

    enum class base_ast_node_type {
        STMT,
        EXPR,
        SCOPE,
    };

}
