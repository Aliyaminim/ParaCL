%option c++
%{
    /*definitions*/
    #include "lexer.hpp"
    #define yyterminate();
%}

%option noyywrap nounput noinput nodefault
%option yyclass="yy::Lexer"

WS [ \t\n\r\v]+
DIGIT [0-9]
DIGIT1 [1-9]
NUMBER (0|{DIGIT1}{DIGIT}*)
IDENTIFIER [a-zA-Z_][a-zA-Z_{DIGIT}]*

/* rules */
%%

{WS} /*for now do nothing*/

"if"    { return yy::parser::make_IF(); }
"else"  { return yy::parser::make_ELSE(); }
"while" { return yy::parser::make_WHILE(); }
"print" { return yy::parser::make_PRINT(); }
"?"     { return yy::parser::make_QMARK(); }
"("     { return yy::parser::make_LPAREN(); }
")"     { return yy::parser::make_RPAREN(); }
"{"     { return yy::parser::make_LBRACE(); }
"}"     { return yy::parser::make_RBRACE();}
";"     { return yy::parser::make_SCOLON(); }
":"     { return yy::parser::make_COLON(); }
","     { return yy::parser::make_COMMA();}

"+"     { return yy::parser::make_PLUS(); }
"-"     { return yy::parser::make_MINUS(); }
"*"     { return yy::parser::make_MULTIPLY(); }
"/"     { return yy::parser::make_DIVIDE(); }
"%"     { return yy::parser::make_MODULUS(); }
"="     { return yy::parser::make_ASSIGN(); }

"=="    { return yy::parser::make_EQUAL(); }
"!="    { return yy::parser::make_NOT_EQUAL(); }
"<"     { return yy::parser::make_LESS(); }
"<="    { return yy::parser::make_LESS_EQ(); }
">"     { return yy::parser::make_GREATER(); }
">="    { return yy::parser::make_GREATER_EQ(); }

{IDENTIFIER}    { return yy::parser::make_VAR(yytext); }
{NUMBER}  { return yy::parser::make_NUMBER(std::atoi(yytext)); }

.         { throw yy::parser::syntax_error("Unknown symbol"); }
<<EOF>> { return yy::parser::make_EOF(); yyterminate();}

%%