#pragma once

/**
 * A type representing a single node that could be used to assemble a singly-linked list.
 */
template <typename T> 
struct ListNode {
    T data;           // element stored in each node
    ListNode* next;   // pointer to the next node (nullptr if none)

    /** Define a constructor to more easily create new ListNodes. **/
    ListNode(const T& d = 0, ListNode* n = nullptr) {
        data = d;
        next = n;
    }
};
