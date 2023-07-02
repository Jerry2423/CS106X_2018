#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include <queue>
#include <unordered_set>
#define MAX_V 100
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::istringstream;
using std::string;
using std::pair;
using std::priority_queue;
using std::unordered_set;

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

struct Vertex {
    int num;
    int cost;
    bool visited;
    Vertex* prev;

    Vertex(int num, int cost=0, bool visited=false, Vertex* prev=nullptr) : num(num), cost(cost),
        visited(visited), prev(prev) {}
};

bool operator >(const Vertex& a, const Vertex& b) {
    return a.cost > b.cost;
}

class Graph {
    private:
        int num_v_;
        vector<Vertex>* adj;
    public:
        Graph(int v) : num_v_(v), adj(new vector<Vertex>[v]) {}
        ~Graph() {delete [] adj;}
        void addEdge(int u, int v, int w);
        vector<int> shortest_path(int start);
};

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(Vertex(v, w));
    adj[v].push_back(Vertex(u, w));
}

vector<int> Graph::shortest_path(int start) {
    // init vector and pq-todo
    vector<int> dis(num_v_, INT_MAX);
    unordered_set<int> visited; // unordered_set: hashset
    dis[start] = 0;
    priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> todo;
    todo.push(Vertex(start, 0));
    // while still have to-do
    while (!todo.empty()) {
        auto to_process = todo.top();
        todo.pop();
        visited.insert(to_process.num);

        for (auto i : adj[to_process.num]) {
            if (visited.find(i.num) == visited.end()) {
                dis[i.num] = std::min(dis[i.num], dis[to_process.num] + i.cost); // i.cost means the weight from the neighbor point to_process to the curr i point
                todo.push(Vertex(i.num, dis[i.num]));
            }
        }
    }
    return dis;
    // pop the first(leat distance) and marked as visited

    // update its neighbors

    // unvisited? yes then compare and enque
}

int main() {
    Graph g(7);
    // g.addEdge(0, 1, 4);
    // g.addEdge(0, 2, 2);
    // g.addEdge(1, 2, 1);
    // g.addEdge(1, 3, 5);
    // g.addEdge(2, 3, 8);
    // g.addEdge(2, 4, 10);
    // g.addEdge(3, 4, 2);
    // g.addEdge(3, 5, 6);
    // g.addEdge(4, 5, 3);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 10);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 5, 5);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 8);
    g.addEdge(3, 6, 4);
    g.addEdge(4, 6, 6);
    g.addEdge(5, 6, 1);

    auto ans = g.shortest_path(0);
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
}
