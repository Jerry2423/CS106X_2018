/*
 * File: grid.h
 * ------------
 * This file exports the <code>Grid</code> class, which offers a
 * convenient abstraction for representing a two-dimensional array.
 *
 * @version 2018/03/12
 * - added overloads that accept GridLocation: get, inBounds, locations, set, operator []
 * @version 2018/03/10
 * - added methods front, back, clear
 * @version 2017/11/14
 * - added iterator version checking support
 * @version 2017/10/18
 * - fix compiler warnings
 * @version 2016/12/09
 * - bug fix in resize method (credit to Liu Ren)
 * @version 2016/09/24
 * - refactored to use collections.h utility functions
 * - made member variables actually private (oops)
 * - added size() method
 * @version 2016/08/10
 * - added constructor support for std initializer_list usage, such as
 *   {{1, 2, 3}, {4, 5, 6}}
 * @version 2016/08/04
 * - fixed operator >> to not throw errors
 * @version 2015/07/05
 * - using global hashing functions rather than global variables
 * @version 2014/11/20
 * - minor bug fixes in member initializers
 * @version 2014/11/13
 * - added comparison operators <, >=, etc.
 * - added template hashCode function
 * @version 2014/10/10
 * - added resize(true) function with ability to retain old contents
 * - made ==, != operators const as they should be
 * - added comparison operators ==, !=
 * 2014/08/16
 * - added width, height functions; added mapAllColumnMajor
 * 2014/07/09
 * - changed checkGridIndexes range checking function into a private member
 *   function to avoid unused-function errors on some newer compilers
 */

#ifndef _grid_h
#define _grid_h

#include <initializer_list>
#include <iostream>
#include <string>
#include <sstream>
#include "collections.h"
#include "system/error.h"
#include "gridlocation.h"
#include "hashcode.h"
#include "util/random.h"
#include "util/strlib.h"
#include "vector.h"

/*
 * Class: Grid<ValueType>
 * ----------------------
 * This class stores an indexed, two-dimensional array.  The following code,
 * for example, creates an identity matrix of size <code>n</code>, in which
 * the elements are 1.0 along the main diagonal and 0.0 everywhere else:
 *
 *<pre>
 *    Grid&lt;double&gt; createIdentityMatrix(int n) {
 *       Grid&lt;double&gt; matrix(n, n);
 *       for (int i = 0; i &lt; n; i++) {
 *          matrix[i][i] = 1.0;
 *       }
 *       return matrix;
 *    }
 *</pre>
 */

template <typename ValueType>
class Grid {
public:
    /* Forward reference */
    class GridRow;
    class GridRowConst;

    /*
     * Constructor: Grid
     * Usage: Grid<ValueType> grid;
     *        Grid<ValueType> grid(nRows, nCols);
     * ------------------------------------------
     * Initializes a new grid.  The second form of the constructor is
     * more common and creates a grid with the specified number of rows
     * and columns.  Each element of the grid is initialized to the
     * default value for the type.  The default constructor creates an
     * empty grid for which the client must call <code>resize</code> to
     * set the dimensions.
     * The three-argument constructor also accepts an initial value and
     * fills every cell of the grid with that value.
     */
    Grid();
    Grid(int nRows, int nCols);
    Grid(int nRows, int nCols, const ValueType& value);

    /*
     * This constructor uses an initializer list to set up the grid.
     * Usage: Grid<int> grid {{1, 2, 3}, {4, 5, 6}};
     */
    Grid(std::initializer_list<std::initializer_list<ValueType> > list);

    /*
     * Destructor: ~Grid
     * -----------------
     * Frees any heap storage associated with this grid.
     */
    virtual ~Grid();
    
    /*
     * Method: back
     * Usage: ValueType value = grid.back();
     * -------------------------------------
     * Returns the last value in the grid in the order established by the
     * <code>foreach</code> macro.
     * This is equivalent to grid[numRows - 1][numCols - 1].
     * If the grid is empty, generates an error.
     */
    ValueType back() const;

    /*
     * Method: clear
     * Usage: grid.clear();
     * --------------------
     * Sets every value in the grid to its element type's default value.
     */
    void clear();

    /*
     * Method: equals
     * Usage: if (grid.equals(grid2)) ...
     * ----------------------------------
     * Returns <code>true</code> if this grid contains exactly the same
     * values as the given other grid.
     * Identical in behavior to the == operator.
     */
    bool equals(const Grid<ValueType>& grid2) const;
    
