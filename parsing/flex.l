%option c++
%{
    /*definitions*/
    #include "lexer.hpp"
    int curr_line = 1;
    #ifdef DEBUG
        int debugg_num = 0;
    #endif
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

"\n"    {curr_line++; };
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

"&&"    { return yy::parser::make_AND(); }
"||"    { return yy::parser::make_OR(); }
"!"     { return yy::parser::make_NOT(); }

{IDENTIFIER}    {
    #ifdef DEBUG
        std::cout << "Variable's name is " << yytext << std::endl;
    #endif
    return yy::parser::make_VAR(yytext);
}
{NUMBER}  {
    #ifdef DEBUG
    debugg_num = std::atoi(yytext);
    #endif
    return yy::parser::make_NUMBER(std::atoi(yytext));
}

.       {
    #ifdef DEBUG
        std::cout << yytext << std::endl;
    #endif
    throw yy::parser::syntax_error("Unknown symbol");
}
<<EOF>> { return yy::parser::make_EOF(); yyterminate();}

%%