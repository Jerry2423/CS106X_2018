/*
 * CS 106B/X Fractal Recursion Problems
 * This file contains the implementation for PlasmaColor.
 * 
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#include "plasmacolor.h"
#include <cctype>
#include <cmath>
#include <sstream>
#include "gmath.h"
#include "hashcode.h"
#include "random.h"
#include "gwindow.h"

PlasmaColor::PlasmaColor() {
    this->colorValue = randomReal(0.0, 1.0);
}

PlasmaColor::PlasmaColor(double colorValue) {
    this->colorValue = colorValue;
}

std::string PlasmaColor::toString() const {
    double red, green, blue = 0.0;

    // Red
    if (colorValue < 0.5) {
        red = colorValue * 2;
    } else {
        red = (1.0 - colorValue) * 2;
    }

    // Green
    if (colorValue >= 0.3 && colorValue < 0.8) {
        green = (colorValue - 0.3) * 2;
    } else if (colorValue < 0.3) {
        green = (0.3 - colorValue) * 2;
    } else {
        green = (1.3 - colorValue) * 2;
    }

    // Blue
    if (colorValue >= 0.5) {
        blue = (colorValue - 0.5) * 2;
    } else {
        blue = (0.5 - colorValue) * 2;
    }

    if (red > 1.0) red = 1.0;
    if (red < 0) red = 0;
    if (green > 1.0) green = 1.0;
    if (green < 0) green = 0;
    if (blue > 1.0) blue = 1.0;
    if (blue < 0) blue = 0;

    return convertRGBToColor((int)(red * 255), (int)(green * 255), (int)(blue * 255));
}

int PlasmaColor::toRGBColor() const {
    return convertColorToRGB(toString());
}

double PlasmaColor::getColorValue() const {
    return colorValue;
}

PlasmaColor operator +(const PlasmaColor& m, const PlasmaColor& n) {
    return PlasmaColor(m.colorValue + n.colorValue);
}

PlasmaColor operator +(const PlasmaColor& m, double n) {
    return PlasmaColor(m.colorValue + n);
}

PlasmaColor operator -(const PlasmaColor& m, const PlasmaColor& n) {
    return PlasmaColor(m.colorValue - n.colorValue);
}

PlasmaColor operator -(const PlasmaColor& m, double n) {
    return PlasmaColor(m.colorValue - n);
}

PlasmaColor operator /(const PlasmaColor& m, double n) {
    return PlasmaColor(m.colorValue / n);
}

std::ostream& operator <<(std::ostream& out, const PlasmaColor& c) {
    out << c.getColorValue();
    return out;
}