    /*
     * Method: fill
     * Usage: grid.fill(value);
     * ------------------------
     * Stores the given value in every cell of this grid.
     */
    void fill(const ValueType& value);

    /*
     * Method: front
     * Usage: ValueType value = grid.front();
     * --------------------------------------
     * Returns the first value in the grid in the order established by the
     * <code>foreach</code> macro.  This is equivalent to grid[0][0].
     * If the grid is empty, generates an error.
     */
    ValueType front() const;

    /*
     * Method: get
     * Usage: ValueType value = grid.get(row, col);
     * --------------------------------------------
     * Returns the element at the specified <code>row</code>/<code>col</code>
     * position in this grid.  This method signals an error if the
     * <code>row</code> and <code>col</code> arguments are outside
     * the grid boundaries.
     */
    ValueType get(int row, int col);
    const ValueType& get(int row, int col) const;
    ValueType get(const GridLocation& loc);
    const ValueType& get(const GridLocation& loc) const;

    /*
     * Method: height
     * Usage: int nRows = grid.height();
     * ---------------------------------
     * Returns the grid's height, that is, the number of rows in the grid.
     */
    int height() const;
    
    /*
     * Method: inBounds
     * Usage: if (grid.inBounds(row, col)) ...
     * ---------------------------------------
     * Returns <code>true</code> if the specified row and column position
     * is inside the bounds of the grid.
     */
    bool inBounds(int row, int col) const;
    bool inBounds(const GridLocation& loc) const;

    /*
     * Method: isEmpty
     * Usage: if (grid.isEmpty()) ...
     * ---------------------------------------
     * Returns <code>true</code> if the grid has 0 rows and/or 0 columns.
     */
    bool isEmpty() const;

    /*
     * Method: locations
     * Usage: for (GridLocation loc : grid.locations()) ...
     * ----------------------------------------------------
     * Returns a range of (row,col) locations found in this grid.
     * This allows a nice abstraction for looping over the 2D grid range
     * of indexes using a single for loop.
     * By default the locations are arranged in row-major order,
     * but if you pass the rowMajor parameter of false, the locations will be
     * returned in column-major order instead.
     */
    GridLocationRange locations(bool rowMajor = true) const;

    /*
     * Method: mapAll
     * Usage: grid.mapAll(fn);
     * -----------------------
     * Calls the specified function on each element of the grid.  The
     * elements are processed in <b><i>row-major order,</i></b> in which
     * all the elements of row 0 are processed, followed by the elements
     * in row 1, and so on.
     */
    void mapAll(void (*fn)(ValueType value)) const;
    void mapAll(void (*fn)(const ValueType& value)) const;

    template <typename FunctorType>
    void mapAll(FunctorType fn) const;

    /*
     * Method: mapAllColumnMajor
     * Usage: grid.mapAllColumnMajor(fn);
     * ----------------------------------
     * Calls the specified function on each element of the grid.  The
     * elements are processed in <b><i>column-major order,</i></b> in which
     * all the elements of column 0 are processed, followed by the elements
     * in column 1, and so on.
     */
    void mapAllColumnMajor(void (*fn)(ValueType value)) const;
    void mapAllColumnMajor(void (*fn)(const ValueType& value)) const;

    template <typename FunctorType>
    void mapAllColumnMajor(FunctorType fn) const;

    /*
     * Method: numCols
     * Usage: int nCols = grid.numCols();
     * ----------------------------------
     * Returns the number of columns in the grid.
     * This is equal to the grid's width.
     */
    int numCols() const;

    /*
     * Method: numRows
     * Usage: int nRows = grid.numRows();
     * ----------------------------------
     * Returns the number of rows in the grid.
     * This is equal to the grid's height.
     */
    int numRows() const;

    /*
     * Method: resize
     * Usage: grid.resize(nRows, nCols);
     * ---------------------------------
     * Reinitializes the grid to have the specified number of rows
     * and columns.  If the 'retain' parameter is true,
     * the previous grid contents are retained as much as possible.
     * If 'retain' is not passed or is false, any previous grid contents
     * are discarded.
     */
    void resize(int nRows, int nCols, bool retain = false);

