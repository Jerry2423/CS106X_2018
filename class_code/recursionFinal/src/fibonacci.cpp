#include <iostream>
#include <string>
#include "console.h"
#include "recursion.h"
#include "map.h"
using namespace std;

int fibonacci(int i);
int fiboHelper(int i, Map<int, int>& catche);

int mainFib() {
    cout << fibonacci(7) << endl;
    //cout << fibonacci(-9) << endl;
    return 0;
}

//Wraper function which wraps a recursive function
int fibonacci(int i) {
    /*
    if (i <= 0) {
        throw "expect a positive input"; //precondition for a recursive function
    } else {
        if (i == 1 || i == 2)
            return 1;
        else
            return fibonacci(i-1) + fibonacci(i-2);
    }
    */
    Map<int, int> memoization;
    return fiboHelper(i, memoization);
}

//memoization method
int fiboHelper(int i, Map<int, int> &catche) {
    cout << recursionIndent() << "the" << i << "th fibo with memory " << catche << endl;
    if (i <= 2){
        return 1;
    } else if (catche.containsKey(i)) {
        return catche[i];
    } else {
        int result = fiboHelper(i-1, catche) + fiboHelper(i-2, catche);
        catche[i] = result;
        return result;
    }
}
