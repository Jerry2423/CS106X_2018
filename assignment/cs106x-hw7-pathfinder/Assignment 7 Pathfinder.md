# Assignment 7: Pathfinder



![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/hero.png)

In this assignment, you'll implement several path searching algorithms in the Pathfinder program that altogether allow the user to navigate maps, terrains and mazes. Specifically, your job is to implement the following algorithms:

- Depth-First Search (DFS)
- Breadth-First Search (BFS)
- Dijkstra's Algorithm
- A* Search
- Alternate Path

Turn in only the following files:

- **PathfinderAlgorithms.cpp**, the C++ code for your search algorithms
- **PathfinderAlgorithmsTests.cpp** to test your implementation
- **debugging.txt**, a file detailing a bug you encountered in this assignment and how you approached debugging it

The ZIP contains other files/libraries; do not modify these. Your code must work with the other files unmodified.

## Development Strategy and Hints



- **Trace through the algorithms by hand** on small sample graphs before coding them.
- **Work step-by-step.** Complete each algorithm before starting the next one. You can test each individually even if others are incomplete. We suggest doing DFS/BFS, then Dijkstra's, then A*, and finally Alternate Path.
- **Start out with tiny worlds first**. It is much easier to trace your algorithm and/or print every step of its execution if the world is small. Once your output matches perfectly on tiny files, go to larger ones.
- **In Dijkstra's algorithm**, you cannot call `changePriority` on a vertex that is not already in the queue. You also cannot call `changePriority` with a priority less urgent (greater) than the existing priority in the queue.
- Remember that edge costs are **doubles**, not ints.
- **You will need to keep track of some information**, such as which nodes you have visited, the "previous" node, current Dijkstra costs, etc. yourself, since the graph/edges/vertices do not. Think about how you might keep track of this information.
- **In A\* search**, when storing the candidate distance to a vertex, do *not* add the heuristic value in. The heuristic is only used when setting the priorities in the priority queue, not when setting the cost fields of vertexes.
- Don't forget to keep **previous** pointers up-to-date in Dijkstra's algorithm or A* search. Otherwise, though you'll dequeue the vertexes in the proper order, your resulting path might end up incorrect.
- **In Dijkstra's algorithm**, don't stop your algorithm early when you enqueue the ending vertex; stop it when you dequeue the ending vertex (that is, when you color the vertex green). Just because you have found the ending vertex for the first time does not mean you have already found the best way to get there!
- ***Test your code thoroughly!\*** We'll be running a battery of automated tests on your code; make sure to test various different inputs to ensure it works correctly.
- **The alternate path algorithm that we ask you to implement is slow**. Test it on small maps. On the Stanford map, it’s normal for it to take a few seconds, and on Istanbul and San Francisco it can take several minutes.



## Pathfinder GUI

This program displays various 2-dimensional worlds that represent either maps, mazes, or terrain and allows the user to generate paths in a world from one point to another. When you start up the program, you will see a graphical window containing a map of Stanford, and a secondary console window that displays text information about the world and the algorithms being run. The program is also able to display terrain, where <u>bright colors indicate higher elevations and darker colors represent lower elevations</u>, and mazes, where white squares are open and black squares represent walls.

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/map.png)

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/terrain.png)

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/maze.png)

*A Pathfinder map*

*A Pathfinder terrain*

*A Pathfinder maze*

If you click on any two points in the world (or circles, in the case of the maps), the program will find a path from the starting position to the ending position. As it does so, it will color the vertexes green, yellow, and gray based on the colors assigned to them by the algorithm. Once the path is found, the program will highlight it and display information about the path in the console. The user can select one of five path-searching algorithms in the top menu:

- depth-first search (DFS)
- breadth-first search (BFS)
- Dijkstra's algorithm
- A* search
- Alternate Path



The window also contains several controls. You can load mazes, terrains or maps of different sizes from the bottom drop-down menu, and then click the "Load" button to display them.

You can also optionally turn off or increase the animation delay of the program, which will allow you to more clearly see the exploration steps your algorithms are performing by looking at the colors of various nodes.

When comparing different algorithms, not that you do not have to re-select the start and end points each time; if you run an algorithm, and then select another algorithm and click "Run", it will run the new algorithm with the same start and end points you previously selected.

------

## Provided Data Types

The 2D world is represented by a `BasicGraph`, where <u>each vertex represents a specific location on the world</u>. If it is a maze, <u>each location represents one square in the maze's grid-like world.</u> <u>**Open maze squares** are connected by edges to any other **neighboring open squares** that are directly adjacent to them (differ by +/- 1 row or column exactly), and black "wall" squares are not connected as neighbors to any other squares;</u> no edges touch them. If the world is a terrain, each location <u>represents some elevation between 0 (lowland) and 1 (high mountain peak)</u>. <u>Terrain</u> locations are connected to neighbors in <u>all 8 directions including diagonal neighbors</u>, but <u>maze</u> locations are only connected to neighbors <u>directly up, down, left, and right.</u> Map locations (represented by circles) are <u>connected based on the layout of the map.</u>