    /*
     * Method: set
     * Usage: grid.set(row, col, value);
     * ---------------------------------
     * Replaces the element at the specified <code>row</code>/<code>col</code>
     * location in this grid with a new value.  This method signals an error
     * if the <code>row</code> and <code>col</code> arguments are outside
     * the grid boundaries.
     */
    void set(int row, int col, const ValueType& value);
    void set(const GridLocation& loc, const ValueType& value);

    /*
     * Method: size
     * Usage: int size = grid.size();
     * ------------------------------
     * Returns the total number of elements in the grid, which is equal to the
     * number of rows times the number of columns.
     */
    int size() const;

    /*
     * Method: toString
     * Usage: string str = grid.toString();
     * ------------------------------------
     * Converts the grid to a printable string representation.
     * The string returned is a 1-dimensional representation such as:
     * "{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}"
     */
    std::string toString() const;

    /*
     * Method: toString2D
     * Usage: string str = grid.toString2D();
     * --------------------------------------
     * Converts the grid to a printable string representation.
     * The string returned is a 2-dimensional representation such as:
     * "{{1, 2, 3},\n
     *   {4, 5, 6},\n
     *   {7, 8, 9}}"
     */
    std::string toString2D(
            std::string rowStart = "{",
            std::string rowEnd = "}",
            std::string colSeparator = ", ",
            std::string rowSeparator = ",\n ") const;

    /*
     * Method: width
     * Usage: int nCols = grid.width();
     * --------------------------------
     * Returns the grid's width, that is, the number of columns in the grid.
     */
    int width() const;


    /*
     * Operator: []
     * Usage:  grid[row][col]
     * ----------------------
     * Overloads <code>[]</code> to select elements from this grid.
     * This extension enables the use of traditional array notation to
     * get or set individual elements.  This method signals an error if
     * the <code>row</code> and <code>col</code> arguments are outside
     * the grid boundaries.
     */
    GridRow operator [](int row);
    const GridRowConst operator [](int row) const;
    ValueType& operator [](const GridLocation& loc);
    const ValueType& operator [](const GridLocation& loc) const;

    /*
     * Additional Grid operations
     * --------------------------
     * In addition to the methods listed in this interface, the Grid
     * class supports the following operations:
     *
     *   - Stream I/O using the << and >> operators
     *   - Deep copying for the copy constructor and assignment operator
     *   - Iteration using the range-based for statement and STL iterators
     *
     * The iteration forms process the grid in row-major order.
     */
    
    /*
     * Operator: ==
     * Usage: if (grid1 == grid2) ...
     * ------------------------------
     * Compares two grids for equality.
     */
    bool operator ==(const Grid& grid2) const;

    /*
     * Operator: !=
     * Usage: if (grid1 != grid2) ...
     * ------------------------------
     * Compares two grids for inequality.
     */
    bool operator !=(const Grid& grid2) const;
    
    /*
     * Operators: <, >, <=, >=
     * Usage: if (grid1 < grid2) ...
     * -----------------------------
     * Relational operators to compare two grids.
     * The <, >, <=, >= operators require that the ValueType has a < operator
     * so that the elements can be compared pairwise.
     */
    bool operator <(const Grid& grid2) const;
    bool operator <=(const Grid& grid2) const;
    bool operator >(const Grid& grid2) const;
    bool operator >=(const Grid& grid2) const;

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in the file is logically part    */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

    /*
     * Implementation notes: Grid data structure
     * -----------------------------------------
     * The Grid is internally managed as a dynamic array of elements.
     * The array itself is one-dimensional, the logical separation into
     * rows and columns is done by arithmetic computation.  The layout
     * is in row-major order, which is to say that the entire first row
     * is laid out contiguously, followed by the entire second row,
     * and so on.
     */

private:
    /* Instance variables */
    ValueType* elements;  /* A dynamic array of the elements   */
    int nRows;            /* The number of rows in the grid    */
    int nCols;            /* The number of columns in the grid */
    unsigned int m_version = 0;  // structure version for detecting invalid iterators

    /* Private method prototypes */

    /*
     * Throws an ErrorException if the given row/col are not within the range of
     * (0,0) through (rowMax-1,colMax-1) inclusive.
     * This is a consolidated error handler for all various Grid members that
     * accept index parameters.
     * The prefix parameter represents a text string to place at the start of
     * the error message, generally to help indicate which member threw the error.
     */
    void checkIndexes(int row, int col,
                      int rowMax, int colMax,
                      std::string prefix) const;
    int gridCompare(const Grid& grid2) const;

