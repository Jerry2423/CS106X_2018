#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "vector.h"
#include "set.h"
#include "map.h"
#include <fstream>
using namespace std;

//bool contain(Vector<string> &words, string token);

int mainTotal()
{
    ifstream fileInput;
    fileInput.open("lover.txt");
    string token;
    //Vector<string> words; it takes almost 2min
    Set<string> words; //2s if we use set
    while (fileInput >> token) {
        words.add(token);
    }
    cout << words.size() << endl;
    cout << words.contains("hi");
    fileInput.close();

    return 0;
}

/*
bool contain(Vector<string> &words, string token) {
    for (int i = 0; i < words.size(); i++)
        if (words[i] == token)
            return true;
    return false;
}

*/


/* * * * * * Test Cases * * * * * */

