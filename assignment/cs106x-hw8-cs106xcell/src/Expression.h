// This is the .h file that you will turn in (TODO: replace this comment!)

#pragma once

#include <string>
#include "CellRange.h"
#include "map.h"
#include "set.h"
using std::string;

#define RANGE_IMPLEMENTED true

// forward declarations
class ExpressionParser;
class CS106XCellModel;
class Expression;
class CompoundExp;
class DoubleExp;
class IdentifierExp;
class TextStringExp;
class RangeExp;

/**
 * This enumerated type is used to differentiate the five different
 * expression types.
 */
enum ExpressionType {COMPOUND, DOUBLE, IDENTIFIER, TEXTSTRING, RANGE};

/**
 * This parent class is used to represent a node in an expression tree.
 * Expression itself is an "abstract" class, which means that there are
 * never any objects whose actual type is Expression.  All objects are
 * instead created using one of five concrete subclasses:
 *
 *  1. DoubleExp     -- a numeric constant                  (such as 3.14 or 42)
 *  2. TextStringExp -- a text string constant              (such as "hello")
 *  3. IdentifierExp -- a string representing an identifier (such as "A5")
 *  4. CompoundExp   -- two expressions combined by an operator  (such as "B1+A2")
 *  5. RangeExp      -- (FOR YOU TO IMPLEMENT) a range of cells whose values are aggregated by a function (such as "SUM(B2:B5)")
 *
 * The Expression class defines the interface common to all expressions;
 * each subclass provides its own implementation of the common interface.
 */
class Expression {
public:
    /**
     * Specifies the constructor for the base Expression class.  Each subclass
     * constructor will define its own constructor.
     */
    Expression();

    /**
     * The destructor deallocates the storage for this expression.  This method
     * must be declared virtual to ensure that the correct subclass destructor
     * is called when deleting an expression.
     */
    virtual ~Expression();

    /**
     * Evaluates this expression and returns its value in the context of
     * the specified map of existing cell values.
     * Also caches the value internally so that subsequent calls of getValue()
     * will return it without recalculating the value.
     */
    virtual double eval(const Map<std::string, double>& cellValues) = 0;

    /**
     * Returns the raw text that was passed in to parse this expression,
     * such as "=A2+SUM(B1:B6)*5".
     * This value will be an empty string unless this expression is the root
     * of the overall expression tree.
     */
    virtual std::string getRawText() const;

    /**
     * Returns the type of the expression, which must be one of the constants
     * COMPOUND, DOUBLE, RANGE, IDENTIFIER, or TEXTSTRING.
     */
    virtual ExpressionType getType() const = 0;

    /**
     * Returns the calculated value of this expression *without* re-calculating it.
     * If you have never called eval() on this expression before, this function
     * will return 0.0.
     * If you call eval(), the value calculated by eval will be saved in this
     * expression and returned from future calls to getValue.
     */
    virtual double getValue() const;

    /**
     * Returns true if this expression represents a formula that must be calculated.
     * A formula can be a reference to another cell (such as "=A2") or a more
     * complex expression involving operators (such as "=A2+B1-SUM(C4:C7)").
     * A single number is not considered a formula, even if it is entered starting with "="
     * (e.g. "=2" is not a formula).
     */
    virtual bool isFormula() const = 0;

    /**
     * Returns a string representation of this expression.
     */
    virtual std::string toString() const = 0;

private:
    std::string rawText;
    double value;

    /**
     * Sets the raw text stored in this expression.
     * Called by Parser.
     */
    virtual void setRawText(const std::string& rawText);

    /**
     * Sets the value stored in this expression.
     * Called internally by eval().
     */
    virtual void setValue(double value);

    // allows the subclasses to call setValue, but not other client code
    friend class CompoundExp;
    friend class DoubleExp;
    friend class IdentifierExp;
    friend class TextStringExp;
    friend class ExpressionParser;
    friend class RangeExp;
};


