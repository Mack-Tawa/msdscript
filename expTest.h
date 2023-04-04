////
//// Created by Mack on 1/19/23.
////
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
#include "pointer.h"
#include "Env.h"

PTR(Env) empty = NEW(emptyEnv)();

//
///**
// * making tests: maybe have vars at top like setup in JUnit.
// * caps class names
// * make prettier
// *
// */
//
//
//TEST_CASE("interp")
//{
//    CHECK( (NEW(MultExpr))(NEW(NumExpr)(3), NEW(NumExpr))(2)))
//                  ->interp(empty)->equals(NEW(numVal)(6)));
//    CHECK((NEW(NumExpr))(6))->interp(empty)->equals(NEW(numVal)(6)));
////    CHECK( (NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr))(10), NEW(NumExpr))(15)),NEW(AddExpr)(NEW(NumExpr))(20),NEW(NumExpr))(20))))
////                   ->interp(empty)==65);
//}
//
TEST_CASE("equals") {
    CHECK((NEW(AddExpr)(NEW(NumExpr)(3),
                        NEW(NumExpr)(5))->to_string() == "(3+5)"));
    CHECK((NEW(VarExpr)("x"))->equals(NEW(VarExpr)("y")) == false);
//    CHECK((NEW(AddExpr)(NEW(NumExpr)(2)), NEW(NumExpr)(3)))))->to_string() == "(2+3)");
    //->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))) == true);
}
//
//
TEST_CASE("different types same NumExpr) vals") {

    CHECK((NEW(AddExpr)(NEW(NumExpr)(-143), NEW(NumExpr)(25)))->equals(
            NEW(MultExpr)(NEW(NumExpr)(-143), NEW(NumExpr)(25))) ==
          false);
    CHECK_FALSE((NEW(NumExpr)(1))->equals(NEW(NumExpr)(5)));
    CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(4), NEW(NumExpr)(6)), NEW(NumExpr)(5)), NEW(NumExpr)(55))->equals
            ((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(4), NEW(NumExpr)(6)), NEW(NumExpr)(5)), NEW(NumExpr)(55))) ==
          true);
}
//
TEST_CASE("checking sub for add") {
    CHECK((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24)))
                  ->subst("x", NEW(VarExpr)("y"))
                  ->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(24))));

    CHECK((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7)))
                  ->subst("x", NEW(VarExpr)("y"))
                  ->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7))));

    CHECK((NEW(VarExpr)("x"))
                  ->subst("x", NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7)))
                  ->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7))));


}
//
TEST_CASE("Checking mult expression substitution") {
    CHECK((NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24)))
                  ->subst("x", NEW(VarExpr)("y"))
                  ->equals(NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(24))));

    CHECK_FALSE((NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24)))
                        ->subst("z", NEW(VarExpr)("y"))
                        ->equals(NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(24))));
}

TEST_CASE("Checking substituting something that isn't in there") {
    CHECK((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24)))
                  ->subst("z", NEW(VarExpr)("y"))
                  ->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24))));

    CHECK((NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24)))
                  ->subst("z", NEW(VarExpr)("y"))
                  ->equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(24))));
}

TEST_CASE("CHECKING PRINT") {
    CHECK((NEW(NumExpr)(10))->to_string() == "10");
}

TEST_CASE("CHECKING PRETTY PRINT") {

    CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)), NEW(NumExpr)(4)))->pretty_print_to_string() ==
          "(2 * 3) * 4");
    CHECK((NEW(NumExpr)(1))->pretty_print_to_string() == "1");
    CHECK((NEW(VarExpr)("a"))->pretty_print_to_string() == "a");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(3)))->pretty_print_to_string() == "1 + 3");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(2), NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->pretty_print_to_string() ==
          "2 * 3 * 4");


}

TEST_CASE("Branden's tests") {
    PTR(MultExpr) complexMultExprWithVar = NEW(MultExpr)(
            NEW(AddExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))), NEW(NumExpr)(3));
    PTR(MultExpr) complexMultExprWithNoVar = NEW(MultExpr)(
            NEW(AddExpr)(NEW(NumExpr)(2), NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))), NEW(NumExpr)(3));

    CHECK(complexMultExprWithNoVar->pretty_print_to_string() == "(2 + 2 * 3) * 3");
    CHECK(complexMultExprWithVar->pretty_print_to_string() == "(x + 2 * 3) * 3");
    CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)), NEW(NumExpr)(4)))->pretty_print_to_string() ==
          "(2 * 3) * 4");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(2), NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->pretty_print_to_string() ==
          "2 * 3 * 4");
    CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                         NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->pretty_print_to_string() ==
          "(1 * 2) * 3 * 4");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(2), NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->pretty_print_to_string() ==
          "2 * 3 * 4");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))->pretty_print_to_string() ==
          "1 * (2 + 3)");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))->pretty_print_to_string() ==
          "1 * (2 + 3)");
}

