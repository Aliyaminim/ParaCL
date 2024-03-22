#pragma once

#include "lexer.hpp"
#include "parser.tab.hh"
#include "scope_node.hpp"
#include "ast_tree.hpp"
#include "base_ast_node.hpp"

namespace yy {
    class Driver final {
        Lexer plex;
        AST::astree ast_;
        AST::scope_node* current_parsing_scope;
    public:
        Driver(): plex(Lexer()), ast_(AST::astree()),
                    current_parsing_scope(ast_.get_root()) {}

        void set_ast_root(AST::scope_node* ptr) {
            ast_.set_root(ptr);
        }

        auto get_ast_root() { return ast_.get_root(); }

        parser::symbol_type yylex() {
            parser::symbol_type tt = static_cast<parser::symbol_type>(plex.get_token());
            return tt;
        }

        bool parse() {
            parser parser(this);
            bool res = parser.parse();
            return !res;
        }

        template <typename NodeType, typename... Args>
        auto *make_node(Args&&... args) {
            auto node = ast_.make_node<NodeType>(std::forward<Args>(args)...);
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
