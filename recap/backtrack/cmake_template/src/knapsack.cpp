#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

struct WeightObject {
    int weight;
    int value;
};

int fillKnapsackHelper(vector<WeightObject>& objects, int curr_weight, int value) {
    auto comp = [](WeightObject a, WeightObject b) {return a.weight < b.weight;};
    // don't forget the empty base case
    if (objects.empty() ||curr_weight < (std::min_element(objects.begin(), objects.end(),comp))->weight) {
        return value;
    } else {
        // get the last element of objects
        auto ob = objects[objects.size()-1];
        objects.pop_back();
        //check include?
        int i_value = 0;
        if (ob.weight <= curr_weight) {
            //if so: put ob into bag and explore
            i_value = fillKnapsackHelper(objects, curr_weight-ob.weight, value+ob.value);
            //record include value i_value
        }
        //try exclude and explore
        int e_value = fillKnapsackHelper(objects, curr_weight, value);
        //record exclude value e_value
        //unchoose
        objects.push_back(ob);
        //return the max(i_value, e_value)
        return std::max(i_value, e_value);


    }
}

int fillKnapsack(vector<WeightObject>& objects, int target_weight) {
    return fillKnapsackHelper(objects, target_weight, 0);
}

int main() {
//    vector<WeightObject> v {{4, 12}, {6, 9}, {1, 7}, {3, 14}, {7, 11}, {5, 8}, {6, 10}};
    vector<WeightObject> v {{95,55}, {4, 10}, {60, 47}, {32, 5}, {23, 4}, {72, 50}, {80, 8}, {62, 61}, {65, 85}, {46, 87}};
    std::cout << fillKnapsack(v, 269) << std::endl;
    return 0;
}
