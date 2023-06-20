#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"
#include "recursion.h"
#include "vector.h"
using namespace std;

//NOTE: This version of code is wrong!!!!
//Misunderstanding "each step's choice!"

struct WeightedObject
{
   int weight;
   int value;
};

int countCall = 0; // nonononononononono!~

int fillKnapsack(const Vector<WeightedObject>& objects, int targetWeight);
void fillKnapsackHelper(Vector<WeightedObject> &objects, int targetWeight, int weightSoFar, int& maxValue, Vector<WeightedObject> &inBag);
int min(Vector<WeightedObject>& objects);
int totalValue(Vector<WeightedObject>& objects);
//bool operator <(WeightedObject v1, WeightedObject v2);

int mainWrong() {
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
    cout << countCall << endl;
    return 0;
}

//bool operator <(WeightedObject v1, WeightedObject v2) {
//    return v1.weight < v2.weight;
//}

int min(Vector<WeightedObject>& objects) {
    if (objects.isEmpty()) {
        return 0;
    } else {
        int minWeight = objects[0].weight;
        for (WeightedObject item : objects) {
            if (item.weight < minWeight)
                minWeight = item.weight;
        }
        return minWeight;
    }
}

int totalValue(Vector<WeightedObject> &objects) {
    int total = 0;
    for (WeightedObject item : objects) {
        total += item.value;
    }
    return total;
}

//brute force algorithm
void fillKnapsackHelper(Vector<WeightedObject> &objects, int targetWeight, int weightSoFar, int& maxValue, Vector<WeightedObject> &inBag) {
    countCall += 1;
    if ((weightSoFar + min(objects) > targetWeight && weightSoFar <= targetWeight) || objects.isEmpty()) {
        //stop store min
        if (totalValue(objects) > maxValue)
            maxValue = totalValue(objects);
    } else {
        for (int i = 0; i < objects.size(); i++) { // this is wrong!!!! we need think "each step's" choices: include/exclude instead of considering all choices we hace in this problem!!
            WeightedObject item = objects[0];
            int minWeight = min(objects);
            objects.remove(0);
            if (weightSoFar + minWeight <= targetWeight) {
                inBag.add(item);
                fillKnapsackHelper(objects, targetWeight, weightSoFar+item.weight, maxValue, inBag);
                inBag.remove(inBag.size()-1);
            }
            fillKnapsackHelper(objects, targetWeight, weightSoFar, maxValue, inBag);
            objects.insert(0, item);
        }
    }
}

int fillKnapsack(const Vector<WeightedObject> &objects, int targetWeight) {
    Vector<WeightedObject> ob = objects;
    Vector<WeightedObject> inBag;
    int maxValue = -1;
    fillKnapsackHelper(ob, targetWeight, 0, maxValue, inBag);
    return maxValue;
}
