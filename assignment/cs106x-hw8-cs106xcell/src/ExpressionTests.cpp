#include "ExpressionTests.h"
#include "Expression.h"
#include "CS106XCellModel.h"
#include "TestDriver.h"
#include "map.h"

using namespace std;
ENABLE_TESTS();

ADD_TEST("RangeExp") {
    RangeExp r("MIN", CellRange("A1", "C3"));
    expect(r.toString() == "MIN(A1:C3)");
}

// Tests that a double expression properly stores its value
ADD_TEST("DoubleExp initialization") {
    DoubleExp e(2);
    expect(e.getValue() == 2.0);
    expect(e.toString() == "2");
}

// Tests that a double expression evaluates to its original value
ADD_TEST("DoubleExp eval") {
    Map<string, double> evalMap;  // make an empty cell map for testing
    DoubleExp e(2);
    expect(e.eval(evalMap) == 2.0);
    expect(e.getValue() == 2.0);
}

ADD_TEST("RangeExp eval") {
    Map<string, double> evalMap {{"A1", 1}, {"A2", 3}, {"A3", 5}, {"B1", 2}, {"B2", 4}, {"B3", 6}};
    RangeExp e("sum", {"a1", "b3"});
    expect(e.eval(evalMap) == 21);
    expect(e.getValue() == 21);
}
ADD_TEST("CompoundExp eval") {
    Map<string, double> evalMap {{"A1", 1}, {"A2", 3}, {"A3", 5}, {"B1", 2}, {"B2", 4}, {"B3", 6}, {"C2", 10}};
    RangeExp* e = new RangeExp("sum", {"a1", "b3"});
    IdentifierExp* e1 = new IdentifierExp("c2");
    CompoundExp e2("*", e, e1);
    expect(e1->eval(evalMap) == 10);
    expect(e2.eval(evalMap) == 210);
    expect(e2.getValue() == 210);
    delete e;
    delete e1;
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */
