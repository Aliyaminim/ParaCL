#pragma once

#include <memory>
#include "lexer.hpp"
#include "parser.tab.hh"
#include "scope_node.hpp"
#include "ast_tree.hpp"
#include "tree.hpp"

namespace yy {
class Driver final {
    std::unique_ptr<Lexer> plex;
    AST::scope_node * current_parsing_scope;
    AST::astree * ast_;
public:
    Driver(): plex(std::make_unique<Lexer>()) {}

    parser::symbol_type yylex() {
        parser::symbol_type tt = static_cast<parser::symbol_type>(plex->get_token());
        return tt;
    }

    bool parse() {
        parser parser(this);
        bool res = parser.parse();
        return !res;
    }

    template <typename NodeType, typename... Args>
    AST::base_ast_node *make_node(Args&&... args) {
        auto node = ast_->make_node<NodeType>(std::forward<Args>(args)...);
        //
        return node;
    }


};
} //namespace yy
