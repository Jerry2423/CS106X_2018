#include "PathfinderUtil.h"

bool verifyPath(const BasicGraph& graph, const Vector<Vertex*>& path, Vertex* start, Vertex* end) {
    Vertex* studentStart = path[0];
    Vertex* studentEnd = path[path.size() - 1];
    if (path[0] != start) {
        std::cout << "Warning: Start of path is not the start location." << std::endl;
        std::cout << "         (Expected " << start->name << ", found "
                  << (studentStart ? studentStart->name : "nullptr") << std::endl;
        return false;
    }
    if (path[path.size() - 1] != end) {
        std::cout << "Warning: End of path is not the end location." << std::endl;
        std::cout << "         (Expected " << end->name << ", found "
                  << (studentEnd ? studentEnd->name : "nullptr") << std::endl;
        return false;
    }

    for (int i = 0; i < path.size(); i++) {
        Vertex* v = path[i];
        if (!v) {
            std::cerr << "Invalid path: null vertex at index " << i << std::endl;
            return false;
        }
        Vertex* vcheck = graph.getVertex(v->name);
        if (vcheck != v) {
            std::cerr << "Invalid path: vertex " << v->name << " at index " << i
                      << " points to memory not found in the graph" << std::endl;
            return false;
        }

        if (i > 0) {
            Vertex* prev = path[i - 1];
            Edge* edge = graph.getEdge(prev, v);
            if (!edge) {
                std::cerr << "Invalid path: no edge exists from "
                          << prev->name << " to " << v->name << std::endl;
                return false;
            }
        }
    }
    return true;
}
