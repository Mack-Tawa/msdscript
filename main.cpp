#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "Parse.h"




int main(int argc, const char * argv[]) {

    while (1) {
        Expr *e = parse_expr(std::cin);
        std::cout<<"The answer is: ";
        std::cout<<to_string(e->interp());
        std::cout << "\n";
        e->pretty_print(std::cout);
        std::cout << "\n";
        skip_whitespace(std::cin);
        if (std::cin.eof())
            break;
    }

    use_arguments(argc, const_cast<char **>(argv));





    return 0;
}


