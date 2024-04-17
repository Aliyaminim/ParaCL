#pragma once

#include "base_ast_node.hpp"
#include <unordered_map>
#include <string_view>

namespace AST {
    class Symbol_table final {
        std::unordered_map<std::string_view, VAL_TYPE> var_names;
    public:
        bool contains(std::string_view name) const { return var_names.contains(name); }

        void add(std::string_view name) { var_names.emplace(name, VAL_TYPE{}); }

        VAL_TYPE &operator[](std::string_view name) { return var_names[name]; }

    };

}
