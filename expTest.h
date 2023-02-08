//
// Created by Mack on 1/19/23.
//

#ifndef MSDSCRIPT_EXPTEST_H
#define MSDSCRIPT_EXPTEST_H

#include <sstream>
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

TEST_CASE("CHECKING PRINT") {
    CHECK( (new Num(10))->to_string() == "10" );
}

TEST_CASE("CHECKING PRETTY PRINT") {
//    new Mult (new Mult (new Num(2), new Num(3)), new Num(4))->equals()
//    CHECK(((new Mult( new Num(1), new Add(new Num(2), new Num(3)))->pretty_print_to_string()) == "1 * (2 + 3)");
    //->to_string()->equals("1 * (2+3")));
    CHECK( (new Mult (new Mult (new Num(2), new Num(3)), new Num(4)))->pretty_print_to_string() == "(2 * 3) * 4");
    CHECK((new Num(1))->pretty_print_to_string() == "1");
    CHECK((new Var("a"))->pretty_print_to_string() == "a");
    CHECK((new Add( new Num(1), new Num(3)))->pretty_print_to_string() == "1 + 3");
    CHECK((new Mult (new Num(2), new Mult (new Num(3), new Num(4))))->pretty_print_to_string() == "2 * 3 * 4");


}

TEST_CASE("Branden's tests") {
    Mult* complexMultExprWithVar = new Mult(new Add(new Var("x"), new Mult(new Num(2), new Num(3))), new Num(3));
    Mult* complexMultExprWithNoVar = new Mult(new Add(new Num(2), new Mult(new Num(2), new Num(3))), new Num(3));

CHECK(complexMultExprWithNoVar->pretty_print_to_string() == "(2 + 2 * 3) * 3");
CHECK(complexMultExprWithVar->pretty_print_to_string() == "(x + 2 * 3) * 3");
CHECK((new Mult (new Mult (new Num(2), new Num(3)), new Num(4)))->pretty_print_to_string() == "(2 * 3) * 4");
CHECK((new Mult (new Num(2), new Mult (new Num(3), new Num(4))))->pretty_print_to_string() == "2 * 3 * 4");
CHECK((new Mult (new Mult(new Num(1), new Num(2) ), new Mult (new Num(3), new Num(4))))->pretty_print_to_string() == "(1 * 2) * 3 * 4");
CHECK((new Mult (new Num(2), new Mult (new Num(3), new Num(4))))->pretty_print_to_string() == "2 * 3 * 4");
CHECK((new Mult(new Num(1), new Add(new Num(2), new Num(3))))->pretty_print_to_string() == "1 * (2 + 3)");
    CHECK( (new Mult (new Num(1), new Add(new Num(2),new Num(3))))->pretty_print_to_string() == "1 * (2 + 3)");
}

//Jons tests
    TEST_CASE("Pretty Print -- Add"){
        Num* testNum1 = new Num(1);
        Num* testNum2 = new Num(2);
        Num* testNum3 = new Num(3);
        Num* testNum4 = new Num(4);

        Var* testVar1 = new Var("a");
        Var* testVar2 = new Var("b");

        Add* testAdd1 = new Add(testNum1, testNum2);
        Add* testAdd2 = new Add(testNum3, testAdd1);
        Add* testAdd3 = new Add(testAdd1, testNum3);
        Add* testAdd4 = new Add(testNum3, testNum4);
        Add* testAdd5 = new Add(testAdd1, testAdd4);

        Add* testAdd6 = new Add(testNum1, testVar1);

        Mult* testMult1 = new Mult(testNum3, testNum4);

        Add* testMixed1 = new Add(testNum1, testMult1);

        std::stringstream out("");
        testAdd2->pretty_print(out);
        CHECK(out.str() == "3 + 1 + 2");

        out.str("");
        testAdd3->pretty_print(out);
        CHECK(out.str() == "(1 + 2) + 3");

        out.str("");
        testMixed1->pretty_print(out);
        CHECK(out.str() == "1 + 3 * 4");

        out.str("");
        testAdd5->pretty_print(out);
        CHECK(out.str() == "(1 + 2) + 3 + 4");

        out.str("");
        testAdd6->pretty_print(out);
        CHECK(out.str() == "1 + a");
    }

    TEST_CASE("Pretty Print -- Mult"){
        Num* testNum1 = new Num(1);
        Num* testNum2 = new Num(2);
        Num* testNum3 = new Num(3);
        Num* testNum4 = new Num(4);

        Add* testAdd1 = new Add(testNum1, testNum2);
        Add* testAdd2 = new Add(testNum3, testNum4);

        Mult* testMult1 = new Mult(testNum1, testNum2);
        Mult* testMult2 = new Mult(testNum3, testMult1);
        Mult* testMult3 = new Mult(testMult1, testNum3);
        Mult* testMult4 = new Mult(testNum3, testNum4);
        Mult* testMult5 = new Mult(testMult1, testMult4);

        std::stringstream out("");
        testMult2->pretty_print(out);
        CHECK(out.str() == "3 * 1 * 2");

        out.str("");
        testMult3->pretty_print(out);
        CHECK(out.str() == "(1 * 2) * 3");

        out.str("");
        testMult5->pretty_print(out);
        CHECK(out.str() == "(1 * 2) * 3 * 4");

        Mult* testMixed1 = new Mult(testNum3, testAdd1);
        Mult* testMixed2 = new Mult(testAdd1, testNum3);
        Mult* testMixed3 = new Mult(testAdd1, testAdd2);

        out.str("");
        testMixed1->pretty_print(out);
        CHECK(out.str() == "3 * (1 + 2)");

        out.str("");
        testMixed2->pretty_print(out);
        CHECK(out.str() == "(1 + 2) * 3");

        out.str("");
        testMixed3->pretty_print(out);
        CHECK(out.str() == "(1 + 2) * (3 + 4)");
    }
TEST_CASE("mult_mults_mults_mults from william ")
{
CHECK((new Mult( new Mult(new Num(10), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10))))
              ->pretty_print_to_string()  == "(10 * (10 * 10) * 10) * 10 * 10");
}


#endif MSDSCRIPT_EXPTEST_H