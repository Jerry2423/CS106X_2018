#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"
#include "recursion.h"
#include "vector.h"
using namespace std;

struct WeightedObject
{
   int weight;
   int value;
};

int fillKnapsack(Vector<WeightedObject>& objects, int targetWeight);

int main() {
    Vector<WeightedObject> v;
    WeightedObject item1 {6, 9};
    WeightedObject item2 {1, 7};
    WeightedObject item3 {3, 14};
    WeightedObject item4 {7, 11};
    WeightedObject item5 {5, 8};
    WeightedObject item6 {6, 10};
    WeightedObject item7 {4, 12};
    v.add(item1);v.add(item2);v.add(item3);v.add(item4);v.add(item5);v.add(item6);v.add(item7);
    //cout << totalValue(v) << endl;
    cout << fillKnapsack(v, 18) << endl;
    return 0;
}

// returns the greatest value with given objects and largeWeight
int fillKnapsack(Vector<WeightedObject> &objects, int targetWeight) {
    if (objects.isEmpty() || targetWeight <= 0) {
        return 0;
    } else {
        WeightedObject item = objects.removeBack();
        //no choose
        int best = fillKnapsack(objects, targetWeight); // if backtrack with a function that has return value, remember use a variable to store the value while using recursion for the rest.
        if (item.weight <= targetWeight) {
            //choose
            int choose = fillKnapsack(objects, targetWeight-item.weight) + item.value;
            best = max(best, choose);
        }
        //undo: after all choices had been tried.
        objects.add(item);
        return best;
    }
}
