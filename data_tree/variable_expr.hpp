#pragma once

#include "base_ast_node.hpp"
#include <string>

namespace AST {
    class variable_expr : public base_expr_node {
        std::string name;
        VAL_TYPE value;
    public:
        explicit variable_expr(std::string nm) : name(nm) {}

        VAL_TYPE get_value(){
            return value;
        }

        void set_value(VAL_TYPE res){                   // поместить в private
            value = res;
            return;
        }
    };
}
