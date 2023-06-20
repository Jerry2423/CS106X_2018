#include<iostream>
#include<string>
#include"strlib.h"
using namespace std;

int evaluate(const string& exp);
int evalHelper(const string& exp, int& index);


int main() {
    cout << evaluate("(2+2)") << endl;
    cout << evaluate("(1+((2*3)+4))") << endl;
    cout << evaluate("((1+3)+((1+2)*5))") << endl;
    return 0;
}

/*
 *(2+2)
 *(1+(2+5)*3)
*/

int evaluate(const string &exp) {
    int index = 0;
    return evalHelper(exp, index);
}

/*
 *(2+2)
 *(1+(2+5)*3)
 *^
*/

int evalHelper(const string &exp,int& index) {
    cout << recursionIndent() << "eval helper exp = " << exp << ", index = " << index << endl;
    if (isdigit(exp[index])) {
       int result = exp[index] - '0';
       index += 1;
       cout << "base case result = " << result << endl;
       return result;
    } else { //if (exp[index] == '('){
        index += 1;
        //operand
        int left = evalHelper(exp, index);
        //operator
        char op = exp[index];
        index += 1;
        //operand
        int right = evalHelper(exp, index);
        index += 1; // skip )
        if (op == '+') {
            cout << "recur case return " << left + right << endl;
            return left + right;
        }
        else {
            cout << "recur case return " << left * right << endl;
            return left * right;
        }

    }
    //')'
    //'+, *'
}
