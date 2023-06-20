/*
 * CS 106X, Nick Troccoli
 * This file implements the members of the ArrayStack class.
 * See ArrayStack.h for the declarations.
 */

#include "arraystack.h"
#include "error.h"
#include <sstream>

// The initial size of our internal array
const int INITIAL_CAPACITY = 8;

ArrayStack::ArrayStack() {
    size = 0;
    capacity = INITIAL_CAPACITY;
    elements = new int[capacity];
}

ArrayStack::~ArrayStack() {
    delete[] elements;
}

void ArrayStack::push(int n) {
    if (size >= capacity) {
        // resize to a larger array and move over existing elements
        int *biggerArray = new int[capacity * 2];
        for (int i = 0; i < size; i++) {
            biggerArray[i] =  elements[i];
        }

        delete[] elements;
        elements = biggerArray;
        capacity *= 2;
    }

    elements[size] = n;
    size++;
}

int ArrayStack::pop() {
    if (isEmpty()) {
        error("Cannot pop from empty stack");
        return -1;
    }

    // We don't need to zero out the element because it will
    // be overwritten on a future push().
    int elementToReturn = elements[size - 1];
    size--;
    return elementToReturn;
}

int ArrayStack::peek() const {
    if (isEmpty()) {
        error("Cannot peek empty stack");
        return -1;
    }
    return elements[size - 1];
}

bool ArrayStack::isEmpty() const {
    return size == 0;
}

string ArrayStack::toString() const {
    ostringstream out;
    out << "{";
    if (!isEmpty()) {
        out << elements[0];   // fencepost
        for (int i = 1; i < size; i++) {
            out << ", " << elements[i];
        }
    }
    out << "}";
    return out.str();
}

ostream& operator <<(ostream& out, const ArrayStack& stack) {
    out << stack.toString();
    return out;
}









