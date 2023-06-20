#include <iostream>
#include "Fraction.h"

/* Constructor: Fraction()
 * -----------------------
 * Creates a new fraction that represents 1/1.
 */
Fraction::Fraction() {
    num = 1;
    denom = 1;
}

/* Constructor: Fraction(num, denom)
 * ---------------------------------
 * Creates a new fraction that represents num/denom.
 * Reduces the fraction if possible by finding the GCD.
 */
Fraction::Fraction(int num, int denom) {
    this->num = num;
    this->denom = denom;

    // reduce in case we were given
    // an unreduced fraction
    reduce();
}

/* getNum()
 * ---------
 * Returns the numerator (simplified) of this fraction.
 */
int Fraction::getNum() {
    return num;
}

/* getDenom()
 * ----------
 * Returns the denominator (simplified) of this fraction.
 */
int Fraction::getDenom() {
    return denom;
}

/* decimal()
 * ---------
 * Returns the decimal representation of the fraction.
 */
double Fraction::decimal() {
    return (double)num / denom;
}

/* reduce()
 * ---------
 * Reduces the function to the lowest possible terms
 * by finding the GCD of the fraction.
 */
void Fraction::reduce() {
    // find the greatest common divisor
    int frac_gcd = gcd(num,denom);

    // reduce by dividing num and denom by the gcd
    num = num / frac_gcd;
    denom = denom / frac_gcd;
}

/* gcd(u, v)
 * ---------
 * Recursively calculates the greatest common divisor
 * of the two given numbers.
 */
int Fraction::gcd(int u, int v) {
    if (v != 0) {
        return gcd(v, u%v);
    } else {
        return u;
    }
}

/* Override * to allow fractions to be multiplied together. */
Fraction Fraction::operator*(const Fraction &second) {
    int newNum = num * second.num;
    int newDenom = denom * second.denom;

    return Fraction(newNum, newDenom); // will be reduced automatically
}

/* Override + to allow fractions to be added together. */
Fraction Fraction::operator +(const Fraction& second) {
    int newNum = num * second.denom + second.num * denom;
    int newDenom = denom * second.denom;

    return Fraction(newNum, newDenom); // will be reduced automatically
}

/* Override << to allow outputting to a stream (e.g. cout) */
ostream& operator<<(ostream& out, Fraction &frac) {
    out << frac.num << "/" << frac.denom;
    return out;
}

