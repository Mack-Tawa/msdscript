//
// Created by Mack on 3/13/23.
//

#ifndef CLION_BULL_VAL_H
#define CLION_BULL_VAL_H


#include "Expr.h"

class Val {
public:
    virtual Val * add_to(Val *other_val) = 0;
    virtual Val * mult_to(Val *other_val) = 0;
    virtual bool equals(Val *other_val) = 0;
    virtual std::string to_string() = 0;
    virtual Expr* toExpr() = 0;
};

class numVal : public Val {
public:
    int val;
    numVal(int input);
    bool equals(Val*rhs);
    Val * add_to(Val *other_val) override;
    Val *mult_to(Val *other_val) override;
    std::string to_string();
    Expr* toExpr();

};


#endif //CLION_BULL_VAL_H
