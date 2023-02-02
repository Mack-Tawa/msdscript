//
// Created by Mack on 1/18/23.
//

#ifndef EXPRESSIONSHW_EXPR_H
#define EXPRESSIONSHW_EXPR_H
#include <string>
//caps


class Expr {

public:
    virtual bool equals(Expr *e) = 0; // 0 means subclass must overwrite equals
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string variable, Expr* expr) = 0;

};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *n);
    int interp();
    bool has_variable();
    Expr* subst(std::string variable, Expr* expr);
};

class Var : public Expr {
public:
    std::string val;
    Var(std::string val);
    bool equals(Expr *n) override;
    int interp();
    bool has_variable();
    Expr* subst(std::string variable, Expr* expr);
};

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    int interp();
    bool has_variable();
    Expr* subst(std::string variable, Expr* expr);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    int interp();
    bool has_variable();
    Expr* subst(std::string variable, Expr* expr);
};

#endif //EXPRESSIONSHW_EXPR_H
