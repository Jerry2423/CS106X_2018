#pragma once

#include <iostream>
#include "ListNode.h"
using namespace std;

/**
 * A type representing an ordered list of ints.  This class is implemented under the hood using
 * a singly-linked list.
 */
class LinkedListClass {
public:
    /**
     * Constructs a new empty list with zero elements.
     *
     * This function runs in time O(1).
     */
    LinkedListClass();

    /**
     * Frees all internal memory allocated by this structure.
     *
     * This function runs in time O(N).
     */
    ~LinkedListClass();

    /**
     * Returns the number of elements currently in the list
     *
     * This function runs in time O(1).
     *
     * @return list size
     */
    int size() const;

    /**
     * Returns a string representation of the list.
     * The string is a single line, with each element appearing
     * in list order, separated by a single space.  E.g.
     * "1 10 12 22".
     *
     * This function runs in time O(N).
     *
     * @return a string representation of this list
     */
    string toString() const;

    /**
     * Returns the element in the list at this index.
     * If the index is out of bounds, throws a string exception.
     *
     * This function runs in time O(N).
     *
     * @param index the index of the element to return
     * @return the element at this index
     */
    int get(int index) const;

    /**
     * Adds the element to the end of the list.
     *
     * This function runs in time O(N).
     *
     * @param value the value to add to the list
     */
    void add(int value);

    /**
     * Removes the element in the list at this index.
     * If the index is out of bounds, throws a string exception.
     *
     * This function runs in time O(N).
     *
     * @param index the index of the element to remove
     */
    void remove(int index);

    /**
     * Removes the element at the front of the list.
     * If the list is empty, throws a string exception.
     *
     * This function runs in time O(1).
     */
    void removeFront();

    /**
     * Inserts the element in the list at this index.
     * If the index is out of bounds, throws a string exception.
     *
     * This function should run in time O(N).
     *
     * @param index the index of the element to return
     * @param value the value to add to the list
     */
    void insert(int index, int value);

    /**
     * Removes all elements from the list.
     *
     * This function runs in time O(N).
     */
    void clear();

private:
    ListNode<int>* front;
    int currSize;
    void deleteListStartingAt(ListNode<int> *node);
};
