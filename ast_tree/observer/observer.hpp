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
            case base_expr_node_type::ASSIGNMENT:
                return eval(static_cast<assignment_expr*>(X));

            case base_expr_node_type::BINARY_EXPR:
                return eval(static_cast<binary_expr*>(X));

            case base_expr_node_type::NUMBER_EXPR:
                return eval(static_cast<number_expr*>(X));

            case base_expr_node_type::UNARY_EXPR:
                return eval(static_cast<unary_expr*>(X));

            case base_expr_node_type::VAR_EXPR:
                return eval(static_cast<variable_expr*>(X));

            case base_expr_node_type::READ_EXPR:
                return eval(static_cast<read_expr*>(X));

            default:
                throw std::runtime_error("Unknown expression!");
            }
        }

        VAL_TYPE eval(binary_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }

            switch (X->get_bin_type())
            {
            case binary_oper::BINARY_ADD:
                return eval(X->get_lhs()) + eval(X->get_rhs());

            case binary_oper::BINARY_SUB:
                return eval(X->get_lhs()) - eval(X->get_rhs());

            case binary_oper::BINARY_MUL:
                return eval(X->get_lhs()) * eval(X->get_rhs());

            case binary_oper::BINARY_DIV:{
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                return eval(X->get_lhs()) / eval(X->get_rhs());}

            case binary_oper::BINARY_MOD:{
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                return eval(X->get_lhs()) % eval(X->get_rhs());}

            case binary_oper::BINARY_EQU:
                return eval(X->get_lhs()) == eval(X->get_rhs());

            case binary_oper::BINARY_NEQU:
                return eval(X->get_lhs()) != eval(X->get_rhs());

            case binary_oper::BINARY_GREATER:
                return eval(X->get_lhs()) > eval(X->get_rhs());

            case binary_oper::BINARY_LESS:
                return eval(X->get_lhs()) < eval(X->get_rhs());

            case binary_oper::BINARY_GREATER_EQU:
                return eval(X->get_lhs()) >= eval(X->get_rhs());

            case binary_oper::BINARY_LESS_EQU:
                return eval(X->get_lhs()) <= eval(X->get_rhs());

            case binary_oper::BINARY_OR:
                return eval(X->get_lhs()) || eval(X->get_rhs());

            case binary_oper::BINARY_AND:
                return eval(X->get_lhs()) && eval(X->get_rhs());

            default:
                throw std::runtime_error("Unknown binary expression!");
            }
        }

        VAL_TYPE eval(unary_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_un_type())
            {
            case unary_oper::UNARY_MINUS:
                return -eval(X->get_rhs());

            case unary_oper::UNARY_NOT:
                return !eval(X->get_rhs());

            case unary_oper::UNARY_PLUS:
                return eval(X->get_rhs());

            default:
                throw std::runtime_error("Unknown unary expression!");
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
                msg += X->get_name();
                throw std::runtime_error(msg);
            }
            auto var_value = const_cast<scope_node*>(var_scope)->get_var_value(X->get_name());
            return var_value;
        }

        VAL_TYPE eval(base_ast_node * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_ast_type())
            {
            case base_ast_node_type::EXPR:
                return eval(static_cast<base_expr_node*>(X));

            case base_ast_node_type::STMT:{
                eval(static_cast<base_stmt_node*>(X));
                return 0;}

            case base_ast_node_type::SCOPE:{
                eval(static_cast<scope_node*>(X));
                return 0;}

            default:
                throw std::runtime_error("Unknown node type!");
            }
        }

        void eval(scope_node* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            for (auto i : X->get_container()){
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
                eval(static_cast<if_stmt*>(X));
                break;}
            case base_stmt_node_type::WHILE_STMT:{
                eval(static_cast<while_stmt*>(X));
                break;}
            case base_stmt_node_type::PRINT_STMT:{
                eval(static_cast<print_stmt*>(X));
                break;}
            default:
                throw std::runtime_error("Unknown statement!");
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
