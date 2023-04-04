//
// Created by Mack on 3/13/23.
//

#ifndef CLION_BULL_VAL_H
#define CLION_BULL_VAL_H
#include "pointer.h"


class Expr;
class Env;
CLASS(Val) {
public:
    virtual PTR(Val) add_to(PTR(Val)other_val) = 0;
    virtual  PTR(Val) mult_to( PTR(Val)other_val) = 0;
    virtual bool equals( PTR(Val)other_val) = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
    virtual  PTR(Val) call( PTR(Val) actualArg) = 0;
};

class numVal : public Val {
public:
    int val;
    numVal(int input);
    bool equals( PTR(Val)rhs) override;
     PTR(Val) add_to( PTR(Val)other_val) override;
     PTR(Val)mult_to( PTR(Val)other_val) override;
    std::string to_string() override;
    bool is_true() override;
     PTR(Val) call( PTR(Val) actualArg)override;
};

class boolVal : public Val {
public:
    std::string b = "";
    boolVal(bool bol);
    bool equals( PTR(Val) rhs) override;
     PTR(Val) add_to( PTR(Val)other_val) override;
    PTR(Val)mult_to(PTR(Val)other_val) override;
    std::string to_string() override;
    bool is_true()override;
    PTR(Val) call(PTR(Val) actualArg)override;
};

class FunVal : public Val {
public:
//    std::string b = "";
    std::string formalArg;
    PTR(Expr) body;
    PTR(Env) env;
    FunVal(std::string formalArg, PTR(Expr)body, PTR(Env) env);


    bool equals(PTR(Val)rhs) override;
    PTR(Val) add_to(PTR(Val)other_val) override;
    PTR(Val)mult_to(PTR(Val)other_val) override;
    std::string to_string() override;
    bool is_true()override;
    PTR(Val) call(PTR(Val) actualArg)override;
};


#endif //CLION_BULL_VAL_H
