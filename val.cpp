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

    if ((long) val * (long) other_num->val > INT_MAX || (long) val * (long) other_num->val < INT_MIN) {
        throw std::runtime_error("input too big or too small");
    }

    return new numVal((unsigned) val * (unsigned) other_num->val);
}


Val *numVal::add_to(Val *other_val) {
    numVal *other_num = dynamic_cast<numVal *>(other_val);
    if (other_num == nullptr) throw std::runtime_error("add of non-number");

    if ((long) val * (long) other_num->val > INT_MAX || (long) val + (long) other_num->val < INT_MIN) {
        throw std::runtime_error("input too big or too small");
    }

    return new numVal((unsigned) val + (unsigned) other_num->val);
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

Val *numVal::call(Val *actualArg) {
    throw std::runtime_error("Cannot use 'call' for a numVal");
}


/********************************************
 *                boolVal                   *
 ********************************************/

boolVal::boolVal(bool bol) {
    if (bol) {
        this->b = "_true";
    } else this->b = "_false";
}

Val *boolVal::add_to(Val *other_val) {
    throw std::runtime_error("trying to add a boolVal ya dingus");
}

Val *boolVal::mult_to(Val *other_val) {
    throw std::runtime_error("trying to mult two boolVals ya poopoo head");
}

std::string boolVal::to_string() {
    return b;
}

Expr *boolVal::toExpr() {
    if (b == "_true") {
        return new BoolExpr(true);
    } else {
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

Val *boolVal::call(Val *actualArg) {
    throw std::runtime_error("Cannot use 'call' with a boolVal");
}

/********************************************
 *                FunVal                   *
 ********************************************/

FunVal::FunVal(std::string formalArgInput, Expr *body) {
    this->formalArg = formalArgInput;
    this->body = body;
}

Val *FunVal::add_to(Val *other_val) {
    throw std::runtime_error("trying to add two funVals dingus");
}

Val *FunVal::mult_to(Val *other_val) {
    throw std::runtime_error("trying to mult two boolVals ya poopoo head");
}

bool FunVal::equals(Val *rhs) {
    FunVal *v = dynamic_cast<FunVal *>(rhs);
    if (v == nullptr) {
        return false;
    }
    if (this->formalArg == v->formalArg && this->body->equals(v->body)) {
        return true;
    }
}

std::string FunVal::to_string() {
    std::string output = "_fun (";
    output += formalArg;
    output += ") ";
    output += body->to_string();
    return output;
}

Expr *FunVal::toExpr() {
    return new FunExpr(this->formalArg, this->body);
}

bool FunVal::is_true() {
    throw std::runtime_error("Trying to use 'is_true' on a funval");
}
#include <iostream>
Val *FunVal::call(Val *actualArg) {
    std::cout << "In FunVal::call";
    return this->body->subst(formalArg, actualArg->toExpr())->interp();
}