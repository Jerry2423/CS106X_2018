#include<iostream>
#include<string>
#include "map.h"
#include "strlib.h"
#include<fstream>
using namespace std;

int mainWords() {
    ifstream inputFile;
    inputFile.open("lover.txt");
    if (inputFile.fail())
        return 0;
    string token;

    Map<string, int> countWords;
    while (inputFile >> token) {
        if (countWords.containsKey(toLowerCase(token)))
            countWords[token] += 1;
        else
            countWords[toLowerCase(token)] = 1;
    }
    inputFile.close();
    while (true) {
        cout << "look for a word ?" << endl;
        string s;
        cin >> s;
        if (countWords.containsKey(s))
            cout << countWords[s] << endl;
        else
            cout << "word not found" << endl;
    }
    return 0;
}
