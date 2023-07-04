#ifndef GRAPH_H__
#define GRAPH_H__

#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <stack>
using std::vector; using std::map; using std::pair; using std::priority_queue;
using std::stack; using std::queue;
using std::cout; using std::endl;
using name_type = int;
using weight_type = int;

struct Vertex {
    name_type name;
    vector<pair<weight_type, Vertex*>> adj; // edge_weight is diff from the cost; edge_weight is the weight of an single edge
    Vertex* prev;
    bool visited;
    weight_type cost; // cost: from some point to this point, the total cost/weight
    Vertex(name_type name) : name(name), prev(nullptr), visited(false), cost(0) {}
};

class Graph {
private:
    map<name_type, Vertex*> info;
    void resetGraph();
    // define a comare type
    struct VertexBigger {
        bool operator() (const Vertex* a, const Vertex* b) {
            return a->cost > b->cost;
        }
    };
    
public:
    void addVertex(const name_type& name);
    void addVertex(const vector<name_type>& names);
    void addEdge(const name_type& frm, const name_type& dest, weight_type weight=0);
    void removeVertex(const name_type& name);
    void removeEdge(const name_type& src, const name_type& dest);

    bool containVertex(const name_type& name) const; 
    bool containEdge(const name_type& src, const name_type& destm ) const;
    void printGraph() const;

    // Dijkstra's algorithm
    map<name_type, weight_type> shortestPath(const name_type& start);
    void shortestPath(const name_type& start, const name_type& end);
    // BFS for minimumEdgePath
    void minimumEdgePath(const name_type& start, const name_type& end);

    ~Graph();
};

bool Graph::containVertex(const name_type &name) const {
    return !(info.find(name) == info.end());
}

bool Graph::containEdge(const name_type &src, const name_type &dest) const {
    if (!containVertex(src) || !containVertex(dest)) {
        return false;
    }
    for (const auto& i : info.find(src)->second->adj) {
        if (i.second->name == dest) {
            return true;
        }
    }
    return false;
}

void Graph::addVertex(const name_type& name) {
    if (!containVertex(name)) {
        info[name] = new Vertex(name);
    }
}

void Graph::addVertex(const vector<name_type>& names) {
    for (const auto& i : names) {
        addVertex(i);
    }
}

void Graph::addEdge(const name_type &frm, const name_type &dest, weight_type weight) {
    if (weight < 0) {
        throw "edge weight cannot be negative";
    }
    if (!containEdge(frm, dest)) {
        addVertex(frm);
        addVertex(dest);
        info[frm]->adj.push_back(std::make_pair(weight, info[dest]));
        info[dest]->adj.push_back(std::make_pair(weight, info[frm]));
    }
}

void Graph::printGraph() const {
    for (const auto& i : info) {
        cout << "node " << i.first << ":";
        for (const auto& j : i.second->adj) {
            cout << " " << j.second->name;
        }
        cout << endl;
    }
}

void Graph::removeVertex(const name_type &name) {
    if (containVertex(name)) {
        for (auto& i : info[name]->adj) {
            i.second->adj.erase(std::remove_if(i.second->adj.begin(), i.second->adj.end(), [name](pair<weight_type, Vertex*> element) {return element.second->name == name;}));
        }
        delete info[name];
        info.erase(info.find(name)); // remember to remove it from info
    }
}

void Graph::removeEdge(const name_type &src, const name_type& dest) {
    if (containEdge(src, dest)) {
        // remove and erase idiom
        info[src]->adj.erase(std::remove_if(info[src]->adj.begin(), info[src]->adj.end(), [dest](pair<weight_type, Vertex*> element){return element.second->name == dest;}));
        info[dest]->adj.erase(std::remove_if(info[dest]->adj.begin(), info[dest]->adj.end(), [src](pair<weight_type, Vertex*> element){return element.second->name == src;}));

    }
}

Graph::~Graph() {
    for (auto& i : info) {
        delete i.second;
        i.second = nullptr;
    }
}


void Graph::resetGraph() {
    for (auto& i : info) {
        i.second->prev = nullptr;
        i.second->cost = 0;
        i.second->visited = false;
    }
}

map<name_type, weight_type> Graph::shortestPath(const name_type& start) {
    if (!containVertex(start)) {
        throw "give valid start point";
    }
    if (!containVertex(start)) {
        return {};
    }
    // init map, pq
    map<name_type, weight_type> result;
    priority_queue<Vertex*, vector<Vertex*>, VertexBigger> to_do;
    to_do.push(info.find(start)->second);
    for (const auto& i : info) {
        result[i.second->name] = INT_MAX;
    }
    result[start] = 0;

    // pop front
    while (!to_do.empty()) {
        auto to_process = to_do.top();
        to_do.pop();
        if (to_process->visited) {
            continue;
        }
        to_process->visited = true;
        for (auto& i : to_process->adj) {
            if (!(i.second->visited)) {
                // result[i.second->name] = std::min(result[i.second->name], result[to_process->name] + i.first);
                if (result[i.second->name]  > result[to_process->name] + i.first) {
                    result[i.second->name] = result[to_process->name] + i.first;
                    i.second->prev = to_process;
                    to_do.push(i.second);
                }
                i.second->cost = result[i.second->name]; // UPDATE THE Cost itself
            }
        }
    }
    // the mark made on the graph and vertices should be erased out
    resetGraph();
    return result;

    // go through neighbors, update and enqueue
}

