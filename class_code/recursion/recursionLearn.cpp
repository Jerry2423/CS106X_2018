#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

bool isPalindrome(string s) {
    if (s.size() <= 1) {
        return true;
    } else {
        return s[0] == s[s.size()-1] && isPalindrome(s.substr(1, s.size()-2));
    }
}

int mainPal()
{
    string s;
    cin >> s;
    cout << isPalindrome(s) << endl;
    return 0;
}




/* * * * * * Test Cases * * * * * */

