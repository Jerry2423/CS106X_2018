/*
 * CS 106B/X, Marty Stepp
 * This instructor-provided file contains the declaration of the Board class,
 * used in the 8 Queens example.  We didn't write this code in class.
 */

#ifndef _board_h
#define _board_h

#include <iostream>
#include <string>
#include "grid.h"
using namespace std;

class Board {
public:
    /*
     * Constructs a board of the given size (rows x columns).
     * Throws an integer exception if the size is less than 1.
     */
    Board(int size);

    /*
     * Returns true if it is safe to place a queen at the given row/column
     * position, meaning that no other existing queen can capture it.
     * Throws a string exception if the row or column is out of bounds of the board.
     */
    bool isSafe(int row, int col) const;

    /*
     * Places a queen at the given row/col position.
     * Does not check whether it is safe to do so; call isSafe or isValid for that.
     * Throws a string exception if the row or column is out of bounds of the board.
     */
    void place(int row, int col);

    /*
     * Un-places a queen from the given row/col position.
     * If there wasn't a queen there, has no effect.
     * Throws a string exception if the row or column is out of bounds of the board.
     */
    void remove(int row, int col);

    /*
     * Returns the board's size, its number of rows and columns.
     * A default chess board would have 8 rows and columns.
     */
    int size() const;

    /*
     * Show the solution on current board.
     */
    void showSolution() const;

private:
    Grid<bool> _board;     // grid of board squares  (true=queen, false=empty)
    int _nplaced;
    bool isOccupied(int row, int col) const;
};

#endif
