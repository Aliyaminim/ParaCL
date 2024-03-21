#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type yy::Lexer::get_token()

#include "parser.tab.hh"
#include "location.hpp"

namespace yy {
class Lexer final : public yyFlexLexer {
    position curr_pos;
public:
    parser::symbol_type get_token();

    location upd_loc() {
        auto old_pos = curr_pos;
        curr_pos += yyleng;
        auto new_pos = curr_pos;
        return location{old_pos, new_pos};
    }
};

}//namespace