#pragma once

#include "lexer.hpp"
#include "parser.tab.hh"

namespace yy {
class Driver final {
    Lexer* plex;
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

};
} //namespace yy