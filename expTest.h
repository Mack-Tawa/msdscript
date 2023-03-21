//
// Created by Mack on 1/19/23.
//

#ifndef MSDSCRIPT_EXPTEST_H
#define MSDSCRIPT_EXPTEST_H

#include <sstream>
#include "val.h"
#include "catch.h"
#include "Expr.h"
#include "Parse.h"
#include <fstream>
#include <iostream>

/**
 * making tests: maybe have vars at top like setup in JUnit.
 * caps class names
 * make prettier
 * 
 */


TEST_CASE("interp")
{
    CHECK( (new MultExpr(new NumExpr(3), new NumExpr(2)))
                   ->interp()->equals(new numVal(6)) );
    CHECK((new NumExpr(6))->interp()->equals(new numVal(6)));
//    CHECK( (new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),new AddExpr(new NumExpr(20),new NumExpr(20))))
//                   ->interp()==65);
}

TEST_CASE( "equals" ) {
    CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true );
    CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false );
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new  NumExpr(2), new NumExpr(3))) == true );
}



TEST_CASE( "different types same NumExpr vals" ) {
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(24)))->equals(new MultExpr(new NumExpr(2), new NumExpr(24))) == false);
    CHECK((new AddExpr(new NumExpr(-143), new NumExpr(25)))->equals(new MultExpr(new NumExpr(-143), new NumExpr(25))) == false);
    CHECK_FALSE((new NumExpr(1))->equals(new NumExpr(5)));
//    CHECK_FALSE((new NumExpr(1))->equals(new NumExpr(5)));
    CHECK((new MultExpr(new MultExpr(new NumExpr(4), new NumExpr(6)), new NumExpr(5)), new NumExpr(55))->equals
          ((new MultExpr(new MultExpr(new NumExpr(4), new NumExpr(6)), new NumExpr(5)), new NumExpr(55))) == true);
}

TEST_CASE("checking sub for add") {
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(24)))
                   ->subst("x", new VarExpr("y"))
                   ->equals(new AddExpr(new VarExpr("y"), new NumExpr(24))) );

    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
                   ->subst("x", new VarExpr("y"))
                   ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );

    CHECK( (new VarExpr("x"))
                   ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
                   ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));


}

TEST_CASE("Checking mult expression substitution") {
    CHECK( (new MultExpr(new VarExpr("x"), new NumExpr(24)))
                   ->subst("x", new VarExpr("y"))
                   ->equals(new MultExpr(new VarExpr("y"), new NumExpr(24))) );

    CHECK_FALSE( (new MultExpr(new VarExpr("x"), new NumExpr(24)))
                   ->subst("z", new VarExpr("y"))
                   ->equals(new MultExpr(new VarExpr("y"), new NumExpr(24))) );
}

TEST_CASE("Checking substituting something that isn't in there") {
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(24)))
                   ->subst("z", new VarExpr("y"))
                   ->equals(new AddExpr(new VarExpr("x"), new NumExpr(24))) );

    CHECK( (new MultExpr(new VarExpr("x"), new NumExpr(24)))
                   ->subst("z", new VarExpr("y"))
                   ->equals(new MultExpr(new VarExpr("x"), new NumExpr(24))) );
}

TEST_CASE("CHECKING PRINT") {
    CHECK((new NumExpr(10))->to_string() == "10" );
}

TEST_CASE("CHECKING PRETTY PRINT") {

    CHECK((new MultExpr (new MultExpr (new NumExpr(2), new NumExpr(3)), new NumExpr(4)))->pretty_print_to_string() == "(2 * 3) * 4");
    CHECK((new NumExpr(1))->pretty_print_to_string() == "1");
    CHECK((new VarExpr("a"))->pretty_print_to_string() == "a");
    CHECK((new AddExpr(new NumExpr(1), new NumExpr(3)))->pretty_print_to_string() == "1 + 3");
    CHECK((new MultExpr (new NumExpr(2), new MultExpr (new NumExpr(3), new NumExpr(4))))->pretty_print_to_string() == "2 * 3 * 4");


}

