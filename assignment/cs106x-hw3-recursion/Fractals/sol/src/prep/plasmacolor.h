/*
 * CS 106B/X Fractal Recursion Problems
 * This file contains the functionality provided by PlasmaColor.
 * 
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#ifndef _plasmacolor_h
#define _plasmacolor_h

#include <iostream>
#include <string>

class PlasmaColor {
public:
    /*
     * Constructs a new Plasma Color with a random color.
     */
    PlasmaColor();

    /*
     * Constructs a new Plasma Color with the given internal color value
     * between 0 and 1.0.
     */
    PlasmaColor(double colorValue);

    /*
     * Returns a string representation of this color,
     * in the form "#aarrggbb".
     */
    std::string toString() const;

    /*
     * Returns the underlying color value.
     * You should not need to use this function.
     */
    double getColorValue() const;

    /*
     * Returns an int representation of this color,
     * encoding the RGB values in a single int.
     */
    int toRGBColor() const;

    /*
     * Adds two colors and returns
     * the result as a new color.
     */
    friend PlasmaColor operator +(const PlasmaColor& m, const PlasmaColor& n);

    /*
     * Adds a decimal to a color and returns
     * the result as a new color.
     */
    friend PlasmaColor operator +(const PlasmaColor& m, double n);

    /*
     * Subtracts two colors and returns
     * the result as a new color.
     */
    friend PlasmaColor operator -(const PlasmaColor& m, const PlasmaColor& n);

    /*
     * Subtracts a decimal from a color and returns
     * the result as a new color.
     */
    friend PlasmaColor operator -(const PlasmaColor& m, double n);

    /*
     * Divides two colors and returns
     * the result as a new color.
     */
    friend PlasmaColor operator /(const PlasmaColor& m, const PlasmaColor& n);

    /*
     * Divides a color by a decimal and returns
     * the result as a new color.
     */
    friend PlasmaColor operator /(const PlasmaColor& m, double n);

private:
    double colorValue;   // float value between 0 and 1.0

    std::string calculateRGBColorString() const;
};

/*
 * Writes the color to an output stream.
 */
std::ostream& operator <<(std::ostream& out, const PlasmaColor& c);

#endif // _plasmacolor_h
