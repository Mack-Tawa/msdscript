//
// Created by Mack on 2/24/23.
//

#include "test_msdscript.h"
#include "exec.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//add way to pick pretty/print/interp

int main(int argc, char **argv) {

    if (argc == 2) {

        const char *const interp1_argv[] = {argv[1], "--pretty-print"};
        for (int i = 0; i < 5000; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying " << in << "\n";
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp1_argv, in);
            std::cout << "*************" << endl;
            std::cout << "First:  " << endl << interp1_result.out;
            std::cout << "Second: " << endl << interp2_result.out;
            std::cout << "*************" << endl;
            cout << endl << endl << endl;
            if (interp1_result.out != interp2_result.out) {

                throw std::runtime_error("different results");
            }
        }
        return 0;
    }


    if (argc == 3) {
        const char *const interp1_argv[] = {argv[1], "--pretty-print"};
        const char *const interp2_argv[] = {argv[2], "--pretty-print"};
        for (int i = 0; i < 5000; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying " << in << "\n";
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp2_argv, in);
            std::cout << "*************" << endl;
            std::cout << "First:  " << endl << interp1_result.out;
            std::cout << "Second: " << endl << interp2_result.out;
            std::cout << "*************" << endl;
            cout << endl << endl << endl;
            if (interp1_result.out != interp2_result.out) {

                throw std::runtime_error("different results");
            }
        }
        return 0;
    }
}

std::string letGen() {

    string result;

    int chance = ((rand() % 10) < 2);
    string c;
    if (chance == 0) {
        c = 'x';
    } else {
        c = 'y';
    }

    if (chance == 1) {
        result += "(";
    }

    result += "_let " + c + "=" + to_string(rand() % 10) + " _in " + c + "+" + to_string(rand() % 10);
    if (chance == 1) {
        result += ")";
    }
    return result;
}


std::string random_expr_string() {
    srand(clock());

    string result;

    int chance = ((rand() % 10) < 2);
    if (chance == 1) {
        result += "(";
    }


    int rInt = rand() % 45;

    if ((rand() % 10) < 4) {
        result += std::to_string(rInt);
        if (chance == 1) {
            result += ")";
        }
        return result;
    } else if ((rand() % 10) < 3) {
        result += random_expr_string() + "+" + random_expr_string();
        if (chance == 1) {
            result += ")";
        }
        return result;
    } else if ((rand() % 10) < 3) {
        result += random_expr_string() + "*" + random_expr_string();
        if (chance == 1) {
            result += ")";
        }
        return result;
    }
    else if ((rand() % 10) < 4) {
        return (letGen());
    }
    else {
        result += to_string(rInt);
        if (chance == 1) {
            result += ")";
        }
        return result;
    }
}