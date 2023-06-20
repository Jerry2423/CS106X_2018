 /*
 * CS 106B/X, Julie Zelenski
 *
 * This code contains code to solve the "8 Queens" problem on a chess board
 * using recursive backtracking.
 */

#include <iostream>
#include "Board.h"
#include "console.h"
using namespace std;

// function prototype declarations
bool solveQueens(Board& board, int row = 0);


/*
 * Searches the given chess board for a solution to the N Queens problem
 * of trying to place N queen pieces on a chess board without any of them
 * being able to capture each other.
 */
int main()
{
    Board board(8);
    solveQueens(board);
    return 0;
}

/*
 * Function: solveQueens
 * ---------------------
 * This function is the main entry in solving the N queens problem.
 * It takes the partially-filled board and the row index we are trying
 * to place a queen in. It will return a boolean value which indicates
 * whether or not we found a successful arrangement starting
 * from this configuration.
 *
 * Base case:  if there are no more queens to place,
 * then we have successfully solved the problem!
 *
 * Otherwise, we find a safe column in this row, place a queen at
 * (row,col) of the board and recursively call solveQueens starting
 * at the next row using this new board configuration.
 * If that solveQueens call fails, we will remove that queen from (row,col)
 * and try again with the next safe column within the row.
 * If we have tried all the columns in this row and did not
 * find a solution, then we return false, which then backtracks
 * out of this unsolvable partial configuration.
 *
 * The initial call to solveQueens should an empty board and
 * placing a queen in row 0.
 */

bool solveQueens(Board& board, int row)
{

}
