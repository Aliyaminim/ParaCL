#pragma once

#include "ast_nodes_include.hpp"
#include <iostream>

namespace AST {
    class Visitor final{

    public:

        VAL_TYPE eval(base_expr_node * X){

        }

        VAL_TYPE eval(binary_expr* X, binary_oper t){
            switch (t)
            {
            case binary_oper::BINARY_ADD:
                return eval(X->get_lhs()) + eval(X->get_rhs());
                break;
            case binary_oper::BINARY_SUB:
                return eval(X->get_lhs()) - eval(X->get_rhs());
                break;
            case binary_oper::BINARY_MUL:
                return eval(X->get_lhs()) * eval(X->get_rhs());
                break;
            //...
            default:
                break;
            }
        }

        VAL_TYPE eval(print_stmt* X){
            VAL_TYPE res = eval(X->out_());
            OBUF << res;
            return res;
        }

        VAL_TYPE eval(number_expr* X){
            VAL_TYPE res = X->get_value();
            return res;
        }

    };
}