Note that your code can treat maps, mazes, and terrains exactly the same. You should just think of each kind of world as a graph with vertexes and edges that connect neighboring vertexes. In the case of mazes, vertexes happen to represent 2D locations and neighbors happen to be directly up, down, left, right, etc., but <u>your code does not utilize or rely on that information.</u> Your path-searching algorithms will work on any kind of graph that might be passed to them.

Each vertex in the graph is represented by an instance of the Vertex structure, which has the following members:

| `Vertex` Member  |                         Description                          |
| :--------------: | :----------------------------------------------------------: |
|    `v->name`     |   vertex's name, such as "r34c25" or "vertex17" (a string)   |
|    `v->edges`    |       edges outbound from this vertex (a `Set<Edge*>`)       |
| `v->setColor(c)` | sets this vertex to be drawn in the given color in the GUI, such as the following constants: `UNCOLORED`, `GRAY`, `YELLOW`, or `GREEN`. |
| `v->getColor()`  | returns the color you set previously using `setColor`; initially `UNCOLORED`. |
| `v->toString()`  | returns a printable string representation of the vertex for debugging. |

Each edge in the graph is represented by an instance of the Edge structure, which has the following members:

|  `Edge` Member  |                         Description                          |
| :-------------: | :----------------------------------------------------------: |
|   `e->start`    |  pointer to the starting vertex of this edge (a `Vertex*`)   |
|   `e->finish`   | pointer to the ending vertex of this edge; i.e., `finish` is a neighbor of `start` (a `Vertex*`). |
|    `e->cost`    |            cost to traverse this edge (a double).            |
| `e->toString()` | returns a printable string representation of the edge for debugging. |

