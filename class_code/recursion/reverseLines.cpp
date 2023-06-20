#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void reverseLines(ifstream& inputFile) {
    string line;
    if (!getline(inputFile, line)) {
        cout <<"";
    } else {
        //getline(inputFile, line);
        reverseLines(inputFile);
        cout << line << endl;
    }
}

int mainReverse() {
    ifstream inputFile;
    inputFile.open("file.txt");
    reverseLines(inputFile);
    return 0;
}
