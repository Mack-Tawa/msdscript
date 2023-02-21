//
// Created by Mack on 1/18/23.
//

#include <sstream>
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
std::string Expr::pretty_print_to_string(){
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

//**************Num class methods***************
/**
 * \brief - Constructor for a number
 * \param val - takes in an int
 */
Num::Num(int val) {
    this->val = val;
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool Num::equals(Expr *e) {
    Num *n = dynamic_cast<Num *>(e);
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
int Num::interp() {
    return (this->val);
}

/**
 * \brief - Checks to see if the number has any variables which is always false
 * \return  - False since a num can't have a var
 */
bool Num::has_variable() {
    return false;
}

/**
 * \brief - Returns a number being called
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - the number being called
 */
Expr* Num::subst(std::string variable, Expr* expr) {
    return this;
}

/**
 * \brief - prints the object calling to the stream
 * \param stream - the stream being utilized
 */
void Num::print(std::ostream& stream){
    stream<<std::to_string(val);
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec_none - the precedence is always zero for nums
 */
void Num::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) {
    stream<<this->val;
}

//**************Var class methods***************
/**
 * \brief - the constructor for a Var
 * \param val - the string representing the var
 */
Var::Var(std::string val) {
    this->val = val;
}

/**
 * \brief - Returns true as Var class is a var
 * \return - True
 */
bool Var::has_variable() {
    return true;
}

/**
 * \brief - prints the object calling to the stream
 * \param stream - the stream being utilized
 */
void Var::print(std::ostream& stream) {
    stream<<val;
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec_none - the precedence is always zero for nums
 */
void Var::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) {
    stream<<this->val;
}


/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the Var
 * \param variable - the variable being checked in string format
 * \param expr - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the Var
 */
Expr* Var::subst(std::string variable, Expr* expr) {

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
bool Var::equals(Expr *e) {
    Var *v = dynamic_cast<Var *>(e);
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
int Var::interp() {
    throw std::runtime_error( "no value for variable" );
}

//**************Add class methods***************
/**
 * \brief - constructor for Add class
 * \param lhs - left hand side of the equation
 * \param rhs - right hand side of the equation
 */
Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
int Add::interp() {
    return this->lhs->interp() + this->rhs->interp();
}

/**
 * \brief - Returns if the left hand side or the right hand side expression has a variable
 * @return - Returns if the left hand side or the right hand side expression has a variable
 *
 */
bool Add::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool Add::equals(Expr *e) {
    Add *n = dynamic_cast<Add *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }
}

/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the Var
 * \param variable - the variable being checked in string format
 * \param replacement - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the Var
 */
Expr* Add::subst(std::string variable, Expr* replacement) {
    return new Add(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}

/**
 * \brief - Prints the left side and right side within parentheses
 * \param stream - the stream to be utilized
 */
void Add::print(std::ostream& stream) {
    stream<<("(");
    lhs->print(stream);
    stream<<("+");
    rhs->print(stream);
    stream<<(")");
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec - the precedence is always 1 for Adds
 */
void Add::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) {

    if (prec >= prec_add) {
        stream<<("(");
    }
    lhs->pretty_print_at(stream, prec_add, sPos, true);
    stream<<(" + ");
    rhs->pretty_print_at(stream, prec_none, sPos, false);

    if (prec >= prec_add) {
        stream<<(")");
    }
}

//**************Mult class methods***************
/**
 * \brief - the constructor for Mult class
 * \param lhs - the lhs expression of the equation
 * \param rhs - the rhs expression of the equation
 */
Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief - Gives the value of the number at the bottom of the expression
 * \return - Returns the value of the number adding to the other bottom of the expression
 */
int Mult::interp() {
    return this->lhs->interp() * this->rhs->interp();
}

/**
 * \brief - Tells if the expression calling has a variable on the left or right hand side
 * \return - Returns true if either expression has a Var
 */
bool Mult::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

/**
 * \brief - returns if an expression is equal to another
 * \param e - the expression on the right
 * \return  - if expression is equal to another
 */
bool Mult::equals(Expr *e) {
    Mult *n = dynamic_cast<Mult *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(n->lhs)
                && this->rhs->equals(n->rhs));
    }

}

/**
 * \brief - Returns an expression if the value is the variable, otherwise it returns the Var
 * \param variable - the variable being checked in string format
 * \param replacement - the expression being checked
 * \return - Returns an expression if the value is the variable, otherwise it returns the Var
 */
Expr* Mult::subst(std::string variable, Expr* replacement) {
    return new Mult(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
}

/**
 * \brief - Prints the right hand side and left hand side with a '*' in between. The whole thing is surrounded by parentheses
 * \param stream - The stream being utilized
 */
void Mult::print(std::ostream& stream) {
    stream<<("(");
    lhs->print(stream);
    stream<<("*");
    rhs->print(stream);
    stream<<(")");
}

/**
 * \brief - utilizes the precedence from the parent to print correct parentheses
 * \param stream - the stream being utilized
 * \param prec - the precedence is always 2 for Mults
 */
void Mult::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) {

    if (prec == prec_mult) {
        stream << ("(");
    }

    lhs->pretty_print_at(stream, prec_mult, sPos, false);
    stream << (" * ");
    rhs->pretty_print_at(stream, prec_add, sPos, true);

    if (prec == prec_mult) {
        stream << (")");
    }
}

Let::Let(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}

bool Let::has_variable() {
    return (this->rhs->has_variable() || this->body->has_variable());
}

bool Let::equals(Expr *e) {
    Let *n = dynamic_cast<Let *>(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->lhs == (n->lhs)
                && this->rhs->equals(n->rhs)
                && this->body->equals(n->body));
    }
}

void Let::print(std::ostream& stream) {
    stream<<"(";
    stream<<"_let ";
    stream<<lhs << "=" << rhs->to_string();
    stream<<" _in ";
    stream<<body->to_string();
    stream<<")";
}

void Let::pretty_print_at(std::ostream &stream, precedence_t prec, std::streampos& sPos, bool needPar) {
    if (needPar) {
        stream << "(";
    }
    int temp = stream.tellp();
    int indent = temp - sPos;

    stream << "_let ";
    stream << lhs << " = ";
    rhs->pretty_print_at(stream, prec_none, sPos, false);
    stream<<"\n";
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

Expr* Let::subst(std::string variable, Expr* expr){
    if (lhs == variable) {
        return new Let(lhs, rhs->subst(variable, expr), body);
    }
    return new Let(lhs, (rhs->subst(variable, expr)), body->subst(variable, expr));
}

int Let::interp(){

    return body->subst(lhs, rhs)->interp();

}






//