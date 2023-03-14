//
// Created by Mack on 3/13/23.
//

#ifndef CLION_BULL_VAL_H
#define CLION_BULL_VAL_H


class Expr;
class Val {
public:
    virtual Val * add_to(Val *other_val) = 0;
    virtual Val * mult_to(Val *other_val) = 0;
    virtual bool equals(Val *other_val) = 0;
    virtual std::string to_string() = 0;
    virtual Expr* toExpr() = 0;
    virtual bool is_true() = 0;
};

class numVal : public Val {
public:
    int val;
    numVal(int input);
    bool equals(Val*rhs);
    Val * add_to(Val *other_val) override;
    Val *mult_to(Val *other_val) override;
    std::string to_string() override;
    Expr* toExpr() override;
    bool is_true();
};

class boolVal : public Val {
public:
    std::string b = "";
    boolVal(bool bol);
    bool equals(Val*rhs) override;
    Val * add_to(Val *other_val) override;
    Val *mult_to(Val *other_val) override;
    std::string to_string() override;
    Expr* toExpr() override;
    bool is_true();
};


#endif //CLION_BULL_VAL_H
