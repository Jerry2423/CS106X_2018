// This is the .cpp file that you will turn in (TODO: replace this comment!)

#include "Expression.h"
#include "CellRange.h"
#include "error.h"
#include "range.h"
#include "strlib.h"
#include "CS106XCellUtil.h"
#include "vector.h"

using namespace std;

/**
 * Implementation notes: Expression
 * --------------------------------
 * The Expression class itself implements only those methods that
 * are not designated as pure virtual.
 */
Expression::Expression()
    : rawText(""),
      value(0.0) {
    /* Empty */
}

Expression::~Expression() {
    /* Empty */
}

string Expression::getRawText() const {
    return rawText.empty() ? toString() : rawText;
}

double Expression::getValue() const {
    return value;
}

void Expression::setRawText(const string& rawText) {
    this->rawText = rawText;
}

void Expression::setValue(double value) {
    this->value = value;
}

/**
 * Implementation notes: CompoundExp
 * -------------------------------
 * The CompoundExp subclass represents an expression made up of a left and right
 * subexpression.
 */

Set<string> CompoundExp::KNOWN_OPERATORS {"+", "-", "*", "/"};

CompoundExp::CompoundExp(const string& op, Expression* lhs, Expression* rhs) {
    this->op = op;
    if (!lhs) {
        error("CompoundExp::constructor: null left sub-expression");
    }
    if (!rhs) {
        error("CompoundExp::constructor: null right sub-expression");
    }
    this->lhs = lhs;
    this->rhs = rhs;
}

CompoundExp::~CompoundExp() {
    delete lhs;
    delete rhs;
}

const Expression* CompoundExp::getLeft() const {
    return lhs;
}

string CompoundExp::getOperator() const {
    return op;
}

const Expression* CompoundExp::getRight() const {
    return rhs;
}

ExpressionType CompoundExp::getType() const {
    return COMPOUND;
}

string CompoundExp::toString() const {
    return '(' + lhs->toString() + op + rhs->toString() + ')';
}

bool CompoundExp::isFormula() const {
    return true;
}

double CompoundExp::eval(const Map<std::string, double>& cellValues) {
    (void)cellValues;
    if (op == "+") {
        setValue(lhs->eval(cellValues) + rhs->eval(cellValues));
        return lhs->eval(cellValues) + rhs->eval(cellValues);
    } else if (op == "-") {
        setValue(lhs->eval(cellValues) - rhs->eval(cellValues));
        return lhs->eval(cellValues) - rhs->eval(cellValues);
    } else if (op == "*") {
        setValue(lhs->eval(cellValues) * rhs->eval(cellValues));
        return lhs->eval(cellValues) * rhs->eval(cellValues);
    } else if (op == "/") {
        setValue(lhs->eval(cellValues) / rhs->eval(cellValues));
        return lhs->eval(cellValues) / rhs->eval(cellValues);
    } else {
        throw "invalid operator";
    }
    // TODO: remove the above lines and implement this
}

/**
 * Implementation notes: DoubleExp
 * -------------------------------
 * The DoubleExp subclass represents a numeric constant.
 */
DoubleExp::DoubleExp(double value) {
    setValue(value);
}

ExpressionType DoubleExp::getType() const {
    return DOUBLE;
}

string DoubleExp::toString() const {
    return realToString(value);
}

bool DoubleExp::isFormula() const {
    return false;
}

double DoubleExp::eval(const Map<std::string, double>& cellValues) {
    (void)cellValues;
    setValue(value);
    return value;
    // TODO: remove the above lines and implement this
}

/**
 * Implementation notes: IdentifierExp
 * -----------------------------------
 * The IdentifierExp subclass represents the name of another cell.
 */
IdentifierExp::IdentifierExp(const string& name) {
    this->name = name;
}

ExpressionType IdentifierExp::getType() const {
    return IDENTIFIER;
}

string IdentifierExp::toString() const {
    return name;
}

bool IdentifierExp::isFormula() const {
    return true;
}

double IdentifierExp::eval(const Map<std::string, double>& cellValues) {
    if (!CS106XCellUtil::isValidName(name)) {
        throw "invalid name!";
    }
    if (!cellValues.containsKey(name)) {
        setValue(0);
        return 0;
    }
    setValue(cellValues[toUpperCase(name)]);
    return cellValues[toUpperCase(name)];
    // TODO: remove the above lines and implement this
}

/**
 * Implementation notes: TextStringExp
 * -----------------------------------
 * The TextStringExp subclass represents a text string constant.
 */
TextStringExp::TextStringExp(const string& str) {
    this->str = str;
    setValue(0.0);
}

string TextStringExp::toString() const {
    return str;
}

ExpressionType TextStringExp::getType() const {
    return TEXTSTRING;
}

bool TextStringExp::isFormula() const {
    return false;
}

double TextStringExp::eval(const Map<std::string, double>& cellValues) {
    (void)cellValues;
    setValue(0);
    return 0.0;
}

ostream& operator <<(ostream& out, const Expression& expr) {
    out << expr.toString();
    return out;
}

RangeExp::RangeExp(const string& func_name, const CellRange& range) : func_name(func_name), range(range) {}


ExpressionType RangeExp::getType() const {
    return RANGE;
}

bool RangeExp::isFormula() const {
    return true;
}

string RangeExp::getFunction() const {
    return func_name;
}

// return value correct?
CellRange RangeExp::getRange() const {
    return range;
}

string RangeExp::toString() const {
    string s = "(";
    return func_name+s+range.toString()+")";
}

double RangeExp::eval(const Map<std::string, double> &cellValues) {
    if (!CellRange::isKnownFunctionName(toUpperCase(func_name))) { 
        throw "invalid function name";
    } else {
        Vector<double> values;
        for (const auto& i : range.getAllCellNames()) {
            // cout << "cell name:" << i << endl;
            values.push_back(cellValues[toUpperCase(i)]);
        }
        // cout << "value " << values << endl;
        string temp = toUpperCase(func_name);
        if (temp == "AVERAGE" || temp == "MEAN") {
            setValue(average(values));
            return average(values);
        } else if (temp == "MAX") {
            setValue(max(values));
            return max(values);
        } else if (temp == "MEDIAN") {
            setValue(median(values));
            return median(values); 
        } else if (temp == "MIN") {
            setValue(min(values));
            return min(values);
        } else if (temp == "PRODUCT") {
            setValue(product(values));
            return product(values);
        } else if (temp == "STDEV") {
            setValue(stdev(values));
            return stdev(values);
        } else {
            setValue(sum(values));
            return sum(values);
        }
    }
}
