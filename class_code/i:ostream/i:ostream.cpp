#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

//Reading In A File

int main()
{
    ifstream fileInput;
    fileInput.open("poem.txt");
    string line;
    int lines = 0;
    while (getline(fileInput, line)) {
        cout << "The line says: " << line << endl;
        lines += 1;
    }
    cout << lines << endl;

    return 0;
}




/* * * * * * Test Cases * * * * * */

