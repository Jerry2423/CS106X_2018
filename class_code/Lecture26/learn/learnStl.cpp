#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    v.insert(v.begin(), 10);
    for (auto i : v) {
        cout << i << endl;
    }
    return 0;
}
