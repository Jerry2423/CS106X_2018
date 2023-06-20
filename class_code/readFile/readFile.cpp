#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include <fstream>
#include "filelib.h"
using namespace std;

//Reading In A File: open;read each line; close it

// stream always uses pass by reference
void outputData(ostream& output, string info, int n);
bool getYesOrNo(string prompt);

int main()
{
    ifstream inputFile;
    inputFile.open("poem.txt");
    /* Read lines
    if (inputFile.fail()) {
        cout << "error" << endl;
    } else {
        string line;
        int lines = 0;
        while (getline(inputFile, line)) {
            cout << "The line says " << line << endl;
            lines += 1;
        }
        cout << "total lines is " << lines << " lines" << endl;
    }
    */

    //Read word: tokenize input: looking for blank sapces and slice input between blank spaces
    /*
     *blank spaces: space linebreaks, tabs
    */
    /*Read words >>
    if (inputFile.fail()) {
        cout << "error" << endl;
    }else {
        string token;
        int words = 0;
        while (inputFile >> token) { //extraction operator >>
            cout << "the word is " << token << endl;
            words += 1;
        }
        cout << "total words is " << words << endl;
    }
    */

    //file output
    string s = "my string";
    int n = 4;
    // general output function, by using cout as output, we get console output.
    outputData(cout, s, n);

    if (getYesOrNo("Save to Files")) {
        ofstream outputFile;
        outputFile.open("poem.txt");
        outputData(outputFile, s, n);
        outputFile.close();
    }


    return 0;
}

bool getYesOrNo(string prompt) {
    cout << prompt << " (y for yes; n for no)" << endl;
    string s;
    cin >> s;
    if (s == "y") return true;
    else return false;
    return false;
}

void outputData(ostream &output, string info, int n) {
    output << info << endl << n << endl; // very similar to cout << ...;
}





/* * * * * * Test Cases * * * * * */

