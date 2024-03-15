#pragma once

#include "ast_nodes_include.hpp"

namespace AST {
    VAL_TYPE func_node_print::process_node(){
        VAL_TYPE res = out_->process_node();
        OBUF << res;
        return res;
    }

    VAL_TYPE number_node::process_node(){
        return value_();
    }

    VAL_TYPE assignment_node::process_node(){
        get_lhs()->process_node();
    }

    VAL_TYPE value_expression::process_node(){
        if (calculated){
            return value;
        }
    }
}
