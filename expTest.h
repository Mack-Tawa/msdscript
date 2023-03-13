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
    CHECK( (new Mult(new Num(3), new Num(2)))
                   ->interp()->equals(new numVal(6)) );
    CHECK((new Num(6))->interp()->equals(new numVal(6)));
//    CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))
//                   ->interp()==65);
}

TEST_CASE( "equals" ) {
    CHECK((new Num(1))->equals(new Num(1)) == true );
    CHECK((new Var("x"))->equals(new Var("y")) == false );
    CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new  Num(2), new Num(3))) == true );
}



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

TEST_CASE("Let print") {
CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE("LET STUFF") {
    CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7)))-> pretty_print_to_string()
           == "(5 * (_let x = 5\n"
              "      _in  x * 2) + 1) * 7");
    CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1)))-> pretty_print_to_string()
           == "5 * (_let x = 5\n"
              "     _in  x * 2) + 1");
}

TEST_CASE("william' stuff") {
    SECTION("hw_examples") {
//        CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->interp() == 26);
    }
}

TEST_CASE("Pretty Print examples_Kevin"){           //Created from assignment examples
    std::stringstream out("");
    (new Let("x", new Num(5), new Add(new Var("x"), new Num(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in  x + 1");
    out.str(std::string());
    (new Add(new Let("x", new Num(5), new Var("x")), new Num(1)))->pretty_print(out);
    CHECK(out.str() == "(_let x = 5\n"
                       " _in  x) + 1");

    out.str(std::string());
    (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->pretty_print(out);
    CHECK(out.str() == "5 * (_let x = 5\n"
                       "     _in  x) + 1");
    out.str(std::string());
    (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
            ->pretty_print(out);

    CHECK(out.str() == "_let x = 5\n"
                       "_in  (_let y = 3\n"
                       "      _in  y + 2) + x");
    out.str(std::string());
    (new Let("x", new Let("y", new Num(6), new Mult(new Var("y"), new Num(2))), new Add(new Var("x"), new Num(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = _let y = 6\n"
                       "         _in  y * 2\n"
                       "_in  x + 1");

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
    Let* tripleNestedLet = new Let("x", new Num(1),
                                   new Let("y", new Num(1),
                                           new Mult(new Add(new Var("x"), new Var("y")), new Var("z"))));
    Let* tripleNestedLet2 = new Let("x", new Num(1),
                                    new Let("y", new Num(1),
                                            new Let("z", new Add(new Var("x"), new Num(1)),
                                                    new Add(new Add(new Var("x"), new Var("y")), new Var("z")))));
    Let* tripleNestedLet3 = new Let("x", new Num(1),
                                    new Let("y", new Num(1),
                                            new Let("z", new Add(new Var("x"), new Num(1)),
                                                    new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))));


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
    Let* tripleNestedLet4 =new Let("x", new Num(5),
                                   new Let("y", new Num(3),
                                           new Add(new Var("y"), new Num(2))));
    Let* tripleNestedLet5 =new Let("x", new Num(5),
                                   new Add(new Let("y", new Num(3),
                                                   new Add(new Var("y"), new Num(2))), new Var("x")));
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
        CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x) + 1");

    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("new_edge") {

        CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x * 2) + 1");
        CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7)))-> pretty_print_to_string()
               == "(5 * (_let x = 5\n"
                  "      _in  x * 2) + 1) * 7");
        CHECK( (new Let("x", new Num(10), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10)))))
                       ->pretty_print_to_string()  == "_let x = 10\n"
                                                      "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Num(10), new Num(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * 10 * 10" );
        CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Var("y"), new Num(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * y * 10" );
    }
}

TEST_CASE("Let_equals_mine") {
    SECTION("Values_same") {
        REQUIRE( (new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) )));
    }
    SECTION("Values_same_different_rhs") {
        REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(5), new Add(new Num(2), new Var("x")) )));
    }
    SECTION("Values_same_different_lhs") {
        REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("y", new Num(4), new Add(new Num(2), new Var("x")) )));
    }
    SECTION("Values_same_different_body") {
        REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(4), new Mult(new Num(3), new Var("y")) )));
    }
    SECTION("different_types") {
        REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals( new Mult(new Num(3), new Var("y")) ));
    }
}
TEST_CASE("Let_has_variable_mine") {
    SECTION("has") {
        REQUIRE( (new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->has_variable());
    }
    SECTION("does_not_has") {
        REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Num(4)) ))->has_variable());
    }
}
TEST_CASE("Let_print_mine") {
    CHECK( (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x")))) -> to_string()
           == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK( (new Let("x", new Num(1),
                    new Let("y", new Num(1),
                            new Let("z", new Add(new Var("x"), new Num(1)),
                                    new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))))) -> to_string()
           == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
}
TEST_CASE ("Let_interp_mine") {
    SECTION("hw_examples") {
        CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->interp()->equals(new numVal (26)));
        CHECK((new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))))->interp()->equals(new numVal (30)));
    }

    SECTION("from_pretty_print_edge") {
        CHECK( (new Let("x", new Num(1),
                        new Let("y", new Num(1),
                                new Let("z", new Add(new Var("x"), new Num(1)),
                                        new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))))) -> interp()->equals(new numVal(4)));
        CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7))) ->
        interp()->equals(new numVal (357))); // 51 * 7
        CHECK( (new Let("x", new Num(10), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10)))))
                       ->interp()->equals(new numVal (1000000)));
        CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Num(10), new Num(10)))))
                       ->interp()->equals(new numVal (10000)));
        CHECK_THROWS_WITH( ((new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Var("y"), new Num(10)))))
                                    -> interp()->equals(new numVal (10000))), "no value for variable");
    }
    SECTION("bypass_middle_let") {
        CHECK ((new Let("x", new Num(2), new Let("z", new Num(4), new Add(new Var("x"), new Num(10)))))
                       -> interp()->equals(new numVal (12)));
    }
}

