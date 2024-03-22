#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <memory>
#include "observer.hpp"

using namespace yy;
#define EVAL

int main() {
    int ret = 0;
    Driver driver{};
    std::string infile{"../test/input.in"};
    std::string outfile{"../test/output.out_"};
    try {
        auto ret_parse = driver.parse();
        if (ret_parse) {
            auto root = driver.get_ast_root();
            AST::Observer obs{infile, outfile};
            obs.eval(root);
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}