TEST_CASE("Branden's tests") {
    MultExpr* complexMultExprWithVar = new MultExpr(new AddExpr(new VarExpr("x"), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));
    MultExpr* complexMultExprWithNoVar = new MultExpr(new AddExpr(new NumExpr(2), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));

CHECK(complexMultExprWithNoVar->pretty_print_to_string() == "(2 + 2 * 3) * 3");
CHECK(complexMultExprWithVar->pretty_print_to_string() == "(x + 2 * 3) * 3");
CHECK((new MultExpr (new MultExpr (new NumExpr(2), new NumExpr(3)), new NumExpr(4)))->pretty_print_to_string() == "(2 * 3) * 4");
CHECK((new MultExpr (new NumExpr(2), new MultExpr (new NumExpr(3), new NumExpr(4))))->pretty_print_to_string() == "2 * 3 * 4");
CHECK((new MultExpr (new MultExpr(new NumExpr(1), new NumExpr(2) ), new MultExpr (new NumExpr(3), new NumExpr(4))))->pretty_print_to_string() == "(1 * 2) * 3 * 4");
CHECK((new MultExpr (new NumExpr(2), new MultExpr (new NumExpr(3), new NumExpr(4))))->pretty_print_to_string() == "2 * 3 * 4");
CHECK((new MultExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->pretty_print_to_string() == "1 * (2 + 3)");
    CHECK((new MultExpr (new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->pretty_print_to_string() == "1 * (2 + 3)");
}

//Jons tests
    TEST_CASE("Pretty Print -- AddExpr"){
        NumExpr* testNum1 = new NumExpr(1);
        NumExpr* testNum2 = new NumExpr(2);
        NumExpr* testNum3 = new NumExpr(3);
        NumExpr* testNum4 = new NumExpr(4);

        VarExpr* testVar1 = new VarExpr("a");
        VarExpr* testVar2 = new VarExpr("b");

        AddExpr* testAdd1 = new AddExpr(testNum1, testNum2);
        AddExpr* testAdd2 = new AddExpr(testNum3, testAdd1);
        AddExpr* testAdd3 = new AddExpr(testAdd1, testNum3);
        AddExpr* testAdd4 = new AddExpr(testNum3, testNum4);
        AddExpr* testAdd5 = new AddExpr(testAdd1, testAdd4);

        AddExpr* testAdd6 = new AddExpr(testNum1, testVar1);

        MultExpr* testMult1 = new MultExpr(testNum3, testNum4);

        AddExpr* testMixed1 = new AddExpr(testNum1, testMult1);

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

    TEST_CASE("Pretty Print -- MultExpr"){
        NumExpr* testNum1 = new NumExpr(1);
        NumExpr* testNum2 = new NumExpr(2);
        NumExpr* testNum3 = new NumExpr(3);
        NumExpr* testNum4 = new NumExpr(4);

        AddExpr* testAdd1 = new AddExpr(testNum1, testNum2);
        AddExpr* testAdd2 = new AddExpr(testNum3, testNum4);

        MultExpr* testMult1 = new MultExpr(testNum1, testNum2);
        MultExpr* testMult2 = new MultExpr(testNum3, testMult1);
        MultExpr* testMult3 = new MultExpr(testMult1, testNum3);
        MultExpr* testMult4 = new MultExpr(testNum3, testNum4);
        MultExpr* testMult5 = new MultExpr(testMult1, testMult4);

        std::stringstream out("");
        testMult2->pretty_print(out);
        CHECK(out.str() == "3 * 1 * 2");

        out.str("");
        testMult3->pretty_print(out);
        CHECK(out.str() == "(1 * 2) * 3");

        out.str("");
        testMult5->pretty_print(out);
        CHECK(out.str() == "(1 * 2) * 3 * 4");

        MultExpr* testMixed1 = new MultExpr(testNum3, testAdd1);
        MultExpr* testMixed2 = new MultExpr(testAdd1, testNum3);
        MultExpr* testMixed3 = new MultExpr(testAdd1, testAdd2);

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
CHECK((new MultExpr(new MultExpr(new NumExpr(10), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10))))
              ->pretty_print_to_string()  == "(10 * (10 * 10) * 10) * 10 * 10");
}

TEST_CASE("LetExpr print") {
CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE("LET STUFF") {
    CHECK( (new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7)))-> pretty_print_to_string()
           == "(5 * (_let x = 5\n"
              "      _in  x * 2) + 1) * 7");
    CHECK( (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1)))-> pretty_print_to_string()
           == "5 * (_let x = 5\n"
              "     _in  x * 2) + 1");
}

