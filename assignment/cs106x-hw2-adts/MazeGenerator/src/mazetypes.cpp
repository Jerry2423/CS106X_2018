/**
 * File: maze-types.cpp
 * --------------------
 * Provides the bodies of functions for the Cell and Wall types.
 * See maze-types.h for the declarations of the types and functions.
 *
 * @author Jerry Cain, with modifications by Marty Stepp
 * @version 2016/10/07
 * - 16au 106X initial version
 */

#include "mazetypes.h"
#include <iomanip>
#include <sstream>

// Having to write all this crap just to have minimally usable objects
// is the ultimate proof that C++ needs to die in a fire.

std::string Cell::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

int hashCode(const Cell& cell) {
    int code = hashSeed();
    code = code * hashMultiplier() + hashCode(cell.row);
    code = code * hashMultiplier() + hashCode(cell.col);
    return int(code & hashMask());
}

static int compare(const Cell& one, const Cell& two) {
    return (one.row < two.row) ? -1 : (one.row > two.row) ? 1 :
           (one.col < two.col) ? -1 : (one.col > two.col) ? 1 : 0;
}

bool operator <(const Cell& one, const Cell& two) {
    return compare(one, two) < 0;
}

bool operator <=(const Cell& one, const Cell& two) {
    return compare(one, two) <= 0;
}

bool operator >(const Cell& one, const Cell& two) {
    return compare(one, two) > 0;
}

bool operator >=(const Cell& one, const Cell& two) {
    return compare(one, two) >= 0;
}

bool operator ==(const Cell& one, const Cell& two) {
    return compare(one, two) == 0;
}

bool operator !=(const Cell& one, const Cell& two) {
    return compare(one, two) != 0;
}

std::ostream& operator <<(std::ostream& out, const Cell& cell) {
    out << "{r" << std::setw(2) << std::setfill('0') << cell.row
        << " c" << std::setw(2) << std::setfill('0') << cell.col << "}";
    return out;
}

std::string Wall::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

int hashCode(const Wall& wall) {
    int code = hashSeed();
    code = code * hashMultiplier() + hashCode(wall.one);
    code = code * hashMultiplier() + hashCode(wall.two);
    return int(code & hashMask());
}

static int compare(const Wall& one, const Wall& two) {
    return (one.one < two.one) ? -1 : (one.one > two.one) ? 1 :
           (one.two < two.two) ? -1 : (one.two > two.two) ? 1 : 0;
}

bool operator <(const Wall& one, const Wall& two) {
    return compare(one, two) < 0;
}

bool operator <=(const Wall& one, const Wall& two) {
    return compare(one, two) < 0;
}

bool operator >(const Wall& one, const Wall& two) {
    return compare(one, two) < 0;
}

bool operator >=(const Wall& one, const Wall& two) {
    return compare(one, two) < 0;
}

bool operator ==(const Wall& one, const Wall& two) {
    return compare(one, two) == 0;
}

bool operator !=(const Wall& one, const Wall& two) {
    return compare(one, two) != 0;
}

std::ostream& operator <<(std::ostream& out, const Wall& wall) {
    out << "{" << wall.one << " - " << wall.two << "}";
    return out;
}
