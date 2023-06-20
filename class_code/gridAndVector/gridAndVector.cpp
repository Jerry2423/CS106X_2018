#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "grid.h"
using namespace std;


int main()
{
    Grid<int> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    matrix.fill(10);
    for (int i = 0; i < matrix.numRows(); i++) {
        for (int j = 0; j < matrix.numCols(); j++) matrix[i][j] += i + j;
    }
    cout << matrix << endl;
    return 0;
}




/* * * * * * Test Cases * * * * * */

