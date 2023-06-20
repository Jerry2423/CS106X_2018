/*
 * CS 106X, Nick Troccoli
 * This file implements the bodies of the members of the LinkedListClass.
 * See LinkedListClass.h for the class declaration.
 */

#include "LinkedListClass.h"
#include <sstream>

using namespace std;


LinkedListClass::LinkedListClass() {
    front = nullptr;
    currSize = 0;
}


LinkedListClass::~LinkedListClass() {
    clear();
}


int LinkedListClass::size() const {
    return currSize;
}


string LinkedListClass::toString() const {
    if (front == nullptr) {
        return "(empty)";
    } else {
        ostringstream out;
        ListNode<int>* curr = front;
        while (curr != nullptr) {
            out << curr->data << " ";
            curr = curr->next;
        }
        return out.str();
    }
}


int LinkedListClass::get(int index) const {
    if (index < 0 || index > size()) {
        throw "Index out of bounds";
    }

    ListNode<int>* curr = front;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}


void LinkedListClass::add(int value) {
    ListNode<int> *newNode = new ListNode<int>(value);
    if (front == nullptr) {
        front = newNode;
    } else {
        ListNode<int>* curr = front;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    currSize++;
}


void LinkedListClass::remove(int index) {
    if (index < 0 || index > size()) {
        throw "Index out of bounds";
    }

    if (index == 0) {
        removeFront();
    } else {
        ListNode<int>* curr = front;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }

        ListNode<int>* nodeToDelete = curr->next;
        curr->next = curr->next->next;
        delete nodeToDelete;
        currSize--;
    }
}


void LinkedListClass::removeFront() {
    if (front != nullptr) {
        ListNode<int> *nodeToDelete = front;
        front = front->next;
        delete nodeToDelete;
        currSize--;
    } else {
        throw "Cannot remove front of empty list :(";
    }
}



void LinkedListClass::insert(int index, int value) {
    if (index < 0 || index > size()) {
        throw "Index out of bounds";
    }

    if (index == 0) {
        front = new ListNode<int>(value, front);
    } else {
        ListNode<int> *curr = front;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }

        curr->next = new ListNode<int>(value, curr->next);
    }

    currSize++;
}


void LinkedListClass::clear() {
    deleteListStartingAt(front);
    front = nullptr;
    currSize = 0;
}

void LinkedListClass::deleteListStartingAt(ListNode<int> *node) {
    if (node == nullptr) return;
    deleteListStartingAt(node->next);
    delete node;
}
