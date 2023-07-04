## Graph Design



[Geeks for Geeks Readings](https://www.geeksforgeeks.org/graph-and-its-representations/)

[Reference (used in the `graph.h`)](https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c)

[Design for Competitive Programming1](https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/)

[Design for Competitive Programming2](https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-2-weighted-graph/)

### Vertex

```c++
struct Vertex {
    name_type name;
    vector<pair<weight_type, Vertex*>> adj; // edge_weight is diff from the cost; edge_weight is the weight of an single edge
    Vertex* prev;
    bool visited;
    weight_type cost; // cost: from some point to this point, the total cost/weight
    Vertex(name_type name) : name(name), prev(nullptr), visited(false), cost(0) {}
};

```

采用adjacency list的形式，其中`adj`存放的是用`pair`表示的，与该点incident的边，`pair`第一个元素是边的权重，第二个元素是边的终点。

区分点的`cost`和边的`weight`：点的`cost`是从某一点到该点，所经过各边的`weight`的总和；而`weight`只是一个边的权重



### Graph

```C++
class Graph {
private:
    map<name_type, Vertex*> info;
    void resetGraph();
    // ...
}
```

`Info`用于将点的名字和点本身对应起来，用户在操作图的时候只会用点的名字

`resetGraph()`主要用于清空图上的标记，比如各个点的`prev, visited, cost`的重制，在最短路和bfs时候常用，作为工具函数

**注意**：

在const成员函数访问info的时候不能用`[]`直接访问，因为`[]`是一个non- constant operator；只能`info.find(key)`先找到该key的iterator；map的iterator很有意思， 它有`first`和`second`两个指向，分别指key和value；若要访问value，则是`info.find(key)->second`



### Algorithms



**Ideas for BFS and Dijkstra's Algorithm**

用queue创建一个**todo-list**，不断记录并告诉自己**下一步**要<u>visit</u>哪个点

- BFS: 离自己最近的点
- Dijkstra: 当前cost最小的点

> Dijkstra basic algorithm concept: Create a table of information about the currently known best way **to reach each vertex** (cost, previous vertex), and improve it until it reaches the best solution.

Dijkstra算法里面，*够不着，无穷大的点*没必要放到todo-list里面去



**TODO-List维护**: <u>虽然里面的元素都是unvisited</u>，<u>但在调用的时候仍要检查是否visited了</u>

- 前半句：往里面添加元素的时候只添加unvisited的
- 后边句：从里面pop元素的时候还要检查这个元素是否visited：如果是，直接pop然后啥也不做；否，继续后续操作

- 原因：比如node0与node3相邻；node1与node3也相邻，先visit node0，此时queue为`{1,..., 3, ...}`，后续visit node1，因为此时node3仍然是标记为unvisited，node3**被再次加入queue**：`{..., 3, ..., 3}`，这样node3就重复了2次，当第一个node3被visited之后，还有一个重复的node3在里面，当该node3被pop时候，因为已经被visited了，只需要pop掉，就不要做后续的重复操作了

- 补充：调用pop的时候可以不检查是否visited：It’s okay to have duplicate elements in the queue. 重复visit已经visit过的点没关系，关键在于**首次visit**的相对顺序没有变：距离起始点长度为1的点的**首次visit**一定在长度为2的点的前面，因为长度为2更远的点一定是在长度为1的点**后面首次**加入queue的（induction）

[BFS Implementation](https://www.youtube.com/watch?v=xlVX7dXLS64&ab_channel=Reducible)

![Screen Shot 2023-07-02 at 23.45.04](/Users/bryant/Programming/cs106b/class_code/graph/image/Screen Shot 2023-07-02 at 23.45.04.png)

上述代码第一层就是在检查pop的元素是否visited，对应后半句话



**Init State and TODO-List**

![IMG_4F2244E3ADDC-1](/Users/bryant/Programming/cs106b/class_code/graph/image/IMG_4F2244E3ADDC-1.png)



**记路径BFS易错**

设置`prev`只能**设置1次**，因为如果之前设置过1次，说明之前那次的路径更近（因为是由近及远处理），就不要再设第2次：

```c++
if (!(i.second->prev)) { // pointing to the closest neighbor only
	i.second->prev = front;
}
```