//Jons tests
TEST_CASE("Pretty Print -- AddExpr)") {
    PTR(NumExpr) testNum1 = NEW(NumExpr)(1);
    PTR(NumExpr) testNum2 = NEW(NumExpr)(2);
    PTR(NumExpr) testNum3 = NEW(NumExpr)(3);
    PTR(NumExpr) testNum4 = NEW(NumExpr)(4);

    PTR(VarExpr) testVar1 = NEW(VarExpr)("a");
    PTR(VarExpr) testVar2 = NEW(VarExpr)("b");

    PTR(AddExpr) testAdd1 = NEW(AddExpr)(testNum1, testNum2);
    PTR(AddExpr) testAdd2 = NEW(AddExpr)(testNum3, testAdd1);
    PTR(AddExpr) testAdd3 = NEW(AddExpr)(testAdd1, testNum3);
    PTR(AddExpr) testAdd4 = NEW(AddExpr)(testNum3, testNum4);
    PTR(AddExpr) testAdd5 = NEW(AddExpr)(testAdd1, testAdd4);

    PTR(AddExpr) testAdd6 = NEW(AddExpr)(testNum1, testVar1);

    PTR(MultExpr) testMult1 = NEW(MultExpr)(testNum3, testNum4);

    PTR(AddExpr) testMixed1 = NEW(AddExpr)(testNum1, testMult1);

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

TEST_CASE("Pretty Print -- MultExpr)") {
    PTR(NumExpr) testNum1 = NEW(NumExpr)(1);
    PTR(NumExpr) testNum2 = NEW(NumExpr)(2);
    PTR(NumExpr) testNum3 = NEW(NumExpr)(3);
    PTR(NumExpr) testNum4 = NEW(NumExpr)(4);

    PTR(AddExpr) testAdd1 = NEW(AddExpr)(testNum1, testNum2);
    PTR(AddExpr) testAdd2 = NEW(AddExpr)(testNum3, testNum4);

    PTR(MultExpr) testMult1 = NEW(MultExpr)(testNum1, testNum2);
    PTR(MultExpr) testMult2 = NEW(MultExpr)(testNum3, testMult1);
    PTR(MultExpr) testMult3 = NEW(MultExpr)(testMult1, testNum3);
    PTR(MultExpr) testMult4 = NEW(MultExpr)(testNum3, testNum4);
    PTR(MultExpr) testMult5 = NEW(MultExpr)(testMult1, testMult4);

    std::stringstream out("");
    testMult2->pretty_print(out);
    CHECK(out.str() == "3 * 1 * 2");

    out.str("");
    testMult3->pretty_print(out);
    CHECK(out.str() == "(1 * 2) * 3");

    out.str("");
    testMult5->pretty_print(out);
    CHECK(out.str() == "(1 * 2) * 3 * 4");

    PTR(MultExpr) testMixed1 = NEW(MultExpr)(testNum3, testAdd1);
    PTR(MultExpr) testMixed2 = NEW(MultExpr)(testAdd1, testNum3);
    PTR(MultExpr) testMixed3 = NEW(MultExpr)(testAdd1, testAdd2);

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
    CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
                                       NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)),
                                                     NEW(NumExpr)(10))),
                         NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10))))
                  ->pretty_print_to_string() == "(10 * (10 * 10) * 10) * 10 * 10");
}

TEST_CASE("LetExpr) print") {
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(AddExpr)(
                                NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
                                NEW(VarExpr)("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE("LET STUFF") {
    CHECK((NEW(MultExpr)((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                                   NEW(MultExpr)(NEW(VarExpr)("x"),
                                                                                                 NEW(NumExpr)(2)))),
                                       NEW(NumExpr)(1))), NEW(NumExpr)(7)))->pretty_print_to_string()
          == "(5 * (_let x = 5\n"
             "      _in  x * 2) + 1) * 7");
    CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5),
                                      NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                   NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)))),
                        NEW(NumExpr)(1)))->pretty_print_to_string()
          == "5 * (_let x = 5\n"
             "     _in  x * 2) + 1");
}

TEST_CASE("william' stuff") {
    SECTION("hw_examples") {
//        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))), NEW(NumExpr)(1)))->interp(empty) == 26);
    }
}

