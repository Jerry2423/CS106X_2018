#include "graph.h"

int main() {
    Graph g;
    g.addVertex({0, 1, 2});
    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 1);
    g.printGraph();
    // g.removeVertex(1);
    // cout << "remove" << endl;
    // g.printGraph();
    // g.removeEdge(0, 2);
    // g.printGraph();


    Graph g1;
    g1.addVertex({0, 1, 2, 3, 4, 5, 6});
    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 3, 1);
    g1.addEdge(0, 2, 4);
    g1.addEdge(1, 3, 3);
    g1.addEdge(1, 4, 10);
    g1.addEdge(2, 3, 2);
    g1.addEdge(2, 5, 5);
    g1.addEdge(3, 4, 2);
    g1.addEdge(3, 6, 4);
    g1.addEdge(3, 5, 8);
    g1.addEdge(4, 6, 6);
    g1.addEdge(5, 6, 1);
    auto ans = g1.shortestPath(0);
    for (auto i : ans) {
        cout << i.first << " " << i.second << endl;
    }

    g1.shortestPath(0, 2);
    g1.shortestPath(0, 4);
    g1.minimumEdgePath(0, 5);

    Graph g2;
    g2.addVertex({0, 1, 2, 3, 4, 5});
    g2.addEdge(0, 1, 4);
    g2.addEdge(0, 2, 2);
    g2.addEdge(1, 2, 1);
    g2.addEdge(1, 3, 5);
    g2.addEdge(2, 3, 8);
    g2.addEdge(2, 4, 10);
    g2.addEdge(3, 4, 2);
    g2.addEdge(3, 5, 6);
    g2.addEdge(4, 5, 3);
    g2.shortestPath(0, 5);
}
