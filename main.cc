#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"

using namespace yy;

int main() {
    int ret = 0;
    Lexer* lexer = new Lexer;
    Driver driver(lexer);
    try {
        driver.parse();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        ret = 1;
    }
    delete lexer;
    return ret;
}