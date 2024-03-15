#pragma once

#include "base_ast_node.hpp"
#include <string>

namespace AST {
    class variable_expr : public base_expr_node {
        std::string name;
    public:
        explicit variable_expr(std::string nm) : name(nm) {}
    };
}

