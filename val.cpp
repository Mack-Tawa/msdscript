//
// Created by Mack on 3/13/23.
//

#include <stdexcept>
#include <string>
#include "val.h"
#include "Expr.h"

bool numVal::equals(PTR(Val)rhs) {
    PTR(numVal)v = CAST(numVal) (rhs);
    if (v == nullptr) {
        return false;
    } else {
        return (this->val == v->val);
    }
}

PTR(Val)numVal::mult_to(PTR(Val)other_val) {
    PTR(numVal)other_num = CAST(numVal) (other_val);
    if (other_num == nullptr) throw std::runtime_error("mult of non-number");

    if ((long) val * (long) other_num->val > INT_MAX || (long) val * (long) other_num->val < INT_MIN) {
        throw std::runtime_error("input too big or too small");
    }

    return NEW(numVal)((unsigned) val * (unsigned) other_num->val);
}
/**
 *
Val *numVal::mult_to(Val *other_val) {
    numVal *other_num = dynamic_cast<numVal *>(other_val);
    if (other_num == nullptr) throw std::runtime_error("mult of non-number");

    if ((long) val * (long) other_num->val > INT_MAX || (long) val * (long) other_num->val < INT_MIN) {
        throw std::runtime_error("input too big or too small");
    }

    return new numVal((unsigned) val * (unsigned) other_num->val);
}
 * @param other_val
 * @return
 */


PTR(Val)numVal::add_to(PTR(Val)other_val) {
    PTR(numVal)other_num = CAST(numVal) (other_val);
    if (other_num == nullptr) throw std::runtime_error("add of non-number");

    if ((long) val + (long) other_num->val > INT_MAX || (long) val + (long) other_num->val < INT_MIN) {
        throw std::runtime_error("input too big or too small");
    }

    return NEW(numVal)((unsigned) val + (unsigned) other_num->val);
}

numVal::numVal(int input) {
    this->val = input;
}

std::string numVal::to_string() {
    std::string output = std::to_string(this->val);
    return output;
}

PTR(Expr)numVal::toExpr() {
    return NEW(NumExpr)(this->val);
}

bool numVal::is_true() {
    throw std::runtime_error("invalid argument");
}

PTR(Val) numVal::call(PTR(Val) actualArg) {
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

PTR(Val)boolVal::add_to(PTR(Val) other_val) {
    throw std::runtime_error("trying to add a boolVal ya dingus");
}

PTR(Val)boolVal::mult_to(PTR(Val)other_val) {
    throw std::runtime_error("trying to mult two boolVals ya poopoo head");
}

std::string boolVal::to_string() {
    return b;
}

PTR(Expr)boolVal::toExpr() {
    if (b == "_true") {
        return NEW(BoolExpr)(true);
    } else {
        return NEW(BoolExpr)(false);
    }
}

bool boolVal::equals(PTR(Val)rhs) {
    PTR(boolVal)v = CAST(boolVal) (rhs);
    if (v == nullptr) {
        return false;
    } else {
        return (this->b == v->b);
    }
}

bool boolVal::is_true() {
    return this->b == "_true";
}

PTR(Val)boolVal::call(PTR(Val)actualArg) {
    throw std::runtime_error("Cannot use 'call' with a boolVal");
}

/********************************************
 *                FunVal                   *
 ********************************************/

FunVal::FunVal(std::string formalArgInput, PTR(Expr)body) {
    this->formalArg = formalArgInput;
    this->body = body;
}

PTR(Val)FunVal::add_to(PTR(Val)other_val) {
    throw std::runtime_error("trying to add two funVals dingus");
}

PTR(Val)FunVal::mult_to(PTR(Val)other_val) {
    throw std::runtime_error("trying to mult two boolVals ya poopoo head");
}

bool FunVal::equals(PTR(Val)rhs) {
    PTR(FunVal )v = CAST(FunVal) (rhs);
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

PTR(Expr)FunVal::toExpr() {
    return NEW(FunExpr)(this->formalArg, this->body);
}

bool FunVal::is_true() {
    throw std::runtime_error("Trying to use 'is_true' on a funval");
}
PTR(Val)FunVal::call(PTR(Val)actualArg) {
    return this->body->subst(formalArg, actualArg->toExpr())->interp();
}
