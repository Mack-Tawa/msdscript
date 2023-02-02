//
// Created by Mack on 1/18/23.
//

#include "Expr.h"

Num::Num(int val) {
    this->val = val;
}

bool Num::equals(Expr *e) {
    Num *n = dynamic_cast<Num *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->val == n->val);
    }
}

int Num::interp() {
    return (this->val);
}

bool Num::has_variable() {
    return false;
}

Expr* Num::subst(std::string variable, Expr* expr) {
    return this;
}

Var::Var(std::string val) {
    this->val = val;
}

bool Var::has_variable() {
    return true;
}

Expr* Var::subst(std::string variable, Expr* expr) {

    if (val == variable) {
        return expr;
    }
    return this;
}


bool Var::equals(Expr *e) {
    Var *v = dynamic_cast<Var *>(e);
    if (v == nullptr) {
        return false;
    } else {
        return (this->val == v->val);
    }
}



int Var::interp() {
    throw std::runtime_error( "no value for variable" );
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

int Add::interp() {
    return this->lhs->interp() + this->rhs->interp();
}

bool Add::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

bool Add::equals(Expr *e) {
    Add *n = dynamic_cast<Add *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }
}

Expr* Add::subst(std::string variable, Expr* replacement) {
    return new Add(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}


Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

int Mult::interp() {
    return this->lhs->interp() * this->rhs->interp();
}

bool Mult::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

bool Mult::equals(Expr *e) {
    Mult *n = dynamic_cast<Mult *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }

}
Expr* Mult::subst(std::string variable, Expr* replacement) {
    return new Mult(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}

