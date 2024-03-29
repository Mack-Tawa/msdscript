#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "Parse.h"
#include "val.h"
#include "Env.h"




int main(int argc, const char *argv[]) {
    PTR(Env) empty = NEW(emptyEnv)();


    try {
        run_mode_t temp = use_arguments(argc, const_cast<char **>(argv));


        if (temp == do_nothing) {

        }
        else if (temp == do_interp) {
            PTR(Expr)e = parse_expr(std::cin);
            cout<<endl;
            e->print(std::cout);
            PTR(Val) result = e->interp(empty);
            std::string resultString = result->to_string();

            std::cout<<endl<<"main reuslt is: "<<resultString<<endl;
            exit(0);
        }
        else if (temp == do_print) {
            PTR(Expr)e = parse_expr(std::cin);
            e->print(std::cout);
            std::cout<<endl;
            exit(0);
        }
        else if( temp == do_pretty_print) {
            PTR(Expr)e = parse_expr(std::cin);
            std::string pp = e->pretty_print_to_string();
            std::cout<<pp<<endl;
            exit(0);
        }
        else{
            cerr<<"No available command called";
        }

    }
    catch (std::runtime_error exn) {
        std::cerr << exn.what() << "\n";
        return 1;
    }
    return 0;
}


