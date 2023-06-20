#include "arraystack.h"

ArrayStack::ArrayStack()
{
    size = 0;
    capacity = INITIAL_CAPACITY;
    array = new int[INITIAL_CAPACITY]();
}

ArrayStack::~ArrayStack() {
    delete[] array;
}

void ArrayStack::push(int value) {
    if (size >= capacity) {
        int *copy = new int[capacity*2];
        for (int i = 0; i < size; i++) {
            copy[i] = array[i];
        }
        delete[] array;
        array = copy;
        capacity *= 2;
    }
    array[size] = value;
    size += 1;
}
int ArrayStack::pop() {
    if (isEmpty()) {
        throw "the stack is empty";
    }
    int out = array[size-1];
    array[size-1] = 0;
    size -= 1;
    return out;

}
int ArrayStack::peek() const {
    if (isEmpty()) {
        throw "the stack is empty";
    }
    return array[size-1];
}
bool ArrayStack::isEmpty() const {
    return size == 0;
}

ostream& operator <<(ostream& out, const ArrayStack& stack) {
    out << "{";
    if (!stack.isEmpty()) {
        out << stack.array[0];
        for (int i = 1; i < stack.size; i++) {
            out << ", " << stack.array[i];
        }
    }
    out << "}";
    return out;
}
