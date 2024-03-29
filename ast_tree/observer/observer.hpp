#pragma once

#include "ast_nodes_include.hpp"
#include <iostream>
#include <exception>
#include <fstream>
#include <cassert>
#include <string>

namespace AST {
    class Observer final{
        std::istream& input_stream;
        std::ostream& output_stream;
    public:
        Observer(std::istream& in_, std::ostream& out_): input_stream(in_), output_stream(out_) {}

        VAL_TYPE eval(base_expr_node * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_expr_type())
            {
            case base_expr_node_type::ASSIGNMENT:{
                assignment_expr * A = static_cast<assignment_expr*>(X);
                return eval(A);
                break;}
            case base_expr_node_type::BINARY_EXPR:{
                binary_expr * B = static_cast<binary_expr*>(X);
                return eval(B, B->get_bin_type());
                break;}
            case base_expr_node_type::NUMBER_EXPR:{
                number_expr * C = static_cast<number_expr*>(X);
                return eval(C);
                break;}
            case base_expr_node_type::UNARY_EXPR:{
                unary_expr * D = static_cast<unary_expr*>(X);
                return eval(D, D->get_un_type());
                break;}
            case base_expr_node_type::VAR_EXPR:{
                variable_expr * E = static_cast<variable_expr*>(X);
                return eval(E);
                break;}
            case base_expr_node_type::READ_EXPR:{
                read_expr * F = static_cast<read_expr*>(X);
                return eval(F);
                break;}
            default:{
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(binary_expr* X, binary_oper t){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (t)
            {
            case binary_oper::BINARY_ADD:{
                return eval(X->get_lhs()) + eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_SUB:{
                return eval(X->get_lhs()) - eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_MUL:{
                return eval(X->get_lhs()) * eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_DIV:{
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                else {return eval(X->get_lhs()) / eval(X->get_rhs());}
                break;}
            case binary_oper::BINARY_MOD:{
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                else {return eval(X->get_lhs()) % eval(X->get_rhs());}
                break;}
            case binary_oper::BINARY_EQU:{
                return eval(X->get_lhs()) == eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_NEQU:{
                return eval(X->get_lhs()) != eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_GREATER:{
                return eval(X->get_lhs()) > eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_LESS:{
                return eval(X->get_lhs()) < eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_GREATER_EQU:{
                return eval(X->get_lhs()) >= eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_LESS_EQU:{
                return eval(X->get_lhs()) <= eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_OR:{
                return eval(X->get_lhs()) || eval(X->get_rhs());
                break;}
            case binary_oper::BINARY_AND:{
                return eval(X->get_lhs()) && eval(X->get_rhs());
                break;}
            default:{
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(unary_expr* X, unary_oper t){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
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
            default:{
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(print_stmt* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = eval(X->out_());
            output_stream << res << std::endl;
            return res;
        }

        VAL_TYPE eval(number_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = X->get_value();
            return res;
        }

        VAL_TYPE eval(assignment_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = eval(X->get_rhs());
            X->define(res);
            return res;
        }

        VAL_TYPE eval(variable_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            auto var_scope = X->get_scope();
            if (!var_scope) {
                std::string msg = "Variable is undeclared: ";
                msg += X->name();
                throw std::runtime_error(msg);
            }
            auto var_value = var_scope->get_var_value(X->name());
            return var_value;
        }

        VAL_TYPE eval(base_ast_node * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_ast_type())
            {
            case base_ast_node_type::EXPR:{
                base_expr_node * A = static_cast<base_expr_node*>(X);
                return eval(A);
                break;}
            case base_ast_node_type::STMT:{
                base_stmt_node * B = static_cast<base_stmt_node*>(X);
                eval(B);
                return 0;
                break;}
            case base_ast_node_type::SCOPE:{
                scope_node * C = static_cast<scope_node*>(X);
                eval(C);
                return 0;
                break;}
            default:{
                return 0;
                break;}
            }
        }

        void eval(scope_node* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            for (auto i : *(X->get_container())){
                eval(i);
            }
        }

        void eval(base_stmt_node* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_expr_type())
            {
            case base_stmt_node_type::IF_STMT:{
                if_stmt * A = static_cast<if_stmt*>(X);
                eval(A);
                break;}
            case base_stmt_node_type::WHILE_STMT:{
                while_stmt * B = static_cast<while_stmt*>(X);
                eval(B);
                break;}
            case base_stmt_node_type::PRINT_STMT:{
                print_stmt * C = static_cast<print_stmt*>(X);
                eval(C);
                break;}
            default:{
                break;}
            }
        }

        void eval(if_stmt* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            if (eval(X->get_condition())){
                eval(X->get_true_scope());
            }
            else{
                if (X->get_else_scope() != nullptr){
                    eval(X->get_else_scope());
                }
            }
        }

        void eval(while_stmt* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            while (eval(X->get_condition())){
                eval(X->get_scope());
            }
        }

        VAL_TYPE eval(read_expr * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE inp;
            input_stream >> inp;
            assert(input_stream.good());
            return inp;
        }
    };
}
