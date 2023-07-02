#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <sstream>
#define MAX_V 100
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::istringstream;
using std::string;

int getInt(const string& prompt = "") {
    while (true) {
        cout << prompt << ":" << endl;
        string info;
        if (!getline(cin, info)) {
            throw "invalid input";
        }
        istringstream s(info);
        int result;
        char ch;
        if (s >> result && !(s >> ch)) {
            return result;
        }
    }
}
void printGraph(int (*arr)[MAX_V], int num_v) {
    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
vector<int> shortestPath(int (*graph)[MAX_V], int num_v, int start);
void shortestPathHelper(int (*graph)[MAX_V], int num_v, set<int>& record, vector<int>& dist);

int main() {

    int num_v = 0, num_e = 0;
    num_v = getInt("give the number of vertices");
    num_e = getInt("give the number of edges");
    // int adj_mat[num_v+1][num_v+1];
    // memset(adj_mat, 0, (num_v+1)*(num_v+1)*sizeof(**adj_mat)); // not sizeof(adj_mat)
    int adj_mat[MAX_V][MAX_V] {0};
    for (int i = 0; i < num_e; i++) {
        int u = getInt("give the number of the first vertex");
        int v = getInt("give the number of the second vertex");
        int dist = getInt("give the weight of the edge");
        adj_mat[u][v] = dist;
        adj_mat[v][u] = dist;
    }
    printGraph(adj_mat, num_v);
    cout << "shortestPath ans:" << endl;

    auto min_dist = shortestPath(adj_mat, num_v, 0);
    cout << min_dist.size() << endl;
    for (auto i : min_dist) {
        cout << i << " ";
    }
    cout << endl;
}

void shortestPathHelper(int (*graph)[MAX_V], int num_v, set<int>& record, vector<int>& dist) {
    while (record.size() < num_v) {
        // find the min dist point that has not been added in the vector, add the corresponding point the the set
        int min_dist = INT_MAX;
        int min_element = 0;
        for (int i = 0; i < dist.size(); i++) {
            if (record.find(i) == record.end()) { // only care about nodes that are not in the set
                if (min_dist > dist[i]) {
                    min_dist = dist[i];
                    min_element = i;
                }
            }
        }
        record.insert(min_element);

        // update the value in the dist
        for (int i = 0; i < dist.size(); i++) {
            if (record.find(i) == record.end()) {
                if (graph[min_element][i]) {
                    dist[i] = std::min(dist[i], dist[min_element] + graph[min_element][i]); // min_element is also the latest added element
                }
            }
        }
    }
}

vector<int> shortestPath(int (*graph)[MAX_V], int num_v, int start) {
    // init the set and the dist vector
    vector<int> dist(num_v, INT_MAX);
    dist[start] = 0;
    set<int> record;
    shortestPathHelper(graph, num_v, record, dist);
    return dist;
}




