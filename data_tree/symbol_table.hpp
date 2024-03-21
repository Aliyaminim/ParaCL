#pragma once

#include "base_ast_node.hpp"
#include <unordered_map>
#include <string>

namespace AST {
class Symbol_table final {
    std::unordered_map<std::string, VAL_TYPE> var_names;
public:

  VAL_TYPE &operator[](const std::string &name) {   return var_names[name]; }

};

} //namespace