#pragma once

#include "base_ast_node.hpp"
#include <unordered_map>
#include <string>

namespace AST {
    class Symbol_table final {
        std::unordered_map<std::string, VAL_TYPE> var_names;
    public:
        bool contains(const std::string &name) const { return var_names.contains(name); }

        void add(const std::string &name) { var_names.emplace(name, VAL_TYPE{}); }

        VAL_TYPE &operator[](const std::string &name) { return var_names[name]; }

        std::unordered_map<std::string, VAL_TYPE>* get_vars() { return &var_names; }

    };

}
