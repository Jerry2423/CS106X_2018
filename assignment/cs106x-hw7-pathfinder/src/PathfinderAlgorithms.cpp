// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "PathfinderAlgorithms.h"
#include "Color.h"
#include "basicgraph.h"
#include "map.h"
#include "queue.h"
#include "priorityqueue.h"
#include "set.h"
#include "vector.h"
// TODO: include any other headers you need; remove this comment

using namespace std;
using route = Vector<Vertex*>;

// The minimum difference to be a valid alternate path
const double SUFFICIENT_DIFFERENCE = 0.2;

void visit(Vertex* node) {
    node->setColor(GREEN);
}

bool isVisited(Vertex* node) {
    return node->getColor() == GREEN || node->getColor() == GRAY;
}

void unvisit(Vertex* node) {
    node->setColor(GRAY);
}

void enque(Vertex* node) {
    node->setColor(YELLOW);
}

bool isInQueue(Vertex* node) {
    return node->getColor() == YELLOW;
}

route depthFirstSearch(const BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    if (!start) {
        return {};
    } else {
        // choose/ visit the node
        visit(start);
        if (start == end) {
            return {start};
        }
        // go through every options:unvisited adj nodes
        for (const auto& i : start->edges) {
            if (!isVisited(i->finish)) {
                auto ans = depthFirstSearch(graph, i->finish, end);
                if (!ans.isEmpty()) {
                    ans.insert(0, start);
                    return ans;
                }
            }
        }
        unvisit(start);
        return {};
        // choose explore
        // if found: no need to unchoose, return currnode + explore path
        // not found: unchoose and 
    }
}

route breadthFirstSearch(const BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Queue<Vertex*> q;
    q.enqueue(start);
    enque(start);
    route path;
    Map<Vertex*, Vertex*> parent;
    parent[start] = nullptr;
    while (!q.isEmpty()) {
        auto top = q.dequeue();
        visit(top);
        if (top == end) {
            break;
        }
        for (const auto& i : top->edges) {
            if (!isVisited(i->finish) && !isInQueue(i->finish)) {
                // cout << i->toString() << endl;
                q.enqueue(i->finish);
                enque(i->finish);
                parent[i->finish] = top; 
            }
        }
    }
    if (!parent.containsKey(end)) {
        return {};
    } else {
        auto curr = end;
        while (curr) {
            path.insert(0, curr);
            curr = parent[curr];
        }
        return path;
    }
}
route dijkstrasAlgorithm(const BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    PriorityQueue<Vertex*> to_visit;
    Map<Vertex*, double> vertex_cost;
    Map<Vertex*, Vertex*> parent;
    parent[start] = nullptr;
    for (const auto& key : graph.getVertexSet()) {
        vertex_cost[key] = POSITIVE_INFINITY;
    }
    vertex_cost[start] = 0;
    enque(start);
    to_visit.enqueue(start, vertex_cost[start]);
    while (!to_visit.isEmpty()) {
        auto top = to_visit.dequeue();
        visit(top);
        if (top == end) {
            break;
        }
        for (const auto& i : top->edges) {
            if (!isVisited(i->finish)) {
                if (vertex_cost[i->finish] > vertex_cost[top] + i->cost) {
                    vertex_cost[i->finish] = vertex_cost[top] + i->cost;
                    enque(i->finish);
                    to_visit.enqueue(i->finish, vertex_cost[i->finish]);
                    // set parent
                    parent[i->finish] = top;
                }
            }
        }
    }
    
    route path;
    if (parent.containsKey(end)) {
        auto curr = end;
        while (curr) {
            path.insert(0, curr);
            curr = parent[curr];
        }

        return path;
    } else {
        return {};
    }
}

double pathCost(const BasicGraph& graph, route path) {
    double total = 0;
    for (int i = 0; i < path.size()-1; i++) {
        total += graph.getEdge(path[i], path[i+1])->cost;
    }
    return total;
}

double pathDiff(route p, route b) {
    double count = 0;
    for (int i = 0; i < p.size(); i++) {
        if (!b.contains(p[i])) {
            count += 1;
        }
    }
    return count / b.size();
}
route aStarHelper(const BasicGraph& graph, Vertex* start, Vertex* end, Vertex* e_start=nullptr, Vertex* e_end=nullptr) {
    PriorityQueue<Vertex*> to_visit;
    Map<Vertex*, double> vertex_cost;
    Map<Vertex*, Vertex*> parent;
    parent[start] = nullptr;
    Set<Vertex*> visited_nodes; // due to the function is called multiple times, cannot use color to determine whether a vertex is visited
    for (const auto& key : graph.getVertexSet()) {
        vertex_cost[key] = POSITIVE_INFINITY;
    }
    vertex_cost[start] = 0;
    enque(start);
    to_visit.enqueue(start, vertex_cost[start]+heuristicFunction(start, end));
    while (!to_visit.isEmpty()) {
        auto top = to_visit.dequeue();
        visit(top);
        visited_nodes.add(top);
        if (top == end) {
            break;
        }
        for (const auto& i : top->edges) {
            if ((i->finish == e_end && top == e_start) || (i->finish == e_start && top == e_end)) {
                // cout << "exluded end meet" << endl; 
                continue;
            }
            if (!visited_nodes.contains(i->finish)) {
                if (vertex_cost[i->finish] > vertex_cost[top] + i->cost) {
                    vertex_cost[i->finish] = vertex_cost[top] + i->cost;
                    enque(i->finish);
                    to_visit.enqueue(i->finish, vertex_cost[i->finish]+heuristicFunction(i->finish, end));
                    // set parent
                    parent[i->finish] = top;
                }
            }
        }
    }
    
    route path;
    if (parent.containsKey(end)) {
        auto curr = end;
        while (curr) {
            path.insert(0, curr);
            curr = parent[curr];
        }
        // cout << "the COST of the path is " << pathCost(graph, path) << endl;
        return path;
    } else {
        return {};
    }
}

route aStar(const BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        YoPriorityQueue<Vertex*> to_visit; 
    return aStarHelper(graph, start, end);
}


route alternatePath(const BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    route best_path = aStar(graph, start, end);
    route alt_path;
    PriorityQueue<route>paths;
    for (int i = 0; i < best_path.size()-1; i++) {
        auto temp = aStarHelper(graph, start, end, best_path[i], best_path[i+1]);
        if (!temp.isEmpty()) {
            paths.enqueue(temp, pathCost(graph, temp));
        }
    }
    while (!paths.isEmpty()) {
        alt_path = paths.dequeue();
        // cout << " exits an alternate" << endl;
        if (pathDiff(alt_path, best_path) > SUFFICIENT_DIFFERENCE) {
            return alt_path;
        }
    }
    return {};
}
