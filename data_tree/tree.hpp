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

struct Node {
    Node *parent_ = nullptr;
    Node_name nname;
    Node(Node *parent, Node_name a) : parent_(parent), nname(a) {};
    virtual ~Node() = default;
};

/*
template <typename BinType>
struct BinOp : public Node {
    BinOp_t op_;
    Node *lhs_ = nullptr, *rhs_ = nullptr;
    BinOp(BinType type, Node *parent, BinOp_t opcode) :
        Node{parent}, op_(opcode) {}
};

*/

struct PrintOp : public Node {

    Node *out_ = nullptr;
    PrintOp(Node *parent, Node_name a, Node* out) :
        Node{parent, a}, out_(out) {}
};

struct NumNode : public Node
{
    int num_;
    NumNode(Node *parent, Node_name a, int x) :
        Node{parent, a}, num_(x) {}
};


Node* MakeNode(Node_name a){
    Node * X = new Node{nullptr, a};
    return X;
}

PrintOp* MakePrOp(int x){
    Node_name print{"print"};
    Node_name numb{"number"};
    NumNode * n = new NumNode{nullptr, numb, x};
    PrintOp * X = new PrintOp{nullptr, print, n};
    return X;
}

PrintOp* MakePrOp(int x, Node * parent){
    Node_name print{"print"};
    Node_name numb{"number"};
    NumNode * n = new NumNode{parent, numb, x};
    PrintOp * X = new PrintOp{parent, print, n};
    return X;
}

void Print_Pr_Op_Node(PrintOp* node){
    Node* A = node->out_;
    NumNode* X = dynamic_cast<NumNode*>(A);
    std::cout << "Oper: Print(" << X->num_ << ")\n";
    return;
}

void MakeNode(...){
    
}   