The vertexes and edges are contained inside a `BasicGraph` object passed to each of your algorithm functions. See the [Stanford C++ library documentation](http://stanford.edu/~stepp/cppdoc/BasicGraph-class.html) for descriptions of the members of the BasicGraph class. In addition to those members, BasicGraph includes all of the public members from its parent class Graph.

------

## Graph Algorithms

In your `PathfinderAlgorithms.cpp` file, you must write the following 5 functions for finding paths, each of which will be called by the provided GUI when the user selects that algorithm, a start point, and an end point:

```
Vector<Vertex*> depthFirstSearch(const BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> breadthFirstSearch(const BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> dijkstrasAlgorithm(const BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> aStar(const BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> alternatePath(const BasicGraph& graph, Vertex* start, Vertex* end);
```

Each of the first four implements a path-searching algorithm taught in class. You should search the given graph for a path from the given start vertex to the given end vertex. If you find such a path, the path you return should be a list of all vertexes along that path, with the starting vertex first (index 0 of the vector) and the ending vertex last.

<u>If no path is found, return an empty vector. If the start and end vertexes are the same, return a one-element vector containing only that vertex.</u> Though the mazes and terrains in our main app are undirected graphs (all edges go both ways), your code should not assume this. In particular, some maps have weighted edges. You may assume that the graph passed has a valid state.

In addition to searching for a path in each algorithm, we also want you to add some code to give colors to various vertexes at various times. This coloring information is used by the GUI to show the progress of your algorithm and to provide the appearance of animation. To give a color to a vertex, call the `setColor` member function on a `Vertex`, passing it a global color constant such as `GRAY`, `YELLOW`, or `GREEN`. For example:

```
Vertex* myVertex = graph.getVertex("foo");
myVertex->setColor(GREEN);                  // set the vertex's color to green
```

Here is a listing of colors available and when you should use them:

- **enqueued = yellow**: Whenever you enqueue a vertex to be visited <u>for the first time</u>, such as in BFS and Dijkstra's algorithm when you add a vertex to a data structure for later processing, color it yellow (`YELLOW`).
- **visited = green**: Whenever your algorithm directly visits and examines a particular vertex, such as when it is dequeued from the processing queue in BFS or Dijkstra's algorithm, or when it is the starting vertex of a recursive call in DFS, color it green (`GREEN`).
- **eliminated = gray**: Whenever your algorithm has finished exploring a vertex and did not find a path from that vertex, and therefore is "giving" up on that vertex as a candidate, color it gray (`GRAY`). The only algorithm that explicitly "backtracks" like this is depth-first search (DFS). You don't need to set any vertexes to gray in any other path-searching algorithms besides DFS.



------

## Implementation Details

**Depth-first search**: You can implement it recursively as shown in lecture, or non-recursively. The choice is up to you. A recursive solution can sometimes run slowly or crash on extremely large worlds; this is okay. You do not need to modify your DFS implementation to avoid crashes due to excessive call stack size.

**Breadth-first search**: Implement the version of the algorithm pseudo-code from lecture. <u>Make sure to keep track of nodes that you have already visited.</u>

**Dijkstra's algorithm**: The version of Dijkstra's algorithm suggested in the course textbook is slightly different than the version we discussed in lecture and is less efficient. Your implementation of Dijkstra's algorithm should follow the version we discussed in lecture. The priority queue should store vertexes to visit, and once you find the destination, you should reconstruct the shortest path back. See the lecture slides for more details.

**A\* search**: As discussed in class, the A* search algorithm is essentially a variation of Dijkstra's algorithm that uses heuristics to fine-tune the order of elements in its priority queue to explore more likely desirable elements first. So when you are implementing A*, you need a heuristic function to incorporate into the algorithm. We supply you with a global function called `heuristicFunction` that accepts pointers to two vertexes v1 and v2 and returns a heuristic value from v1 to v2 as a double. You can assume that this is an admissible heuristic, meaning that it never overestimates the distance to the destination (which is important for A*). For example:

```
Vertex* v1 = graph.getVertex("foo");
Vertex* v2 = graph.getVertex("bar");
double h = heuristicFunction(v1, v2);   // get an A* heuristic between these vertexes
```

Our pseudocode for Dijkstra's algorithm and A* occasionally refers to "infinity" as an initial value when talking about the cost of reaching a vertex. If you want to refer to infinity in your code, you can use the double constant `POSITIVE_INFINITY` that is visible to your code.

Dijkstra's algorithm and A* involve a priority queue of vertexes to process, and furthermore, they each depend on the ability to alter a given vertex's priority in the queue as the algorithm progresses. Use the [Stanford library's `PriorityQueue` class](http://stanford.edu/~stepp/cppdoc/PriorityQueue-class.html) for this. To do this, call the `changePriority` member function on the priority queue and pass it the new priority to use. It is important to use this function here because <u>otherwise there is no way to access an arbitrary element from the priority queue to find the one whose priority you want to change.</u> You would have to remove vertexes repeatedly until you found the one you wanted, which would be very expensive and wasteful. The new priority you pass must be at least as urgent as the old priority for that vertex (because the function bubbles a value upward in the priority queue's internal heap structure).

Note that the notion of a given vertex's current priority might be stored in two places in your code: in your own record-keeping about each Vertex, and in the priority queue's ordering. You'll have to keep these two in sync yourself; if you update just your own records, the priority queue won't know about it if you don't call `changePriority`, and vice versa. If the two values get out of sync, this can lead to bugs in your program.

You can compare the behavior of Dijkstra's algorithm and A* (or any pair of algorithms). First try performing a search between two points using Dijkstra's algorithm, then select A* and press the "Run" button at the top of the GUI window. This will repeat the same search using the currently selected algorithm. Run a search using Dijkstra's algorithm, switch the algorithm choice to "A*," then run that search to see how much more efficient A* is.

Several expected output files have been posted to the class web site. If you have implemented each path-searching algorithm correctly, for DFS you should get any valid path from the start to the end; for BFS you should get the same path lengths as shown in the expected outputs posted on the class web site. For Dijkstra's and A* you should get the same path costs as shown in the expected outputs. For Alternate Path you should get the same path costs. But you do not need to exactly match our path itself, nor its "locations visited", so long as your path is a correct one. Your A* search algorithm should always return a path with the same cost as the path found by Dijkstra's algorithm. If you find that the algorithms give paths of different costs, it probably indicates a bug in your solution. For mazes, all three of BFS, Dijkstra's algorithm, and A* should return paths with the same length and cost.

### Alternative Path

When travelling between two points on a map, you may want to take the fastest route, but if there is a reasonable alternative you might prefer that instead. For example, though highway 101 is often the slightly faster way to get to San Francisco from the peninsula, highway 280 is more beautiful. Your final task is to implement the Alternate Path search algorithm, which is a slight variation of Dijkstra's and A*.

In this example the minimum cost path between the oval and the back of MemChu is shown in red, and a next best alternative is shown in blue:



![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/altRoute.png)



We already know how to find a minimum cost path from a start to a goal. How do we find an alternate route?

To find an alternate path from a start node to an end node, <u>first we are going to calculate the best (i.e., minimum cost) path between start and end, using our A* algorithm.</u> Then, for each edge in the best path we are going to calculate the <u>minimum cost path from start to end that **ignores that edge.**</u> Each search will thus return a candidate “alternate route”. **Your function should return the lowest cost alternate route that is sufficiently different from the original best path.** When we say “sufficiently different,” we mean according to a threshold that we define for you as a constant, `SUFFICIENT_DIFFERENCE`, with a value of 0.2.

To calculate the difference between two paths: we define the difference of an a**lternate path P from the best path B** to be the **number of nodes that are in P but are not in B, divided by the number of nodes in B:**



![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/sufficientDiff.png)



For each edge in the best path you will produce one candidate alternate route. Your function should choose, from those candidates, the minimum cost path that has a difference score <u>greater than 0.2</u> when compared to the original best path (i.e. greater than the defined constant `SUFFICIENT_DIFFERENCE`).

**Example of alternative route calculation:** In the graph below, the minimum cost path from Start to End has four edges. For each edge we compute a candidate alternate route:



![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/pathfinder/alternatePathExample.png)

The minimum-cost path (in blue) is Start → A → B → C → End and has cost 6.

| Excluded Edge |           Alternate Path            | Cost | Difference |
| :-----------: | :---------------------------------: | :--: | :--------: |
|   Start → A   |   Start → **D** → A → B → C → End   |  7   | 1/5 (0.2)  |
|     A → B     | Start → A → **E** → **F** → C → End |  8   | 2/5 (0.4)  |
|     B → C     |   Start → A → B → **F** → C → End   | 7.5  | 1/5 (0.2)  |
|    C → End    |              *No path*              |  ∞   |     0      |



The minimum cost alternate route is the path Start → D → A → B → C → End. However it has a difference score of 0.2 (recall that we are looking for a path with difference score *greater than* 0.2). The minimum cost alternative that *also* has a difference greater than 0.2 is:
`  Start → A → E → F → C → End`
That is the path that your alternative path algorithm should return.

There are different ways to accomplish this modification to your path algorithm. One option is to simply write a separate and modified Dijkstra or A* function that can ignore or exclude an edge, bu this duplicates a lot of code. A better option would be to refactor your code and write a modified function that performs Dijkstra or A*, and can either perform the standard algorithm or can ignore a given edge. Then, you can modify your original Dijkstra or A* function to simply call your new function.

------

## Unit Testing

We have included a unit testing file containing some starting tests for each of these algorithms, **PathfinderAlgorithmsTests.cpp**. You can run these unit tests by running Pathfinder and selecting the "Tests" option on the launch popup.

You should add **at least 3** more unit tests to help you test your implementation. Make sure that your unit tests test as small, isolated components of your code as possible. Make sure to give each test a detailed name, and comment above it explaining what it is testing. See the provided tests for examples of how to create test graphs.

Also remember to turn in **debugging.txt**, explaining a bug you encountered, how you identified it, and how you fixed it. You can find this file in the res/ folder of the starter project.

------

## Extra Features

Though your solution to this assignment must match all of the specifications mentioned previously, it is allowed and encouraged for you to add extra features to your program if you'd like to go beyond the basic assignment. Here are some suggestions:

- ***Implement bidirectional search\***: A common alternative to using A* search is to use a bidirectional search algorithm, in which you search outward from both the start and end vertexes simultaneously. As soon as the two searches find a vertex in common, you can construct a path from the start vertex to the end vertex by joining the two paths to that vertex together. Try coding this algorithm up as another algorithm choice.
- ***Make a new world type\***: The existing code has several classes that extend a superclass World to represent maps, mazes, and terrains. Add your own new subclass for a type of world that we didn't include.
- ***Write better heuristics\***: The heuristic we have provided for estimating terrain costs and map / maze distances is a simple admissible heuristic that works reasonably well. Try seeing if you can modify this function to produce more accurate heuristics. If you do this correctly, you can cut down on the amount of unnecessary searching required. However, make sure that your heuristics are admissible; that is, they should never overestimate the distance from any starting vertex to any destination vertex.
- ***Better alternate path\***: The alternate route algorithm is slow and not guaranteed to find the best alternate. Can you come up with a different algorithm that is faster or that uses a more realistic measure of path distance?
- ***Other\***: If you have your own creative idea for an extra feature, feel free to ask your SL and/or the instructor about it.

*Indicating that you have done extra features:* If you complete any extra features, then in the comment heading on the top of your program, please list all extra features that you worked on and where in the code they can be found (what functions, lines, etc. so that the grader can look at their code easily).

*Submitting a program with extra features:* Since we use automated testing for part of our grading process, it is important that you submit a program that conforms to the preceding spec, even if you want to do extra features. You should submit two versions of each modified program file: for example, a first one named **PathfinderAlgorithms.cpp** without any extra features added (or with all necessary features disabled or commented out), and a second one named **PathfinderAlgorithms-extra.cpp** with the extra features enabled. Please distinguish them by explaining which is which in the comment header. Our turnin system saves every submission you make, so if you make multiple submissions we will be able to view all of them; your previously submitted files will not be lost or overwritten.