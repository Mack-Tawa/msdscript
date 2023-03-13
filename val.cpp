//
// Created by Mack on 3/13/23.
//

#include <stdexcept>
#include <string>
#include "val.h"

bool numVal::equals(Val *rhs) {
    numVal *v = dynamic_cast<numVal *>(rhs);
    if (v == nullptr) {
        return false;
    } else {
        return (this->val == v->val);
    }
}

Val *numVal::mult_to(Val *other_val) {
    numVal *other_num = dynamic_cast<numVal *>(other_val);
    if (other_num == nullptr) throw std::runtime_error("add of non-number");
    return new numVal(val * other_num->val);
}


Val *numVal::add_to(Val *other_val) {
    numVal *other_num = dynamic_cast<numVal *>(other_val);
    if (other_num == nullptr) throw std::runtime_error("add of non-number");
    return new numVal(val + other_num->val);
}

numVal::numVal(int input) {
    this->val = input;
}

std::string numVal::to_string() {
    std::string output = std::to_string(this->val);
    return output;
}

Expr *numVal::toExpr() {
    return new Num(this->val);
}



