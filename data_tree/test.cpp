#include "tree_nodes_include.hpp"
#include "print_function.hpp"

using namespace AST;

int main(){
    // func_node_print* X = MakePrOp(1);
    Node_name scope_name = Node_name{"Main scope"};
    // scope_node * Main_scope = new scope_node{nullptr, scope_name};
    // Main_scope->add_node(X);
    // Print_Pr_Op_Node(X);

    astree * test = new astree();

    number_node * N = dynamic_cast<number_node*>(test->make_node<number_node>(nullptr, scope_name, 4));

    value_expression * X = dynamic_cast<value_expression*>(test->make_node<value_expression>(nullptr, scope_name));

    X->add_value(N);

    func_node_print * Pr = dynamic_cast<func_node_print*>(test->make_node<func_node_print>(nullptr, scope_name, X));
    std::cout << "\n\n\n";
    Pr->process_node();
    std::cout << "\n\n\n";
}
