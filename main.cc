#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <memory>
#include "visitor.hpp"

using namespace yy;

int main() {
    int ret = 0;
    Driver driver{};
    try {
        driver.parse();
        auto root = driver.get_ast_root();
        AST::Visitor vis{};
        std::cout << vis.eval(root);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}