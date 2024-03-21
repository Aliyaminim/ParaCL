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
        auto ret = driver.parse();
        if (ret) {
            auto root = driver.get_ast_root();
            AST::Visitor vis{};
            std::cout << vis.eval(root);
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}
