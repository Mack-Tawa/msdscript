//
// Created by Mack on 1/18/23.
//

#include <sstream>
#include "val.h"
#include "Expr.h"
//
//
//Expr *parse_expr(std::istream &in);
//Expr *parse_num(std::istream &in);
//Expr *parse_multicand(std::istream &in);
//Expr *parse_addend(std::istream &in);
//

/**
 * \brief - Returns an expression as a string
 * \param - Takes in the expression that calls it
 * \@return - Returns an expression as a string
 */
std::string Expr::to_string() {

    std::stringstream st("");
    this->print(st);
    return st.str();
}


/**
 * \brief - Returns an expression with correct parentheses
 * \return - Returns a string to be printed
 */
std::string Expr::pretty_print_to_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

/**
 * \brief - Prints to console the correct parentheses
 * \param stream - the stream input to console
 */
void Expr::pretty_print(std::ostream &stream) {
    std::streampos sPos = 0;
    bool needsPar = false;
    pretty_print_at(stream, prec_none, sPos, needsPar);
}

//**************NumExpr class methods***************
/**
 * \brief - Constructor for a number
 * \param val - takes in an int
 */
NumExpr::NumExpr(int val) {
    this->val = val;
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool NumExpr::equals(Expr *e) {
    NumExpr *n = dynamic_cast<NumExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->val == n->val);
    }
}

/**
 * \brief - Gives the value of the number
 * \return - Returns the value of the number
 */
Val *NumExpr::interp() {
    numVal *v = new numVal(this->val);
    return v;
}

/**
 * \brief - Returns a number being called
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - the number being called
 */
Expr *NumExpr::subst(std::string variable, Expr *expr) {
    return this;
}

/**
 * \brief - prints the object calling to the stream
 * \param stream - the stream being utilized
 */
void NumExpr::print(std::ostream &stream) {
    stream << std::to_string(val);
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec_none - the precedence is always zero for nums
 */
void NumExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    stream << this->val;
}

//**************VarExpr class methods***************
/**
 * \brief - the constructor for a VarExpr
 * \param val - the string representing the var
 */
VarExpr::VarExpr(std::string val) {
    this->val = val;
}


/**
 * \brief - prints the object calling to the stream
 * \param stream - the stream being utilized
 */
void VarExpr::print(std::ostream &stream) {
    stream << val;
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec_none - the precedence is always zero for nums
 */
void VarExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    stream << this->val;
}


/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 */
Expr *VarExpr::subst(std::string variable, Expr *expr) {

    if (val == variable) {
        return expr;
    }
    return this;
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool VarExpr::equals(Expr *e) {
    VarExpr *v = dynamic_cast<VarExpr *>(e);
    if (v == nullptr) {
        return false;
    } else {
        return (this->val == v->val);
    }
}

/**
 * \brief - throws an exception as there is no value for Vars
 * \return - exception
 */
Val *VarExpr::interp() {
    throw std::runtime_error("no value for variable");
}

//**************AddExpr class methods***************
/**
 * \brief - constructor for AddExpr class
 * \param lhs - left hand side of the equation
 * \param rhs - right hand side of the equation
 */
AddExpr::AddExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
Val *AddExpr::interp() {

    return lhs->interp()->add_to(rhs->interp());
}


/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool AddExpr::equals(Expr *e) {
    AddExpr *n = dynamic_cast<AddExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }
}

/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 * \param variable - the variable being checked in string format
 * \param replacement - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 */
