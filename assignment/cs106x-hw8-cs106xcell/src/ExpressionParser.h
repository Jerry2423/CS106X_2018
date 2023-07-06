/**
  * CS106XCell, Autumn 2018
  *
  * File: ExpressionParser.h
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - rename
  **/

#pragma once

#include "Expression.h"
#include "CellRange.h"
#include "tokenscanner.h"
#include "CS106XCellUtil.h"

/** This class contains 1 public utility method to parse text into an Expression object. **/
class ExpressionParser {
public:
    /**
     * Function: parseExpression
     * Usage: Expression* exp = parseExpression(rawText);
     * -------------------------------------------
     * Parses a complete expression from the specified text,
     * making sure that there are no tokens un-processed.
     */
    static Expression* parseExpression(const std::string& rawText);

private:
    static bool readNegativeNumber(TokenScanner& scanner, const std::string& token, double& num);
    static Expression* readExpression(TokenScanner& scanner);
    static Expression* readFormula(TokenScanner& scanner, int prec = 0);
    static CellRange readRange(TokenScanner& scanner);
    static Expression* readTerm(TokenScanner& scanner);
    static int precedence(const std::string& token);
};
