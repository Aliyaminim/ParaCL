#include "tree_nodes_include.hpp"

using namespace AST;

int main(){
    func_node_print* X = MakePrOp(1);
    Node_name scope_name = Node_name{"Main scope"};
    scope_node * Main_scope = new scope_node{nullptr, scope_name};
    Main_scope->add_node(X);
    Print_Pr_Op_Node(X);
}
