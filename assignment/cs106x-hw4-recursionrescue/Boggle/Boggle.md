## Problem Description:

![boggle game](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/img/marty/bogglegame.jpg)

**Boggle** is a board game with a 4x4 square grid of letter cubes where players try to <u>make words by connecting letters on adjacent cubes.</u> For this part of the assignment, you will write code to search a Boggle board for words using backtracking.

We provide you with starter code in **bogglemain.cpp** that implements the text user interface of the game. You must write the functions to search the board for words in **bogglesearch.cpp**.

![lettercube](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/img/marty/letter-cube.jpg)**Letter cubes** are 6-sided dice with a letter on each side rather than a number. In the real game, you shake up the letter cubes and lay them out on the board. In our version, we will ask you to type the 16 letters that make up the board.

The goal is to <u>find words on the board by tracing a path through **neighboring letters**.</u> Two letter cubes are <u>neighbors if they are next to each other horizontally, vertically, or diagonally.</u> Therefore there are <u>up to eight neighbors</u> near a cube. Each cube can be used <u>at most once</u> in a given word.

In the real-life version of this game, all players work at the same time, listing the words they find on a piece of paper. But in the version we will write, a single human player will play a single turn against an omniscient computer opponent.

The **human player** plays first, entering words one by one. Your code verifies that the <u>word is is at least 4 letters long</u>, then uses <u>backtracking to see if the word can be made using letters on the board, using any cube at most once.</u>**(one solution)**

Once the player has found as many words as they can, the **computer player** takes a turn. The computer searches through the board using recursive backtracking to find all the possible words that can be formed. The computer's algorithm is similar to the human's, but rather than verifying the existence of a single word in the board, <u>you are exhaustively finding the set of all possible words.</u>

*Comparing output:* Your program uses an instructor-provided **graphical user interface**, and it produces only a small amount of console output. The Stanford console window does not pop up; the console output will appear in the bottom Application Output area of Qt Creator to help you debug your code. You can copy/paste your console output from the bottom of Qt Creator into our web-based [Output Comparison Tool page](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/diff.shtml) to see if your boards' words match ours.

![screenshot](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/img/marty/boggle-screenshot-1.png)

## Implementation Details:

You must implement the following functions to complete the Boggle game. You must write the functions with exactly the headers shown here. (It is fine to have "helper functions" as needed.) None of your functions should print any output to the console.

### Utility function: Generate a random board

```
Grid<char> generateRandomBoard(int size, const Vector<string>& letterCubes)
```

In this function you should generate and return a random Boggle board of the given size using the given collection of letter cube values. This function is **not recursive** and can be implemented using loops. The *size* parameter is the number of rows or columns; for example, if *size* is 4, you should return a grid with 4 rows and 4 columns to represent a 4x4 game board. You may assume that <u>a valid size</u> has been passed (between 4 and 6 inclusive). **Error handling**

The vector of cubes passed represents the letter cubes to be "rolled" to generate your random board. **Assume that the vector contains exactly *size* * *size* strings, each of which is exactly 6 characters long.** error

**The standard Boggle game comes with sixteen letter cubes, each with particular letters on each of their six faces. The letters on each cube are not random; they were chosen in such a way that common letters come up more often and it is easier to get a good mix of vowels and consonants.**? We want your Boggle game to match this. The following table lists all of the letters on all six faces of each of the sixteen cubes from the original Boggle. You <u>don't need to declare these cubes</u> in your code; these are the sixteen string elements of the vector that is passed to your function.

```
AAEEGN, ABBJOO, ACHOPS, AFFKPS,
AOOTTW, CIMOTU, DEILRX, DELRVY,
DISTTY, EEGHNW, EEINSU, EHRTVW,
EIOSST, ELRTTY, HIMNQU, HLNNRZ
```

At the beginning of each game, you must "shake" (randomize) the board cubes. There are two different random aspects to consider:

1. A random location on the NxN game board should be chosen for each cube. (For example, the `AAEEGN` cube should not always appear in the top-left square of the board; it should randomly appear in one of the 16 available squares with equal probability.)
2. A random side from each cube should be chosen to be the face-up letter of that cube. (For example, the `AAEEGN` cube should not always show A; it should randomly show A 1/3 of the time, E 1/3 of the time, G 1/6 of the time, and N 1/6 of the time.)

