#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include <iostream>
using namespace std;

const int INITIAL_CAPACITY = 8;


class ArrayStack
{
public:
    ArrayStack();
    ~ArrayStack();

    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;

    friend ostream& operator <<(ostream& out, const ArrayStack& stack);

private:
    int* array;
    int size;
    int capacity;
};

#endif // ARRAYSTACK_H
