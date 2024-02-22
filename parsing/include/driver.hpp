#pragma once

#include <numeric>
#include "parser.tab.hh"
#include <FlexLexer.h>

namespace yy {
class Driver final {
    FlexLexer* plex;
public:
    Driver(FlexLexer* plex_): plex(plex_) {}

    parser::token_type yylex(parser::semantic_type* yylval) {
        parser::token_type tt = static_cast<parser::token_type>(plex->yylex());
        if (tt == yy::parser::token_type::TOKEN_NUMBER)
            yylval->as<int>() = std::stoi(plex->YYText());
        return tt;
    }

    bool parse() {
        parser parser(this);
        bool res = parser.parse();
        return !res;
    }

};
} //namespace yy