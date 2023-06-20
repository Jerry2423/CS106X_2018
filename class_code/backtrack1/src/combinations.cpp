#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
using namespace std;

string uniqueStr(string s);
void combinations(string s, int k);
void combinationsHelper(string s, int k, string comb = "");

int main() {
    combinations(uniqueStr("GOOGLE"), 3);
    return 0;
}

void combinationsHelper(string s, int k, string comb) {
    if (comb.size() == k) {
        cout << comb << endl;
    } else {
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            string newStr = s.substr(0, i) + s.substr(i+1);
            combinationsHelper(newStr, k, comb+ch);
        }
    }
}

void combinations(string s, int k) {
    combinationsHelper(s, k);
}

string uniqueStr(string s) {
    Set<char> letters;
    for (char c : s) {
        letters.add(c);
    }
    string uniqueString = "";
    for (char c : letters)
        uniqueString += c;
    return uniqueString;
}
