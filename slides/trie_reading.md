# Trie

In [computer science](https://en.wikipedia.org/wiki/Computer_science), a **trie**, also called **digital tree** or **prefix tree**,[[1\]](https://en.wikipedia.org/wiki/Trie#cite_note-cvr14-1) is a type of [*k*-ary](https://en.wikipedia.org/wiki/M-ary_tree) [search tree](https://en.wikipedia.org/wiki/Search_tree), a [tree](https://en.wikipedia.org/wiki/Tree_(data_structure)) [data structure](https://en.wikipedia.org/wiki/Data_structure) used for locating specific keys from within a set. These keys are most often [strings](https://en.wikipedia.org/wiki/String_(computer_science)), with <u>links between nodes defined not by the entire key, but by individual [characters](https://en.wikipedia.org/wiki/Character_(computing)). In order to access a key (to recover its value, change it, or remove it), the trie is traversed [depth-first](https://en.wikipedia.org/wiki/Depth-first_search), following the links between nodes, which represent each character in the key.</u>**各节点之间的link表示一个字符，访问一个key可以通过遍历节点之间的link来复原**

Unlike a [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree), nodes in the <u>trie do not store their associated key</u>. Instead, **a node's position in the trie defines the key with which it is associated.（走到某一个节点的位置，整个遍历的过程就定义/还原了一个key）** <u>This distributes the value of each key across the data structure, and means that not every node necessarily has an associated value.</u>

All the children of a node <u>have a common [prefix](https://en.wikipedia.org/wiki/Prefix) of the string associated with that parent node</u>, and the root is associated with the [empty string](https://en.wikipedia.org/wiki/Empty_string). This task of storing data accessible by its prefix can be accomplished in a memory-optimized way by employing a [radix tree](https://en.wikipedia.org/wiki/Radix_tree).

**Summary**

- Hallmark: prefix! + a link stores a character (position of a node stores a word)