    /*
     * Hidden features
     * ---------------
     * The remainder of this file consists of the code required to
     * support deep copying and iteration.  Including these methods
     * in the public interface would make that interface more
     * difficult to understand for the average client.
     */

    /*
     * Deep copying support
     * --------------------
     * This copy constructor and operator= are defined to make a
     * deep copy, making it possible to pass/return grids by value
     * and assign from one grid to another.  The entire contents of
     * the grid, including all elements, are copied.  Each grid
     * element is copied from the original grid to the copy using
     * assignment (operator=).  Making copies is generally avoided
     * because of the expense and thus, grids are typically passed
     * by reference, however, when a copy is needed, these operations
     * are supported.
     */
    void deepCopy(const Grid& grid) {
        int n = grid.nRows * grid.nCols;
        elements = new ValueType[n];
        for (int i = 0; i < n; i++) {
            elements[i] = grid.elements[i];
        }
        nRows = grid.nRows;
        nCols = grid.nCols;
        m_version++;
    }

public:
    Grid& operator =(const Grid& src) {
        if (this != &src) {
            delete[] elements;
            deepCopy(src);
        }
        return *this;
    }

    Grid(const Grid& src) {
        deepCopy(src);
    }

    /*
     * Iterator support
     * ----------------
     * The classes in the StanfordCPPLib collection implement input
     * iterators so that they work symmetrically with respect to the
     * corresponding STL classes.
     */
    class iterator : public std::iterator<std::input_iterator_tag, ValueType> {
    public:
        iterator(const Grid* theGp, int theIndex)
                : gp(theGp),
                  index(theIndex),
                  itr_version(theGp->version()) {
            // empty
        }

        iterator(const iterator& it)
                : gp(it.gp),
                  index(it.index),
                  itr_version(it.itr_version) {
            // empty
        }

        iterator& operator ++() {
            stanfordcpplib::collections::checkVersion(*gp, *this);
            index++;
            return *this;
        }

        iterator operator ++(int) {
            stanfordcpplib::collections::checkVersion(*gp, *this);
            iterator copy(*this);
            operator++();
            return copy;
        }

        bool operator ==(const iterator& rhs) {
            return gp == rhs.gp && index == rhs.index;
        }

        bool operator !=(const iterator& rhs) {
            return !(*this == rhs);
        }

        ValueType& operator *() {
            stanfordcpplib::collections::checkVersion(*gp, *this);
            return gp->elements[index];
        }

        ValueType* operator ->() {
            stanfordcpplib::collections::checkVersion(*gp, *this);
            return &gp->elements[index];
        }

        unsigned int version() const {
            return itr_version;
        }

    private:
        const Grid* gp;
        int index;
        unsigned int itr_version;
    };

    iterator begin() const {
        return iterator(this, 0);
    }

    iterator end() const {
        return iterator(this, nRows * nCols);
    }

    /*
     * Returns the internal version of this collection.
     * This is used to check for invalid iterators and issue error messages.
     */
    unsigned int version() const;

    /*
     * Private class: Grid<ValType>::GridRow
     * -------------------------------------
     * This section of the code defines a nested class within the Grid template
     * that makes it possible to use traditional subscripting on Grid values.
     */
    class GridRow {
    public:
        GridRow() : gp(nullptr), row(0) {
            /* Empty */
        }

        ValueType& operator [](int col) {
            gp->checkIndexes(row, col, gp->nRows-1, gp->nCols-1, "operator [][]");
            gp->m_version++;
            return gp->elements[(row * gp->nCols) + col];
        }

        ValueType operator [](int col) const {
            gp->checkIndexes(row, col, gp->nRows-1, gp->nCols-1, "operator [][]");
            return gp->elements[(row * gp->nCols) + col];
        }

        int size() const {
            return gp->width();
        }

    private:
        GridRow(Grid* gridRef, int index) {
            gp = gridRef;
            row = index;
        }

        Grid* gp;
        int row;
        friend class Grid;
    };
    friend class GridRow;

    class GridRowConst {
    public:
        GridRowConst() : gp(nullptr), row(0) {
            /* Empty */
        }

        const ValueType operator [](int col) const {
            gp->checkIndexes(row, col, gp->nRows-1, gp->nCols-1, "operator [][]");
            return gp->elements[(row * gp->nCols) + col];
        }

        int size() const {
            return gp->width();
        }

