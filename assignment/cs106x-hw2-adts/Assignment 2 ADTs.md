# Assignment 2: ADTs



The purpose of this assignment is to gain familiarity with a variety of ADTs such as Vectors, Stacks, Queues, Maps, Sets, Lexicons and Grids. **This is an individual assignment. You should write your own solution and not work in a pair on this program.**

This assignment consists of three parts: **Word Ladder**, where you find ways to morph one word into another, **Random Writer**, where your program randomly generates text based on a provided input text, and **Maze Generator**, where your program randomly generates solvable Mazes of different sizes. Each part can be programmed separately, but they should be submitted together. Your output should match exactly as much as possible (e.g. randomization for RandomWriter is acceptable, as are different word ladders of the same length as the sample output, assuming they are valid). The starter code for this project is available as a ZIP archive (this contains 3 separate QT projects, one for each part of this assignment).

## Development Strategy and Hints

This program can be tricky if you don't develop and debug it step-by-step. Don't try to write everything all at once. Make sure to test each part of the algorithm before you move on.



1. Think about exactly what types of collections to use for each part. Are duplicates allowed? Does order matter? Do you need random access? Where will you add/remove elements? Etc. Note that some parts of each program require you to make compound collections, that is, a collection of collections.
2. Refer to the [Stanford Library Documentation](http://stanford.edu/~stepp/cppdoc/)! This page documents all methods on Stanford Library collections.
3. Test each function with a very small input first. For example, use input file tiny.txt with a small number of words; this will let you print your entire map and examine its contents for debugging purposes.
4. Recall that you can print the contents of any collection to `cout` and examine its contents for debugging.
5. Remember that when you assign one collection to another using the = operator, <u>it makes a full copy of the entire contents of the collection.</u> This could be useful if you want to copy a collection.
6. You can loop over the elements of a vector or set using a for-each loop. A for-each also works on a map, iterating over the keys in the map. You can look up each associated value based on the key in the loop.
7. Don't forget to test your input on unusual inputs, like large and small values of N, large and small # of words to generate, large and small input files, and so on. It's hard to verify random input, but you can look in smallish input files to verify that a given word really does follow a given prefix from your map.



------

## Style

As in other assignments, you should follow our [Style Guide](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/style) for information about expected coding style. You are also expected to follow all of the general style constraints emphasized in the Homework 1 specs, such as the ones about good problem decomposition, parameters, using proper C++ idioms, and commenting. The following are additional points of emphasis and style constraints specific to this problem:

*Algorithms*: You should follow the general algorithms as described in this document and should not substitute a very different algorithm. You should not write a recursive algorithm for any of these problems.

*Collections*: You are expected to make intelligent decisions about what kind of collections from the Stanford C++ library to use at each step of your algorithm, as well as using those collections properly. Limit yourself to collections that have been taught in class; for example, do not use the Graph or BasicGraph collections. As much as possible, pass collections by reference, because passing them by value makes an expensive copy of the collection. Do not use pointers, arrays, or STL containers on this program.

*Redundancy*: You should avoid expensive operations that would cause you to reconstruct bulky collections multiple times unnecessarily. For example, you should not make a deep copy of all of the walls or cells in the maze unless absolutely necessary.



## Word Ladder

A **word ladder** is a bridge from one word to another, formed by changing one letter at a time, with the constraint that at each step the sequence of letters still forms a valid word. For example, here is a word ladder connecting the word `"code"` to the word `"data"`. Each changed letter is underlined as an illustration:

```
code` → `cade` → `cate` → `date` → `data
```

There are many other word ladders that connect these two words, but this one is the <u>shortest path</u> between them. That is, there might be others of the same length, but none with fewer steps than this one.

In the first part of this assignment, write a program that repeatedly prompts the user for two words and finds a minimum-length ladder linking the words. You must use the <u>Stack and Queue</u> collections from Chapter 5, along with following a particular provided algorithm to find the shortest word ladder.

### Example Run:

Here is an example log of interaction between your program and the user (with console input in red):



```
Welcome to CS 106B/X Word Ladder!
Please give me two English words, and I will convert the
first into the second by modifying one letter at a time.

Dictionary file name: dictionary.txt

Word 1 (or Enter to quit): code 
Word 2 (or Enter to quit): data 
A ladder from data back to code:
data date cate cade code

Word 1 (or Enter to quit): 
Have a nice day.
```



Notice that the word ladder <u>prints out in reverse order, from the second word back to the first.</u> If there are multiple valid word ladders of the same length between a given starting and ending word, your program can <u>choose any of them.</u> In this example, it would be fine for your program to choose any ladder of length 5, as that is the minimum length in this case.

Your code should <u>ignore case;</u> in other words, the user should be able to type uppercase, lowercase, mixed case, etc. words and the ladders should still <u>be found and displayed in lowercase.</u> You should also check for several kinds of **user input errors**, and not assume that the user will type valid input. Specifically, you should check that both words typed by the user are <u>valid words found in the dictionary</u>, that <u>they are the same length</u>, and that they are <u>not the same word.</u> If you receive invalid input, your program should print an error message and re-prompt the user. See the example output for examples.

Before the program can actually calculate a word ladder, it needs to <u>first read in a dictionary of all english words.</u> At the start, your program should prompt the user to enter a dictionary file name to use as the source of the English words. If the user types a filename that does not exist, reprompt them - see the example output for examples. We provide a file `dictionary.txt` for you to use, with one word per line (there are also smaller dictionary files included to help with testing). Read the dictionary file **just once** at the start of your program into a `Lexicon`. A `Lexicon` is another Stanford Library collection that can very efficiently store dictionaries of words (the runtime of many common single-word operations is `O(W)`, where `W` is the length of the word). Please see [the Lexicon class reference](http://stanford.edu/~stepp/cppdoc/Lexicon-class.html) for details. Once you read in the dictionary of words into the Lexicon, you can use the `contains()` method to check if a word is in the dictionary. You should **not loop over the dictionary as part of solving this problem.**

### Algorithm

Finding a word ladder is a specific instance of what is known as a shortest-path problem: a problem in which we try to find the shortest possible route from a given start to a given end point. Shortest-path problems come up in routing Internet packets, comparing gene mutations, Google Maps, and many other domains. The strategy we will use for finding the shortest path between our start and end words is called breadth-first search ("BFS"). This is a search process that gradually expands the set of paths among which we search “outwards:” BFS first considers all possible paths that are one step away from the starting point, then all possible paths two steps away, and so on, until a path is found connecting the start and end point. <u>A step can be understood as one unit of measurement</u>—depending on the problem, this could be a millisecond, a minute, a mile, a subway stop, and so on. By exploring all possible paths of a given length before incrementing to the next length, BFS guarantees that the first solution you find will be the shortest possible.

For word ladders, start by examining ladders that contain only words that are one “step” away from the starting word—i.e., words in which only one letter has been changed. If you find your ending word among these one-step-away ladders, congratulations—you’re done! If not, look for your target word in all ladders containing words that are two steps away, i.e., ladders in which two letters have been changed. Then check three letters, four, etc., until your target word is located. We implement the breadth-first algorithm using a `Queue` that stores partial ladders, each of which represents a possibility that we will examine in turn to see if it is a complete path between our start and ends words. Each partial ladder is represented as a `Stack`, which means that your overall collection will be a `Queue` of `Stack`s.

Here is a partial pseudocode description of the algorithm to solve the word-ladder problem. **Note:** some students complain at this point that we have given you too much information and that they want to figure the problem out on their own — if so, great! Don’t look at the pseudocode below if you want to try it on your own!

#### [Word Ladder Pseudocode (Click to show/hide)](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/assignments/adts.html#collapseTwo)

Some of the pseudo-code corresponds almost one-to-one with actual C++ code. Other parts are more abstract, such as the instruction to examine each "neighbor" of a given word. A neighbor of a given word w is a word of the same length as w that differs by exactly 1 letter from w. For example, “date” and “data” are neighbors; “dog” and “bog” are neighbors.

Your solution is not allowed to look for neighbors by looping over the dictionary every time; this is much too inefficient. To find all neighbors of a given word, use two nested loops: one that goes through each character index in the word, and one that loops through the letters of the alphabet from a-z, replacing the character in that index position with each of the 26 letters in turn. For example, when examining neighbors of “date”, you'd try:



- `aate,bate,cate,...,zate` ← *all possible neighbors where only the 1st letter is changed.*
- `date,dbte,dcte,...,dzte` ← *all possible neighbors where only the 2nd letter is changed.*
- ...
- `data,datb,datc,...,datz` ← *all possible neighbors where only the 4th letter is changed.*



Note that many of the possible letter combinations along the way (aate, dbte, datz, etc.) are not valid English words. Your algorithm has access to an English dictionary, and each time you generate a word using this looping process, you should look it up in the dictionary to make sure that it is actually a legal English word. Only valid English words should be included in your group of neighbors.

Another way of visualizing the search for neighboring words is to think of each letter index in the word as being a "spinner" that you can spin up and down to try all values A-Z for that letter. The diagram below tries to depict this:

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192//images/adts/spinner.png)

Another subtle issue is that you should not reuse words that have been included in a previous, shorter ladder. For example, suppose that you have the partial ladder cat → cot → cog in your queue. Later on, if your code is processing the ladder cat → cot → con, one neighbor of con is cog, so you might want to examine cat → cot → con → cog. But doing so is unnecessary. If there is a word ladder that begins with these four words, then there must be a shorter one that, in effect, cuts out the middleman by eliminating the unnecessary word con. As soon as you've enqueued a ladder ending with a specific word, you've found a minimum-length path from the starting word to the end word in that ladder, so you never have to enqueue that end word again.

To implement this strategy, keep track of the set of words that have already been used in any ladder. Ignore those words if they come up again. Keeping track of which words you've used also eliminates the possibility of getting trapped in an infinite loop by building a circular ladder, such as cat → cot → cog → bog → bag → bat → cat.

A final tip: it may be helpful to test your program on smaller dictionary files first to find bugs or issues related to your dictionary or to word searching.





## Maze Generator

In this problem you will write code to display the construction of a two-dimensional maze. Here's an example of one your program might generate:

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-1.png)

The goal is to create an n by n maze so there's one unique path from the upper left corner to the lower right one. Our algorithm for generating such mazes is fairly straightforward to describe and can be implemented using the services of the Stanford collections library. (By the way, it's not really our algorithm. It's a simplified version of [Kruskal's algorithm for minimal spanning trees](https://en.wikipedia.org/wiki/Kruskal's_algorithm), which we'll more formally discuss later on when we talk about graphs.)

The basic idea has you start with a maze where all possible walls are present, as in the figure shown below. All walls are present, and the grid is divided into 10 x 10 = 100 squares that we'll call locations or cells. (Our example here happens to involve a 10 x 10 grid, but it generalizes to any dimension.)

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-2.png)

