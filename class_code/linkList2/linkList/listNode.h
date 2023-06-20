#ifndef LISTNODE_H
#define LISTNODE_H


template<typename T>
struct ListNode
{
    T data;
    ListNode* next;
    ListNode(T data, ListNode* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

#endif // LISTNODE_H
