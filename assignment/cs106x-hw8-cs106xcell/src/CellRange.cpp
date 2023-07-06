/**
  * CS106XCell, Autumn 2018
  *
  * File: CellRange.cpp
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - moved generic util functions to CS106XCellUtil
  **/

#include "CellRange.h"
#include <cmath>
#include <sstream>
#include "error.h"
#include "CS106XCellUtil.h"

// all functions allowed in a range expression
const Set<std::string> CellRange::FUNCTION_NAMES {
    "AVERAGE", "MAX", "MEAN", "MEDIAN", "MIN", "PRODUCT", "STDEV", "SUM"
};

CellRange::CellRange(int startRow, int startColumn, int endRow, int endColumn) {
    startCellName = CS106XCellUtil::toCellName(startRow, startColumn);
    endCellName = CS106XCellUtil::toCellName(endRow, endColumn);
    if (!CS106XCellUtil::isValidName(startCellName)) {
        error("invalid start cell name: " + startCellName);
    }
    if (!CS106XCellUtil::isValidName(endCellName)) {
        error("invalid end cell name: " + endCellName);
    }
    if (!isValid()) {
        error("invalid range: " + toString());
    }
}

CellRange::CellRange(const std::string& startCellName, const std::string& endCellName) :
        startCellName(startCellName),
        endCellName(endCellName) {
    if (!CS106XCellUtil::isValidName(startCellName)) {
        error("invalid start cell name: " + startCellName);
    }
    if (!CS106XCellUtil::isValidName(endCellName)) {
        error("invalid end cell name: " + endCellName);
    }
    if (!isValid()) {
        error("invalid range: " + toString());
    }
}

Set<std::string> CellRange::getAllCellNames() const {
    Set<std::string> cellnames;
    int startRow = getStartRow();
    int startCol = getStartColumn();
    int endRow = getEndRow();
    int endCol = getEndColumn();
    for (int row = startRow; row <= endRow; row++) {
        for (int col = startCol; col <= endCol; col++) {
            std::string cellname = CS106XCellUtil::toCellName(row, col);
            cellnames.add(cellname);
        }
    }
    return cellnames;
}

std::string CellRange::getEndCellName() const {
    return endCellName;
}

int CellRange::getEndColumn() const {
    int row, col;
    CS106XCellUtil::toRowColumn(endCellName, row, col);
    return col;
}

int CellRange::getEndRow() const {
    int row, col;
    CS106XCellUtil::toRowColumn(endCellName, row, col);
    return row;
}

std::string CellRange::getStartCellName() const {
    return startCellName;
}

int CellRange::getStartColumn() const {
    int row, col;
    CS106XCellUtil::toRowColumn(startCellName, row, col);
    return col;
}

int CellRange::getStartRow() const {
    int row, col;
    CS106XCellUtil::toRowColumn(startCellName, row, col);
    return row;
}

bool CellRange::isValid() const {
    int startRow, startCol, endRow, endCol;
    if (!CS106XCellUtil::toRowColumn(startCellName, startRow, startCol)
            || !CS106XCellUtil::toRowColumn(endCellName, endRow, endCol)) {
        return false;
    }
    return 0 <= startRow && startRow <= endRow
        && 0 <= startCol && startCol <= endCol;
}

std::string CellRange::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

std::ostream& operator <<(std::ostream& out, const CellRange& range) {
    return out << range.getStartCellName() << ":" << range.getEndCellName();
}

/** FUNCTION VERIFICATION AND IMPLEMENTATION **/

bool CellRange::isKnownFunctionName(const std::string& function) {
    return FUNCTION_NAMES.contains(toUpperCase(function));
}

double min(const Vector<double>& values) {
    double min = values[0];
    for (int i = 1; i < values.size(); i++) {
        if (values[i] < min) {
            min = values[i];
        }
    }
    return min;
}

double max(const Vector<double>& values) {
    double max = values[0];
    for (int i = 1; i < values.size(); i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    return max;
}

double sum(const Vector<double>& values) {
    double sum = 0;
    for (double n : values) {
        sum += n;
    }
    return sum;
}

double product(const Vector<double>& values) {
    double prod = 1;
    for (double n : values) {
        prod *= n;
    }
    return prod;
}

/* This function should be accessible by both name "mean" and "average" */
double average(const Vector<double>& values) {
    return sum(values) / values.size();
}

double median(const Vector<double>& values) {
    Vector<double> clone = values;
    sort(clone.begin(), clone.end());
    int sz = values.size();
    if (sz % 2 == 0) {
        return (clone[sz / 2] + clone[sz / 2 - 1]) / 2;
    } else {
        return clone[sz / 2];
    }
}

double stdev(const Vector<double>& values) {
    double sum = 0;
    double sumsquares = 0;
    for (double n : values) {
        sum += n;
        sumsquares += n * n;
    }
    int sz = values.size();
    return sqrt((sz * sumsquares - sum * sum) / (sz * sz));
}