TEST_CASE("Nabil's parse") {
    CHECK_THROWS_WITH(parse_str("()"), "invalid input");

//
    CHECK(parse_str("(1)")->equals(new Num(1)));
    CHECK(parse_str("(((1)))")->equals(new Num(1)));
//
    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );
////
    CHECK( parse_str("1")->equals(new Num(1)) );
    CHECK( parse_str("10")->equals(new Num(10)) );
    CHECK( parse_str("-3")->equals(new Num(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "invalid input" );

    CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
    CHECK( parse_str("x")->equals(new Var("x")) );
    CHECK( parse_str("xyz")->equals(new Var("xyz")) );
    CHECK( parse_str("xYz")->equals(new Var("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );

    CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );

    CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );
//
    CHECK( parse_str("z * x + y")
                   ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                                    new Var("y"))) );
//
    CHECK( parse_str("z * (x + y)")
                   ->equals(new Mult(new Var("z"),
                                     new Add(new Var("x"), new Var("y"))) ));
}

TEST_CASE("my parse") {
    CHECK(parse_str("_let x=5 _in ((_let y=3 _in (y+2))+x)")->equals(new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x")))));
    CHECK(parse_str("_let x = 2 _in x + 5")->equals(new Let("x", new Num(2), new Add(new Var("x"), new Num(5)))));
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

    CHECK((parse(ss))->equals(new Add(new Num(2), new Num(3))));

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let againadsf") {
    Let* tripleNestedLet = new Let("x", new Num(1),
                                   new Let("y", new Num(1),
                                           new Mult(new Add(new Var("x"), new Var("y")), new Var("z"))));
    Let* tripleNestedLet2 = new Let("x", new Num(1),
                                    new Let("y", new Num(1),
                                            new Let("z", new Add(new Var("x"), new Num(1)),
                                                    new Add(new Add(new Var("x"), new Var("y")), new Var("z")))));
    Let* tripleNestedLet3 = new Let("x", new Num(1),
                                    new Let("y", new Num(1),
                                            new Let("z", new Add(new Var("x"), new Num(1)),
                                                    new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))));


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
    Let* tripleNestedLet4 =new Let("x", new Num(5),
                                   new Let("y", new Num(3),
                                           new Add(new Var("y"), new Num(2))));
    Let* tripleNestedLet5 =new Let("x", new Num(5),
                                   new Add(new Let("y", new Num(3),
                                                   new Add(new Var("y"), new Num(2))), new Var("x")));
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
        CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x) + 1");
        CHECK( (new Mult(new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") ,new  Num(1)) )), new Num(3) )) -> pretty_print_to_string()
               == "(2 * _let x = 5\n"
                  "     _in  x + 1) * 3");
    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("new_edge") {
        CHECK( (new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") ,new  Num(1)) ) )) -> pretty_print_to_string()
               == "2 * _let x = 5\n"
                  "    _in  x + 1");
        CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1)))-> pretty_print_to_string()
               == "5 * (_let x = 5\n"
                  "     _in  x * 2) + 1");
        CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7)))-> pretty_print_to_string()
               == "(5 * (_let x = 5\n"
                  "      _in  x * 2) + 1) * 7");
        CHECK( (new Let("x", new Num(10), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10)))))
                       ->pretty_print_to_string()  == "_let x = 10\n"
                                                      "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Num(10), new Num(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * 10 * 10" );
        CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Var("y"), new Num(10)))))
                       -> pretty_print_to_string() == "_let x = 1\n"
                                                      "_in  (x * (10 * 10) * x) * y * 10" );
    }
}

TEST_CASE("val to string") {
    CHECK((new Num(5))->interp()->to_string() == "5");
}
TEST_CASE("toExpr") {
    CHECK((new numVal(4))->toExpr()->equals(new Num(4)) == true);
}
TEST_CASE("equals bad") {
    CHECK_FALSE((new numVal (4))->equals(nullptr));
}

TEST_CASE("addto bad") {
    CHECK_THROWS_WITH((new numVal(5))->add_to(reinterpret_cast<Val *>(new Num(5))), "add of non-number");
}

TEST_CASE("multTo bad") {
    CHECK_THROWS_WITH((new numVal(5))->mult_to(reinterpret_cast<Val *>(new Num(5))), "add of non-number");
}


#endif //MSDSCRIPT_EXPTEST_H