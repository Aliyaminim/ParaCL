#pragma once

#include <memory>
#include "lexer.hpp"
#include "parser.tab.hh"
#include "scope_node.hpp"
#include "ast_tree.hpp"
#include "base_ast_node.hpp"

namespace yy {
class Driver final {
    std::unique_ptr<Lexer> plex;
    std::unique_ptr<AST::astree> ast_;
    AST::scope_node* current_parsing_scope;
public:
    Driver(): plex(std::make_unique<Lexer>()), ast_(std::make_unique<AST::astree>()),
                current_parsing_scope(nullptr) {}

    void set_ast_root(AST::base_ast_node* ptr) {
        ast_->set_root(ptr);
    }

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

    void set_curr_parsing_scope(AST::scope_node* sc) { current_parsing_scope = sc; }

    AST::scope_node* get_curr_parsing_scope() { return current_parsing_scope; }

    void reset_curr_parsing_scope() {
        current_parsing_scope = current_parsing_scope->get_parent_scope();
    }
};
} //namespace yy
