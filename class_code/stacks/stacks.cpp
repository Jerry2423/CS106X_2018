#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "stack.h"
using namespace std;
//note: no indexes for stack and queue
// use of stack: reversal related LIFO: bottom -> top 最后进来的最先就要出去、被调用
bool isPalindrome(string s);

int main()
{
    string s = "abb";
    cout << isPalindrome(s) << endl;

    return 0;
}

bool isPalindrome(string s) {
    Stack<char> reversedChar;
    for (char c: s)
        reversedChar.push(c);
    string reversedWord = "";
    // idiom of stack: pop each element until the stack is empty
    while (!reversedChar.isEmpty()) {
        reversedWord += reversedChar.pop();
    }
    return reversedWord == s;
}


/* * * * * * Test Cases * * * * * */

