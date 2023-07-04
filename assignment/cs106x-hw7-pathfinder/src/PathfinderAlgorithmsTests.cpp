#include "PathfinderAlgorithmsTests.h"
#include "PathfinderAlgorithms.h"
#include "PathfinderUtil.h"

using namespace std;
ENABLE_TESTS();

/* This graph looks like the following:
 *
 *     A ---> B
 *     ^      |
 *     |      |
 *     |      v
 *     D<-----C
 *
 * It is a small graph to test whether a path can be found where there
 * is only one option.
 */
ADD_TEST("DFS: small square graph") {
    BasicGraph g = {"A", "B", "C", "D"};    // Create a graph with 4 vertices
    g.addEdge("A", "B");
    g.addEdge("B", "C");
    g.addEdge("C", "D");
    g.addEdge("D", "A");

    Vertex *aVertex = g.getVertex("A");
    Vertex *dVertex = g.getVertex("D");
    Vector<Vertex *> foundPath = depthFirstSearch(g, aVertex, dVertex);

    /* verifyPath is a provided function (in PathfinderUtil.h) that can check the
     * validity of a path in a graph.
     *
     * In this case, the only valid path is A-B-C-D.
     */
    expect(verifyPath(g, foundPath, aVertex, dVertex));
    expect(foundPath.size() == 4);
    expect(foundPath[1] == g.getVertex("B"));
    expect(foundPath[2] == g.getVertex("C"));
}

/* This graph looks like the following:
 *
 *     A ---> B
 *     |       \
 *     v        v
 *     C        D
 *     |       ^
 *     v       |
 *     E-------|
 *
 * It is a small graph to test whether the shortest path is found when
 * two paths exist.
 */
ADD_TEST("BFS: small pentagon graph") {
    BasicGraph g = {"A", "B", "C", "D", "E"};    // Create a graph with 5 vertices
    g.addEdge("A", "B");
    g.addEdge("B", "D");
    g.addEdge("A", "C");
    g.addEdge("C", "E");
    g.addEdge("E", "D");

    Vertex *aVertex = g.getVertex("A");
    Vertex *dVertex = g.getVertex("D");
    Vector<Vertex *> foundPath = breadthFirstSearch(g, aVertex, dVertex);

    /* verifyPath is a provided function (in PathfinderUtil.h) that can check the
     * validity of a path in a graph.
     *
     * In this case, the shortest path is A-B-D, not A-C-E-D.
     */
    expect(verifyPath(g, foundPath, aVertex, dVertex));
    expect(foundPath.size() == 3);
    expect(foundPath[1] == g.getVertex("B"));
}

/* This graph looks like the following:
 *
 *        50
 *      A ---> B
 *   1  |       \ 65
 *      v        v
 *      C        D
 *   2  |       ^
 *      v       |
 *      E-------|
 *          2
 *
 * It is a small graph to test whether the shortest path by edge cost
 * is found when two paths exist, and when the shortest path by edge
 * cost is not the shortest path by number of edges.
 */
ADD_TEST("Dijkstra: small pentagon graph") {
    BasicGraph g = {"A", "B", "C", "D", "E"};    // Create a graph with 5 vertices
    g.addEdge("A", "B", 50);
    g.addEdge("B", "D", 65);
    g.addEdge("A", "C", 1);
    g.addEdge("C", "E", 2);
    g.addEdge("E", "D", 2);

    Vertex *aVertex = g.getVertex("A");
    Vertex *dVertex = g.getVertex("D");
    Vector<Vertex *> foundPath = dijkstrasAlgorithm(g, aVertex, dVertex);

    /* verifyPath is a provided function (in PathfinderUtil.h) that can check the
     * validity of a path in a graph.
     *
     * In this case, the shortest path by cost is A-C-E-D, not A-B-D.
     */
    expect(verifyPath(g, foundPath, aVertex, dVertex));
    expect(foundPath.size() == 4);
    expect(foundPath[1] == g.getVertex("C"));
    expect(foundPath[2] == g.getVertex("E"));
}

/* This graph looks like the following:
 *
 *        50
 *      A ---> B
 *   1  |       \ 65
 *      v        v
 *      C        D
 *   2  |       ^
 *      v       |
 *      E-------|
 *          2
 *
 * It is a small graph to test whether the shortest path by edge cost
 * is found when two paths exist, and when the shortest path by edge
 * cost is not the shortest path by number of edges.  This test is essentially
 * the same as the previous one for Dijkstra, and tests whether A*
 * finds the same path as Dijkstra.
 */
ADD_TEST("A*: small pentagon graph") {
    BasicGraph g = {"A", "B", "C", "D", "E"};    // Create a graph with 5 vertices
    g.addEdge("A", "B", 50);
    g.addEdge("B", "D", 65);
    g.addEdge("A", "C", 1);
    g.addEdge("C", "E", 2);
    g.addEdge("E", "D", 2);

    Vertex *aVertex = g.getVertex("A");
    Vertex *dVertex = g.getVertex("D");
    Vector<Vertex *> foundPath = aStar(g, aVertex, dVertex);

    /* verifyPath is a provided function (in PathfinderUtil.h) that can check the
     * validity of a path in a graph.
     *
     * In this case, the shortest path by cost is A-C-E-D, not A-B-D.
     */
    expect(verifyPath(g, foundPath, aVertex, dVertex));
    expect(foundPath.size() == 4);
    expect(foundPath[1] == g.getVertex("C"));
    expect(foundPath[2] == g.getVertex("E"));
}

/* This graph is the graph shown in the discussion of the alternate path algorithm.
 * See the spec for a visualization.
 * This test ensures that a valid alternate path is found that is sufficiently
 * different from the original shortest path.
 */
ADD_TEST("Alternate Path: spec example") {
    BasicGraph g = {"A", "B", "C", "D", "E", "F", "Start", "End"};    // Create a graph with 8 vertices
    g.addEdge("Start", "A", 1);
    g.addEdge("Start", "D", 1);
    g.addEdge("D", "A", 1);
    g.addEdge("A", "B", 1);
    g.addEdge("A", "E", 2);
    g.addEdge("E", "B", 2);
    g.addEdge("E", "F", 2);
    g.addEdge("B", "C", 3);
    g.addEdge("B", "F", 2.5);
    g.addEdge("F", "C", 2);
    g.addEdge("C", "End", 1);

    Vertex *startVertex = g.getVertex("Start");
    Vertex *endVertex = g.getVertex("End");
    Vector<Vertex *> foundPath = alternatePath(g, startVertex, endVertex);

    /* verifyPath is a provided function (in PathfinderUtil.h) that can check the
     * validity of a path in a graph.
     *
     * In this case, the shortest path by cost is Start-A-B-C-End, and the shortest
     * alternate path is Start-A-E-F-C-End.
     */
    expect(verifyPath(g, foundPath, startVertex, endVertex));
    expect(foundPath.size() == 6);
    expect(foundPath[1] == g.getVertex("A"));
    expect(foundPath[2] == g.getVertex("E"));
    expect(foundPath[3] == g.getVertex("F"));
    expect(foundPath[4] == g.getVertex("C"));
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */
