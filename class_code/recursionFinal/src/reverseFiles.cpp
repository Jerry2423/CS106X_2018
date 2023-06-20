#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "recursion.h"
using namespace std;

void reverseFile(ifstream& input);

int mainReverse() {
    ifstream input;
    input.open("readme.txt");
    reverseFile(input);
    return 0;
}

void reverseFile(ifstream &input) {
    string line;
    /* the following can be rewritten: implicit base case
    if (!getline(input, line)) {
        //do nothing
        // base case
    } else {
        reverseFile(input);
        cout << line << endl;
    }
    */
    /*
     * if (x) {
     *  do nothing
     * } else {
           do something
        }
     */
    /*same as:
     * if (not x) { do something }
     */
    if (getline(input, line)) {
        reverseFile(input); //recursive case
        cout << line << endl;
    }
}
