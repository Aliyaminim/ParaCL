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
        BINARY_AND
    };

    enum class unary_oper {
        UNARY_PLUS,
        UNARY_MINUS,
        UNARY_NOT,
    };
}