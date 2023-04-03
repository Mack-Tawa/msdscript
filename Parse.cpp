//
// Created by Mack on 2/21/23.
//

#include <sstream>
#include <iostream>
#include "Parse.h"

PTR(Expr)parse(std::istream &in) {
    skip_whitespace(in);
    if (!in.eof()) {
        throw std::runtime_error("Invalid input in parse");
    }
    char c = in.peek();
    if (c == 10)
        consume(in, c);
    return parse_expr(in);
}

PTR(Expr)parse_str(std::string s) {
    std::stringstream in(s);
    PTR(Expr)e = parse_expr(in);
    if (!in.eof()) {
        throw std::runtime_error("Invalid input in parse");
    }
    return e;
}

std::string parse_keyword(std::istream &in) {
    std::string result = "";
    while (true) {
        char c = in.peek();
        if (isalpha(c)) {
            result += c;
            consume(in, c);
        } else {
            break;
        }
    }
    return result;

}



PTR(Expr)parse_expr(std::istream &in) {
    PTR(Expr)e;
    e = parse_comparg(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '=') {
        consume(in, '=');
        consume(in, '=');
        PTR(Expr)rhs = parse_expr(in);
        return NEW (EqExpr)(e, rhs);
    } else {
        return e;
    }
}

//new com
PTR(Expr)parse_comparg(std::istream &in) {
    PTR(Expr)e;
    e = parse_addend(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        PTR(Expr)rhs = parse_addend(in);
        return NEW (AddExpr) (e, rhs);
    } else {
        return e;
    }
}

PTR(Expr)parse_addend(std::istream &in) {

    PTR(Expr)e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        PTR(Expr)rhs = parse_addend(in);
        return NEW(MultExpr) (e, rhs);
    } else
        return e;
}

PTR(Expr)parseVar(std::istream &in) {
    stringstream ss;
    while (true) {
        int c = in.peek();
        if (isalpha(c)) {
            ss.put(c);
            consume(in, c);
        }
        else if (c == '_') {
            throw ("parsevar invalid input");
        }
        else
            break;
    }
    return NEW(VarExpr)(ss.str());
}

PTR(Expr)parseLet(std::istream &in) {
    PTR(LetExpr) building = NEW(LetExpr) ("test", NEW(NumExpr) (0), NEW(NumExpr) (0));

    skip_whitespace(in);

    std::string variableName = "";
    while (1) {
        int c = in.peek();
        if (isalpha(c)) {
            variableName += c;
            consume(in, c);
        } else
            break;
    }
    building->lhs = variableName;
    skip_whitespace(in);
    consume(in, '=');
    skip_whitespace(in);
    building->rhs = parse_expr(in);
    skip_whitespace(in);
    consume(in, '_');
    consume(in, 'i');
    consume(in, 'n');
    skip_whitespace(in);

    building->body = parse_expr(in);
    return building;
}

PTR(Expr)parseIf(std::istream &in) {
    skip_whitespace(in);

    PTR(Expr)statement = parse_expr(in);
    skip_whitespace(in);

    consume(in, '_');
    if (parse_keyword(in) != "then") {
        throw std::runtime_error("invalid argument for 'then' statement");
    }
    skip_whitespace(in);

    PTR(Expr)then = parse_expr(in);
    skip_whitespace(in);

    consume(in, '_');
    if (parse_keyword(in) != "else") {
        throw std::runtime_error("invalid argument for 'else' statement");
    }
    PTR(Expr)els = parse_expr(in);
    return NEW(IfExpr)(statement, then, els);
}


PTR(Expr)parse_num(std::istream &in) {
    long n = 0;
    bool negative = false;
    int d = in.peek();
    if (d == '-') {
        negative = true;
        consume(in, '-');
        if (!isdigit(in.peek()) || in.peek() == EOF) {
            throw std::runtime_error("parse num invalid input");
        }
    }

    while (1) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            n = n * 10 + (c - '0');
        } else
            break;
    }

    if (negative)
        n = -n;

    if ((signed int)n > INT_MAX || (long)n < INT_MIN) {
        throw std::runtime_error("Integer overflow error");
    }

    return NEW(NumExpr)((int)n);
}

void skip_whitespace(std::istream &in) {
    while (true) {
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}

void consume(std::istream &in, int expect) {
    int c = in.get();

    if (c != expect)
        throw std::runtime_error("consume mismatch");
}

PTR(Expr) parse_fun(std::istream &in) {

    skip_whitespace(in);

    std::string variableName = "";
    consume(in, '(');
    while (1) {
        int c = in.peek();
        if (isalpha(c)) {
            consume(in, c);
            variableName += c;
        } else
            break;
    }
    skip_whitespace(in);
    consume(in, ')');
    skip_whitespace(in);

    PTR(Expr) body = parse_expr(in);
    skip_whitespace(in);

    return NEW (FunExpr)(variableName, body);
}


PTR(Expr) parse_inner(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();

    if ((c == '-') || isdigit(c))
        return parse_num(in);
    else if (isalpha(c)) {
        return parseVar(in);
    } else if (c == '_') {
        consume(in, '_');
        std::string result = parse_keyword(in);
        if (result == "let") {
            return parseLet(in);
        } else if (result == "if") {
            return parseIf(in);
        } else if (result == "true") {
            return NEW(BoolExpr)(true);
        } else if (result == "false") {
            return NEW(BoolExpr)(false);
        }
        else if (result == "fun") {
            return parse_fun(in);
        }
        else {
            throw runtime_error("did not get a proper command");
        }
    } else if (c == '(') {
        consume(in,'(');
        PTR(Expr)e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')')
            throw std::runtime_error("missing close parenthesis");
        return e;
    } else {
        consume(in, c);
        throw std::runtime_error("parse_inner invalid input");
    }
}

PTR(Expr) parse_multicand(std::istream &in) {

    PTR(Expr) expr = parse_inner(in);
    while (in.peek() == '(') {
        consume(in, '(');
        PTR(Expr) actual_arg = parse_expr(in);
        consume(in, ')');
        expr = NEW(CallExpr)(expr,
                            actual_arg);
    }
    return expr;
}

