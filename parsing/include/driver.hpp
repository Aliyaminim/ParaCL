#pragma once

#include "lexer.hpp"
#include "parser.tab.hh"
#include <memory>

namespace yy {
class Driver final {
    std::unique_ptr<Lexer> plex;
public:
    Driver(std::unique_ptr<Lexer> plex_): plex(std::move(plex_)) {}

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