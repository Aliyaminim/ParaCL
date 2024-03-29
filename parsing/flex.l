%option c++
%{
    #include "lexer.hpp"
    #include <string>
    #define yyterminate();
%}

%option noyywrap nounput noinput nodefault yylineno
%option yyclass="yy::Lexer"

WS [ \t\n\r\v]+
DIGIT [0-9]
DIGIT1 [1-9]
NUMBER (0|{DIGIT1}{DIGIT}*)
IDENTIFIER [a-zA-Z_][a-zA-Z_0-9]*

/* rules */
%%

[\n\r]+ { curr_pos.lines(yyleng); }
[ \t]+  { curr_pos.columns(yyleng); }

"//".* { upd_loc(); }

"if"    { return yy::parser::make_IF(upd_loc()); }
"else"  { return yy::parser::make_ELSE(upd_loc()); }
"while" { return yy::parser::make_WHILE(upd_loc()); }
"print" { return yy::parser::make_PRINT(upd_loc()); }
"?"     { return yy::parser::make_QMARK(upd_loc()); }
"("     { return yy::parser::make_LPAREN(upd_loc()); }
")"     { return yy::parser::make_RPAREN(upd_loc()); }
"{"     { return yy::parser::make_LBRACE(upd_loc()); }
"}"     { return yy::parser::make_RBRACE(upd_loc());}
";"     { return yy::parser::make_SCOLON(upd_loc()); }
":"     { return yy::parser::make_COLON(upd_loc()); }
","     { return yy::parser::make_COMMA(upd_loc());}

"+"     { return yy::parser::make_PLUS(upd_loc()); }
"-"     { return yy::parser::make_MINUS(upd_loc()); }
"*"     { return yy::parser::make_MULTIPLY(upd_loc()); }
"/"     { return yy::parser::make_DIVIDE(upd_loc()); }
"%"     { return yy::parser::make_MODULUS(upd_loc()); }
"="     { return yy::parser::make_ASSIGN(upd_loc()); }

"=="    { return yy::parser::make_EQUAL(upd_loc()); }
"!="    { return yy::parser::make_NOT_EQUAL(upd_loc()); }
"<"     { return yy::parser::make_LESS(upd_loc()); }
"<="    { return yy::parser::make_LESS_EQ(upd_loc()); }
">"     { return yy::parser::make_GREATER(upd_loc()); }
">="    { return yy::parser::make_GREATER_EQ(upd_loc()); }

"&&"    { return yy::parser::make_AND(upd_loc()); }
"||"    { return yy::parser::make_OR(upd_loc()); }
"!"     { return yy::parser::make_NOT(upd_loc()); }

{IDENTIFIER} {
    return yy::parser::make_VAR(yytext, upd_loc());
}
{NUMBER} {
    return yy::parser::make_NUMBER(std::atoi(yytext), upd_loc());
}

. {
  std::string msg = "unknown character '"; msg += yytext; msg += "'";
  throw parser::syntax_error(upd_loc(), msg);
}

<<EOF>> { return yy::parser::make_EOF(upd_loc()); yyterminate();}

%%