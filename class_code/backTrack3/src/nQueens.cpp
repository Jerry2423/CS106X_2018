#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"
#include "recursion.h"
#include "set.h"
using namespace std;

void nQueens(int n);

void nQueensHelper(int n, Grid<int>& board, Set<Grid<int>>& answers);

bool isSafe(Grid<int>& board, int row, int col);
bool isOccupy(Grid<int> board, int row, int col);
bool nQueensHelperSingle(int n, Grid<int> &board, int row);


int mainQueen() {
    nQueens(4);
    Grid<int> m (4, 4);
    m.fill(0);
    m[0][0] = 1;
    m[1][2] = 1;
    cout << isSafe(m, 3, 1);
    return 0;
}


bool isOccupy(Grid<int> board, int row, int col) {
    return board.inBounds(row, col) && board[row][col] != 0;
}

//检查row，col的位置能不能放，注意此时还没放，注意清晰函数的功能和问题的情景、precondition
bool isSafe(Grid<int>& board, int row, int col) {
    for (int i = 0; i < board.numRows(); i++) {
        if (isOccupy(board, i, col) || isOccupy(board, row, i) || isOccupy(board, row+i, col+i) || isOccupy(board, row+i, col-i)||
                isOccupy(board, row-i, col+i) || isOccupy(board, row-i, col-i)) {
            return false;
        }
    }
    return true;
}

 //to slow cannot get an answer:Brute force recursive
/*
void nQueensHelper(int n, Grid<int>& board, Set<Grid<int>>& answers) {
    //cout << recursionIndent() << n << board <<endl;
    if (n == 0) {
        if (!answers.contains(board)) {
            cout << board << endl;
            answers.add(board);
        }
    } else {
        for (int i = 0; i < board.numRows(); i++) {
            for (int j = 0; j < board.numCols(); j++) {
                if (isSafe(board, i, j)) {
                    board[i][j] = 1;

                    nQueensHelper(n-1, board, answers);
                    //cout << board << endl;
                    board[i][j] = 0;
                }
            }
        }
    }
}
*/

//limit our choice: each place in each line
void nQueensHelper(int n, Grid<int> &board, int row) {
    if (n == 0) {
        cout << board << endl;

    } else {
        for(int col = 0; col < board.numCols(); col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 1;
                nQueensHelper(n-1, board, row+1);
                board[row][col] = 0;
            }
        }
    }
}

// find single solution: if solution is found prints it and return true; if nosolution found return false
bool nQueensHelperSingle(int n, Grid<int> &board, int row) {
    if (n == 0) {
        cout << board << endl;
        //tell upper function not to recurse anymore 找到了答案要告诉上级

        return true;

    } else {
        for(int col = 0; col < board.numCols(); col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 1;
                //接受下级的返回值，找到了嘛？
                bool result = nQueensHelperSingle(n-1, board, row+1);
                //找到了就结束
                if (result)
                    return result;
                /*bug: even though this time is fail, we need to continue;
                 *if (result)
                 *  reutrn true;
                 *else //wrong
                 *  return false;
                 */
                board[row][col] = 0;
            }
        }
    }
    return false;
}

void nQueens(int n) {
    Grid<int> board (n, n);
    Set<Grid<int>> answers;
    board.fill(0);
    nQueensHelperSingle(n, board, 0);
}