TEST_CASE("Pretty Print examples_Kevin") {           //Created from assignment examples
    std::stringstream out("");
    (NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = 5\n"
                       "_in  x + 1");
    out.str(std::string());
    (NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")), NEW(NumExpr)(1)))->pretty_print(out);
    CHECK(out.str() == "(_let x = 5\n"
                       " _in  x) + 1");

    out.str(std::string());
    (NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))),
                  NEW(NumExpr)(1)))->pretty_print(out);
    CHECK(out.str() == "5 * (_let x = 5\n"
                       "     _in  x) + 1");
    out.str(std::string());
    (NEW(LetExpr)("x", NEW(NumExpr)(5),
                  NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
                               NEW(VarExpr)("x"))))
            ->pretty_print(out);

    CHECK(out.str() == "_let x = 5\n"
                       "_in  (_let y = 3\n"
                       "      _in  y + 2) + x");
    out.str(std::string());
    (NEW(LetExpr)("x", NEW(LetExpr)("y", NEW(NumExpr)(6), NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
                  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->pretty_print(out);
    CHECK(out.str() == "_let x = _let y = 6\n"
                       "         _in  y * 2\n"
                       "_in  x + 1");

}

TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
    PTR(LetExpr) tripleNestedLet = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                             NEW(MultExpr)(
                                                                     NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
                                                                     NEW(VarExpr)("z"))));
    PTR(LetExpr) tripleNestedLet2 = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                              NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                             NEW(NumExpr)(1)),
                                                                           NEW(AddExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                                     NEW(VarExpr)("y")),
                                                                                        NEW(VarExpr)("z")))));
    PTR(LetExpr) tripleNestedLet3 = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                              NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                             NEW(NumExpr)(1)),
                                                                           NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                                      NEW(VarExpr)(
                                                                                                              "y")),
                                                                                         NEW(VarExpr)("z")))));


    CHECK(tripleNestedLet->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  (x + y) * z"
    );
    CHECK(tripleNestedLet2->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) + z"
    );
    CHECK(tripleNestedLet3->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) * z"
    );
    PTR(LetExpr) tripleNestedLet4 = NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(3),
                                                              NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))));
    PTR(LetExpr) tripleNestedLet5 = NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                 NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
                                                                           NEW(AddExpr)(NEW(VarExpr)("y"),
                                                                                        NEW(NumExpr)(2))),
                                                              NEW(VarExpr)("x")));
    std::stringstream out("");
    out.str("");
    tripleNestedLet4->pretty_print(out);
    CHECK(out.str() ==
          "_let x = 5\n"
          "_in  _let y = 3\n"
          "     _in  y + 2"
    );

    CHECK(tripleNestedLet5->pretty_print_to_string() == "_let x = 5\n"
                                                        "_in  (_let y = 3\n"
                                                        "      _in  y + 2) + x");
    SECTION("assignment_examples") {
        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))),
                            NEW(NumExpr)(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x) + 1");

    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("NEW()_edge") {

        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                        NEW(MultExpr)(NEW(VarExpr)("x"),
                                                                                      NEW(NumExpr)(2)))),
                            NEW(NumExpr)(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x * 2) + 1");
        CHECK((NEW(MultExpr)((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                                       NEW(MultExpr)(NEW(VarExpr)("x"),
                                                                                                     NEW(NumExpr)(2)))),
                                           NEW(NumExpr)(1))), NEW(NumExpr)(7)))->pretty_print_to_string()
              == "(5 * (_let x = 5\n"
                 "      _in  x * 2) + 1) * 7");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                         NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(NumExpr)(10))),
                                                                 NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 10\n"
                                                    "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                        NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))),
                                                                NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * 10 * 10");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                        NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))),
                                                                NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * y * 10");
    }
}

TEST_CASE("Let_equals_mine") {
    SECTION("Values_same") {
        REQUIRE((NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))->equals(
                NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
    }SECTION("Values_same_different_rhs") {
        REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))->equals(
                NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
    }SECTION("Values_same_different_lhs") {
        REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))->equals(
                NEW(LetExpr)("y", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
    }SECTION("Values_same_different_body") {
        REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))->equals(
                NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(MultExpr)(NEW(NumExpr)(3), NEW(VarExpr)("y")))));
    }SECTION("different_types") {
        REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4), NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))->equals(
                NEW(MultExpr)(NEW(NumExpr)(3), NEW(VarExpr)("y"))));
    }
}

TEST_CASE("Let_print_mine") {
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
                        NEW(AddExpr)(
                                NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
                                NEW(VarExpr)("x"))))->to_string()
          == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1),
                        NEW(LetExpr)("y", NEW(NumExpr)(1),
                                     NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
                                                  NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
                                                                NEW(VarExpr)("z"))))))->to_string()
          == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
}

TEST_CASE ("Let_interp_mine") {
//    SECTION("hw_examples") {
////        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))),
////                      NEW(NumExpr)(1)))->interp(empty)->equals(NEW(numVal)(26)));
////        CHECK((NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(
////                1)))))->interp(empty)->equals(NEW(numVal)(30)));
//    }


    SECTION("from_pretty_print_edge") {
        PTR(Env) empty = NEW(emptyEnv)();

        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1),
                      NEW(LetExpr)("y", NEW(NumExpr)(1),
                      NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
                      NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
                      NEW(VarExpr)("z"))))))->interp(empty)->equals(NEW(numVal)(4)));
        CHECK((NEW(MultExpr)((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                      NEW(MultExpr)(NEW(VarExpr)("x"),
                      NEW(NumExpr)(2)))),
                      NEW(NumExpr)(1))), NEW(NumExpr)(7)))->
                      interp(empty)->equals(NEW(numVal)(357))); // 51 * 7
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                      NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(NumExpr)(10))),
                      NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->interp(empty)->equals(NEW(numVal)(1000000)));
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                      NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))),
                      NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->interp(empty)->equals(NEW(numVal)(10000)));
        CHECK_THROWS_WITH(((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))), NEW(MultExpr)(NEW(VarExpr)("y"),
                NEW(NumExpr)(10)))))
                ->interp(empty)->equals(NEW(numVal)(10000))), "no value for variable");
    }SECTION("bypass_middle_let") {
        PTR(Env) empty = NEW(emptyEnv)();

        CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(2),
                       NEW(LetExpr)("z", NEW(NumExpr)(4), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(10)))))
                       ->interp(empty)->equals(NEW(numVal)(12)));
    }
}

