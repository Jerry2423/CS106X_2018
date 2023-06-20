/*
 * CS 106X, Nick Troccoli
 * This header declares the ArrayStack class and its members.
 * A ArrayStack encapsulates the list methods from previous lectures
 * into an object that keeps track of the front of the list.
 * See ArrayStack.cpp for the implementation of the methods.
 */

#pragma once

#include <iostream>
using namespace std;

class ArrayStack {
public:
    /* Constructs a new empty stack. */
    ArrayStack();
    
    /* Destructor frees up memory allocated by the stack. */
    ~ArrayStack();

    // member functions (methods)
    
    /* Adds the given element on top of the stack. */
    void push(int n);
    
    /*
     * Removes and returns the top element from the stack.
     * Throws an error if the stack is empty.
     */
    int pop();
    
    /*
     * Returns the top element from the stack without removing it.
     * Throws an error if the stack is empty.
     */
    int peek() const;
    
    /* Returns true if the stack contains no elements, or false otherwise. */
    bool isEmpty() const;

    /* Returns a string representation of the given stack. */
    string toString() const;

private:
    // member variables (instance variables / fields)
    int* elements;
    int size;
    int capacity;
};

/* Prints the stack to the given output stream. */
ostream& operator <<(ostream& out, const ArrayStack& stack);