Expr *AddExpr::subst(std::string variable, Expr *replacement) {
    return new AddExpr(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}

/**
 * \brief - Prints the left side and right side within parentheses
 * \param stream - the stream to be utilized
 */
void AddExpr::print(std::ostream &stream) {
    stream << ("(");
    lhs->print(stream);
    stream << ("+");
    rhs->print(stream);
    stream << (")");
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec - the precedence is always 1 for Adds
 */
void AddExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {

    if (prec >= prec_add) {
        stream << ("(");
    }
    lhs->pretty_print_at(stream, prec_add, sPos, true);
    stream << (" + ");
    rhs->pretty_print_at(stream, prec_none, sPos, false);

    if (prec >= prec_add) {
        stream << (")");
    }
}

//**************MultExpr class methods***************
/**
 * \brief - the constructor for MultExpr class
 * \param lhs - the lhs expression of the equation
 * \param rhs - the rhs expression of the equation
 */
MultExpr::MultExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
Val *MultExpr::interp() {
    return this->lhs->interp()->mult_to(this->rhs->interp());
}


/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool MultExpr::equals(Expr *e) {
    MultExpr *n = dynamic_cast<MultExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }

}

/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 * \param variable - the variable being checked in string format
 * \param replacement - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the VarExpr
 */
Expr *MultExpr::subst(std::string variable, Expr *replacement) {
    return new MultExpr(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}

/**
 * \brief - Prints the right hand side and left hand side with a '*' in between. The whole thing is surrounded by parentheses
 * \param stream - The stream being utilized
 */
void MultExpr::print(std::ostream &stream) {
    stream << ("(");
    lhs->print(stream);
    stream << ("*");
    rhs->print(stream);
    stream << (")");
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec - the precedence is always 2 for Mults
 */
void MultExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {

    if (prec == prec_mult) {
        stream << ("(");
    }

    lhs->pretty_print_at(stream, prec_mult, sPos, true);
    stream << (" * ");
    if (prec == prec_add) {
        rhs->pretty_print_at(stream, prec_add, sPos, true);
    } else rhs->pretty_print_at(stream, prec_add, sPos, false);

    if (prec == prec_mult) {
        stream << (")");
    }
}

LetExpr::LetExpr(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}


bool LetExpr::equals(Expr *e) {
    LetExpr *n = dynamic_cast<LetExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs == (n->lhs)
                && this->rhs->equals(n->rhs)
                && this->body->equals(n->body));
    }
}

void LetExpr::print(std::ostream &stream) {
    stream << "(";
    stream << "_let ";
    stream << lhs << "=" << rhs->to_string();
    stream << " _in ";
    stream << body->to_string();
    stream << ")";
}

void LetExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    if (needPar) {
        stream << "(";
    }
    int temp = stream.tellp();
    int indent = temp - sPos;

    stream << "_let ";
    stream << lhs << " = ";
    rhs->pretty_print_at(stream, prec_none, sPos, false);
    stream << "\n";
    sPos = stream.tellp();


    for (int i = 0; i < indent; i++) {
        stream << ' ';
    }

    stream << "_in  ";
    body->pretty_print_at(stream, prec_none, sPos, false);

    if (needPar) {
        stream << ")";
    }

}

Expr *LetExpr::subst(std::string variable, Expr *expr) {
    if (lhs == variable) {
        return new LetExpr(lhs, rhs->subst(variable, expr), body);
    }
    return new LetExpr(lhs, (rhs->subst(variable, expr)), body->subst(variable, expr));
}

Val *LetExpr::interp() {
    return (this->body->subst(lhs, rhs)->interp());
}


/**
 * *******************************
 *         BOOLEXPR
 * *******************************
 *
 * @param e
 * @return
 */

BoolExpr::BoolExpr(bool buh) {
    if (buh) {
        this->b = true;
    } else {
        b = false;
    }
}

bool BoolExpr::equals(Expr *e) {
    BoolExpr *n = dynamic_cast<BoolExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->b == n->b);
    }
}

Val *BoolExpr::interp() {
    return new boolVal(b);
}

/**
 * \brief - Returns a number being called
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - the number being called
 */
Expr *BoolExpr::subst(std::string variable, Expr *expr) {
    return this;
}

/**
 * \brief - prints the object calling to the stream
 * \param stream - the stream being utilized
 */
void BoolExpr::print(std::ostream &stream) {
    if (b) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec_none - the precedence is always zero for nums
 */
void BoolExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    if (b) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

/****************
* if then else
*****************/

IfExpr::IfExpr(Expr *test, Expr *then, Expr *els) {
    test_part = test;
    then_part = then;
    else_part = els;
}

bool IfExpr::equals(Expr *e) {
    IfExpr *n = dynamic_cast<IfExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->test_part->equals(n->test_part)
                && this->then_part->equals(n->then_part) && this->else_part->equals(n->else_part));
    }
}

