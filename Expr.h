//
// Created by Mack on 1/18/23.
//

#ifndef EXPRESSIONSHW_EXPR_H
#define EXPRESSIONSHW_EXPR_H
#include <string>
//caps

typedef enum {

    prec_none,      // = 0
    prec_add,       // = 1
    prec_mult       // = 2
} precedence_t;


class Val;
class Expr {

public:
    virtual bool equals(Expr *e) = 0; // 0 means subclass must overwrite equals
    virtual Val* interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string variable, Expr* expr) = 0;
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
    bool equals(Expr *n)override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class VarExpr : public Expr {
public:
    std::string val;
    VarExpr(std::string val);
    bool equals(Expr *n) override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class AddExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    AddExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class MultExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    MultExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class LetExpr : public Expr {
public:

    LetExpr(std::string lhs, Expr *rhs, Expr *body);

    std::string lhs;
    Expr *rhs;
    Expr *body;
    bool equals(Expr *n) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(std::string variable, Expr* expr) override;
    void print(std::ostream& stream) override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) override;
};

class BoolExpr : public Expr {
public:
    BoolExpr(bool);
    bool b;
    bool equals(Expr *e) override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class IfExpr : public Expr {
public:
    Expr *test_part;
    Expr *then_part;
    Expr *else_part;

    IfExpr(Expr* test, Expr* then, Expr* els);

    bool equals(Expr *e)override ;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class EqExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
    EqExpr(Expr*lhs, Expr*rhs);
    bool equals(Expr *e) override;
    Val* interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};
#endif //EXPRESSIONSHW_EXPR_H
