#ifndef AST_CPP
#define AST_CPP

#include "scope_node.hpp"
#include "node_types.hpp"

#include "tree.hpp"
#include "number_node.hpp"
#include "variable_node.hpp"
#include "value_expressions.hpp"
#include "assignment.hpp"



namespace AST {
    class astree {
        scope_node * singular_scope = nullptr;
        scope_node * current_scope = nullptr;

    public:


        template <typename NodeType, typename... t_args> base_ast_node* make_node(t_args && ... args){
            auto new_node = new NodeType(std::forward<t_args>(args)...);
            return new_node;
        }

        // template <> base_ast_node* make_node<AST::number_node, int>(int && X, scope_node * curr_scope){
        //     number_node * N = new number_node{nullptr, "", X};
        //     return N;
        // }

        // auto new_node = new NodeType(std::forward<t_args>(args)...)


        // template <typename NodeType, typename... t_args> base_ast_node* make_node(t_args &&...args, scope_node * curr_scope){
        //     switch (NodeType)
        //     {
        //     case terminal_nodes::INT:
        //         number_node * N = new number_node{nullptr, "", std::forward<t_args>(args)...};
        //         return N;
        //         break;
            
        //     default:
        //         break;
        //     }
            // Пока ничего не делает, определиться с типами t_args, которые попадают в макеноду


            //create_expression<T>* nodeX = new create_expression<T>{};
            //curr_scope->add_node(nodeX);
            //Привязка к текущему скоупу

            // Функция узнает текущий скоуп от дерева
            // Затем узнает тип операции
            // Затем делает саму ноду свичом по типам операций
            // 
        //     return nullptr;
        // }






    };
}
#endif
