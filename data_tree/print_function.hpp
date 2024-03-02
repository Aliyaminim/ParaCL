#pragma once

#include "tree.hpp"
#include "number_node.hpp"

struct func_node_print : public base_ast_node {
    //
    base_ast_node *out_ = nullptr;
    func_node_print(base_ast_node *parent, Node_name a, base_ast_node* out) :
        base_ast_node{parent, a}, out_(out) {}
};

func_node_print* MakePrOp(int x){
    Node_name print{"print"};
    Node_name numb{"number"};
    NumNode * n = new NumNode{nullptr, numb, x};
    func_node_print * X = new func_node_print{nullptr, print, n};
    return X;
}

func_node_print* MakePrOp(int x, base_ast_node * parent){
    Node_name print{"print"};
    Node_name numb{"number"};
    NumNode * n = new NumNode{parent, numb, x};
    func_node_print * X = new func_node_print{parent, print, n};
    return X;
}

void Print_Pr_Op_Node(func_node_print* node){
    base_ast_node* A = node->out_;
    NumNode* X = dynamic_cast<NumNode*>(A);
    std::cout << "Oper: Print(" << X->num_ << ")\n";
    return;
}