// map<name_type, weight_type> Graph::shortestPath(const name_type& start) {
//     if (!containVertex(start)) {
//         throw "the starting point does not exist";
//     }
//     // init. mark all the point
//     for (auto& i : info) {
//         i.second->cost = INT_MAX;
//     }
//     info[start]->cost = 0;
//     priority_queue<Vertex*, vector<Vertex*>, VertexBigger> pq;
//     for (const auto& i : info) {
//         pq.push(i.second);
//     }
//     map<name_type, weight_type> result;
//     while (!pq.empty()) {
//         auto front = pq.top();
//         pq.pop();
//         front->visited = true;
//         result[front->name] = front->cost;
//         for (auto& i : front->adj) {
//             if (!(i.second->visited)) {
//                 i.second->cost = std::min(i.second->cost, i.first + front->cost);
//             }
//         }
//     }
//     resetGraph();
//     return result;
// }

// void Graph::shortestPath(const name_type& start, const name_type& end) {
//     for (auto& i : info) {
//         i.second->cost = INT_MAX;
//     }
//     info[start]->cost = 0;
//     priority_queue<Vertex*, vector<Vertex*>, VertexBigger> pq;
//     for (const auto& i : info) {
//         pq.push(i.second);
//     }
//     while (!pq.empty()) {
//         auto front = pq.top();
//         pq.pop();
//         front->visited = true;
//         if (front->name == end) {
//             break;
//         }
//         for (auto& i : front->adj) {
//             if (!(i.second->visited)) {
//                 if (i.second->cost > i.first + front->cost) {
//                     i.second->cost = i.first + front->cost;
//                     i.second->prev = front;
//                 }
//             }
//         }
//     }
//     auto curr = info[end];
//     stack<name_type> path;
//     while (curr) {
//         path.push(curr->name);
//         curr = curr->prev;
//     }
//     cout << "the minimum distance from " << start << " to " << end << " is: " << info[end]->cost << endl;
//     while (!path.empty()) {
//         cout << path.top() << " ";
//         path.pop();
//     }
//     cout << endl;
//     resetGraph();
//
// }
void Graph::shortestPath(const name_type& start, const name_type& end) {
    if (!containVertex(start) || !containVertex(end)) {
        throw "invalid starting or ending point";
    }
    // init pq, mark every vertex
    for (auto& i : info) {
        i.second->cost = INT_MAX;
    }
    info[start]->cost = 0;
    priority_queue<Vertex*, vector<Vertex*>, VertexBigger> to_do;
    to_do.push(info[start]);
    // pop front, visited check end?
    while (!to_do.empty()) {
        auto process_node = to_do.top();
        to_do.pop();
        if (process_node->visited) {
            continue;
        }
        process_node->visited = true;
        if (process_node->name == end) {
            break;
        }
        for (auto& i : process_node->adj) {
            if (!(i.second->visited)) {
                // update neighbors and set prev if has less value
                if (i.second->cost > process_node->cost + i.first) {
                    i.second->cost = process_node->cost + i.first;
                    i.second->prev = process_node;
                    to_do.push(i.second);
                }
            }
        }
    }
    // print result
    stack<name_type> path;
    Vertex* dest = info[end];
    while (dest) {
        path.push(dest->name);
        dest = dest->prev;
    }
    cout << "the minimum distance is " << info[end]->cost << " with the path:";
    while (!path.empty()) {
        cout << " " << path.top();
        path.pop();
    }
    cout << endl;

    // resetGraph
    resetGraph();
}

void Graph::minimumEdgePath(const name_type &start, const name_type &end) {
    if (!containVertex(start) || !containVertex(end)) {
        throw "invalid starting or ending point";
    }
    queue<Vertex*> to_do;
    to_do.push(info[start]);
    while (!to_do.empty()) {
        auto front = to_do.front();
        // it's okay to delete the following statement, just used for removing duplication
        if (front->visited) {
            to_do.pop();
            continue;
        }
        front->visited = true;
        to_do.pop();
        if (front->name == end) {
            break;
        }
        for (auto& i : front->adj) {
            if (!i.second->visited) {
                to_do.push(i.second);
                if (!(i.second->prev)) { // pointing to the closest neighbor only
                    i.second->prev = front;
                }
            }
        }
    }
    stack<name_type> path;
    auto curr = info[end];
    while (curr) {
        path.push(curr->name);
        curr = curr->prev;
    }
    cout << "the minimum edges path is:";
    while (!path.empty()) {
        cout << " " << path.top();
        path.pop();
    }
    cout << endl;
    resetGraph();
}

#endif // !DEBUG
