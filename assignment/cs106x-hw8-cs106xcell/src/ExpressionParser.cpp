/**
  * CS106XCell, Autumn 2018
  *
  * File: ExpressionParser.cpp
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - rename
  **/

#include "ExpressionParser.h"
#include <iostream>
#include <string>
#include "error.h"
#include "set.h"
#include "strlib.h"
#include "tokenscanner.h"

// set to true to see debug messages related to parsing
static const bool DEBUG = false;

/**
 * Implementation notes: parseExpression
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */
Expression* ExpressionParser::parseExpression(const std::string& rawText) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.scanStrings();
    scanner.setInput(rawText);
    Expression* exp = readExpression(scanner);
    exp->setRawText(rawText);
    return exp;
}

/**
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */
int ExpressionParser::precedence(const std::string& token) {
    if (token == "+" || token == "-") {
        return 1;
    } else if (token == "*" || token == "/") {
        return 2;
    } else {
        return 0;
    }
}

/**
 * Implementation notes: readExpression
 * ------------------------------------
 * This function scans an overall cell expression.
 * An expression can be a number, a string, or a formula.
 */
Expression* ExpressionParser::readExpression(TokenScanner& scanner) {
    if (DEBUG) std::cout << "  readExpr(" << scanner << ")" << std::endl;
    std::string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (token == "=") {
        // beginning of a formula
        Expression* exp = readFormula(scanner);
        if (scanner.hasMoreTokens()) {
            error("Parse error: Unexpected token: \"" + scanner.nextToken() + "\"");
        }
        return exp;
    }
    if (type == OPERATOR && token == "-") {
        double num = 0.0;
        if (readNegativeNumber(scanner, token, num)) {
            return new DoubleExp(num);
        }
    }
    if (type == NUMBER && !scanner.hasMoreTokens()) {
        return new DoubleExp(stringToReal(token));
    } else {
        return new TextStringExp(trim(scanner.getInput()));
    }
}

/**
 * Implementation notes: readFormula
 * Usage: exp = readFormula(scanner, prec);
 * ----------------------------------------
 * This implementation uses precedence to resolve the ambiguity in
 * the grammar.  At each level, the parser reads operators and subexpressions
 * until it finds an operator whose precedence is greater than the prevailing
 * one.  When a higher-precedence operator is found, readE calls itself
 * recursively to read that subexpression as a unit.
 */
Expression* ExpressionParser::readFormula(TokenScanner& scanner, int prec) {
    if (DEBUG) std::cout << "  readForm(" << scanner << "), prec=" << prec << ")" << std::endl;
    Expression* exp = readTerm(scanner);
    std::string token;
    while (true) {
        // read operator
        token = scanner.nextToken();
        int tprec = precedence(token);
        if (tprec <= prec) {
            break;
        }

        if (!scanner.hasMoreTokens()) {
            error("Parse error: Invalid binary " + token
                  + " expression; missing right operand");
            exp = nullptr;
        } else {
            Expression* rhs = readFormula(scanner, tprec);
            exp = new CompoundExp(token, exp, rhs);
        }
    }
    scanner.saveToken(token);
    return exp;
}

// pre: Prev token is stored in 'token'.
// post: If prev token is '-' and followed directly by a number,
//       that negative number is stored in 'num' and true is returned.
//       Else, false is returned.
bool ExpressionParser::readNegativeNumber(TokenScanner& scanner, const std::string& token, double& num) {
    TokenType type = scanner.getTokenType(token);
    if (token == "-" && type == OPERATOR && scanner.hasMoreTokens()) {
        std::string token2 = scanner.nextToken();
        TokenType type2 = scanner.getTokenType(token2);
        if (type2 == NUMBER) {
            num = -stringToReal(token2);
            return true;
        } else {
            scanner.saveToken(token2);   // un-read
        }
    }
    return false;
}

/**
 * Implementation notes: readRange
 * Usage: exp = readRange(scanner);
 * --------------------------------
 * This function scans a range of cells, such as A1:A7.
 */
CellRange ExpressionParser::readRange(TokenScanner& scanner) {
    if (DEBUG) std::cout << "  readRange(" << scanner << ")" << std::endl;
    if (scanner.nextToken() != "(") {
        error("Parse error: Invalid range format; missing initial (.");
    }
    std::string startCellName = scanner.nextToken();
    if (!CS106XCellUtil::isValidName(startCellName)) {
        error("Parse error: Invalid start cell name for range: \"" + startCellName + "\"");
    }

    std::string sep = scanner.nextToken();
    if (sep != ":" && sep != "-") {
        error("Parse error: Invalid range format; missing : in middle.");
    }
    std::string endCellName = scanner.nextToken();
    if (!CS106XCellUtil::isValidName(endCellName)) {
        error("Parse error: Invalid end cell name for range: \"" + endCellName + "\"");
    }
    if (scanner.nextToken() != ")") {
        error("Parse error: Invalid range format; missing final ).");
    }

    CellRange range(startCellName, endCellName);
    return range;
}

/**
 * Implementation notes: readTerm
 * ------------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */
Expression* ExpressionParser::readTerm(TokenScanner& scanner) {
    if (DEBUG) std::cout << "readTerm(" << scanner << ")" << std::endl;
    std::string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    Expression* result = nullptr;
    if (token == "(") {
        // beginning of a parenthesized expression
        Expression* exp = readFormula(scanner);
        token = scanner.nextToken();
        if (token != ")") {
            error("Parse error: Unclosed parenthesis.");
        } else {
            result = exp;
        }
        return result;
    }
    if (type == OPERATOR && token == "-") {
        double num = 0.0;
        if (readNegativeNumber(scanner, token, num)) {
            return new DoubleExp(num);
        }
    }
    if (type == NUMBER) {
        result = new DoubleExp(stringToReal(token));
    } else if (type == WORD) {
        token = toUpperCase(token);
#if RANGE_IMPLEMENTED == true
        if (CellRange::isKnownFunctionName(token)) {
            result = new RangeExp(token, readRange(scanner));
        } else
#endif
        if (CS106XCellUtil::isValidName(token)) {
            result = new IdentifierExp(token);
        } else {
            error("Parse error: Invalid cell name or token: \"" + token + "\"");
        }
    } else {
        result = new TextStringExp(token);
    }
    return result;
}
