#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "Parse.h"




int main(int argc, const char * argv[]) {


    run_mode_t temp = use_arguments(argc, const_cast<char **>(argv));


    if (temp == do_nothing) {

    }
    else if (temp == do_interp) {
        std::cout<<"Interpreting"<<endl;
        Expr *e = parse_expr(std::cin);
        int result = e->interp();
        std::cout<<"the result is: " << result << endl;
        exit(0);
    }
    else if (temp == do_print) {
        std::cout<<"Printing"<<endl;
        Expr *e = parse_expr(std::cin);
        e->print(std::cout);
        std::cout<<endl;
        exit(0);
    }
    else if( temp == do_pretty_print) {
        std::cout<<"Pretty printing"<<endl;
        Expr *e = parse_expr(std::cin);
        e->pretty_print(std::cout);
        std::cout<<endl;
        exit(0);
    }
    else{
        cerr<<"No available command called";
    }




    while (1) {
        Expr *e = parse_expr(std::cin);
        std::cout<<"The answer is: ";
        std::cout<<to_string(e->interp());
        std::cout << "\n";
        e->pretty_print(std::cout);
        std::cout << "\n";
        skip_whitespace(std::cin);
        std::cout<<EOF;
        if (std::cin.eof())
            break;
    }







    return 0;
}


