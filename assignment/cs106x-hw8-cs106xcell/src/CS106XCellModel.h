// This is the .h file that you will turn in (TODO: replace this comment!)

#pragma once

#include <iostream>
#include <string>
#include "Expression.h"
#include "basicgraph.h"
#include "observable.h"
#include "vector.h"

using namespace std;

class CS106XCellModel: public Observable<string> {
public:
    /**
     * Create a new model object that is initially empty.
    **/
    CS106XCellModel();

    /**
     * Frees any dynamically allocated memory.
     **/
    ~CS106XCellModel();

    /**
     * Clears all data for all cells in the model, representing an empty spreadsheet.
     **/
    void clear();

    /**
     * Clears all data for the existing cells and replaces it with data read in
     * from the specified spreadsheet file.  The file should be formatted such that
     * each line contains information on one cell, and it is formatted as
     *
     *      CELL_NAME CELL_VALUE
     *
     * For instance,
     *
     * A1 =2+2
     * A2 Hi
     *
     * Would be a file where A1 has value 4 (with formula 2+2) and A2 has value "Hi".
     */
    void load(istream& infile);

    /**
     * Saves the current cell states to file.  The file is formatted such that
     * each line contains information on one cell, and it is formatted as
     *
     *      CELL_NAME CELL_VALUE
     *
     * For instance,
     *
     * A1 =2+2
     * A2 Hi
     *
     * Would be a file where A1 has value 4 (with formula 2+2) and A2 has value "Hi".
     */
    void save(ostream& outfile) const;

    /**
     * Tells the model to update the stored text for the given cell name to be
     * the provided raw text.  The raw text must be parseable into a valid Expression
     * object - if not, an error is thrown.  The cellname must be a valid spreadsheet
     * cell (but may be either upper or lower case); otherwise an exception is thrown.
     * If the parameters are valid, it updates this cell's value, as well as all cells
     * that depend on this cell, and notifies its observers of any cell updates.
     **/
    void setCell(const string& cellname, const string& rawText);

    /**
     * Returns a pointer to the Expression object that represents this cell's value.
     * If this cell is invalid, or if it is empty, this method returns nullptr.
     * The cellname may be either upper or lower case.
     **/
    const Expression *getExpressionForCell(const string& cellname) const;

private:
    BasicGraphV<Expression*> cellGraph;
    Map<string, double> cache;
    // TODO: add any private members here
    void setDependency(const Expression* exp, const string& cell_name);     
    Vector<string>topSort() const;
};
