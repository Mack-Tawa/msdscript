//
// Created by Mack on 1/13/23.
//

#ifndef HW1_CMDLINE_H
#define HW1_CMDLINE_H
using namespace std;

typedef enum {

    do_nothing,
    do_interp,
    do_print,
    do_pretty_print

} run_mode_t;



run_mode_t use_arguments(int argc, char** argv);

#endif //HW1_CMDLINE_H
