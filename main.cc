#include "driver.hpp"
#include "lexer.hpp"

using namespace yy;

int main() {
    FlexLexer* lexer = new Lexer;
    Driver driver(lexer);
    driver.parse();
    delete lexer;
}