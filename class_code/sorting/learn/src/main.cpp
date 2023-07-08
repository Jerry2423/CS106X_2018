#include <__bit_reference>
#include <iostream>
#include <queue>
#include <type_traits>
#include <vector>
#include "console.h"
#include "vector.h"
#include "queue.h"
using std::cout;
using std::endl;
using std::vector;

void selectionSort(Vector<int>& v) {
    for (int i = 0; i < v.size()-1; i++) {
        for (int j = i+1; j < v.size(); j++) {
            if (v[j] < v[i]) {
                std::swap(v[j], v[i]);
            }
        }
    }
}

void insertionSort(Vector<int>& v) {
    // i pointer pointing to the "to-insert" element and use temp to store the element
    for (int i = 0; i < v.size(); i++) {
        int temp = v[i];
        int j = i;
        // j pointer pointing to the new sublist where the first j-1 elements are sorted
        while (j > 0 && temp < v[j-1]) { // temp is less than its left element, then move the left element to the right(the left should be less than the right)
            // find a position for temp: move the element in (j-1) sublist to the right if it's bigger than temp
            // right<-left
            v[j] = v[j-1];
            j--;
        }
        // j is the position for temp, assign temp to it
        v[j] = temp;

    }

}

void mergeSort(Vector<int>& v) {
    if (v.size() <= 1) { // the base case should be equal or less than 1! two base cases: 0 / 1 element in an array
        return;
    }
    auto left = v.subList(0, v.size()/2);
    auto right = v.subList(v.size()/2, v.size()-v.size()/2);
    mergeSort(left);
    mergeSort(right);
    int l_index, r_index, v_index;
    l_index = r_index = v_index = 0;
    // one more index for v_index: change the vector v in place
    while (l_index < left.size() && r_index < right.size()) {
        if (left[l_index] < right[r_index]) {
            v[v_index] = left[l_index];
            l_index++;
        } else {
            v[v_index] = right[r_index];
            r_index++;
        }
        v_index++;
    }
    for (int i = l_index; i < left.size(); i++) {
        v[v_index] = left[i];
        v_index++;
    }
    for (int j = r_index; j < right.size(); j++) {
        v[v_index] = right[j];
        v_index++;
    }

}

void mergeSort(vector<int>& v) {
    if (v.size() <= 1) {
        return;
    }
    vector<int> left = vector<int>(v.begin(), v.begin()+v.size()/2);
    vector<int> right = vector<int>(v.begin()+v.size()/2, v.end());
    mergeSort(left);
    mergeSort(right);
    int l_index, r_index, v_index;
    l_index = r_index = v_index = 0;
    // one more index for v_index: change the vector v in place
    while (l_index < left.size() && r_index < right.size()) {
        if (left[l_index] < right[r_index]) {
            v[v_index] = left[l_index];
            l_index++;
        } else {
            v[v_index] = right[r_index];
            r_index++;
        }
        v_index++;
    }
    for (int i = l_index; i < left.size(); i++) {
        v[v_index] = left[i];
        v_index++;
    }
    for (int j = r_index; j < right.size(); j++) {
        v[v_index] = right[j];
        v_index++;
    }

}

void printVec(const vector<int>& v) {
    if (!v.empty()) {
        cout << "{" << v[0];
        for (int i = 1; i < v.size(); i++) {
            cout << ", " << v[i];
        }
        cout << "}" << endl;
    }
}


int getMedian(int a, int b, int c) {
    if (a >= b && a >= c) {
        if (c > b) {
            return c;
        } else {
            return b;
        }
    } else if (b >= a && b >= c) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b > a) {
            return b;
        } else {
            return a;
        }
    }
}

// quick sort idea:
/*
- find a pivot
- put the pivot to the end
- partition the element from 0~last_one-1: the left element(use a left pointer pointing to) should be less than pivot: 
- if not: the left is greater than pivot, swap it with the right element
- the right should be grater than pivot: if not: the right is less than the pivot: swap it with the left element
- put the pivot back to its correct position
- recursion handles the rest:0~pivot-1;pivot+1~end
- put action: swap
*/
void quickSortHelper(Vector<int>& v, int low, int high) {
    if (low < high) {
        // choose median as the pivot
        int pivot = getMedian(v[low], v[high], v[(low+high)/2]); 
        // put the pivot to the end
        if (pivot == v[low]) {
            std::swap(v[low], v[high]);
        } else if (pivot == v[(low+high)/2]) {
            std::swap(v[(low+high)/2], v[high]);
        } else {
            std::swap(v[high], v[high]);
        }
        // partition
        int l_index = low, r_index = high-1;
        // when l_index > r_index, the process is over; it's okay to be equal, then at the end when l_index > r_index, l_index is in the right partition which should be grater than the pivot, since pivot is at end, 
        // the value to which this "right-position" l_index pointing should swap with pivot stading at the end of the vector
        while (l_index <= r_index) {
            // before every operation and loop, we need to check l_index<=r_index since every loop could make the condition invalid
            while (l_index <= r_index && v[l_index] < pivot) { // increase l_index until a element grater than the pivot is found: since we assume that the elements in the left should be less than the pivot, if we find one greater than pivot, we need stop and swap it to the right
                l_index++;
            } 
            while (l_index <= r_index && v[r_index] > pivot) {
                r_index--;
            }
            if (l_index <= r_index) {
                std::swap(v[l_index], v[r_index]);
                // move the pointers forward
                l_index++;
                r_index--;
            }
        }
        // put pivot back to the partition position, which is its final position in the ordered vector
        std::swap(v[l_index], v[high]);

        // sort the rest to part, we should not include l_index position since it's the correct position for pivot
        quickSortHelper(v, low, l_index-1);
        quickSortHelper(v, l_index+1, high);
    }
}
void quickSort(Vector<int>& v) {
    quickSortHelper(v, 0, v.size()-1);
}


int main() {
    cout << "hi" << endl;
    Vector<int> v {73, 34, 56, 22, 1};
    vector<int> v1 {73, 34, 56, 22, 1};
    mergeSort(v1);
    printVec(v1);
    quickSort(v);
    cout << v << endl;
    cout << getMedian(1, 2, 3) << endl;
    return 0;
}
