#pragma once

#include "base_ast_node.hpp"

namespace AST {
class print_stmt : public base_stmt_node {
    base_expr_node *out;

public:
    explicit print_stmt(base_expr_node* out_ = nullptr) : out(out_) {}
};
}