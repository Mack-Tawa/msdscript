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



class Expr {

public:
    virtual bool equals(Expr *e) = 0; // 0 means subclass must overwrite equals
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string variable, Expr* expr) = 0;
    virtual void print(std::ostream& stream) = 0;
    std::string to_string();
    std::string pretty_print_to_string();
    void pretty_print(std::ostream&stream);
    virtual void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)= 0;






};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *n)override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class Var : public Expr {
public:
    std::string val;
    Var(std::string val);
    bool equals(Expr *n) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr)override;
    void print(std::ostream& stream)override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *n) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string variable, Expr* expr) override;
    void print(std::ostream& stream) override;
    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar)override;

};

class Let : public Expr {
public:

    Let(std::string lhs, Expr *rhs, Expr *body);

    std::string lhs;
    Expr *rhs;
    Expr *body;
    bool equals(Expr *n) override;
    int interp() override;
    bool has_variable() override;
    Expr* subst(std::string variable, Expr* expr) override;
    void print(std::ostream& stream) override;

    void pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) override;
};



#endif //EXPRESSIONSHW_EXPR_H
