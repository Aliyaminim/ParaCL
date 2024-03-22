#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <filesystem>
#include "observer.hpp"

using namespace yy;
#define EVAL

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "ERROR:\n Please enter ./ParaCL <file>" << std::endl;
        return 1;
    } else if (!std::filesystem::is_regular_file(argv[1])) {
        std::cerr << "ERROR:\nCan't open file " << argv[1] << std::endl;
    }
    std::ifstream input_stream{argv[1]};

    int ret = 0;
    Driver driver(input_stream);
    try {
        auto ret_parse = driver.parse();
        if (ret_parse)
            driver.evaluate();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}