For this program we will talk about "chambers," meaning groups of one or more locations that can reach each other because there is a path between them that is not blocked by walls. For example, if you were to knock down the walls separating three location cells L1, L2, and L3, we would now say that those three cells are part of the same chamber because they can all reach each other. With each iteration, your algorithm considers a <u>randomly selected wall that has not been considered before</u>, and <u>removes that wall if and only if it separates two cells that currently cannot reach each other;</u> that is, two cells that are part of two different chambers. The first randomly selected wall can always be removed, because all location cells are initially their own chambers.

The series of figures below illustrate the algorithm in action. The leftmost figure below shows a randomly chosen first wall being removed. After a several more iterations, you'll see that more randomly selected walls have been removed, as shown in the middle figure. All walls are considered exactly once in some random order until all location cells are part of one large connected chamber together. Initially there are 100 one-cell chambers in the 10 x 10 maze, so eventually 99 walls are erased to yield the completed maze shown in the rightmost figure below.

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-3.png)
*a single wall removed*

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-4.png)
*some walls removed*

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-6.png)
*99 walls removed (done)*

Your algorithm should not remove any more walls than necessary to complete the maze. This means that a wall must NOT be removed if the location cells on each side of that wall are already reachable from each other; that is, if they are already part of the same connected chamber. For example, the figure below is the same as the middle figure above, except with some walls circled. The circled walls in that figure should NOT be removed by the algorithm if it randomly checks them, because the location cells on the two sides of those walls are already part of the same chamber and can already reach each other.

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-maze-5.png)
*some walls that should not be removed*

