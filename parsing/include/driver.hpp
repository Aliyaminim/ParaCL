#pragma once

#include "lexer.hpp"
#include "parser.tab.hh"
#include "tree_nodes_include.hpp"

namespace yy {
class Driver final {
    Lexer* plex;
private:
    AST::scope_node * current_parsing_scope;
    AST::astree * ast_;
public:
    Driver(Lexer* plex_): plex(plex_) {}

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
    base_ast_node *make_node(Args&&... args) {
        auto node = ast_.make_node<NodeType>(std::forward<Args>(args)...);
        //
        return node;
    }


};
} //namespace yy
