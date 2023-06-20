#include <iostream>
#include <string>
#include "console.h"
#include "recursion.h"
using namespace std;

int evaluate(const string& exp);
int evaluateHelper(const string& exp, int& index);

int mainEval() {
    cout << evaluate("((1+3)+((1+2)*5))") << endl;
    return 0;
}

int evaluate(const string &exp) {
    int index = 0;
    return evaluateHelper(exp, index);
}

/*
 * ((1+3)+((1+2)*5))
 * (1+(2*4))
 *(2+2)
 *    ^
 *((1+(2+5)*3)*5)
 * ^
*/

int evaluateHelper(const string &exp, int& index) {
    cout << recursionIndent() << "evaluate exp = " << exp << "at index = " << index << endl; //debug trick: at the first line print the parameters
    if (isdigit(exp[index])) {
        int result = exp[index] - '0';
        index += 1;
        cout << recursionIndent() << "base return is " << result << endl;
        return result;
    } else { //if (exp[index] == '(') {
        index += 1;
        int left = evaluateHelper(exp, index);
        char op = exp[index];
        index += 1;
        int right = evaluateHelper(exp, index);
        index += 1;
        if (op == '+') {
            cout << recursionIndent() << "recur result is " << left + right << endl;
            return left + right;
        } else {
            cout << recursionIndent() << "recur result is " << left * right << endl;
            return left * right;
        }
    }
}
