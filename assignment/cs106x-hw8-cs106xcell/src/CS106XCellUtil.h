/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellUtil.h
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - moved generic util functions to CS106XCellUtil
  **/

#include <string>
#include "set.h"

#pragma once

/** This class provides various static utility functions to convert cell names back
 * and forth with indices, and to handle the functions applied to ranges of cells.
 * These are static members, which means you call them like this:
 *
 *      bool isValid = CS106XCellUtil::isValidName(someName);
 **/
class CS106XCellUtil {
public:

    // Information about this application
    static const std::string APPLICATION_NAME;
    static const std::string APPLICATION_FILE_EXTENSION;

    /**
     * Returns true if the given name is a valid Excel-style name for a cell.
     * For example, "A17" or "BZF45" are valid cell names.
     */
    static bool isValidName(const std::string& cellname);

    /**
     * Converts the given 0-based row and columns into an Excel-style cell name.
     */
    static std::string toCellName(int row, int column);

    /**
     * Converts the given Excel-style cell name into a 0-based row and column,
     * setting both of the given integer output parameters by reference.
     * For example, passing "C7" sets row to 6 (7-1) and column to 2 ('A' + 2 -> 'C').
     * Returns true if successful and false if not.
     */
    static bool toRowColumn(const std::string& cellname, int& row, int& column);

    /**
     * Extracts the alphabetic column name from an Excel-style cell name such as "C7"
     * and converts it into a 0-based column index such as 2 for 'C'.
     * If the given string is not properly formatted, returns -1.
     */
    static int toColumn(const std::string& cellname);

    /**
     * Extracts the 1-based row number from an Excel-style cell name such as "C7"
     * and converts it into a 0-based row index such as 6.
     * If the given string is not properly formatted, returns -1.
     */
    static int toRow(const std::string& cellname);
};

