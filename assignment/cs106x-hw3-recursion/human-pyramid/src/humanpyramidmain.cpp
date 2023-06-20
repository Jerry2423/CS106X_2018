/*
 * CS106X Human Pyramid
 * This client program runs your human pyramid implementation.
 * You do not need to modify this file.
 * 
 * @author Nick Troccoli, Marty Stepp, Anton Apostolatos, Keith Schwarz
 * @version 2018
 * - modified for 18au x version
 * 
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "console.h"
#include "simpio.h"
#include "humanpyramid.h"
using namespace std;

// constants for Human Pyramids
const int PYRAMID_FIELD_WIDTH = 8;

// testing function prototype declarations
void test_humanPyramidDirect();
void test_humanPyramidRows();

int main() {
    cout << "CS106X Human Pyramid" << endl;
    while (true) {
        cout << endl;
        cout << "Choose an Option:" << endl;
        cout << " 1) Test 'Human Pyramids' on a specific input." << endl;
        cout << " 2) See 'Human Pyramids' weights for a small pyramid." << endl;
        cout << " 0) Quit" << endl;

        int choice = getInteger("Enter your choice: ");
        cout << endl;
        if (choice == 0)       { break; }
        else if (choice ==  1) { test_humanPyramidDirect(); }
        else if (choice ==  2) { test_humanPyramidRows(); }
    }

    cout << "Have a nice day!" << endl;
    return 0;
}

/*
 * Runs and tests your weightOnBackOf function.
 */
void test_humanPyramidDirect() {
    do {
        int row = getInteger("Row: ");
        int col;
        while (true) {
            col = getInteger("Col: ");
            if (col <= row && col >= 0) break;
            cout << "Invalid column size. Column has to be between 0 and # of rows, inclusive." << endl;
        }

        cout << "Weight: " << weightOnBackOf(row, col) << endl;
    } while (getYesOrNo("Another? (Y/N) "));
}

void test_humanPyramidRows() {
    do {
        int numRows;
        while (true) {
            numRows = getInteger("How many rows do you want to print out? ");
            if (numRows > 0) break;
            cout << "Please enter a positive integer." << endl;
        }

        cout << "Weight on each person's back:" << endl;
        for (int row = 0; row < numRows; row++) {
            /* Sacrificial ostringstream so that we don't mess up cout with our
             * manipulations.
             */
            ostringstream line;
            line << setprecision(3) << fixed;
            for (int col = 0; col <= row; col++) {
                line << setw(PYRAMID_FIELD_WIDTH) << weightOnBackOf(row, col) << " ";
            }

            cout << line.str() << endl;
        }
    } while (getYesOrNo("Another? (Y/N) "));
}



