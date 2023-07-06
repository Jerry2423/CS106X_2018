#include "CS106XCellModelTests.h"
#include "CS106XCellModel.h"

using namespace std;
ENABLE_TESTS();

// A model should initially return nullptr for all cell expressions
ADD_TEST("Initially empty") {
    CS106XCellModel model;
    // Just pick a few expressions (non-exhaustive)
    expect(model.getExpressionForCell("A1") == nullptr);
    expect(model.getExpressionForCell("A2") == nullptr);
    expect(model.getExpressionForCell("B1") == nullptr);
    expect(model.getExpressionForCell("B2") == nullptr);
}

// A model should correctly parse and store a double cell expression
ADD_TEST("Set double cell") {
    CS106XCellModel model;
    model.setCell("A1", "2");
    const Expression *e = model.getExpressionForCell("A1");
    expect(e != nullptr);
    expect(e->getType() == DOUBLE);
    expect(e->getValue() == 2.0);
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */
