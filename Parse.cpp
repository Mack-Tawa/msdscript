//
// Created by Mack on 2/21/23.
//

#include "Parse.h"
#include <sstream>
#include <iostream>

Expr *parse (std::istream& in) {
    return parse_expr(in);
}

Expr *parse_str(std::string s) {
    std::stringstream in(s);

    Expr *e = parse_expr(in);
    return e;

}



Expr *parse_expr(std::istream &in) {
    Expr *e;
        e = parse_addend(in);
        skip_whitespace(in);
        int c = in.peek();
        if (c == '+') {
            consume(in, '+');
            Expr *rhs = parse_expr(in);
            return new Add(e, rhs);
        } else {
            return e;
        }
    }

Expr* parse_addend(std::istream &in) {

    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new Mult(e, rhs);
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
            ss.put( c);
            consume(in, c);
        } else
            break;
    }
    return new Var(ss.str());
}

Expr *parseLet(std::istream &in) {

    Let *building = new Let("test", 0, 0);

    int c = in.peek();
    if (c == '_') {
        consume(in, '_');
        consume(in, 'l');
        consume(in, 'e');
        consume(in, 't');
        skip_whitespace(in);
    }
    stringstream ss;
    while (1) {
        int c = in.peek();
        if (isalpha(c)) {
            ss.put( c);
            consume(in, c);
        } else
            break;
    }

    building->lhs = ss.str();
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

Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c))
        return parse_num(in);
    else if (isalpha(c)) {
        return parseVar(in);
    }
    if (c == '_'){
        return parseLet(in);
    }
    else if (c == '(') {
        consume(in, '(');
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
    int n = 0;
    bool negative = false;
    int d = in.peek();
    if (d == '-') {
        negative = true;
        consume(in, '-');
        if (!isdigit(in.peek())){
            throw std::runtime_error("invalid input");
        }
    }

    while (1) {
        int c = in.peek();

        if (isdigit(c)) {
            consume(in, c);
            n = n*10 + (c - '0');
        } else
            break;
    }
    if (negative)
        n = -n;
    return new Num(n);
}

void skip_whitespace(std::istream &in) {
    while (1) {
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