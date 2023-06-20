#include<iostream>
#include<string>
#include<fstream>
#include"map.h"
#include"set.h"
#include"strlib.h"
using namespace std;

void sortLetters(string& s);
void swap(char& c1, char& c2);

int main() {
    string token;
    //sortLetters(s);
    //cout << s << endl;

    Map<string, Set<string>> anagrams, anagramsCopy; //nested ADTs
    ifstream inputFile;
    inputFile.open("lover.txt");
    while (inputFile >> token) {
        token = toLowerCase(token);
        string tokenCopy = token;
        sortLetters(token);
//        if (!anagrams.containsKey(token)){
//            anagrams[token].add(tokenCopy);
//        } else
//            anagrams[token].add(tokenCopy);
        anagrams[token].add(tokenCopy);
    }
    //cout << anagrams << endl;
    inputFile.close();
    //anagramsCopy = anagrams;
    for (string key: anagrams.keys()) {
        if (anagrams[key].size() <= 1)
            anagrams.remove(key);
    }
    //cout << anagrams << endl;

    while (true) {
        cout << "enter a word" << endl;
        string s;
        cin >> s;
        s = toLowerCase(s);
        sortLetters(s);
        if (!anagrams.containsKey(s))
            cout << "DNE" << endl;
        else
            cout << anagrams[s] << endl;
    }
    return 0;
}

void swap(char& c1, char& c2) {
    char temp = c1;
    c1 = c2;
    c2 = temp;
}

void sortLetters(string& s) {
    s = toLowerCase(s);
    for (int i = 0; i < s.size() - 1; i++)
        for (int j = i + 1; j < s.size(); j++) {
            if (s[i] > s[j])
                swap(s[i], s[j]);
        }
}

