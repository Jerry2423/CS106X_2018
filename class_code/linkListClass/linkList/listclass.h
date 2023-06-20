#ifndef LISTCLASS_H
#define LISTCLASS_H
#include "listNode.h"
#include "vector.h"
#include <iostream>
using namespace std;

class ListClass
{
public:
    ListClass();
    ~ListClass();

    void add(int data);
    void vectorToList(Vector<int>& v);
    int get(int index) const;
    void clear(ListNode<int>* front);
    void insert(int index, int data);
    bool isEmpty() const;
    void remove(int index);
    void toString() const;


    int size() const;
    //friend ostream& operator <<(ostream& out, const ListClass<T>& list);


private:
    ListNode<int>* front;
    int currSize;

};

//template<typename T>
//ostream& operator <<(ostream& out, const ListClass<T>& list);

//#include "listclass.cpp"
#endif // LISTCLASS_H
