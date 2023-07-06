/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellUtil.cpp
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - moved generic util functions to CS106XCellUtil
  **/

#include "CS106XCellUtil.h"
#include "error.h"
#include "strlib.h"

const std::string CS106XCellUtil::APPLICATION_NAME = "CS106XCell";
const std::string CS106XCellUtil::APPLICATION_FILE_EXTENSION = ".xcell";

/** CELL NAME CHECKING AND CONVERSION **/

bool CS106XCellUtil::isValidName(const std::string& cellname) {
    int row, col;
    return toRowColumn(cellname, row, col);
}

std::string CS106XCellUtil::toCellName(int row, int column) {
    if (row < 0 || column < 0) {
        error("CS106XCellUtil::toCellName: row/column cannot be negative");
    }

    // convert column into a roughly base-26 Excel column name,
    // e.g. 0 -> "A", 1 -> "B", 26 -> "AA", ...
    std::string colStr;
    int col = column + 1;   // 1-based
    while (col-- > 0) {
        colStr = charToString((char) ('A' + (col % 26))) + colStr;
        col /= 26;
    }
    std::string rowStr = integerToString(row + 1);
    return colStr + rowStr;
}

bool CS106XCellUtil::toRowColumn(const std::string& cellname, int& row, int& column) {
    int rowTemp = toRow(cellname);
    int colTemp = toColumn(cellname);
    if (rowTemp >= 0 && colTemp >= 0) {
        // fill in reference parameters
        row = rowTemp;
        column = colTemp;
        return true;
    } else {
        return false;
    }
}

int CS106XCellUtil::toColumn(const std::string& cellname) {
    // chomp out the row at end and keep only the column
    std::string colStr = trim(toUpperCase(cellname));
    while (!colStr.empty() && !isalpha(colStr[colStr.length() - 1])) {
        colStr.erase(colStr.length() - 1, 1);
    }
    if (colStr.empty() || !isalpha(colStr[0])) {
        return -1;
    }

    // convert alphabetic column letters into a roughly base-26 column index
    int colNum = 0;
    for (int i = 0; i < (int) colStr.length(); i++) {
        char ch = colStr[i];
        if (!isalpha(ch)) {
            return -1;
        } else {
            colNum = colNum * 26 + (ch - 'A' + 1);
        }
    }
    colNum--;   // convert 1-based to 0-based
    return colNum;
}

int CS106XCellUtil::toRow(const std::string& cellname) {
    // chomp out the column at start and keep only the row
    std::string rowStr = trim(toUpperCase(cellname));
    while (!rowStr.empty() && !isdigit(rowStr[0])) {
        rowStr.erase(0, 1);
    }
    if (stringIsInteger(rowStr)) {
        // convert 1-based to 0-based
        return stringToInteger(rowStr) - 1;
    } else {
        return -1;
    }
}
