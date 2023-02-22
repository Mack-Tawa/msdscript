#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "cmdline.h"

//
// Created by Mack on 1/13/23.



run_mode_t use_arguments(int argc, char** argv) {
    bool tested = false;
    for (int i = 1; i < 2; i++) {

        if ((std::string) argv[i] == "--test") {
            if (Catch::Session().run(1, argv) == 0) {
                exit(0);
            }
            else(exit(1));
        }

        else if ((std::string) argv[i] == "--interp") {
            return do_interp;
        }
        else if ((std::string) argv[i] == "--print") {
            return do_print;
        }
        else if ((std::string) argv[i] == "--prettyPrint") {
            return do_pretty_print;
        }

        else{
            cerr<<"No available command requested";
            exit(1);
        }
    }
}