    private:
        GridRowConst(Grid* const gridRef, int index) : gp(gridRef), row(index) {}

        const Grid* const gp;
        const int row;
        friend class Grid;
    };
    friend class GridRowConst;
};

template <typename ValueType>
Grid<ValueType>::Grid()
        : elements(nullptr),
          nRows(0),
          nCols(0) {
    // empty
}

template <typename ValueType>
Grid<ValueType>::Grid(int numRows, int numCols)
        : elements(nullptr),
          nRows(0),
          nCols(0) {
    resize(numRows, numCols);
}

template <typename ValueType>
Grid<ValueType>::Grid(int numRows, int numCols, const ValueType& value)
        : elements(nullptr),
          nRows(0),
          nCols(0) {
    resize(numRows, numCols);
    fill(value);
}

template <typename ValueType>
Grid<ValueType>::Grid(std::initializer_list<std::initializer_list<ValueType> > list)
        : elements(nullptr),
          nRows(0),
          nCols(0) {
    // create the grid at the proper size
    nRows = list.size();
    if (list.begin() != list.end()) {
        nCols = list.begin()->size();
    }
    resize(nRows, nCols);

    // copy the data from the initializer list into the Grid
    auto rowItr = list.begin();
    for (int row = 0; row < nRows; row++) {
        if ((int) rowItr->size() != nCols) {
            error("Grid::constructor: initializer list is not rectangular (must have same # cols in each row)");
        }
        auto colItr = rowItr->begin();
        for (int col = 0; col < nCols; col++) {
            set(row, col, *colItr);
            colItr++;
        }
        rowItr++;
    }
}

template <typename ValueType>
Grid<ValueType>::~Grid() {
    if (elements) {
        delete[] elements;
        elements = nullptr;
    }
}

template <typename ValueType>
ValueType Grid<ValueType>::back() const {
    if (isEmpty()) {
        error("Grid::back: grid is empty");
    }
    return get(nRows - 1, nCols - 1);
}

template <typename ValueType>
void Grid<ValueType>::clear() {
    ValueType defaultValue = ValueType();
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            set(r, c, defaultValue);
        }
    }
}

template <typename ValueType>
bool Grid<ValueType>::equals(const Grid<ValueType>& grid2) const {
    // optimization: if literally same grid, stop
    if (this == &grid2) {
        return true;
    }
    
    if (nRows != grid2.nRows || nCols != grid2.nCols) {
        return false;
    }
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            if (get(row, col) != grid2.get(row, col)) {
                return false;
            }
        }
    }
    return true;
}

template <typename ValueType>
void Grid<ValueType>::fill(const ValueType& value) {
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            set(row, col, value);
        }
    }
}

template <typename ValueType>
ValueType Grid<ValueType>::front() const {
    if (isEmpty()) {
        error("Grid::front: grid is empty");
    }
    return get(0, 0);
}

template <typename ValueType>
ValueType Grid<ValueType>::get(int row, int col) {
    checkIndexes(row, col, nRows-1, nCols-1, "get");
    return elements[(row * nCols) + col];
}

template <typename ValueType>
const ValueType& Grid<ValueType>::get(int row, int col) const {
    checkIndexes(row, col, nRows-1, nCols-1, "get");
    return elements[(row * nCols) + col];
}

template <typename ValueType>
ValueType Grid<ValueType>::get(const GridLocation& loc) {
    return get(loc.row, loc.col);
}

template <typename ValueType>
const ValueType& Grid<ValueType>::get(const GridLocation& loc) const {
    return get(loc.row, loc.col);
}