The Stanford C++ libraries have a file **"shuffle.h"** with a `shuffle` function you can use to rearrange the elements of an array, Vector, or Grid. See shuffle.h if you are curious about how the shuffling algorithm works. ([shuffle.h documentation](http://stanford.edu/~stepp/cppdoc/shuffle.html))

If the user has selected 5x5 Big Boggle, you will be passed size of 5 and a 25-element vector of letter cubes, and you should return an appropriate 5x5 grid. If the user has selected 6x6 Super Big Boggle, you will be passed size of 6 and a 36-element vector of letter cubes, and you should return an appropriate 6x6 grid.

The game also has an option where the user can enter a <u>manual board configuration</u> rather than choosing one randomly. In this option, rather than randomly choosing the letters to be on the board, the user enters a string of 16 (or 25, or 36) characters, representing the cubes from left to right, top to bottom. This is a useful feature for testing your code and can be used even if your random board code is incomplete or broken. You don't need to write any code to support the manual board configuration option; it is already provided by the GUI. The manual configuration is a loophole because it allows the user to type a board that is not possible to create using the real letter cubes, such as a board of all Qs or something like that. We won't try to catch and prevent such a thing, partly because it is useful to be able to test your code on unusual boards.

### Human player's turn:

```
bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& word)
```

Implement the human turn by writing a `humanWordSearch` function with exactly the heading above. The grid of characters represents the game board, and the string word represents the word that the player wants you to search for. Your function should determine whether this word can be formed by connecting neighboring cubes of letters on the board. If so, you should return `true`; if not, you should return `false`.

Certain cases should cause your function to *immediately* return `false` and not perform any recursive search. One such special case is if the word passed is <u>not found in the given dictionary.</u> Another special case is if the word passed has a <u>length less than</u> `BoggleGUI::MIN_WORD_LENGTH` (which defaults to 4).

Your code for this function should use **recursive backtracking** to search the board for the letters of the given word. If the word is an unsuitable length (less than the minimum just described), you should not perform the recursive search. Your method should be **case-insensitive去除大小写！**; you should properly search for the word whether it is passed in upper, lower, or mixed case. <u>You may assume that the characters on the board grid are all uppercase letters from A-Z, and that the word passed contains no characters other than letters from A-Z.</u>**error handling**

Recall that algorithms that use backtracking often rely on additional parameters to keep track of choices. For either of the functions in this problem, you may write **helper functions** that accept any parameters you like, so long as your overall `humanWordSearch` function has exactly the heading above. Your function should not modify the board grid or dictionary lexicon that are passed to it, which is part of the reason they are declared as `const`. (**helper** copy!)

You don't want to visit the same letter cube twice during a given exploration, so for the search algorithm to work, your code needs some way to **"mark"** whether a letter cube has been visited or not. In the Maze problem, we gave you a class that helped you to "mark" squares, but in this problem you will need to come up with your own way to get a similar effect. You will have to decide what is the best strategy to use for marking; it's up to you, as long as it is efficient and works.

*Scoring:* If the word is valid and can be formed on the board (if your method would return `true`), you must also indicate to the GUI that the player has scored points. You can do this using the method `BoggleGUI::scorePoints` as described later in this document. The length of the word determines the score as follows:

- Words of 4 or fewer letters are worth 1 point.
- 5-letter words are worth 2 points.
- 6-letter words are worth 3 points.
- 7-letter words are worth 5 points.
- Words longer than 7 letters are worth 11 points.

There is no penalty for trying an invalid word, but invalid words also do not count toward the player's list or score.

*Graphics:* As each cube is explored, you should **highlight做标记！** it in the GUI to perform an animated search with a 100ms delay (see GUI section later). That is, when your search looks at a given cube on the board and examines it to decide whether it can be included in the word you are searching for, set it to be highlighted. If you backtrack and decide not to use that letter cube in your word search, set it to be un-highlighted. <u>At the start of your human word search, you should</u> <u>clear any highlighting that exists on any letter cubes from previous searches.</u> You can do the highlighting using the methods `BoggleGUI::setHighlighted` and `BoggleGUI::clearHighlighting` as described later in this document.

*Board size:* Note that both of your word search functions must work properly whether you are passed a 4x4, 5x5, 6x6, or any other size board. You may assume that the board's state is valid, that every character in the grid is an uppercase letter from A-Z, and so on.

### Computer player's turn:

```
Set<string> computerWordSearch(const Grid<char>& board,
                              const Lexicon& dictionary,
                              const Set<string>& humanWords)
```

Implement the computer's turn word search by writing a `computerWordSearch` function with exactly the heading above. The grid of characters represents the game board, and the lexicon represents the set of all valid English words in the dictionary. Your code should find *every word* that can be made on the given board that is at least 4 letters long and is found in the given dictionary. Your function should return a `Set` of all such words, <u>all in uppercase.</u>

Your code for this function should use **recursive backtracking** to search the board for all suitable words that can be formed using its letters. The idea is to do a search starting from each of the 16 letter cubes, looking for all valid words that start with that cube's letter. <u>You can explore that starting cube, then each of its neighboring cubes, then each neighbor's neighbor, and so on. Along the way, as you find valid words, you should gather them into a collection, which will eventually be returned at the end of all exploration.</u>

Though similar to your human search, the code is different because you should look for all words, not just verify a single word. Therefore we insist that the code for the computer search must be implemented separately from `humanWordSearch`. **Repeat: Do not try to combine the human and computer into a single helper function, and do not have one of the wordSearch functions call the other one. Write them as completely separate algorithms.**

Your computer word search is passed a set of strings representing all of the words that the human found during his/her turn. The computer's goal is to find all of the words <u>that the human did not already find</u>. So if your recursive search finds a word that was already found by the human, you should not include it in the result that is returned by your computer word search.

*Scoring:* As with the human player's turn, you must compute the number of points scored by the computer for each word and indicate this to the GUI using the method `BoggleGUI::scorePoints`. See the section on the human word search for the list of how many points each word is worth.

*Efficiency and pruning*: Efficiency is very important for this part of the program. It is important to limit the search to ensure that the process can be completed quickly. If written properly, the code to find all words on the board should run in around one second or less. To make sure your code is efficient enough, you must perform the following optimizations:

- use a `Lexicon` to store the English dictionary, and do not needlessly copy the lexicon
- prune the tree of searches by not exploring partial paths that will be unable to form a valid word
- use efficient data structures otherwise in your program (e.g. <u>to represent which words are already found</u>)

*Pruning:* One of the most important Boggle strategies is to **prune dead-end searches**. The `Lexicon` has a `containsPrefix` function that accepts a `string` and returns `true` <u>if any word in the dictionary begins with that substring.</u> For example, if the first cube you examine shows the letter Z and your algorithm tries to explore one of its neighbors that shows an X, your path would start with ZX. In this case, `lex.containsPrefix("ZX")` will return `false` to inform you that there are no English words that begin with the prefix "ZX". Therefore your algorithm should stop that path and move on to other combinations. If you do not implement this optimization, your search will be too slow.

*Graphics:* Unlike the human search, the computer word search **does not perform any highlighting** in the GUI. You should, however, tell the GUI to score the points for each valid word that the computer finds.

Make sure to extensively **test** your program. Run the demo solution linked from this document to see the expected behavior of your program. When in doubt, match the behavior described in this spec and/or that of the demo.

### Graphical User Interface (GUI):

This problem uses an instructor-provided graphical user interface (GUI) for all user interaction rather than a console UI. The GUI is represented by the files **bogglegui.h** and **bogglegui.cpp**. The `BoggleGUI` class has the following static member functions that you can call as needed from your Boggle searching code:

|               Static Member Function                |                         Description                          |
| :-------------------------------------------------: | :----------------------------------------------------------: |
|          `BoggleGUI::clearHighlighting();`          |         Sets all letter cubes to be un-highlighted.          |
|         `BoggleGUI::playSound("filename");`         |        plays a sound effect from the given audio file        |
|       `BoggleGUI::scorePointsHuman(points);`        | Adds the given number of points to the human player's score  |
|       `BoggleGUI::scorePointsHuman(points);`        | Adds the given number of points to the computer player's score |
| `BoggleGUI::setHighlighted(row, col, highlighted);` | Sets the letter cube at the given 0-based row/col index to be highlighted (`true`) or un-highlighted (`false`) |

## Style Details:

As in other assignments, you should follow our [**Style Guide**](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/styleguide.html) for information about expected coding style. You are also expected to follow all of the general style constraints emphasized in the Homework 1-3 specs, such as the ones about good problem decomposition, parameters, using proper C++ idioms, and commenting. The following are additional points of emphasis and style contraints specific to this problem:

*Recursion and backtracking:* Part of your grade will come from appropriately utilizing recursive backtracking to implement your word-finding algorithm as described previously. We will also grade on the elegance of your recursive algorithm; don't create special cases in your recursive code if they are not necessary. Avoid **"arm's length" recursion**, which is where the true base case is not found and unnecessary code/logic is stuck into the recursive case. Efficiency of your recursive backtracking algorithms, such as avoiding dead-end searches by pruning, is very important.

**Redundancy** in recursive code is another major grading focus; avoid repeated logic as much as possible. As mentioned previously, it is fine (sometimes necessary) to use "helper" functions to assist you in implementing the recursive algorithms for any part of the assignment.

*Variables:* While this constraint is not new to this assignment, we want to stress that you should not make any **global variables** or **static variables** (unless they are constants declared with the `const` keyword). Do not use globals as a way of getting around proper recursion and parameter-passing on this assignment.

*Loops/Collections:* Loops and collections *are* allowed on this problem. But your fundamental algorithm must be recursive and not based on looping to perform the entire word search. You must use recursion to handle the self-similar aspects of the problem.

*Commenting:* Of course you should have a comment header at the top of your code file and on top of each function. But we want to remind you that you should also have **inline comments** inside functions to explain complex sections of the code. Don't forget to place descriptive inline comments as needed on any complex code in the bodies to describe nontrivial parts of your algorithms.

## Frequently Asked Questions (FAQ):

For each assignment problem, we receive various frequent student questions. The answers to some of those questions can be found by clicking the link below.

[**Boggle FAQ** (click to show)](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/boggle.html#)

## Possible Extra Features:

Here are some ideas for extra features that you could add to your program:

- **Make the Q a useful letter:** The Q is largely useless unless it is adjacent to a U, so the real Boggle prints Qu together on a single face of the cube. You use both letters together, a strategy that not only makes the Q more playable but also allows you to increase your score because the combination counts as two letters.
- **Embellish the GUI:** Our Boggle GUI module is supplied in source form so you can adapt into a snazzier interface. For example, the current game merely highlights the word; it might be nice if it also drew lines or arrows marking the connections. Or you could use the Stanford C++ library's **"gevent.h"** facilities to let the user assemble a word by clicking or dragging the mouse through the letter cubes. Make it play sounds. Etc.
- **Board exploration:** As you will learn, some Boggle boards are a lot more fruitful that others. Write some code to discover things about the possible boards. Is there an arrangement of the standard cubes that produces a board containing no words? What about an arrangement that produces a longest word, maybe even using all the cubes? What is the highest-scoring board you can construct? Recursion will be handy in trying out all the possible arrangements, but there are a lot of options (do the math on all the permutations...), so you may need to come up with some heuristics to direct your explorations.
- **Other:** If you have your own creative idea for an extra feature, ask your SL and/or the instructor about it.

*Indicating that you have done extra features:* If you complete any extra features, then in the comment heading on the top of your program, please list all extra features that you worked on and where in the code they can be found (what functions, lines, etc. so that the grader can look at their code easily).

*Submitting a program with extra features:* Since we use automated testing for part of our grading process, it is important that you submit a program that conforms to the preceding spec, even if you want to do extra features. If your feature(s) cause your program to change the output that it produces in such a way that it no longer matches the expected sample output test cases provided, you should submit two versions of your program file: a first one with the standard file name without any extra features added (or with all necessary features disabled or commented out), and a second one whose file name has the suffix **-extra.cpp** with the extra features enabled. Please distinguish them in by explaining which is which in the comment header. Our turnin system saves every submission you make, so if you make multiple submissions we will be able to view all of them; your previously submitted files will not be lost or overwritten.