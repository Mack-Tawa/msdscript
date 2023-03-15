//
// Created by Mack on 3/13/23.
//

#include <stdexcept>
#include <string>
#include "val.h"
#include "Expr.h"

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
    if (other_num == nullptr) throw std::runtime_error("mult of non-number");
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
    return new NumExpr(this->val);
}

bool numVal::is_true() {
    throw std::runtime_error("invalid argument");
}

/********************************************
 *                boolVal                   *
 ********************************************/

boolVal::boolVal(bool bol) {
    if (bol) {
        this->b = "_true";
    }
    else this->b = "_false";
}

Val* boolVal::add_to(Val *other_val) {
    throw std::runtime_error("trying to add two boolVals dingus");
}

Val* boolVal::mult_to(Val *other_val) {
    throw std::runtime_error("trying to mult two boolVals ya poopoo head");
}

std::string boolVal::to_string() {
    return b;
}

Expr *boolVal::toExpr() {
    if (b == "_true") {
        return new BoolExpr(true);
    }
    else {
        return new BoolExpr(false);
    }
}

bool boolVal::equals(Val *rhs) {
    boolVal *v = dynamic_cast<boolVal *>(rhs);
    if (v == nullptr) {
        return false;
    } else {
        return (this->b == v->b);
    }
}

bool boolVal::is_true() {
    return this->b == "_true";
}




