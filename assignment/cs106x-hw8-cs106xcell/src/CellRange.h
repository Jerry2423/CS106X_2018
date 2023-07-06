/**
  * CS106XCell, Autumn 2018
  *
  * File: CellRange.h
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - moved generic util functions to CS106XCellUtil
  **/

#pragma once

#include <iostream>
#include "set.h"
#include "vector.h"

/**
 * This struct can be used to identify a range. It represents 0-based
 * start/stop row and column values as locations.
 */
class CellRange {
public:
    /**
     * Constructs a range enclosing the given start and end cells and all
     * cells between them.  The cells are passed by 0-based row and column
     * indexes.
     */
    CellRange(int startRow = 0, int startCol = 0, int endRow = 0, int endCol = 0);

    /**
     * Constructs a range enclosing the given start and end cells and all
     * cells between them.  The cells are passed by Excel-style cell names
     * such as "A4" or "B17".
     */
    CellRange(const std::string& startCellName, const std::string& endCellName);

    /**
     * Returns a set containing the names of all cells in this range.
     * For example, if the range is B3:C5, returns the set containing
     * {"B3", "B4", "B5", "C3", "C4", "C5"}.
     */
    Set<std::string> getAllCellNames() const;

    /**
     * Returns the ending cell in the range as an Excel-style cell name
     * such as "A7". Note that you can just access the end row/column
     * directly using the member variables, but this is provided for
     * convenience in case you want the cell's name rather than the 0-based
     * indexes.
     */
    std::string getEndCellName() const;

    /**
     * Returns the 0-based column of the end of this range.
     * For example, if the range is C5:F7, returns 5
     * (which is the 0-based number for column F from "F7", the sixth column).
     */
    int getEndColumn() const;

    /**
     * Returns the 0-based row of the end of this range.
     * For example, if the range is C5:F7, returns 6
     * (which is the 1-based row 7 from "F7" minus 1 to make it 0-based).
     */
    int getEndRow() const;

    /**
     * Returns the starting cell in the range as an Excel-style cell name
     * such as "A4". Note that you can just access the start row/column
     * directly using the member variables, but this is provided for
     * convenience in case you want the cell's name rather than the 0-based
     * indexes.
     */
    std::string getStartCellName() const;

    /**
     * Returns the 0-based column of the start of this range.
     * For example, if the range is C5:F7, returns 2
     * (which is the 0-based number for column C from "C5", the third column).
     */
    int getStartColumn() const;

    /**
     * Returns the 0-based row of the end of this range.
     * For example, if the range is C5:F7, returns 4
     * (which is the 1-based row 5 from "C5" minus 1 to make it 0-based).
     */
    int getStartRow() const;

    /**
     * Returns a string representation of this range such as "A1:B7".
     */
    std::string toString() const;

    /**
     * Returns true if the given function name is one of the known names in
     * the FUNCTION_NAMES set declared in this class.  This is a static method,
     * which means you call it like this:
     *
     *      bool isKnown = CellRange::isKnownFunctionName(myFunctionName);
     */
    static bool isKnownFunctionName(const std::string& function);

private:
    // Excel-style cell names of start/end of this range (e.g. "A5" or "C7")
    std::string startCellName;
    std::string endCellName;

    /**
     * Returns true if the start row/col come before the end row/col
     * and all are non-negative.
     */
    bool isValid() const;

    // set of all known function names, in uppercase (such as "SUM" and "AVERAGE")
    static const Set<std::string> FUNCTION_NAMES;
};

std::ostream& operator <<(std::ostream& out, const CellRange& range);

/**
 * Implementation of built-in functions supported in cell formulas. Each
 * takes a vector of double values and returns the computed result.
 * These are free-floating functions, so if you import this file you can
 * just call the functions as you normally would, e.g.:
 *
 *      double avg = average(myValues);
 */
double average(const Vector<double>& values);
double sum(const Vector<double>& values);
double product(const Vector<double>& values);
double max(const Vector<double>& values);
double min(const Vector<double>& values);
double median(const Vector<double>& values);
double stdev(const Vector<double>& values);
