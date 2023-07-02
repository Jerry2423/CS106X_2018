#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

# define ROW_MAX 100
# define COL_MAX 100
# define Vertex_MAX 100

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istringstream;

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

template<typename T, size_t m, size_t n>
void printArr(const T (&arr)[m][n]) {
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

void printGraph(int (*arr)[ROW_MAX][COL_MAX], int num_v) {
    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            cout << (*arr)[i][j] << " "; // dont' forget dereference first!
        }
        cout << endl;
    }
}

void printGraph(int (*arr)[COL_MAX], int num_v) {
    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// template<typename T, size_t m, size_t n>
// void printArr(const T arr[m][n]) {
//     for (size_t i = 0; i < m; i++) {
//         for (size_t j = 0; j < n; j++) {
//             cout << arr[i][j] << ' ';
//         }
//         cout << endl;
//     }
// }

void addEdge(std::vector<int>* graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void printGragh(std::vector<int>* graph, int num_v) {
    for (int i = 0; i < num_v; i++) {
        cout << "node" << i << ": ";
        for (auto j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int foo[Vertex_MAX][COL_MAX][ROW_MAX];
void func(int (*arr)[COL_MAX][ROW_MAX]);


int main() {
    int num_v = 0, num_e = 0;
    num_v = getInt("give the number of vertices");
    num_e = getInt("give the number of edges");
    // int adj_mat[num_v+1][num_v+1];
    // memset(adj_mat, 0, (num_v+1)*(num_v+1)*sizeof(**adj_mat)); // not sizeof(adj_mat)
    int adj_mat[ROW_MAX][COL_MAX] {0};
    for (int i = 0; i < num_e; i++) {
        int u = getInt("give the number of the first vertex");
        int v = getInt("give the number of the second vertex");
        adj_mat[u][v] = 1;
        adj_mat[v][u] = 1;
    }
    printGraph(adj_mat, num_v);
    // printGraph(&adj_mat, num_v);

    // adj_list idea: an array of vectors/lists
    // The idea is to represent a graph as an array of vectors such that every vector represents the adjacency list of a vertex. 
    std::vector<int> adj_list[5];
    addEdge(adj_list, 0, 1);
    addEdge(adj_list, 0, 4);
    addEdge(adj_list, 1, 4);
    addEdge(adj_list, 1, 3);
    addEdge(adj_list, 1, 2);
    addEdge(adj_list, 2, 3);
    addEdge(adj_list, 3, 4);
    printGragh(adj_list, 5);
    
}