Since the mazes you generate are random, it's almost impossible for you to match our output and mazes exactly. You can verify your program manually by inspecting the maze to ensure that all location cells are connected into a single chamber and the right number of walls have been removed.

### Implementation Details

```
void generateMaze() {
	// TODO: implement this function
}
		
```

For this program you will write a function generateMaze that performs the work to generate suitable mazes by removing walls. (Of course you should decompose the problem into smaller functions as you write it.) Here is a high-level pseudocode description of the algorithm you should use to generate your maze:

```
how to generate a maze:
    generate a collection of chambers, where each chamber initially includes one unique cell.
    repeat until all chambers are connected:
        randomly choose a wall W from the maze,
                where W separates two location cells that we'll call L1 and L2.
        if L1 and L2 cannot reach each other (if they are in different chambers):
            remove wall W from the maze.
            merge the chambers of L1 and L2.
```

A large part of the challenge of this problem lies in figuring out what collections are best for representing the various data. Notice that your code needs to be able to perform operations like the following efficiently:

- Randomly pick out a wall from the maze;
- Figure out which chamber a given location cell is in;
- Figure out whether two chambers are the same;
- Merge two chambers.

Part of your grade comes from choosing a good collection(s) for storing the data needed. You will probably need to use a <u>nested collection (a.k.a. compound collection)</u> to solve the problem. Hint: Though it's a two-dimensional maze on the screen, a Grid is a poor choice for solving this problem.

