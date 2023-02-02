//
// Created by Mack on 1/19/23.
//

#ifndef MSDSCRIPT_EXPTEST_H
#define MSDSCRIPT_EXPTEST_H
#include "catch.h"
#include "Expr.h"

/**
 * making tests: maybe have vars at top like setup in JUnit.
 * caps class names
 * make prettier
 * 
 */


TEST_CASE("interp")
{
    CHECK( (new Mult(new Num(3), new Num(2)))
                   ->interp()==6 );
    CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))
                   ->interp()==65);
}

TEST_CASE( "equals" ) {
    CHECK((new Num(1))->equals(new Num(1)) == true );
    CHECK((new Var("x"))->equals(new Var("y")) == false );
    CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new  Num(2), new Num(3))) == true );
}

//    TEST_CASE( "not equals" ) {
//    CHECK((new Mult(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == false);
//    CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(3), new Num(2))) == false);
//
//}

TEST_CASE( "different types same Num vals" ) {
    CHECK((new Add(new Num(2), new Num(24)))->equals(new Mult(new Num(2), new Num(24))) == false);
    CHECK((new Add(new Num(-143), new Num(25)))->equals(new Mult(new Num(-143), new Num(25))) == false);
    CHECK_FALSE((new Num(1))->equals(new Num(5)));
//    CHECK_FALSE((new Num(1))->equals(new Num(5)));
    CHECK((new Mult(new Mult(new Num(4), new Num(6)), new Num(5)), new Num(55))->equals
          ((new Mult(new Mult(new Num(4), new Num(6)), new Num(5)), new Num(55))) == true);
}

TEST_CASE("checking sub for add") {
    CHECK( (new Add(new Var("x"), new Num(24)))
                   ->subst("x", new Var("y"))
                   ->equals(new Add(new Var("y"), new Num(24))) );

    CHECK( (new Add(new Var("x"), new Num(7)))
                   ->subst("x", new Var("y"))
                   ->equals(new Add(new Var("y"), new Num(7))) );

    CHECK( (new Var("x"))
                   ->subst("x", new Add(new Var("y"),new Num(7)))
                   ->equals(new Add(new Var("y"),new Num(7))));


}

TEST_CASE("Checking mult expression substitution") {
    CHECK( (new Mult(new Var("x"), new Num(24)))
                   ->subst("x", new Var("y"))
                   ->equals(new Mult(new Var("y"), new Num(24))) );

    CHECK_FALSE( (new Mult(new Var("x"), new Num(24)))
                   ->subst("z", new Var("y"))
                   ->equals(new Mult(new Var("y"), new Num(24))) );
}

TEST_CASE("Checking substituting something that isn't in there") {
    CHECK( (new Add(new Var("x"), new Num(24)))
                   ->subst("z", new Var("y"))
                   ->equals(new Add(new Var("x"), new Num(24))) );

    CHECK( (new Mult(new Var("x"), new Num(24)))
                   ->subst("z", new Var("y"))
                   ->equals(new Mult(new Var("x"), new Num(24))) );

    
}

#endif //MSDSCRIPT_EXPTEST_H
