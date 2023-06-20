/*
 * File: humanpyramid.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file implements the human pyramid function for Homework 3.
 */

#include "humanpyramid.h"
#include <iostream>
#include "map.h"
#include "vector.h"

using namespace std;

int countAll = 0; //nononononono

/**
 * Given a human pyramid in which each person weighs exactly 200 pounds,
 * returns the weight on the back of the person at the specified row and
 * column in the human pyramid. Rows and columns are zero-indexed, so,
 * for example, weightOnBackOf(2, 0) would give the weight on the back of
 * the leftmost person in the third row of the pyramid.
 *
 * @param row The zero-indexed row of the person in the pyramid.
 * @param col The zero-indexed column of the person in the pyramid.
 * @return The weight on the back of that person.
 */
double weightOnBackOfHelper(int row, int col, Map<Vector<int>, double>& catche) {
    // [TODO: delete the lines below this one and fill this function in. ]
//    (void) row;
//    (void) col;
    countAll += 1;
    Vector<int> key ={row, col};
    if (catche.containsKey(key)){
        return catche[key];
    }
    if (row == 0 && col == 0) {
        return 0;
    } else {
        if (col == 0) {
            catche[key] = 100 + 0.5 * weightOnBackOfHelper(row - 1, 0, catche);
            return catche[key];
        } else if (col == row) {
            catche[key] = 100 + 0.5 * weightOnBackOfHelper(row - 1, col - 1, catche);
            return catche[key];
        } else {
            catche[key] = 200 + 0.5 * (weightOnBackOfHelper(row - 1, col - 1, catche) + weightOnBackOfHelper(row - 1, col, catche));
            return catche[key];
        }
    }
}

double weightOnBackOf(int row, int col) {
    // [TODO: delete the lines below this one and fill this function in. ]
    (void) row;
    (void) col;
    Map<Vector<int>, double> catche;
    double ans = weightOnBackOfHelper(row, col, catche);
    //cout << countAll << endl;
    return ans;
}

