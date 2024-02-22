#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

namespace yy {
class Lexer final : public yyFlexLexer {
//will be extended
public:
    int yylex() override;
};

}//namespace