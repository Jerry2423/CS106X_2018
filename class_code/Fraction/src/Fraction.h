#pragma once

#include<ostream>
using namespace std;

/* Class: Fraction
 * ---------------
 * Represents a fraction with a numerator and denominator.
 * This class handles reducing the fraction (if applicable)
 * when it is created.  Supports negative fractions, but whether
 * the numerator or denominator is negative when accessed individually
 * is undefined.
 */
class Fraction {
public:
    /* Constructor: Fraction()
     * -----------------------
     * Creates a new fraction that represents 1/1.
     */
    Fraction();

    /* Constructor: Fraction(num, denom)
     * ---------------------------------
     * Creates a new fraction that represents num/denom.
     * Reduces the fraction if possible by finding the GCD.
     */
    Fraction(int num, int denom);

    /* getNum()
     * ---------
     * Returns the numerator (simplified) of this fraction.
     */
    int getNum();

    /* getDenom()
     * ----------
     * Returns the denominator (simplified) of this fraction.
     */
    int getDenom();

    /* decimal()
     * ---------
     * Returns the decimal representation of the fraction.
     */
    double decimal();

    /* Override * to allow fractions to be multiplied together. */
    Fraction operator*(const Fraction &second);

    /* Override + to allow fractions to be added together. */
    Fraction operator+(const Fraction &second);

    /* Override << to allow outputting to a stream (e.g. cout) */
    friend ostream& operator<<(ostream& out, Fraction &frac);
private:
    int num;   // the numerator
    int denom; // the denominator
    void reduce(); // reduce the fraction to lowest terms
    int gcd(int u, int v);
};
