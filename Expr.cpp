//
// Created by Mack on 1/18/23.
//

#include <sstream>
#include "val.h"
#include "Expr.h"
#include "pointer.h"
#include "Env.h"

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
bool NumExpr::equals(PTR(Expr) e) {
    PTR(NumExpr) n = CAST(NumExpr)  (e);
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
PTR(Val)NumExpr::interp(PTR(Env) env) {
    PTR(numVal) v = NEW(numVal)(this->val);
    return v;
}

/**
 * \brief - Returns a number being called
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - the number being called
 */
PTR(Expr)NumExpr::subst(std::string variable, PTR(Expr)expr) {
    return THIS;
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
PTR(Expr)VarExpr::subst(std::string variable, PTR(Expr)expr) {

    if (val == variable) {
        return expr;
    }
    return THIS;
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool VarExpr::equals(PTR(Expr)e) {
    PTR(VarExpr)v = CAST(VarExpr) (e);
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
PTR(Val)VarExpr::interp(PTR(Env) env) {
    return (env->lookup(this->val));
}

//**************AddExpr class methods***************
/**
 * \brief - constructor for AddExpr class
 * \param lhs - left hand side of the equation
 * \param rhs - right hand side of the equation
 */
AddExpr::AddExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
PTR(Val)AddExpr::interp(PTR(Env) env) {

    return lhs->interp(env)->add_to(rhs->interp(env));}


/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool AddExpr::equals(PTR(Expr)e) {
    PTR(AddExpr)n = CAST(AddExpr)(e);
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
PTR(Expr)AddExpr::subst(std::string variable, PTR(Expr)replacement) {
    return NEW(AddExpr)(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
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
MultExpr::MultExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
PTR(Val)MultExpr::interp(PTR(Env) env) {
    return this->lhs->interp(env)->mult_to(this->rhs->interp(env));
}


/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool MultExpr::equals(PTR(Expr)e) {
    PTR(MultExpr)n = CAST(MultExpr) (e);
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
PTR(Expr)MultExpr::subst(std::string variable, PTR(Expr)replacement) {
    return NEW(MultExpr)(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
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

LetExpr::LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}


bool LetExpr::equals(PTR(Expr)e) {
    PTR(LetExpr)n = CAST(LetExpr) (e);
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

PTR(Expr)LetExpr::subst(std::string variable, PTR(Expr)expr) {
    if (lhs == variable) {
        return NEW(LetExpr) (lhs, rhs->subst(variable, expr), body);
    }
    return NEW(LetExpr)(lhs, (rhs->subst(variable, expr)), body->subst(variable, expr));
}

PTR(Val)LetExpr::interp(PTR(Env) env) {
    PTR(Val) rhs_val = rhs->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(lhs, rhs_val, env);
    return body->interp(new_env);
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

bool BoolExpr::equals(PTR(Expr)e) {
    PTR(BoolExpr)n = CAST(BoolExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->b == n->b);
    }
}

PTR(Val)BoolExpr::interp(PTR(Env) env){
    return NEW(boolVal)(b);
}

/**
 * \brief - Returns a number being called
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - the number being called
 */
 PTR(Expr) BoolExpr::subst(std::string variable, PTR(Expr)expr) {
    return THIS;
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

IfExpr::IfExpr(PTR(Expr)test, PTR(Expr)then, PTR(Expr)els) {
    test_part = test;
    then_part = then;
    else_part = els;
}

bool IfExpr::equals(PTR(Expr)e) {
    PTR(IfExpr)n = CAST(IfExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->test_part->equals(n->test_part)
                && this->then_part->equals(n->then_part) && this->else_part->equals(n->else_part));
    }
}

PTR(Val)IfExpr::interp(PTR(Env) env) {
    if (this->test_part->interp(env)->is_true()) {
        return this->then_part->interp(env);
    } else return this->else_part->interp(env);
}

PTR(Expr)IfExpr::subst(std::string variable, PTR(Expr)expr) {
    return NEW(IfExpr)(this->test_part->subst(variable, expr), this->then_part->subst(variable, expr),
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

EqExpr::EqExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(PTR(Expr)e) {
    PTR(EqExpr)n = CAST(EqExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs));
    }
}

PTR(Val) EqExpr::interp(PTR(Env) env) {
    if (lhs->interp(env)->equals(rhs->interp(env))) {
        return NEW(boolVal)(true);
    }
    else {
        return NEW(boolVal)(false);
    }
}


PTR(Expr) EqExpr::subst(std::string variable, PTR(Expr) expr) {
    return NEW(EqExpr)(lhs->subst(variable, expr), rhs->subst(variable, expr));
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
FunExpr::FunExpr(std::string formalArg, PTR(Expr) body) {
    this->formalArg = std::move(formalArg);
    this->body = body;
}

PTR(Val) FunExpr::interp(PTR(Env) env) {
    return NEW(FunVal)(this->formalArg, this->body, env);
}

bool FunExpr::equals(PTR(Expr)e) {
    PTR(FunExpr)n = CAST(FunExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->formalArg == n->formalArg && this->body->equals(n->body));
    }
}

PTR(Expr) FunExpr::subst(std::string variable, PTR(Expr) expr) {

    if (formalArg == variable) {
        return THIS;
    }
    return NEW(FunExpr)(this->formalArg, this->body->subst(variable, expr));
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

CallExpr::CallExpr(PTR(Expr) toBeCalledFrom, PTR(Expr) actualArg) {
    this->toBeCalled = toBeCalledFrom;
    this-> actualArg = actualArg;
}
PTR(Val) CallExpr::interp(PTR(Env) env) {
    //need to convert funexpr to a funval


    PTR(Val) temp = this->toBeCalled->interp(env);
//    std::cout<< "TBC-interp: \t'" << temp->to_string() << "'\n";
    PTR(Val) act_arg = actualArg->interp(env);
    PTR(Val) ret = temp->call(act_arg);
    return ret;


}

bool CallExpr::equals(PTR(Expr)e) {
    PTR(CallExpr)n = CAST(CallExpr) (e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->actualArg->equals(n->actualArg) && this->toBeCalled->equals(n->toBeCalled));
    }
}

PTR(Expr) CallExpr::subst(std::string variable, PTR(Expr) expr) {
    return NEW(CallExpr)(this->toBeCalled->subst(variable, expr), this->actualArg->subst(variable, expr));
}

void CallExpr::print(std::ostream& stream) {
    stream<<this->toBeCalled->to_string();
    stream<<" ("  + actualArg->to_string() + ')';
}

void CallExpr::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos &sPos, bool needPar) {
    stream<<this->toBeCalled->to_string();
    stream<<" ("  + actualArg->to_string() + ')';
}