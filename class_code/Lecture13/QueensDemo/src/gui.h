/*
 * CS 106B/X, Marty Stepp, Julie Zelenski
 * This file declares the GUI for 8 Queens demo.
 */
#ifndef _gui_h
#define _gui_h

#include "gwindow.h"
#include "grid.h"
using namespace std;

namespace GUI {

void initialize(int dimension);
void consider(int row, int col);
void occupy(int row, int col);
void leave(int row, int col);
void backtrack(int row, int col);
void showSolution(Grid<bool> &board);

} // end namespace

#endif
