/*
 * CS 106B/X, Marty Stepp, Julie Zelenski
 * This instructor-provided file contains the implementation of the Board class,
 * used in the 8 Queens example.  We didn't write this code in class.
 * See Board.h for documentation of each member.
 */

#include "Board.h"
#include "gui.h"
#include "grid.h"

using namespace std;

Board::Board(int size) : _nplaced(0)
{
    if (size < 1) {
        throw size;
    }
    _board.resize(size, size);
    GUI::initialize(size);
}

bool Board::isOccupied(int row, int col) const
{
    return _board.inBounds(row, col) && _board[row][col];
}

bool Board::isSafe(int row, int col) const
{
    GUI::consider(row, col);

    for (int i = 0; i < _board.numRows(); i++) {
        if (isOccupied(i, col) ||  // other rows in this colum
            isOccupied(row, i) ||  // other cols in this row
            isOccupied(row + i, col + i) ||  // SE diag
            isOccupied(row - i, col - i) ||  // NW diag
            isOccupied(row - i, col + i) ||  // NE diag
            isOccupied(row + i, col - i))    // SW diag
        {
            if (col == _board.numCols() - 1) {
                GUI::backtrack(row, col);
            }
            return false;
        }
    }
    return true;
}

void Board::place(int row, int col)
{
    _board[row][col] = true;
    GUI::occupy(row, col);
    if (++_nplaced == _board.numRows()) {
        GUI::showSolution(_board);
    }
}

void Board::remove(int row, int col)
{
    _board[row][col] = false;
    GUI::leave(row, col);
    _nplaced--;
    if (col == _board.numCols() - 1) {
        GUI::backtrack(row, col);
    }
}

int Board::size() const
{
    return _board.numRows();
}
