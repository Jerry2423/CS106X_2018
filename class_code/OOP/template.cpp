#include<iostream>
using namespace std;

template<typename T>
T max(T a, T b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}