TEST_CASE("Nabil's parse") {
    CHECK_THROWS_WITH(parse_str("()"), "parse_inner invalid input");

//
    CHECK(parse_str("(1)")->equals(NEW(NumExpr)(1)));
    CHECK(parse_str("(((1)))")->equals(NEW(NumExpr)(1)));
//
    CHECK_THROWS_WITH(parse_str("(1"), "missing close parenthesis");
////
    CHECK(parse_str("1")->equals(NEW(NumExpr)(1)));
    CHECK(parse_str("10")->equals(NEW(NumExpr)(10)));
    CHECK(parse_str("-3")->equals(NEW(NumExpr)(-3)));
    CHECK(parse_str("  \n 5  ")->equals(NEW(NumExpr)(5)));
    CHECK_THROWS_WITH(parse_str("-"), "parse num invalid input");

    CHECK_THROWS_WITH(parse_str(" -   5  "), "parse num invalid input");
    CHECK(parse_str("x")->equals(NEW(VarExpr)("x")));
    CHECK(parse_str("xyz")->equals(NEW(VarExpr)("xyz")));
    CHECK(parse_str("xYz")->equals(NEW(VarExpr)("xYz")));
    CHECK_THROWS_WITH(parse_str("x_z"), "parsevar invalid input");

    CHECK(parse_str("x + y")->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));

    CHECK(parse_str("x * y")->equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));
//
    CHECK(parse_str("z * x + y")
                  ->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("z"), NEW(VarExpr)("x")),
                                        NEW(VarExpr)("y"))));
//
    CHECK(parse_str("z * (x + y)")
                  ->equals(NEW(MultExpr)(NEW(VarExpr)("z"),
                                         NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")))));
}

TEST_CASE("my parse") {
    CHECK(parse_str("_let x=5 _in ((_let y=3 _in (y+2))+x)")->equals(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(
            NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(VarExpr)("x")))));
    CHECK(parse_str("_let x = 2 _in x + 5")->equals(
            NEW(LetExpr)("x", NEW(NumExpr)(2), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(5)))));
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


TEST_CASE("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let againadsf") {
    PTR(LetExpr) tripleNestedLet = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                             NEW(MultExpr)(
                                                                     NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
                                                                     NEW(VarExpr)("z"))));
    PTR(LetExpr) tripleNestedLet2 = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                              NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                             NEW(NumExpr)(1)),
                                                                           NEW(AddExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                                     NEW(VarExpr)("y")),
                                                                                        NEW(VarExpr)("z")))));
    PTR(LetExpr) tripleNestedLet3 = NEW(LetExpr)("x", NEW(NumExpr)(1),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(1),
                                                              NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                             NEW(NumExpr)(1)),
                                                                           NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                                      NEW(VarExpr)(
                                                                                                              "y")),
                                                                                         NEW(VarExpr)("z")))));


    CHECK(tripleNestedLet->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  (x + y) * z"
    );
    CHECK(tripleNestedLet2->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) + z"
    );
    CHECK(tripleNestedLet3->pretty_print_to_string() ==
          "_let x = 1\n"
          "_in  _let y = 1\n"
          "     _in  _let z = x + 1\n"
          "          _in  (x + y) * z"
    );
    PTR(LetExpr) tripleNestedLet4 = NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                 NEW(LetExpr)("y", NEW(NumExpr)(3),
                                                              NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))));
    PTR(LetExpr) tripleNestedLet5 = NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                 NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
                                                                           NEW(AddExpr)(NEW(VarExpr)("y"),
                                                                                        NEW(NumExpr)(2))),
                                                              NEW(VarExpr)("x")));
    std::stringstream out("");
    out.str("");
    tripleNestedLet4->pretty_print(out);
    CHECK(out.str() ==
          "_let x = 5\n"
          "_in  _let y = 3\n"
          "     _in  y + 2"
    );

    CHECK(tripleNestedLet5->pretty_print_to_string() == "_let x = 5\n"
                                                        "_in  (_let y = 3\n"
                                                        "      _in  y + 2) + x");
    SECTION("assignment_examples") {
        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))),
                            NEW(NumExpr)(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x) + 1");
        CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                         NEW(AddExpr)(NEW(VarExpr)("x"),
                                                                                      NEW(NumExpr)(1)))),
                             NEW(NumExpr)(3)))->pretty_print_to_string()
              == "(2 * _let x = 5\n"
                 "     _in  x + 1) * 3");
    }
        // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
        // where _let would have needed parentheses in the surrounding context
        // (that is, if the _let used in place of the whole * would need parentheses,
        // then it still needs parentheses within the right-hand size of *).
    SECTION("NEW()_edge") {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(2),
                             NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(
                                     1)))))->pretty_print_to_string()
              == "2 * _let x = 5\n"
                 "    _in  x + 1");
        CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                        NEW(MultExpr)(NEW(VarExpr)("x"),
                                                                                      NEW(NumExpr)(2)))),
                            NEW(NumExpr)(1)))->pretty_print_to_string()
              == "5 * (_let x = 5\n"
                 "     _in  x * 2) + 1");
        CHECK((NEW(MultExpr)((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
                                                                                       NEW(MultExpr)(NEW(VarExpr)("x"),
                                                                                                     NEW(NumExpr)(2)))),
                                           NEW(NumExpr)(1))), NEW(NumExpr)(7)))->pretty_print_to_string()
              == "(5 * (_let x = 5\n"
                 "      _in  x * 2) + 1) * 7");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                         NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(NumExpr)(10))),
                                                                 NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 10\n"
                                                    "_in  (x * (10 * 10) * 10) * 10 * 10");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                        NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))),
                                                                NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * 10 * 10");
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(MultExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(MultExpr)(
                                                                        NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)), NEW(VarExpr)("x"))),
                                                                NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(10)))))
                      ->pretty_print_to_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * y * 10");
    }
}

