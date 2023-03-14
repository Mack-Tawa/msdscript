//
// Created by Mack on 2/21/23.
//

#ifndef CLION_BULL_PARSE_H
#define CLION_BULL_PARSE_H
#include "Expr.h"
#include "cmdline.h"

#include <iosfwd>
#include <iostream>



Expr *parse_expr(std::istream &in);

Expr* parse_addend(std::istream &in);

Expr *parse_multicand(std::istream &in);

Expr *parse_num(std::istream &in);

void skip_whitespace(std::istream &in);

Expr *parseVar(std::istream &in);

void consume(std::istream &in, int expect);

Expr *parseLet(std::istream &in);

Expr *parse_str(std::string s);

Expr *parse (std::istream& in);

Expr *parse_comparg(std::istream &in);


#endif //CLION_BULL_PARSE_H