Val *IfExpr::interp() {
    if (this->test_part->interp()->is_true()) {
        return this->then_part->interp();
    } else return this->else_part->interp();
}

Expr *IfExpr::subst(std::string variable, Expr *expr) {
    return new IfExpr(this->test_part->subst(variable, expr), this->then_part->subst(variable, expr),
                      this->else_part->subst(variable, expr));
}


void IfExpr::print(std::ostream &stream) {

    stream << "(_if ";
    test_part->print(stream);
    stream << " _then ";
    then_part->print(stream);

    stream << " _else ";
    else_part->print(stream);
    stream<<")";
}

void IfExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    this->print(stream);
}

/*********************
 *      Equals
 *********************/

EqExpr::EqExpr(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(Expr *e) {
    EqExpr *n = dynamic_cast<EqExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs));
    }
}

Val* EqExpr::interp() {
    if (lhs->interp()->equals(rhs->interp())) {
        return new boolVal(true);
    }
    else {
        return new boolVal(false);
    }
}


Expr* EqExpr::subst(std::string variable, Expr* expr) {
    return new EqExpr(lhs->subst(variable, expr), rhs->subst(variable, expr));
}

void EqExpr::print(std::ostream& stream) {
    stream<<"(";
    lhs->print(stream);
    stream<<"==";
    rhs->print(stream);
    stream<<")";
}

void EqExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    stream<<"(";
    lhs->print(stream);
    stream<<" == ";
    rhs->print(stream);
    stream<<")";
}

/**
 * ********************  FunExpr  ********************
 * @param formalArg
 * @param body
 * ********************  FunExpr  ********************/
FunExpr::FunExpr(std::string formalArg, Expr* body) {
    this->formalArg = std::move(formalArg);
    this->body = body;
}

Val* FunExpr::interp() {
    return new FunVal(this->formalArg, this->body);
}

bool FunExpr::equals(Expr *e) {
    FunExpr *n = dynamic_cast<FunExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->formalArg == n->formalArg && this->body->equals(n->body));
    }
}

Expr* FunExpr::subst(std::string variable, Expr* expr) {
    if (formalArg == variable) {
        return this;
    }
    return new FunExpr(this->formalArg, this->body->subst(variable, expr));
}

void FunExpr::print(std::ostream& stream) {
    stream<<"_fun (" + formalArg + ") " + body->to_string();
}

void FunExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
//    stream<<"(";
//    lhs->print(stream);
//    stream<<" == ";
//    rhs->print(stream);
//    stream<<")";
}

/**
 * ********************  CallExpr  ********************
 * @param formalArg
 * @param body
 * ********************  CallExpr  ********************/

CallExpr::CallExpr(Expr* toBeCalledFrom, Expr* actualArg) {
    this->toBeCalled = toBeCalledFrom;
    this-> actualArg = actualArg;
}
#include <iostream>
Val* CallExpr::interp() {
    //need to convert funexpr to a funval
    std::cout << "In CallExpr:interp()\n";
    std::cout << "To Be Called: \t'" << toBeCalled->to_string() << "'\n";
    std::cout << "Actual Arg: \t'"<< actualArg->to_string() << "'\n";

    Val* temp = this->toBeCalled->interp();
    std::cout<< "TBC-interp: \t'" << temp->to_string() << "'\n";
    Val* act_arg = actualArg->interp();

    std::cout<< "AA-interp: \t'" << act_arg->to_string() << "'\n";

    Val * ret = temp->call(act_arg);
    std::cout<< "Ret: '" << ret->to_string() << "'\n";

    return ret;


}

bool CallExpr::equals(Expr *e) {
    CallExpr *n = dynamic_cast<CallExpr *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->actualArg->equals(n->actualArg) && this->toBeCalled->equals(n->toBeCalled));
    }
}

Expr* CallExpr::subst(std::string variable, Expr* expr) {
    return new CallExpr(this->toBeCalled->subst(variable, expr), this->actualArg->subst(variable, expr));
}

void CallExpr::print(std::ostream& stream) {
    stream<<this->toBeCalled->to_string();
    stream<<" ("  + actualArg->to_string() + ')';
}

void CallExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    stream<<this->toBeCalled->to_string();
    stream<<" ("  + actualArg->to_string() + ')';
}