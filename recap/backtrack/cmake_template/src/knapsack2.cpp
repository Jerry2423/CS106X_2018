#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

struct WeightObject {
    int weight;
    int value;
};

int fillKnapsackHelper(vector<WeightObject>& objects, int curr_weight) {
    if (objects.empty() || curr_weight == 0) {
        return 0;
    } else {
        auto ob = objects[objects.size()-1];
        objects.pop_back();
        int i_value = 0;
        if (ob.weight <= curr_weight) {
            i_value = ob.value + fillKnapsackHelper(objects, curr_weight - ob.weight);
        }
        int e_value = fillKnapsackHelper(objects, curr_weight);
        objects.push_back(ob);
        return std::max(i_value, e_value);
    }
}

int fillKnapsack(vector<WeightObject>& objects, int target_weight) {
    return fillKnapsackHelper(objects, target_weight);
}


int main() {
    vector<WeightObject> v {{4, 12}, {6, 9}, {1, 7}, {3, 14}, {7, 11}, {5, 8}, {6, 10}};
    // vector<WeightObject> v {{95,55}, {4, 10}, {60, 47}, {32, 5}, {23, 4}, {72, 50}, {80, 8}, {62, 61}, {65, 85}, {46, 87}};
    std::cout << fillKnapsack(v, 18) << std::endl;
    return 0;
}
