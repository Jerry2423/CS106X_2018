#include <iostream>
#include <string>
#include <cmath>
#include "grid.h"
#include "console.h"
#include "SimpleTest.h"
using namespace std;


bool knightCanMove(const Grid<string> &board, int r1, int c1, int r2, int c2);

int main()
{
    Grid<string> board(8, 8);
    board[1][2] = "knight";
    cout << knightCanMove(board, 1, 2, 2, 4) << endl;
    return 0;
}


bool knightCanMove(const Grid<string> &board, int r1, int c1, int r2, int c2) {
    if (!board.inBounds(r1, c1) || !board.inBounds(r2, c2) || board[r1][c1] != "knight")
        return false;
    int d1 = abs(r1 - r2), d2 = abs(c1 - c2);
    if ((d1 == 2 && d2 == 1) || (d1 == 1 && d2 == 2))
        if (board.inBounds(r1, c1) && board.inBounds(r2, c2))
            return true;
    return false;
}

/*
bool knightCanMove(const Grid<int> &board, int r1, int c1, int r2, int c2) {
    int rows = board.numRows() - 1;
    int cols = board.numCols() - 1;
    Grid<int> move = {
        {1, 2},
        {-1, 2},
        {1, -2},
        {-1, -2},
        {-2, 1},
        {2, 1},
        {-2, -1},
        {2, -1}
    };
    for (int i = 0; i < move.numRows(); i++) {
        if (r1 + move[i][0] == r2 && c1 + move[i][1] == c2) return true;
    }
    return false;
}
*/



/* * * * * * Test Cases * * * * * */