class RangeExp : public Expression {
public:
    // constructor
    RangeExp(const string& func_name, const CellRange& range);

    // eval
    virtual double eval(const Map<std::string, double>& cellValues);

    // return type
    virtual ExpressionType getType() const;

    // isFormula
    virtual bool isFormula() const;

    // toString
    virtual string toString() const;

    // getFunction() const
    string getFunction() const;

    // getRange() const
    CellRange getRange() const;

private:
    string func_name;
    CellRange range;
};

/**
 * COMPOUND
 * --------
 * This subclass represents a compound expression consisting of
 * two subexpressions joined by an operator.
 */
class CompoundExp : public Expression {
public:
    /**
     * The constructor initializes a new compound expression composed of
     * the operator (op) and the left and right subexpression (lhs and rhs).
     */
    CompoundExp(const std::string& op, Expression* lhs, Expression* rhs);

    /** Frees the memory for this expression and its sub-expressions. */
    virtual ~CompoundExp();

    /** Returns the evaluated result of applying the operator to the left and right operands. */
    virtual double eval(const Map<std::string, double>& cellValues);

    /** Returns COMPOUND. */
    virtual ExpressionType getType() const;

    /** Returns true. */
    virtual bool isFormula() const;

    /** Returns a parenthesized version of this expression, such as "(A1 + B2)". */
    virtual std::string toString() const;

    /** Returns the left-hand-side subexpression of a compound expression. */
    const Expression* getLeft() const;

    /** Returns the operator used in a compound expression. */
    std::string getOperator() const;

    /** Returns the right-hand-side subexpression of a compound expression. */
    const Expression* getRight() const;

private:
    std::string op;    // the operator string (+, -, *, /)
    Expression* lhs;
    Expression* rhs;   // the left and right subexpression

    /* set of all operators that can appear in a compound expression (e.g. "+", "-") */
    static Set<std::string> KNOWN_OPERATORS;
};


/**
 * DOUBLE
 * --------
 * This subclass represents a numeric constant.
 */
class DoubleExp : public Expression {
public:
    /** The constructor creates a new integer constant expression. */
    DoubleExp(double value);

    /** Just returns the double's value itself. */
    virtual double eval(const Map<std::string, double>& cellValues);

    /** Returns DOUBLE. */
    virtual ExpressionType getType() const;

    /** Returns false. */
    virtual bool isFormula() const;

    /** Returns the real number as a string, such as "3.14" or "42". */
    virtual std::string toString() const;
};


/**
 * IDENTIFIER
 * --------
 * This subclass represents an identifier used as a variable name, such as "A2".
 */
class IdentifierExp : public Expression {
public:
    /** The constructor creates an identifier expression with the specified name. */
    IdentifierExp(const std::string& name);

    /** Returns the value of the referred cell by checking in the map. */
    virtual double eval(const Map<std::string, double>& cellValues);

    /** Returns IDENTIFIER. */
    virtual ExpressionType getType() const;

    /** Returns true. */
    virtual bool isFormula() const;

    /** Returns the identifier such as "A2". */
    virtual std::string toString() const;

private:
    std::string name;   // the name of the identifier
};


/**
 * TEXTSTRING
 * --------
 * This subclass represents a text string constant.
 */
class TextStringExp : public Expression {
public:
    /** The constructor creates a new text string constant expression. */
    TextStringExp(const std::string& str);

    /** Returns 0.0 because strings have no numeric value. */
    double eval(const Map<std::string, double>& cellValues);

    /** Returns false. */
    virtual bool isFormula() const;

    /** Returns TEXTSTRING. */
    ExpressionType getType() const;

    /** Returns the string passed to the constructor. */
    std::string toString() const;

private:
    std::string str;   // the value of the text string constant
};

/**
 * Prints the given expression out to the given output stream.
 */
std::ostream& operator <<(std::ostream& out, const Expression& expr);
