#ifndef LISTCLASS_H
#define LISTCLASS_H
#include "listNode.h"
#include "vector.h"
#include <iostream>
using namespace std;

template<typename T>
class ListClass
{
public:
    ListClass();
    ~ListClass();

    void add(T data);
    void vectorToList(Vector<T>& v);
    //void clear(ListNode<T>* front);
    T get(int index) const;
    void insert(int index, T data);
    bool isEmpty() const;
    void remove(int index);
    void toString() const;

    int size() const;


private:
    ListNode<T>* front;
    int currSize;
    void clear(ListNode<T>* front);

};



#include "listclass.cpp"
#endif // LISTCLASS_H
