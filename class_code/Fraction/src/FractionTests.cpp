#include "FractionTests.h"
#include "Fraction.h"

using namespace std;
ENABLE_TESTS();

/* At most how far off a double can be before being incorrect.
 * We need this because it's not always accurate to compare double
 * equality due to small amounts of imprecision.
 */
const double DOUBLE_ERROR_BUFFER = 0.000000001;

/* A default fraction should be 1/1. */
ADD_TEST("Default fraction") {
    Fraction frac;
    expect(frac.getNum() == 1);
    expect(frac.getDenom() == 1);
}

/* A custom denominator should match the constructor parameters */
ADD_TEST("Custom denominator") {
    Fraction frac(1, 2);
    expect(frac.getNum() == 1);
    expect(frac.getDenom() == 2);
}

/* A custom numerator should match the constructor parameters */
ADD_TEST("Custom numerator") {
    Fraction frac(2, 1);
    expect(frac.getNum() == 2);
    expect(frac.getDenom() == 1);
}

/* A custom numerator and denominator should match the constructor parameters */
ADD_TEST("Custom fraction (2/3)") {
    Fraction frac(2, 3);
    expect(frac.getNum() == 2);
    expect(frac.getDenom() == 3);
}

/* A fraction with a negative numerator */
ADD_TEST("Negative fraction (numerator)") {
    Fraction frac(-5, 6);
    expect(fabs(frac.decimal() - -5.0 / 6) < DOUBLE_ERROR_BUFFER);
}

/* A fraction with a negative denominator */
ADD_TEST("Negative fraction (denominator)") {
    Fraction frac(5, -6);
    expect(fabs(frac.decimal() - -5.0 / 6) < DOUBLE_ERROR_BUFFER);
}

/* A fraction with negative numerator and denominator should be positive */
ADD_TEST("Negative fraction (both)") {
    Fraction frac(-5, -6);
    expect(fabs(frac.decimal() - 5.0 / 6) < DOUBLE_ERROR_BUFFER);
}

/* A negative fraction that can be reduced */
ADD_TEST("Negative fraction (reduced)") {
    Fraction frac(-3, 6);
    expect(fabs(frac.decimal() - -0.5) < DOUBLE_ERROR_BUFFER);
}

/* Testing numerator > denominator */
ADD_TEST("Large fraction") {
    Fraction frac(7, 3);
    expect(frac.getNum() == 7);
    expect(frac.getDenom() == 3);
}

/* A custom fraction should be reduced if it can be */
ADD_TEST("Custom reducible fraction by 2 (4/6)") {
    Fraction frac(4, 6);
    expect(frac.getNum() == 2);
    expect(frac.getDenom() == 3);
}

/* A custom fraction should be reduced if it can be */
ADD_TEST("Custom reducible fraction by 3 (9/15)") {
    Fraction frac(9, 15);
    expect(frac.getNum() == 3);
    expect(frac.getDenom() == 5);
}

/* A custom fraction should be reduced if it can be */
ADD_TEST("Custom reducible fraction to 1") {
    Fraction frac(9, 9);
    expect(frac.getNum() == 1);
    expect(frac.getDenom() == 1);
}

/* A custom fraction should be reduced if it can be */
ADD_TEST("Custom reducible fraction to 0") {
    Fraction frac(0, 10);
    expect(frac.getNum() == 0);
    expect(frac.getDenom() == 1);
}

/* Correctly converting to a decimal */
ADD_TEST("2/3 to decimal") {
    Fraction frac(2, 3);
    double decimal = 2.0 / 3;
    expect(fabs(frac.decimal()  - decimal) < DOUBLE_ERROR_BUFFER);
}

/* Correctly converting to a decimal */
ADD_TEST("5/10 to decimal") {
    Fraction frac(5, 10);
    expect(frac.decimal() == 0.5);
}

/* Adding fractions (but not reducing) */
ADD_TEST("Add fractions") {
    Fraction frac1(2, 5);
    Fraction frac2(1, 5);
    Fraction sum = frac1 + frac2;
    expect(sum.getNum() == 3);
    expect(sum.getDenom() == 5);
}

/* Adding fractions and reducing the result */
ADD_TEST("Add fractions and reduce") {
    Fraction frac1(1, 10);
    Fraction frac2(7, 10);
    Fraction sum = frac1 + frac2;
    expect(sum.getNum() == 4);
    expect(sum.getDenom() == 5);
}

/* Adding fractions and reducing the result */
ADD_TEST("Add fractions and reduce to 1") {
    Fraction frac1(1, 10);
    Fraction frac2(9, 10);
    Fraction sum = frac1 + frac2;
    expect(sum.getNum() == 1);
    expect(sum.getDenom() == 1);
}

/* Multiplying fractions (but not reducing) */
ADD_TEST("Multiplying fractions") {
    Fraction frac1(3, 5);
    Fraction frac2(3, 4);
    Fraction product = frac1 * frac2;
    expect(product.getNum() == 9);
    expect(product.getDenom() == 20);
}

/* Multiplying fractions and reducing */
ADD_TEST("Multiplying fractions and reduce") {
    Fraction frac1(3, 5);
    Fraction frac2(2, 3);
    Fraction product = frac1 * frac2;
    expect(product.getNum() == 2);
    expect(product.getDenom() == 5);
}

/* Make sure the fraction is represented in a stream properly */
ADD_TEST("Fraction printout") {
    Fraction frac(2, 3);
    ostringstream stream;
    stream << frac;
    expect(stream.str() == "2/3");
}