TEST_CASE("val to string") {
    PTR(Env) empty = NEW(emptyEnv)();

    CHECK((NEW(NumExpr)(5))->interp(empty)->to_string() == "5");
}

TEST_CASE("toExpr") {
    PTR(Env) empty = NEW(emptyEnv)();

}

TEST_CASE("equals bad") {
    CHECK_FALSE((NEW(numVal)(4))->equals(nullptr));
}

TEST_CASE("addto bad") {
    CHECK_THROWS_WITH((NEW(numVal)(5))->add_to(NEW(boolVal)(true)), "add of non-number");
}

TEST_CASE("multTo bad") {
    CHECK_THROWS_WITH((NEW(numVal)(5))->mult_to(NEW(boolVal)(false)), "mult of non-number");
}

TEST_CASE("BoolExpr EQUALS") {
    CHECK((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(true)) == true);
    CHECK((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(false)) == false);
    CHECK((NEW(BoolExpr)(false))->equals(NEW(BoolExpr)(false)) == true);
    CHECK_FALSE((NEW(BoolExpr)(true))->equals(NEW(NumExpr)(5)));
}


TEST_CASE("BoolExpr INTERP") {
    PTR(Env) empty = NEW(emptyEnv)();

    CHECK((NEW(BoolExpr)(true))->interp(empty)->equals(NEW(boolVal)(true)));
    CHECK((NEW(BoolExpr)(false))->interp(empty)->equals(NEW(boolVal)(false)));
}


TEST_CASE("BoolExpr subst") {
    CHECK((NEW(BoolExpr)(true))->subst("x", NEW(VarExpr)("y"))->equals(NEW(BoolExpr)(true)));
    CHECK_FALSE((NEW(BoolExpr)(false))->subst("x", NEW(VarExpr)("y"))->equals(NEW(BoolExpr)(true)));
}

TEST_CASE("BoolExpr print") {
    CHECK((NEW(BoolExpr)(true))->to_string() == "_true");
    CHECK_FALSE((NEW(BoolExpr)(false))->to_string() == "_true");
    CHECK((NEW(BoolExpr)(false))->to_string() == "_false");
}

TEST_CASE("BoolExpr print_print") {
    CHECK((NEW(BoolExpr)(true))->pretty_print_to_string() == "_true");
    CHECK((NEW(BoolExpr)(false))->pretty_print_to_string() == "_false");
}

TEST_CASE("IfExpr) Equals") {

    CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->
                  equals((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))));
    CHECK_FALSE((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(5), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->
                        equals((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))));

}

TEST_CASE(("IfExpr) Interp")) {
    CHECK(
    (NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->interp(empty)->equals(
            NEW(numVal)(6)));
    CHECK(
    (NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(64)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->interp(empty)->equals(
            NEW(numVal)(7)));
}


TEST_CASE(("IfExpr) print")) {
    CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(5), NEW(NumExpr)(6)))->to_string() ==
                  "(_if (1==2) _then 5 _else 6)");
    CHECK(
    (NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(BoolExpr)(true + 1)))->interp(empty)->equals(NEW(numVal)(5)));
}

TEST_CASE("BoolExpr tests") {
    CHECK((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(true)));
    CHECK(!(NEW(BoolExpr)(false))->equals(NEW(BoolExpr)(true)));
    CHECK(!((NEW(BoolExpr)(false))->equals(NEW(NumExpr)(10))));
    CHECK(((NEW(BoolExpr)(true))->equals(NEW(BoolExpr)((NEW(NumExpr)(1))->equals(NEW(NumExpr)(1))))));


    CHECK(((NEW(BoolExpr)(true))->interp(empty))->equals(NEW(boolVal)(true)));
    CHECK(((NEW(BoolExpr)(false))->interp(empty))->equals(NEW(boolVal)(false)));
    CHECK(!((NEW(BoolExpr)(false))->interp(empty))->equals(NEW(boolVal)(true)));


    CHECK(((NEW(BoolExpr)(true))->subst("x", NEW(NumExpr)(4))->equals(NEW(BoolExpr)(true))));

    CHECK((((NEW(BoolExpr)(true))->to_string()) == "_true"));
    CHECK((((NEW(BoolExpr)(false))->to_string()) == "_false"));

    CHECK((((NEW(BoolExpr)(true))->pretty_print_to_string()) == "_true"));
    CHECK((((NEW(BoolExpr)(false))->pretty_print_to_string()) == "_false"));
}

TEST_CASE("numVal) tests") {
    CHECK_THROWS_WITH(((NEW(numVal)(5))->add_to(NEW(boolVal)(true))), "add of non-number");
    CHECK_THROWS_WITH(((NEW(numVal)(5))->mult_to(NEW(boolVal)(true))), "mult of non-number");

    CHECK(((NEW(numVal)(5))->to_string()) == "5");

    CHECK(!((NEW(numVal)(5))->equals(NEW(boolVal)(false))));

    CHECK_THROWS_WITH(((NEW(numVal)(5))->is_true()), "invalid argument");
}


TEST_CASE("BoolVal tests") {
    CHECK_THROWS_WITH(((NEW(boolVal)(true))->add_to(NEW(numVal)(7))), "trying to add a boolVal) ya dingus");
    CHECK_THROWS_WITH(((NEW(boolVal)(true))->mult_to(NEW(numVal)(8))), "trying to mult two boolVal)s ya poopoo head");

    CHECK(((NEW(boolVal)(true))->toExpr())->equals(NEW(BoolExpr)(true)));
    CHECK(((NEW(boolVal)(false))->toExpr())->equals(NEW(BoolExpr)(false)));

    CHECK(((NEW(boolVal)(true))->to_string()) == "_true");
    CHECK(((NEW(boolVal)(false))->to_string()) == "_false");

    CHECK(!((NEW(boolVal)(true))->equals(NEW(numVal)(4))));
    CHECK(((NEW(boolVal)(true))->equals(NEW(boolVal)(true))));
    CHECK(((NEW(boolVal)(false))->equals(NEW(boolVal)(false))));

    CHECK(!((NEW(boolVal)(false))->is_true()));
    CHECK(((NEW(boolVal)(true))->is_true()));
}

TEST_CASE("If and Equality tests") {
    CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->equals(
          (NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))));
    CHECK(!(NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->equals(
          (NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(7), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))));
    CHECK(!(NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->equals(
          (NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(6), NEW(NumExpr)(7)))));
    CHECK(!(NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->equals(
          (NEW(BoolExpr)(true))));

    CHECK_THROWS_WITH(
    (NEW(IfExpr)(NEW(NumExpr)(4), NEW(NumExpr)(6), NEW(NumExpr)(7)))->interp(empty), "invalid argument");
    CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6),
                  NEW(NumExpr)(7)))->interp(empty)->to_string() == "6");
    CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(2), NEW(NumExpr)(4)), NEW(NumExpr)(6),
                  NEW(NumExpr)(7)))->interp(empty)->to_string() == "7");

    CHECK((((NEW(IfExpr)(NEW(EqExpr(NEW(VarExpr)("x"), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->subst("x",
                  NEW(NumExpr)(
                  4)))->interp(empty))->equals(
                  NEW(numVal)(6)));
    CHECK((((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(VarExpr)("y"), NEW(NumExpr)(7)))->subst("y",
                  NEW(NumExpr)(
                  77)))->interp(empty))->equals(
                  NEW(numVal)(77)));
    CHECK((((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(VarExpr)("y"), NEW(NumExpr)(7)))->subst("y",
                  NEW(NumExpr)(
                  77)))->interp(empty))->equals(
                  NEW(numVal)(77)));


    CHECK(((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6), NEW(NumExpr)(7)))->to_string())
                  == "(_if (4==4) _then 6 _else 7)");
CHECK(((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)), NEW(NumExpr)(6),
                       NEW(NumExpr)(7)))->pretty_print_to_string())
        == "(_if (4==4) _then 6 _else 7)");

              CHECK(((NEW(EqExpr(NEW(NumExpr)(4), NEW(NumExpr)(4)))->pretty_print_to_string()) == "(4 == 4)");
      }

//TEST_CASE("Conditional parse tests") {
//    SECTION("from quiz") {
//        CHECK((parse_str("_if 1 == 2 _then 5 _else 6"))->
//                      equals(NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(5), NEW(NumExpr)(6))));
//
//        CHECK((((parse_str("_if 1 == 2 _then 5 _else 6"))->interp(empty))->to_string()) == "6");
//        CHECK((((parse_str("1 == 2"))->interp(empty))->to_string()) == "_false");
//        CHECK((((parse_str("(1 + 2) == (3 + 0)"))->interp(empty))->to_string()) == "_true");
//        CHECK((((parse_str("1 + 2 == 3 + 0"))->interp(empty))->to_string()) == "_true");
//        CHECK_THROWS_WITH(((((parse_str("(1 == 2) + 3 "))->interp(empty))->to_string()) == "_true"),
//                          "trying to add a boolVal) ya dingus");
//        CHECK((((parse_str("1==2+3"))->interp(empty))->to_string()) == "_false");
//        CHECK((((parse_str("_if _false _then 5 _else 6"))->interp(empty))->to_string()) == "6");
//        CHECK((((parse_str("_if _false _then _false _else _true"))->interp(empty))->to_string()) == "_true");
//        CHECK_THROWS_WITH(((((parse_str("_true + _false"))->interp(empty))->to_string()) == "_false"),
//                          "trying to add a boolVal) ya dingus");
//        CHECK_THROWS_WITH(((((parse_str("_true + 1"))->interp(empty))->to_string()) == "_false"),
//                          "trying to add a boolVal) ya dingus");
//        CHECK((((parse_str("_true == _true"))->interp(empty))->to_string()) == "_true");
//        CHECK((((parse_str("1 == _true"))->interp(empty))->to_string()) == "_false");
//        CHECK_THROWS_WITH(((((parse_str("_if 1 + 2\n"
//                                        "_then _false\n"
//                                        "_else _true"))->interp(empty))->to_string()) == "_false"), "invalid argument");
//        CHECK((((parse_str("_if _true _then 5 _else _true + 1"))->interp(empty))->to_string()) == "5");
//        CHECK_THROWS_WITH(((((parse_str("_if _false\n"
//                                        "_then 5\n"
//                                        "_else _true + 1"))->interp(empty))->to_string()) == "_false"),
//                          "trying to add a boolVal) ya dingus");
//
//        CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
//                                        "_in  _if _true\n"
//                                        "     _then 5\n"
//                                        "     _else x"))->interp(empty))->to_string()) == "false"),
//                          "trying to add a boolVal) ya dingus");
//        CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
//                                        "_in  _if _true\n"
//                                        "     _then 5\n"
//                                        "     _else x"))->interp(empty))->to_string()) == "false"),
//                          "trying to add a boolVal) ya dingus");
//        CHECK((((parse_str("(_if _true _then 5 _else _true) + 1"))
//                ->interp(empty))->to_string()) == "6");
//        CHECK((((parse_str("_if (_if 1 == 2 _then _false _else _true) _then 5 _else 6"))
//                ->interp(empty))->to_string()) == "5");
//
//        CHECK((NEW(IfExpr)(NEW(EqExpr(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(5),
//                              NEW(NumExpr)(6)))->interp(empty)->equals(NEW(numVal)(6)));
//                      CHECK((NEW(AddExpr)(
//                              NEW(EqExpr(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(3)))->to_string() ==
//                             "((1==2)+3)");
//              }
//              };

              TEST_CASE("fix") {
              SECTION("to complete coverage") {
              // misspell then and else for parsing
              CHECK_THROWS_WITH(((((parse_str("(_if _true\n"
              " _thn 5\n"
              " _else _true) + 1"))->interp(empty))->to_string()) == "6"), "invalid argument for 'then' statement");
              CHECK_THROWS_WITH(((((parse_str("(_if _true\n"
              " _then 5\n"
              " _ele _true) + 1"))->interp(empty))->to_string()) == "6"), "invalid argument for 'else' statement");
              // misspell in for let
              CHECK_THROWS_WITH(((parse_str("_let x = _let y = 6\n"
              "         _n  y * 2\n"
              "_i  x + 1"))->equals(
              NEW(LetExpr)("x", NEW(LetExpr)("y", NEW(NumExpr)(6), NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
              NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))), "consume mismatch");
      }
      }



              TEST_CASE("CallExpr) to_string") {
              CHECK((NEW(CallExpr)(
              NEW(FunExpr)(("x"), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))), NEW(NumExpr)(10)))->to_string() ==
              "_fun (x) (x+1) (10)");
      }


              TEST_CASE("CallExpr) interp") {
              CHECK((NEW(CallExpr)(
              NEW(FunExpr)(("x"), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))),
              NEW(NumExpr)(10)))->interp(empty)->equals(NEW(numVal)(11)));
              CHECK((NEW(CallExpr)(
              NEW(FunExpr)(("x"), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))),
              NEW(NumExpr)(10)))->interp(empty)->to_string() == "11");
      }
