#ifndef TREE_CPP
#define TREE_CPP

#include <iostream>
#include <string>
#include <vector>

#define OBUF std::cout

using VAL_TYPE = int;

// Типы операций генерируются бизоном и флексом, далее используются нодами

namespace AST {

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
    virtual VAL_TYPE process_node() = 0;
};

}

#endif