#pragma once

#include "ast_nodes_include.hpp"
#include <iostream>

namespace AST {
    class Visitor final{

    public:

        VAL_TYPE eval(base_expr_node * X){
            switch (X->get_expr_type())
            {
            case base_expr_node_type::ASSIGNMENT:
                assignment_expr * A = static_cast<assignment_expr*>(X);
                return eval(A);
                break;
            case base_expr_node_type::BINARY_EXPR:
                binary_expr * B = static_cast<binary_expr*>(X);
                return eval(B, B->get_bin_type());
                break;
            case base_expr_node_type::NUMBER_EXPR:
                number_expr * C = static_cast<number_expr*>(X);
                return eval(C);
                break;
            case base_expr_node_type::UNARY_EXPR:
                unary_expr * D = static_cast<unary_expr*>(X);
                return eval(D, D->get_un_type());
                break;
            case base_expr_node_type::VAR_EXPR:
                variable_expr * E = static_cast<variable_expr*>(X);
                return eval(E);
                break;
            default:
                break;
            }
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
            case binary_oper::BINARY_DIV:
                if (eval(X->get_rhs()) == 0){ /* error*/ }
                else {return eval(X->get_lhs()) / eval(X->get_rhs());}
                break;
            case binary_oper::BINARY_MOD:
                return eval(X->get_lhs()) % eval(X->get_rhs());
                break;
            case binary_oper::BINARY_EQU:
                return eval(X->get_lhs()) == eval(X->get_rhs());
                break;
            case binary_oper::BINARY_NEQU:
                return eval(X->get_lhs()) != eval(X->get_rhs());
                break;
            case binary_oper::BINARY_GREATER:
                return eval(X->get_lhs()) > eval(X->get_rhs());
                break;
            case binary_oper::BINARY_LESS:
                return eval(X->get_lhs()) < eval(X->get_rhs());
                break;
            case binary_oper::BINARY_GREATER_EQU:
                return eval(X->get_lhs()) >= eval(X->get_rhs());
                break;
            case binary_oper::BINARY_LESS_EQU:
                return eval(X->get_lhs()) <= eval(X->get_rhs());
                break;
            case binary_oper::BINARY_OR:
                return eval(X->get_lhs()) || eval(X->get_rhs());
                break;
            case binary_oper::BINARY_AND:
                return eval(X->get_lhs()) && eval(X->get_rhs());
                break;
            default:
                break;
            }
        }

        VAL_TYPE eval(unary_expr* X, unary_oper t){
            switch (t)
            {
            case unary_oper::UNARY_MINUS:
                return -eval(X->get_rhs());
                break;
            case unary_oper::UNARY_NOT:
                return -eval(X->get_rhs());
                break;
            case unary_oper::UNARY_PLUS:
                return eval(X->get_rhs());
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

        VAL_TYPE eval(assignment_expr* X){
            VAL_TYPE res = eval(X->get_rhs());
            return res;
        }

        VAL_TYPE eval(variable_expr* X){
            VAL_TYPE res = X->get_value();
            return res;
        }
    };
}