template <typename ValueType>
int Grid<ValueType>::height() const {
    return nRows;
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
    return row >= 0 && col >= 0 && row < nRows && col < nCols;
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(const GridLocation& loc) const {
    return inBounds(loc.row, loc.col);
}

template <typename ValueType>
bool Grid<ValueType>::isEmpty() const {
    return nRows == 0 || nCols == 0;
}

template <typename ValueType>
GridLocationRange Grid<ValueType>::locations(bool rowMajor) const {
    return GridLocationRange(0, 0, numRows() - 1, numCols() - 1, rowMajor);
}

template <typename ValueType>
void Grid<ValueType>::mapAll(void (*fn)(ValueType value)) const {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
void Grid<ValueType>::mapAll(void (*fn)(const ValueType& value)) const {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
template <typename FunctorType>
void Grid<ValueType>::mapAll(FunctorType fn) const {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
void Grid<ValueType>::mapAllColumnMajor(void (*fn)(ValueType value)) const {
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
void Grid<ValueType>::mapAllColumnMajor(void (*fn)(const ValueType& value)) const {
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
template <typename FunctorType>
void Grid<ValueType>::mapAllColumnMajor(FunctorType fn) const {
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
    return nCols;
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
    return nRows;
}

template <typename ValueType>
void Grid<ValueType>::resize(int numRows, int numCols, bool retain) {
    if (numRows < 0 || numCols < 0) {
        std::ostringstream out;
        out << "Grid::resize: Attempt to resize grid to invalid size ("
               << numRows << ", " << numCols << ")";
        error(out.str());
    }

    // optimization: don't do the resize if we are already that size
    if (numRows == this->nRows && numCols == this->nCols && retain) {
        return;
    }
    
    // save backup of old array/size
    ValueType* oldElements = this->elements;
    int oldnRows = this->nRows;
    int oldnCols = this->nCols;
    
    // create new empty array and set new size
    this->nRows = numRows;
    this->nCols = numCols;
    this->elements = new ValueType[numRows * numCols];
    
    // initialize to empty/default state
    ValueType value = ValueType();
    for (int i = 0; i < numRows * numCols; i++) {
        this->elements[i] = value;
    }
    
    // possibly retain old contents
    if (retain) {
        int minRows = oldnRows < numRows ? oldnRows : numRows;
        int minCols = oldnCols < numCols ? oldnCols : numCols;
        for (int row = 0; row < minRows; row++) {
            for (int col = 0; col < minCols; col++) {
                this->elements[(row * numCols) + col] = oldElements[(row * oldnCols) + col];
            }
        }
    }
    
    // free old array memory
    if (oldElements) {
        delete[] oldElements;
    }
    m_version++;
}

template <typename ValueType>
void Grid<ValueType>::set(int row, int col, const ValueType& value) {
    checkIndexes(row, col, nRows - 1, nCols - 1, "set");
    elements[(row * nCols) + col] = value;
    m_version++;
}

template <typename ValueType>
void Grid<ValueType>::set(const GridLocation& loc, const ValueType& value) {
    set(loc.row, loc.col, value);
}

template <typename ValueType>
int Grid<ValueType>::size() const {
    return nRows * nCols;
}

template <typename ValueType>
std::string Grid<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
unsigned int Grid<ValueType>::version() const {
    return m_version;
}

template <typename ValueType>
std::string Grid<ValueType>::toString2D(
        std::string rowStart, std::string rowEnd,
        std::string colSeparator, std::string rowSeparator) const {
    std::ostringstream os;
    os << rowStart;
    int nr = numRows();
    int nc = numCols();
    for (int i = 0; i < nr ; i++) {
        if (i > 0) {
            os << rowSeparator;
        }
        os << rowStart;
        for (int j = 0; j < nc; j++) {
            if (j > 0) {
                os << colSeparator;
            }
            writeGenericValue(os, get(i, j), /* forceQuotes */ true);
        }
        os << rowEnd;
    }
    os << rowEnd;
    return os.str();
}

template <typename ValueType>
int Grid<ValueType>::width() const {
    return nCols;
}

template <typename ValueType>
typename Grid<ValueType>::GridRow Grid<ValueType>::operator [](int row) {
    return GridRow(this, row);
}

template <typename ValueType>
ValueType& Grid<ValueType>::operator [](const GridLocation& loc) {
    checkIndexes(loc.row, loc.col, nRows-1, nCols-1, "operator []");
    return elements[(loc.row * nCols) + loc.col];
}

template <typename ValueType>
const typename Grid<ValueType>::GridRowConst
Grid<ValueType>::operator [](int row) const {
    return GridRowConst(const_cast<Grid*>(this), row);
}

template <typename ValueType>
const ValueType& Grid<ValueType>::operator [](const GridLocation& loc) const {
    checkIndexes(loc.row, loc.col, nRows-1, nCols-1, "operator []");
    return elements[(loc.row * nCols) + loc.col];
}

template <typename ValueType>
bool Grid<ValueType>::operator ==(const Grid& grid2) const {
    return equals(grid2);
}

template <typename ValueType>
bool Grid<ValueType>::operator !=(const Grid& grid2) const {
    return !equals(grid2);
}

template <typename ValueType>
bool Grid<ValueType>::operator <(const Grid& grid2) const {
    return gridCompare(grid2) < 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator <=(const Grid& grid2) const {
    return gridCompare(grid2) <= 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator >(const Grid& grid2) const {
    return gridCompare(grid2) > 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator >=(const Grid& grid2) const {
    return gridCompare(grid2) >= 0;
}

template <typename ValueType>
void Grid<ValueType>::checkIndexes(int row, int col,
                                   int rowMax, int colMax,
                                   std::string prefix) const {
    const int rowMin = 0;
    const int colMin = 0;
    if (row < rowMin || row > rowMax || col < colMin || col > colMax) {
        std::ostringstream out;
        out << "Grid::" << prefix << ": (" << row << ", " << col << ")"
            << " is outside of valid range [";
        if (rowMin < rowMax && colMin < colMax) {
            out << "(" << rowMin << ", " << colMin <<  ")..("
                << rowMax << ", " << colMax << ")";
        } else if (rowMin == rowMax && colMin == colMax) {
            out << "(" << rowMin << ", " << colMin <<  ")";
        } // else min > max, no range, empty grid
        out << "]";
        error(out.str());
    }
}

template <typename ValueType>
int Grid<ValueType>::gridCompare(const Grid& grid2) const {
    int h1 = height();
    int w1 = width();
    int h2 = grid2.height();
    int w2 = grid2.width();
    int rows = h1 > h2 ? h1 : h2;
    int cols = w1 > w2 ? w1 : w2;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (r >= h1) {
                return -1;
            } else if (r >= h2) {
                return 1;
            }
            
            if (c >= w1) {
                return -1;
            } else if (c >= w2) {
                return 1;
            }
            
            if (get(r, c) < grid2.get(r, c)) {
                return -1;
            } else if (grid2.get(r, c) < get(r, c)) {
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Implementation notes: << and >>
 * -------------------------------
 * The insertion and extraction operators use the template facilities in
 * strlib.h to read and write generic values in a way that treats strings
 * specially.
 */
template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const Grid<ValueType>& grid) {
    os << "{";
    int nRows = grid.numRows();
    int nCols = grid.numCols();
    for (int i = 0; i < nRows; i++) {
        if (i > 0) {
            os << ", ";
        }
        os << "{";
        for (int j = 0; j < nCols; j++) {
            if (j > 0) {
                os << ", ";
            }
            writeGenericValue(os, grid.get(i, j), /* forceQuotes */ true);
        }
        os << "}";
    }
    return os << "}";
}

template <typename ValueType>
std::istream& operator >>(std::istream& is, Grid<ValueType>& grid) {
    Vector<Vector<ValueType> > vec2d;
    if (!(is >> vec2d)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    int nRows = vec2d.size();
    int nCols = (nRows == 0) ? 0 : vec2d[0].size();
    grid.resize(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            grid[i][j] = vec2d[i][j];
        }
    }

    return is;
}

/*
 * Template hash function for grids.
 * Requires the element type in the Grid to have a hashCode function.
 */
template <typename T>
int hashCode(const Grid<T>& g) {
    return stanfordcpplib::collections::hashCodeCollection(g);
}

/*
 * Function: randomElement
 * Usage: element = randomElement(grid);
 * -------------------------------------
 * Returns a randomly chosen element of the given grid.
 * Throws an error if the grid is empty.
 */
template <typename T>
const T& randomElement(const Grid<T>& grid) {
    if (grid.isEmpty()) {
        error("randomElement: empty grid was passed");
    }

    int randomIndex = randomInteger(0, grid.size() - 1);
    int row = randomIndex / grid.numCols();
    int col = randomIndex % grid.numCols();
    return grid.get(row, col);
}

/*
 * Randomly rearranges the elements of the given grid.
 */
template <typename T>
void shuffle(Grid<T>& grid) {
    int rows = grid.numRows();
    int cols = grid.numCols();
    int length = rows * cols;
    for (int i = 0; i < length; i++) {
        int j = randomInteger(i, length - 1);
        if (i != j) {
            int r1 = i / cols;
            int c1 = i % cols;
            int r2 = j / cols;
            int c2 = j % cols;
            T temp = grid[r1][c1];
            grid[r1][c1] = grid[r2][c2];
            grid[r2][c2] = temp;
        }
    }
}

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#endif // _grid_h