*Efficiency*: We discussed efficiency in terms of Big-Oh notation in lecture. While your algorithms are not restricted to any particular Big-Oh complexity class, you should verify that your algorithm removes the right number of walls and runs efficiently. The main way you should ensure your efficiency is in your choice of appropriate collections to store the data. Our solution can finish generating a 20x20 maze in under 1 second, a 30x30 maze in under 3-4 seconds, and a 40x40 maze in around 7-8 seconds (with the animation turned off), though this varies heavily from machine to machine. If your solution requires several multiples longer to finish (e.g. one minute or more for large mazes), it is likely implemented inefficiently and should be optimized further.

Your code will interact with some files provided by the instructor. You should include the header file `"mazetypes.h"` in your program to allow your code to access our provided types. The `mazetypes.h` file defines two types of object structures named `Cell` and `Wall` types that you should use in your algorithm. We have not talked much about using objects in the course so far, but these two are simple ones. A `Cell` object has only two public data fields inside it, two integers named `row` and `col`. A `Wall` object has only two public data fields inside it, two `Cells` named `one` and `two` representing the two location cells that are separated by this wall. Below are examples of using `Cell` and `Wall` objects:

```
// using Cell objects
Cell mycell;
mycell.row = 4;
mycell.col = 17;

// declare and initialize
Cell mycell2 {9, 22};

// store Cell in collection
Vector v;
v.add(mycell);
v[0].row++;

// print a Cell: {r09 c22}
Set set;
set.add(mycell2);
for (const Cell& cell : set) {
    cout << cell << endl;
}
		
// using Wall objects
Cell mycell1 {4, 17};
Cell mycell2 {22, 9};
Wall wall {mycell1, mycell2};
cout << wall.one << endl;   // {r04 c17}
cout << wall.two << endl;   // {r22 c09}

// store Wall in collection
Vector v;
v.add(wall);
v[0].one.row++;
v[0].two.col--;

...
		
```

Unlike most of the programs you have written so far in this course, in this problem you will not write the `main` function, nor will you perform any direct user interaction with `cout` or user input functions. Instead you should include the header file `"mazegui.h"` in your file to allow your code to utilize an instructor-provided graphical user interface (GUI). The `mazegui.h` file has the program's `main` function and handles the overall user interaction. The graphical UI has only a few functions that you will need to use in your code. They are listed in the table below.

| Command                      | Description                                                  |
| :--------------------------- | :----------------------------------------------------------- |
| `MazeGUI::getAllCells()`     | Returns all location cells in the maze as a `Vector` of `Cell` objects. |
| `MazeGUI::getAllWalls()`     | Returns all walls between cells in the maze as a `Vector` of `Wall` objects. The vector has already been shuffled into a random order. |
| `MazeGUI::removeWall(wall);` | Removes the given wall (represented as a `Wall` object) from the maze. |

Here is a screenshot of the GUI in action. You can use the GUI to create a maze of a given size (containing walls between all neighboring locations), and press the Generate button to engage your code to try to remove the walls as appropriate. To speed up the program, turn off the "Animation" checkbox before generating.

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/adts/mazegenerator-gui-screenshot.png)
*The instructor-provided GUI*

*Debugging*: Though the program has a graphical UI, you can still use `cout` to print statements to the console to help you debug your program. Such messages will appear in the bottom console pane of Qt Creator. Remember to remove any such debugging output from your code before you turn it in. Also see the debugging handout for more tips on how to debug your programs.