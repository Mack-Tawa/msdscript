//
// Created by Mack on 2/21/23.
//

#include "Parse.h"
#include <sstream>
#include <iostream>

Expr *parse(std::istream &in) {
    return parse_expr(in);
}

Expr *parse_str(std::string s) {
    std::stringstream in(s);
    Expr *e = parse_expr(in);
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

Expr *parse_expr(std::istream &in) {
    Expr *e;
    e = parse_comparg(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '=') {
        consume(in, '=');
        consume(in, '=');
        Expr *rhs = parse_expr(in);
        return new EqExpr(e, rhs);
    } else {
        return e;
    }
}

//new com
Expr *parse_comparg(std::istream &in) {
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_addend(in);
        return new AddExpr(e, rhs);
    } else {
        return e;
    }
}

Expr *parse_addend(std::istream &in) {

    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new MultExpr(e, rhs);
    } else
        return e;
}

Expr *parseVar(std::istream &in) {
    stringstream ss;
    while (1) {
        int c = in.peek();
        if (c == '_') {
            consume(in, c);
            throw ("invalid input");
        }
        if (isalpha(c)) {
            ss.put(c);
            consume(in, c);
        } else
            break;
    }
    return new VarExpr(ss.str());
}

Expr *parseLet(std::istream &in) {
    LetExpr *building = new LetExpr("test", 0, 0);

    skip_whitespace(in);
    int c = in.peek();

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

Expr *parseIf(std::istream &in) {
    skip_whitespace(in);

    Expr *statement = parse_expr(in);
    skip_whitespace(in);

    consume(in, '_');
    if (parse_keyword(in) != "then") {
        throw std::runtime_error("invalid argument for 'then' statement");
    }
    skip_whitespace(in);

    Expr *then = parse_expr(in);
    skip_whitespace(in);

    consume(in, '_');
    if (parse_keyword(in) != "else") {
        throw std::runtime_error("invalid argument for 'else' statement");
    }
    Expr *els = parse_expr(in);
    return new IfExpr(statement, then, els);
}

Expr *parse_multicand(std::istream &in) {
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
            return new BoolExpr(true);
        } else if (result == "false") {
            return new BoolExpr(false);
        } else {
            throw runtime_error("did not get a proper command");
        }
    } else if (c == '(') {
        consume(in,'(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')')
            throw std::runtime_error("missing close parenthesis");
        return e;
    } else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}

Expr *parse_num(std::istream &in) {
    long n = 0;
    bool negative = false;
    int d = in.peek();
    if (d == '-') {
        negative = true;
        consume(in, '-');
        if (!isdigit(in.peek()) || in.peek() == EOF) {
            throw std::runtime_error("invalid input");
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

    if (n > INT_MAX || n < INT_MIN) {
        throw std::runtime_error("Integer overflow error");
    }

    return new NumExpr(n);
}

void skip_whitespace(std::istream &in) {
    if (in.peek() == 10) {
        return;
    }
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

