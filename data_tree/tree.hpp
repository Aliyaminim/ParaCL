#pragma once

#include <iostream>
#include <string>
#include <vector>


// Типы операций генерируются бизоном и флексом, далее используются нодами


struct Node_name{
    private:
        std::string data;
    public:
        Node_name(std::string st) : data(st) {
        }
        std::string get_data(){
            return data;
        };
};

struct base_ast_node {
    base_ast_node *parent_ = nullptr;
    Node_name nname;
    base_ast_node(base_ast_node *parent, Node_name & a) : parent_(parent), nname(a) {};
    virtual ~base_ast_node() = default;
};

struct NumNode : public base_ast_node
{
    int num_;
    NumNode(base_ast_node *parent, Node_name a, int x) :
        base_ast_node{parent, a}, num_(x) {}
};


base_ast_node* MakeNode(Node_name a){
    base_ast_node * X = new base_ast_node{nullptr, a};
    return X;
}
