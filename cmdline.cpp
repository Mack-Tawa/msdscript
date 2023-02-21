#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"

//
// Created by Mack on 1/13/23.



int use_arguments(int argc, char** argv) {
    bool tested = false;
    for (int i = 1; i < argc; i++) {
        if (tested && (std::string) argv[i] == "--test") {
            std::cerr << "already tested\n";
            exit(1);
        }
        if ((std::string) argv[i] == "--help") {
            std::cout << "Your options are --help or --test\n";
            exit(0);
        }
        if ((std::string) argv[i] == "--test") {
            Catch::Session().run(1, argv);
            tested = true;
        }
        if ((std::string) argv[i] == "--interp") {
            Catch::Session().run(1, argv);
            tested = true;
        }
        if ((std::string) argv[i] == "--print") {
            Catch::Session().run(1, argv);
            tested = true;
        }
        if ((std::string) argv[i] == "--interp") {
            Catch::Session().run(1, argv);
            tested = true;
        }
        if ((std::string) argv[i] == "--pretty-print") {
            Catch::Session().run(1, argv);
            tested = true;
        }
        else {
            std::cerr << "unknown input" << "\n";
            exit(1);
        }
    }
    return 0;
}
