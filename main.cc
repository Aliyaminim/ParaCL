#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <memory>
#include "visitor.hpp"

using namespace yy;
#define EVAL

int main() {
    int ret = 0;
    Driver driver{};
    try {
        driver.parse();
        #ifdef EVAL
        auto root = driver.get_ast_root();
        AST::Visitor vis{};
        std::cout << vis.eval(root);
        #endif
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}
