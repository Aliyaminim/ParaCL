#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type yy::Lexer::get_token()

#include "parser.tab.hh"

namespace yy {
class Lexer final : public yyFlexLexer {
//will be extended
public:
    parser::symbol_type get_token();
};

}//namespace