//
//
              TEST_CASE("quiz function vals") {
              PTR(Env) empty = NEW(emptyEnv)();

              // 1
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in f(5) ")->interp(empty)->equals(NEW(numVal)) (6)));

//    // 2
              CHECK(parse_str("_let f = _fun (x)\n"
              "           7\n"
              "_in f(5)")->interp(empty)->equals(NEW(numVal)) (7)));

              // 3
              CHECK(parse_str("_let f = _fun (x)\n"
              "           _true\n"
              "_in f(5) ")->interp(empty)->equals(NEW(boolVal)) (true)));

              // 4
              CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
              "           x + _true\n"
              "_in f(5) ")->interp(empty), "add of non-number");

              // 5
              CHECK(parse_str("_let f = _fun (x)\n"
              "           x + _true\n"
              "_in 5 + 1 ")->interp(empty)->equals(NEW(numVal)) (6)));

              // 6
              CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
              "           7\n"
              "_in  f(5 + _true)")->interp(empty), "add of non-number");

              // 7
              CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1\n"
              "_in f + 5")->interp(empty), "trying to add two funVals dingus");

              // 8
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in _if _false\n"
              "    _then f(5)\n"
              "    _else f(6)")->interp(empty)->equals(NEW(numVal)) (7)));

              // 9
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in _let g = _fun (y) y+ 2 \n"
              "_in _if _true\n"
              "    _then f(5)\n"
              "    _else g(5)")->interp(empty)->equals(NEW(numVal)) (6)));

              // 10
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in _let g = _fun (y) y+ 2 \n"
              "_in f(g(5)) ")->interp(empty)->equals(NEW(numVal)) (8)));

              // 11
              CHECK(parse_str("_let f = _fun (x) x+ 1 _in _let g = _fun (y) f(y + 2) _in g(5) ")->interp(empty)->equals(NEW(numVal)) (8)));

              // 12
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in _let g = _fun (x)\n"
              "              f(2) + x\n"
              "_in g(5) ")->interp(empty)->equals(NEW(numVal)) (8)));

              // 13
              CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in f 5 ")->interp(empty), "Invalid input in parse");

              // 14
              CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
              "_in (f)(5) ")->interp(empty)->equals(NEW(numVal)) (6)));

//     15
              PTR(Expr) add_x_1 = NEW(AddExpr)) (NEW(VarExpr)) ("x"), NEW(NumExpr))) (1));
    shared_ptr<FunVal> fun_val_x_add_x_1 = NEW(FunVal)("x", add_x_1, empty);
    CHECK(parse_str("_fun (x) x+ 1 ")->interp(empty)->equals(fun_val_x_add_x_1));

//    16
    CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
                    "_in f ")->interp(empty)->equals(fun_val_x_add_x_1));

// 17
    CHECK(parse_str("(_fun (x)\n"
                    "   x + 1)(5)")->interp(empty)->equals(NEW(numVal))(6)));

// 18
    CHECK(parse_str("_let f = _if _false\n"
                    "            _then _fun (x)  \n"
                    "                        x+ 1 \n"
                    "           _else _fun (x)\n"
                    "                       x+ 2\n"
                    "_in f(5)")->interp(empty)->equals(NEW(numVal))(7)));

// 19
    CHECK(parse_str("(_if _false \n"
                    "  _then _fun (x)\n"
                    "            x+ 1\n"
                    "   _else _fun (x)\n"
                    "                x + 2)(5)")->interp(empty)->equals(NEW(numVal))(7)));

// 20
    CHECK(parse_str("_let f = _fun (g)\n"
                    "           g(5)\n"
                    "_in _let g = _fun (y)  \n"
                    "             y + 2\n"
                    "_in f(g) ")->interp(empty)->equals(NEW(numVal))(7)));

// 21
    CHECK(parse_str("_let f = _fun (g)\n"
                    "           g(5)\n"
                    "_in f(_fun (y)\n"
                    "        y + 2)")->interp(empty)->equals(NEW(numVal))(7)));

// 22
    CHECK(parse_str("_let f = _fun (x)\n"
                    "           _fun (y)\n"
                    "x+ y _in (f(5))(1) ")->interp(empty)->equals(NEW(numVal))(6)));

// 23
    CHECK(parse_str("_let f = _fun (x)\n"
                    "           _fun (y)\n"
                    "x+ y _in f(5)(1) ")->interp(empty)->equals(NEW(numVal))(6)));

// 24
    CHECK(parse_str("_let f = _fun (x)\n"
                    "           _fun (g)\n"
                    "             g(x + 1)\n"
                    "_in _let g = _fun (y)\n"
                    "              y+ 2 \n"
                    "_in (f(5))(g) ")->interp(empty)->equals(NEW(numVal))(8)));

// 25
    CHECK(parse_str("_let f = _fun (x)\n"
                    "           _fun (g)\n"
                    "             g(x + 1)\n"
                    "_in _let g = _fun (y)\n"
                    "y+ 2 _in f(5)(g)")->interp(empty)->equals(NEW(numVal))(8)));

// 26
    CHECK(parse_str("_let f = _fun (f)\n"
                    "           _fun (x)\n"
                    "             _if x == 0\n"
                    "             _then 0\n"
                    "             _else x + f(f)(x + -1)\n"
                    "_in f(f)(3)")->interp(empty)->equals(NEW(numVal))(6)));
    CHECK(parse_str(
            "_let factrl = _fun (factrl) _fun (x) _if x == 1 _then 1 _else x * factrl(factrl)(x + -1) _in  factrl(factrl)(10)")->interp(
            empty)->to_string() == "3628800");

}


#endif //MSDSCRIPT_EXPTEST_H