TEST_CASE("william' stuff") {
    SECTION("hw_examples") {
//        CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))->interp() == 26);
    }
}

TEST_CASE("Pretty Print examples_Kevin"){           //Created from assignment examples
    std::stringstream out("");
    (new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in  x + 1");
    out.str(std::string());
    (new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr(1)))->pretty_print(out);
    CHECK(out.str() == "(_let x = 5\n"
                       " _in  x) + 1");

    out.str(std::string());
    (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))->pretty_print(out);
    CHECK(out.str() == "5 * (_let x = 5\n"
                       "     _in  x) + 1");
    out.str(std::string());
    (new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))
            ->pretty_print(out);

    CHECK(out.str() == "_let x = 5\n"
                       "_in  (_let y = 3\n"
                       "      _in  y + 2) + x");
    out.str(std::string());
    (new LetExpr("x", new LetExpr("y", new NumExpr(6), new MultExpr(new VarExpr("y"), new NumExpr(2))), new AddExpr(new VarExpr("x"), new NumExpr(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = _let y = 6\n"
                       "         _in  y * 2\n"
                       "_in  x + 1");

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
    LetExpr* tripleNestedLet = new LetExpr("x", new NumExpr(1),
                                           new LetExpr("y", new NumExpr(1),
                                                       new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z"))));
    LetExpr* tripleNestedLet2 = new LetExpr("x", new NumExpr(1),
                                            new LetExpr("y", new NumExpr(1),
                                                        new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                                    new AddExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));
    LetExpr* tripleNestedLet3 = new LetExpr("x", new NumExpr(1),
                                            new LetExpr("y", new NumExpr(1),
                                                        new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                                    new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));


    CHECK(tripleNestedLet -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  (x + y) * z"
    );
    CHECK(tripleNestedLet2 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) + z"
    );
    CHECK(tripleNestedLet3 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) * z"
    );
    LetExpr* tripleNestedLet4 =new LetExpr("x", new NumExpr(5),
                                           new LetExpr("y", new NumExpr(3),
                                                       new AddExpr(new VarExpr("y"), new NumExpr(2))));
    LetExpr* tripleNestedLet5 =new LetExpr("x", new NumExpr(5),
                                           new AddExpr(new LetExpr("y", new NumExpr(3),
                                                                   new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")));
    std::stringstream out("");
    out.str("");
    tripleNestedLet4->pretty_print(out);
    CHECK(out.str() ==
          "_let x = 5\n"
          "_in  _let y = 3\n"
          "     _in  y + 2"
    );

    CHECK(tripleNestedLet5 -> pretty_print_to_string() == "_let x = 5\n"
                                                          "_in  (_let y = 3\n"
                                                          "      _in  y + 2) + x");
    SECTION("assignment_examples") {
        CHECK( (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x) + 1");

    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("new_edge") {

        CHECK( (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x * 2) + 1");
        CHECK( (new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7)))-> pretty_print_to_string()
               == "(5 * (_let x = 5\n"
                  "      _in  x * 2) + 1) * 7");
        CHECK( (new LetExpr("x", new NumExpr(10), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->pretty_print_to_string()  == "_let x = 10\n"
                                                      "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK( (new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * 10 * 10" );
        CHECK( (new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new VarExpr("y"), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * y * 10" );
    }
}

TEST_CASE("Let_equals_mine") {
    SECTION("Values_same") {
        REQUIRE( (new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->equals(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) )));
    }
    SECTION("Values_same_different_rhs") {
        REQUIRE( !(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->equals(new LetExpr("x", new NumExpr(5), new AddExpr(new NumExpr(2), new VarExpr("x")) )));
    }
    SECTION("Values_same_different_lhs") {
        REQUIRE( !(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->equals(new LetExpr("y", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) )));
    }
    SECTION("Values_same_different_body") {
        REQUIRE( !(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->equals(new LetExpr("x", new NumExpr(4), new MultExpr(new NumExpr(3), new VarExpr("y")) )));
    }
    SECTION("different_types") {
        REQUIRE( !(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->equals(new MultExpr(new NumExpr(3), new VarExpr("y")) ));
    }
}
TEST_CASE("Let_has_variable_mine") {
    SECTION("has") {
        REQUIRE( (new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new VarExpr("x")) ))->has_variable());
    }
    SECTION("does_not_has") {
        REQUIRE( !(new LetExpr("x", new NumExpr(4), new AddExpr(new NumExpr(2), new NumExpr(4)) ))->has_variable());
    }
}
TEST_CASE("Let_print_mine") {
    CHECK( (new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))) -> to_string()
           == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK( (new LetExpr("x", new NumExpr(1),
                        new LetExpr("y", new NumExpr(1),
                                    new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))))) -> to_string()
           == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
}
TEST_CASE ("Let_interp_mine") {
    SECTION("hw_examples") {
        CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))->interp()->equals(new numVal (26)));
        CHECK((new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->interp()->equals(new numVal (30)));
    }

    SECTION("from_pretty_print_edge") {
        CHECK( (new LetExpr("x", new NumExpr(1),
                            new LetExpr("y", new NumExpr(1),
                                        new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                    new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))))) -> interp()->equals(new numVal(4)));
        CHECK( (new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7))) ->
        interp()->equals(new numVal (357))); // 51 * 7
        CHECK( (new LetExpr("x", new NumExpr(10), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->interp()->equals(new numVal (1000000)));
        CHECK( (new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->interp()->equals(new numVal (10000)));
        CHECK_THROWS_WITH( ((new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new VarExpr("y"), new NumExpr(10)))))
                                    -> interp()->equals(new numVal (10000))), "no value for variable");
    }
    SECTION("bypass_middle_let") {
        CHECK ((new LetExpr("x", new NumExpr(2), new LetExpr("z", new NumExpr(4), new AddExpr(new VarExpr("x"), new NumExpr(10)))))
                       -> interp()->equals(new numVal (12)));
    }
}

TEST_CASE("Nabil's parse") {
    CHECK_THROWS_WITH(parse_str("()"), "invalid input");

//
    CHECK(parse_str("(1)")->equals(new NumExpr(1)));
    CHECK(parse_str("(((1)))")->equals(new NumExpr(1)));
//
    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );
////
    CHECK( parse_str("1")->equals(new NumExpr(1)) );
    CHECK( parse_str("10")->equals(new NumExpr(10)) );
    CHECK( parse_str("-3")->equals(new NumExpr(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new NumExpr(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "invalid input" );

    CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
    CHECK( parse_str("x")->equals(new VarExpr("x")) );
    CHECK( parse_str("xyz")->equals(new VarExpr("xyz")) );
    CHECK( parse_str("xYz")->equals(new VarExpr("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );

    CHECK( parse_str("x + y")->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))) );

    CHECK( parse_str("x * y")->equals(new MultExpr(new VarExpr("x"), new VarExpr("y"))) );
//
    CHECK( parse_str("z * x + y")
                   ->equals(new AddExpr(new MultExpr(new VarExpr("z"), new VarExpr("x")),
                                        new VarExpr("y"))) );
//
    CHECK( parse_str("z * (x + y)")
                   ->equals(new MultExpr(new VarExpr("z"),
                                         new AddExpr(new VarExpr("x"), new VarExpr("y"))) ));
}

TEST_CASE("my parse") {
    CHECK(parse_str("_let x=5 _in ((_let y=3 _in (y+2))+x)")->equals(new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))));
    CHECK(parse_str("_let x = 2 _in x + 5")->equals(new LetExpr("x", new NumExpr(2), new AddExpr(new VarExpr("x"), new NumExpr(5)))));
}

TEST_CASE("consume") {
    //static void consume(std::istream &in, int expect) {
//    std::filebuf fb;
//    std::istream is(&fb);
    std::stringstream ss;
    ss.put('h');
    ss.put('e');
    ss.put('k');
    CHECK_THROWS_WITH(consume(ss, 'j'), "consume mismatch");
}

TEST_CASE("parse") {
    std::string test = "yeehaw";
    std::stringstream ss(test);

    ss.put('2');
    ss.put('+');
    ss.put('3');

    CHECK((parse(ss))->equals(new AddExpr(new NumExpr(2), new NumExpr(3))));

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let againadsf") {
    LetExpr* tripleNestedLet = new LetExpr("x", new NumExpr(1),
                                           new LetExpr("y", new NumExpr(1),
                                                       new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z"))));
    LetExpr* tripleNestedLet2 = new LetExpr("x", new NumExpr(1),
                                            new LetExpr("y", new NumExpr(1),
                                                        new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                                    new AddExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));
    LetExpr* tripleNestedLet3 = new LetExpr("x", new NumExpr(1),
                                            new LetExpr("y", new NumExpr(1),
                                                        new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
                                                                    new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")), new VarExpr("z")))));


    CHECK(tripleNestedLet -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  (x + y) * z"
    );
    CHECK(tripleNestedLet2 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) + z"
    );
    CHECK(tripleNestedLet3 -> pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) * z"
    );
    LetExpr* tripleNestedLet4 =new LetExpr("x", new NumExpr(5),
                                           new LetExpr("y", new NumExpr(3),
                                                       new AddExpr(new VarExpr("y"), new NumExpr(2))));
    LetExpr* tripleNestedLet5 =new LetExpr("x", new NumExpr(5),
                                           new AddExpr(new LetExpr("y", new NumExpr(3),
                                                                   new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")));
    std::stringstream out("");
    out.str("");
    tripleNestedLet4->pretty_print(out);
    CHECK(out.str() ==
          "_let x = 5\n"
          "_in  _let y = 3\n"
          "     _in  y + 2"
    );

    CHECK(tripleNestedLet5 -> pretty_print_to_string() == "_let x = 5\n"
                                                          "_in  (_let y = 3\n"
                                                          "      _in  y + 2) + x");
    SECTION("assignment_examples") {
        CHECK( (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x) + 1");
        CHECK( (new MultExpr(new MultExpr(new NumExpr (2), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x") , new  NumExpr(1)) )), new NumExpr(3) )) -> pretty_print_to_string()
               == "(2 * _let x = 5\n"
                  "     _in  x + 1) * 3");
    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("new_edge") {
        CHECK( (new MultExpr(new NumExpr (2), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x") , new  NumExpr(1)) ) )) -> pretty_print_to_string()
               == "2 * _let x = 5\n"
                  "    _in  x + 1");
        CHECK( (new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x * 2) + 1");
        CHECK( (new MultExpr((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new MultExpr(new VarExpr("x"), new NumExpr(2)))), new NumExpr(1))), new NumExpr(7)))-> pretty_print_to_string()
               == "(5 * (_let x = 5\n"
                  "      _in  x * 2) + 1) * 7");
        CHECK( (new LetExpr("x", new NumExpr(10), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new NumExpr(10))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       ->pretty_print_to_string()  == "_let x = 10\n"
                                                      "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK( (new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new NumExpr(10), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * 10 * 10" );
        CHECK( (new LetExpr("x", new NumExpr(1), new MultExpr(new MultExpr(new VarExpr("x"), new MultExpr(new MultExpr(new NumExpr(10), new NumExpr(10)), new VarExpr("x"))), new MultExpr(new VarExpr("y"), new NumExpr(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * y * 10" );
    }
}

TEST_CASE("val to string") {
    CHECK((new NumExpr(5))->interp()->to_string() == "5");
}
TEST_CASE("toExpr") {
    CHECK((new numVal(4))->toExpr()->equals(new NumExpr(4)) == true);
}
TEST_CASE("equals bad") {
    CHECK_FALSE((new numVal (4))->equals(nullptr));
}

TEST_CASE("addto bad") {
    CHECK_THROWS_WITH((new numVal(5))->add_to(new boolVal(true)), "add of non-number");
}

TEST_CASE("multTo bad") {
    CHECK_THROWS_WITH((new numVal(5))->mult_to(new boolVal(false)), "mult of non-number");
}

TEST_CASE("BoolExpr EQUALS") {
    CHECK((new BoolExpr(true))->equals(new BoolExpr(true)) == true);
    CHECK((new BoolExpr(true))->equals(new BoolExpr(false)) == false);
    CHECK((new BoolExpr(false))->equals(new BoolExpr(false)) == true);
    CHECK_FALSE((new BoolExpr(true))->equals(new NumExpr(5)));
}


TEST_CASE("BoolExpr INTERP") {
    CHECK((new BoolExpr(true))->interp()->equals(new boolVal(true)));
    CHECK((new BoolExpr(false))->interp()->equals(new boolVal(false)));
}

TEST_CASE("BoolExpr hasVar") {
    CHECK_FALSE((new BoolExpr(true))->has_variable());
    CHECK_FALSE((new BoolExpr(false))->has_variable());
}

TEST_CASE("BoolExpr subst") {
    CHECK((new BoolExpr(true))->subst("x", new VarExpr("y"))->equals(new BoolExpr(true)));
    CHECK_FALSE((new BoolExpr(false))->subst("x", new VarExpr("y"))->equals(new BoolExpr(true)));
}
TEST_CASE("BoolExpr print") {
    CHECK((new BoolExpr(true))->to_string() == "_true");
    CHECK_FALSE((new BoolExpr(false))->to_string() == "_true");
    CHECK((new BoolExpr(false))->to_string() == "_false");
}

TEST_CASE("BoolExpr print_print") {
    CHECK((new BoolExpr(true))->pretty_print_to_string() == "_true");
    CHECK((new BoolExpr(false))->pretty_print_to_string() == "_false");
}

TEST_CASE("IfExpr Equals") {
//    CHECK((new IfExpr(new BoolExpr(true), new NumExpr(3), new NumExpr(4)))->interp()->to_string() == new numVal(3)->to_string());

    CHECK((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) ->
    equals((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))));
    CHECK_FALSE((new IfExpr(new EqExpr(new NumExpr(5), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) ->
            equals((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))));

}

TEST_CASE(("IfExpr Interp")) {
    CHECK((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))->interp()->equals(new numVal(6)));
    CHECK((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(64)), new NumExpr(6), new NumExpr(7)))->interp()->equals(new numVal(7)));
}

TEST_CASE(("IfExpr hasVar")) {
    CHECK_FALSE((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))->has_variable());
}

TEST_CASE(("IfExpr print")) {
    CHECK((new IfExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(5), new NumExpr(6)))->to_string() ==
    "(_if (1==2) _then 5 _else 6)");
    CHECK((new IfExpr(new BoolExpr(true), new NumExpr(5), new BoolExpr(true + 1)))->interp()->equals(new numVal(5)));
}

TEST_CASE("BoolExpr tests") {
    CHECK((new BoolExpr(true)) -> equals(new BoolExpr(true)));
    CHECK(!(new BoolExpr(false)) -> equals(new BoolExpr(true)));
    CHECK(!((new BoolExpr(false)) -> equals(new NumExpr(10))) );
    CHECK(((new BoolExpr(true)) -> equals(new BoolExpr((new NumExpr(1)) -> equals(new NumExpr (1)))) ));


    CHECK(((new BoolExpr(true)) -> interp()) -> equals(new boolVal(true)));
    CHECK(((new BoolExpr(false)) -> interp()) -> equals(new boolVal(false)));
    CHECK(!((new BoolExpr(false)) -> interp()) -> equals(new boolVal(true)));

    CHECK(((new BoolExpr(true)) -> has_variable()) == false);

    CHECK(((new BoolExpr(true)) -> subst("x", new NumExpr(4)) -> equals(new BoolExpr(true))));

    CHECK((((new BoolExpr(true)) -> to_string()) == "_true"));
    CHECK((((new BoolExpr(false)) -> to_string()) == "_false"));

    CHECK((((new BoolExpr(true)) -> pretty_print_to_string()) == "_true"));
    CHECK((((new BoolExpr(false)) -> pretty_print_to_string()) == "_false"));
}

TEST_CASE("NumVal tests") {
    CHECK_THROWS_WITH( ((new numVal(5)) ->add_to(new boolVal(true))) , "add of non-number");
    CHECK_THROWS_WITH(((new numVal(5))->mult_to(new boolVal(true))) , "mult of non-number");

    CHECK(((new numVal(5)) -> to_string()) == "5");

    CHECK(!((new numVal(5)) ->equals(new boolVal(false))));

    CHECK_THROWS_WITH( ((new numVal(5)) ->is_true()) , "invalid argument");
}


TEST_CASE("BoolVal tests") {
    CHECK_THROWS_WITH( ((new boolVal(true)) ->add_to(new numVal(7))) , "trying to add two boolVals dingus");
    CHECK_THROWS_WITH(((new boolVal(true))->mult_to(new numVal(8))) , "trying to mult two boolVals ya poopoo head");

    CHECK(((new boolVal(true)) ->toExpr()) -> equals(new BoolExpr(true)));
    CHECK(((new boolVal(false)) ->toExpr()) -> equals(new BoolExpr(false)));

    CHECK(((new boolVal(true)) ->to_string()) == "_true");
    CHECK(((new boolVal(false)) ->to_string()) == "_false");

    CHECK(!((new boolVal(true)) ->equals(new numVal(4))));
    CHECK(((new boolVal(true)) ->equals(new boolVal(true))));
    CHECK(((new boolVal(false)) ->equals(new boolVal(false))));

    CHECK(!((new boolVal(false)) ->is_true()));
    CHECK(((new boolVal(true)) ->is_true()));
}

TEST_CASE("If and Equality tests") {
    CHECK((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> equals((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))));
    CHECK(!(new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> equals((new IfExpr(new EqExpr(new NumExpr(7), new NumExpr(4)), new NumExpr(6), new NumExpr(7)))));
    CHECK(!(new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> equals((new IfExpr(new BoolExpr(true), new NumExpr(6), new NumExpr(7)))));
    CHECK(!(new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> equals((new BoolExpr(true))));

    CHECK_THROWS_WITH( (new IfExpr(new NumExpr(4), new NumExpr(6), new NumExpr(7))) -> interp(), "invalid argument");
    CHECK((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> interp() -> to_string() == "6" );
    CHECK((new IfExpr(new EqExpr(new NumExpr(2), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> interp() -> to_string() == "7" );

    CHECK(!((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> has_variable()));
    CHECK(((new IfExpr(new EqExpr(new VarExpr("x"), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> has_variable()));
    CHECK(((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new VarExpr("y"), new NumExpr(7))) -> has_variable()));
    CHECK(((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(77), new VarExpr("z"))) -> has_variable()));

    CHECK((((new IfExpr(new EqExpr(new VarExpr("x"), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> subst("x", new NumExpr(4))) -> interp()) -> equals(new numVal(6)));
    CHECK((((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new VarExpr("y"), new NumExpr(7))) -> subst("y", new NumExpr(77))) -> interp()) -> equals(new numVal(77)));
    CHECK((((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new VarExpr("y"), new NumExpr(7))) -> subst("y", new NumExpr(77))) -> interp()) -> equals(new numVal(77)));


    CHECK(((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> to_string())
    == "(_if (4==4) _then 6 _else 7)" );
    CHECK(((new IfExpr(new EqExpr(new NumExpr(4), new NumExpr(4)), new NumExpr(6), new NumExpr(7))) -> pretty_print_to_string())
    == "(_if (4==4) _then 6 _else 7)" );

    CHECK(((new EqExpr(new NumExpr(4), new NumExpr(4))) -> pretty_print_to_string()) == "(4 == 4)");
}

TEST_CASE("Conditional parse tests") {
    SECTION("from quiz") {
        CHECK( (parse_str ( "_if 1 == 2 _then 5 _else 6")) ->
                equals(new IfExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(5), new NumExpr(6))));

        CHECK( (((parse_str ( "_if 1 == 2 _then 5 _else 6")) -> interp()) -> to_string()) == "6");
        CHECK( (((parse_str ( "1 == 2")) -> interp()) -> to_string()) == "_false");
        CHECK( (((parse_str ( "(1 + 2) == (3 + 0)")) -> interp()) -> to_string()) == "_true");
        CHECK( (((parse_str ( "1 + 2 == 3 + 0")) -> interp()) -> to_string()) == "_true");
        CHECK_THROWS_WITH(( (((parse_str ( "(1 == 2) + 3 ")) -> interp()) -> to_string()) == "_true"), "trying to add two boolVals dingus");
        CHECK( (((parse_str ( "1==2+3")) -> interp()) -> to_string()) == "_false");
        CHECK( (((parse_str ( "_if _false _then 5 _else 6")) -> interp()) -> to_string()) == "6");
        CHECK( (((parse_str ( "_if _false _then _false _else _true")) -> interp()) -> to_string()) == "_true");
        CHECK_THROWS_WITH(( (((parse_str ( "_true + _false")) -> interp()) -> to_string()) == "_false"), "trying to add two boolVals dingus");
        CHECK_THROWS_WITH(( (((parse_str ( "_true + 1")) -> interp()) -> to_string()) == "_false"), "trying to add two boolVals dingus");
        CHECK( (((parse_str ( "_true == _true")) -> interp()) -> to_string()) == "_true");
        CHECK( (((parse_str ( "1 == _true")) -> interp()) -> to_string()) == "_false");
        CHECK_THROWS_WITH(( (((parse_str ( "_if 1 + 2\n"
                                           "_then _false\n"
                                           "_else _true")) -> interp()) -> to_string()) == "_false"), "consume mismatch");
        CHECK( (((parse_str ( "_if _true _then 5 _else _true + 1")) -> interp()) -> to_string()) == "5");
        CHECK_THROWS_WITH(( (((parse_str ( "_if _false\n"
                                           "_then 5\n"
                                           "_else _true + 1")) -> interp()) -> to_string()) == "_false"), "consume mismatch");

        CHECK_THROWS_WITH(( (((parse_str ( "_let x = _true + 1\n"
                                           "_in  _if _true\n"
                                           "     _then 5\n"
                                           "     _else x")) -> interp()) -> to_string()) == "_false"), "consume mismatch");
        CHECK_THROWS_WITH(( (((parse_str ( "_let x = _true + 1\n"
                                           "_in  _if _true\n"
                                           "     _then 5\n"
                                           "     _else x")) -> interp()) -> to_string()) == "_false"), "consume mismatch");
        CHECK( (((parse_str ( "(_if _true _then 5 _else _true) + 1"))
        -> interp()) -> to_string()) == "6");
        CHECK( (((parse_str ( "_if (_if 1 == 2 _then _false _else _true) _then 5 _else 6"))
                                -> interp()) -> to_string()) == "5");
    }
    SECTION("Stu tests"){
        CHECK( (new IfExpr(new EqExpr(new NumExpr(1),new NumExpr(2)),new NumExpr(5), new NumExpr(6)))->interp()->equals(new numVal(6)));
        CHECK( (new AddExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(3)))->to_string() == "((1==2)+3)");
    };
    SECTION("to complete coverage") {
        // misspell then and else for parsing
        CHECK_THROWS_WITH(( (((parse_str ( "(_if _true\n"
                                           " _thn 5\n"
                                           " _else _true) + 1")) -> interp()) -> to_string()) == "6"), "consume mismatch");
        CHECK_THROWS_WITH(( (((parse_str ( "(_if _true\n"
                                           " _then 5\n"
                                           " _ele _true) + 1")) -> interp()) -> to_string()) == "6"), "consume mismatch");
        // misspell in for let
        CHECK_THROWS_WITH(( (parse_str ( "_let x = _let y = 6\n"
                                         "         _n  y * 2\n"
                                         "_i  x + 1")) -> equals(new LetExpr("x", new LetExpr("y", new NumExpr(6), new MultExpr(new VarExpr("y"), new NumExpr(2))), new AddExpr(new VarExpr("x"), new NumExpr(1))))), "consume mismatch");
    }
}




#endif //MSDSCRIPT_EXPTEST_H