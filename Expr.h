//
// Created by Mack on 1/18/23.
//

#ifndef EXPRESSIONSHW_EXPR_H
#define EXPRESSIONSHW_EXPR_H
#include <string>
#include "pointer.h"
//caps

typedef enum {

    prec_none,      // = 0
    prec_add,       // = 1
    prec_mult,       // = 2
    prec_fun         // = 3
} precedence_t;


class Val;
CLASS(Expr) {

public:
    virtual bool equals(PTR(Expr)e) = 0; // 0 means subCLASS() must overwrite equals
    virtual PTR(Val) interp() = 0;
    virtual PTR(Expr) subst(std::string variable, PTR(Expr) expr) = 0;
    virtual void print(std::ostream& stream) = 0;
    std::string to_string();
    std::string pretty_print_to_string();
    void pretty_print(std::ostream&stream);
    virtual void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)= 0;

};

class NumExpr : public Expr {
public:
    int val;
    NumExpr(int val);
    bool equals(PTR(Expr)n)override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class VarExpr : public Expr {
public:
    std::string val;
    VarExpr(std::string val);
    bool equals(PTR(Expr)n) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class AddExpr : public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;
    AddExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)n) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class MultExpr : public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;
    MultExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)n) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class LetExpr : public Expr {
public:

    LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body);

    std::string lhs;
    PTR(Expr)rhs;
    PTR(Expr)body;
    bool equals(PTR(Expr)n) override;
    PTR(Val) interp() override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr) override;
    void print(std::ostream& stream) override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) override;
};

class BoolExpr : public Expr {
public:
    BoolExpr(bool);
    bool b;
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class IfExpr : public Expr {
public:
    PTR(Expr)test_part;
    PTR(Expr)then_part;
    PTR(Expr)else_part;

    IfExpr(PTR(Expr) test, PTR(Expr) then, PTR(Expr) els);

    bool equals(PTR(Expr)e)override ;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class EqExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    EqExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)e) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class FunExpr : public Expr {
public:
    std::string formalArg;
    PTR(Expr) body;
    FunExpr(std::string formalArg, PTR(Expr)body);

    bool equals(PTR(Expr)e) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class CallExpr : public Expr {
public:

    PTR(Expr) toBeCalled;
    PTR(Expr) actualArg;
    CallExpr(PTR(Expr)toBeCalled, PTR(Expr)actualArg);


    bool equals(PTR(Expr)e) override;
    PTR(Val) interp()override;
    PTR(Expr) subst(std::string variable, PTR(Expr) expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};



#endif //EXPRESSIONSHW_EXPR_H
