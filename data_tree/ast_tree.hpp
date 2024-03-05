#pragma once

#include "tree.hpp"
#include "scope_node.hpp"

namespace AST {
    class astree {
        scope_node * singular_scope = nullptr;
        scope_node * current_scope = nullptr;

    public:
        template <typename NodeType, typename... t_args> base_ast_node* make_node(t_args &&...args, scope_node * curr_scope){
            // Пока ничего не делает, определиться с типами t_args, которые попадают в макеноду


            //create_expression<T>* nodeX = new create_expression<T>{};
            //curr_scope->add_node(nodeX);
            //Привязка к текущему скоупу

            // Функция узнает текущий скоуп от дерева
            // Затем узнает тип операции
            // Затем делает саму ноду свичом по типам операций
            // 
            return nullptr;
        }






    };
}
