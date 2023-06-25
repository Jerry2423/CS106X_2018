# Assignment 5: MiniBrowser

![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/hero.png)

In this assignment, you'll use classes and linked lists to implement several features found in a web browser. Specifically, the starter code contains logic to search Wikipedia for an article and display that Wikipedia Article to a user. Your job is to implement the following features:

- Displaying text: The text is laid out in individual lines on a graphical canvas. We have a scrollbar that should allow a user to move up or down a page, changing which lines are displayed. You'll implement a **Vector**-backed class to determine which lines should be displayed.
- History via forwards and back buttons: these buttons should allow you to return to the previous screen via the back button or return to a more recent screen via the forward button, just as these buttons work in a web browser. You will use a **doubly-linked list** in your implementation.
- Cache: Recently viewed pages should be saved to allow the back button to load more quickly. You'll use a **doubly-linked list** in your implementation

In order to test your implementation, you are welcome to run the full program (and you will need an internet connection to do so). We, however, suggest that you test each component individually using the provided unit test classes for each part of the assignment. You will need to add several tests for each of the components to be confident that your implementation is correct.



## Development Strategy and Hints



- **Draw pictures**: When manipulating linked lists, it is often helpful to draw pictures of the linked list before, during, and after each of the operations you perform on it. Manipulating linked lists can be tricky, but if you have a picture in front of you as you're coding, it can make your job substantially easier.
- **List states:** When processing a linked list, you should consider different list states and transitions between them in your code as you add and remove elements. You should also think about the effect of adding a node in the front, middle, and back of the list of a given state.
- ***Test your code thoroughly!\*** We'll be running a battery of automated tests on your code; make sure to test various different inputs and edge cases to ensure it works correctly. One tip to help test your data structures is writing `print` methods for your data structures that print out a text representation of its data. That way, you can call your print function to help you debug, just as you would print out an ADT when stuck on previous assignments. The debugger will also almost certainly come in handy, as you can explicitly see the values of pointers.
- ***Implement the parts in order:\*** The parts are designed to be in order of increasing difficulty. The cache in particular is much more challenging than the other parts of the assignment.



------

## Style

As in other assignments, you should follow our Style Guide for information about expected coding style. You are also expected to follow all of the general style constraints emphasized in the Homework 1-4 specs, such as the ones about good problem decomposition, parameters, using proper C++ idioms, and commenting. The following are additional points of emphasis and style constraints specific to this problem:

*Commenting*: Add descriptive comments to your .h and .cpp files. Both files should have top-of-file header comments that summarize what your program does, and how. One file should have header comments atop each member function (either the .h or .cpp; your choice). The .cpp file should have internal comments describing the details of each function's implementation.

*Redundancy*: avoid repeated logic as much as possible. Your classes will be graded on whether you make good choices about what members it should have, and other factors such as which are public vs. private, and const-correctness, and so on. We also expect you to remove redundancy within a single class. For instance, if one implementation has a common operation, make a private helper function and call it multiple times in that file.

*Restrictions on pointers*: The whole point of this assignment is to practice pointers, linked lists and classes. Therefore, do not declare or use any other collections in any part of your code, except for the `Vector` in `LineManager` and the `HashMap` in `Cache`. There are some C++ "smart pointer" libraries that manage pointers and memory automatically, allocating and freeing memory as needed; you should not use any such libraries on this assignment.

*Make member functions `const` as appropriate.* Some of the member functions you will write do not modify the state of the instance they are being called on. For all such functions, mark them as `const` at the end of their headers in the .h and .cpp files in your code. For example, if a member named `foo` doesn't modify the instance, you should change its header to:

*You should implement all required member functions exactly as specified*, and should not make any changes to the function parameters, name, return type, etc.

```
		class MyClass {
		    ...
		    void functionName() const;
		};
		
```

*Avoiding memory leaks*: This item is listed under Style even though it is technically a functional requirement, because memory leakage is not usually visible while a program is running. To ensure that your classes do not leak memory, you must delete all of the node objects in your linked lists whenever data is removed or cleared from the list. You must also properly implement a destructor that deletes the heap memory used by instances of your classes.



## Displaying Text

Once you complete this part of the assignment, your browser should be able to display scrollable webpage text. If left unimplemented, you will not see any text onscreen.

In this part of the assignment, you'll implement a class called `LineManager` that <u>stores all the lines for the current webpage, and provides information about which lines should be displayed onscreen.</u> The only member variable (a.k.a. instance variable; private variable; field) you are allowed to have in your implementation is a <u>Vector of pointers to Lines.</u> do not use any other collections or data structures in any part of your code, or have any other private instance variables.

You will need to use `Line` objects, <u>which represent a single line of text</u> (spanning the entire width of the page). Below is an image of MiniBrowser, with each line outlined in red. The widths of all the lines are the same, and you can <u>sort lines by y-coordinate, with the top line (one with the smallest y-coordinate) as the smallest.</u> In the example below, the line "The Princess Bride is a 1973 fantasy romance novel by American" is the first Line in the webpage.

![A screenshot with each line outlined in red](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/Lines.png)

You will not need to manipulate or interact with the text; you can just treat the lines as <u>rectangles (potentially with space between them) that together make up the webpage. No two `Line` objects will overlap.</u>

The browser already handles <u>splitting the entire webpage into lines.</u> However, since the webpage (generally) is not visible all at once, <u>not all of the lines need to be drawn</u>; in fact, drawing all of the lines would make your browser run very slowly. The solution is an optimization to <u>only draw those lines that will be visible, so your job is to write a function to determine which lines should be drawn.</u> As the user scrolls up or down the page, the <u>"visible range" of lines will change.</u>

Browsers also need to handle user clicks, recognizing, for example, if the user is attempting to follow a <u>hyperlink. You will implement a method that, given a y-coordinate, returns a pointer to the line at that location.</u> Our starter code will then search that line for a link, allowing the user to travel to different pages.

[At this link](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/assignments/minibrowser-line-demo.html), you will find a sample interactive webpage with 12 lines of text and a scrollbar on the right (inside the black box). The black box indicates what is actually visible on the computer, but as you drag the scrollbar (give it a try), the lines will scroll out of view. The browser could render (draw) all the lines of the webpage, <u>but since only 4-5 are visible at a time, it can optimize and only draw those that are fully or partially on the screen.</u> Below the screen, linesInRange's value will update with which lines are in the viewable range of the screen.
The red "x" on the screen represents a location where the user may click; the line at the location of the "x" is reflected next to lineAt at the bottom of the demo. Note that there may be space between the lines, so the element is sometimes nullptr.

A `Line` has the following fields and methods:

|  Field/Method  |                         Description                          |
| :------------: | :----------------------------------------------------------: |
| double lowY()  | Returns the low end of the range occupied by this line. This value is inclusive. |
| double highY() | Returns the high end of the range occupied by this line. This value is inclusive. |

Since each line spans the width of a page, we only need to store information about its height and vertical placement, not its width or horizontal placement.

As each `Line` corresponds to a line of text, we can **order** `Lines` by their y-coordinate, meaning that the first `Line` is the line at the top of the screen.

To avoid having to store the text associated with a Line multiple times and to more easily be able to link a Line a user clicked on with the text, you will only be dealing with **pointers to `Lines`**. Thus, whenever you store or manipulate the `Lines`, you should do so using pointers. You should not **create `Lines`** in your implementation.

Your job is to implement the following functions:

|                     Method                      |                         Description                          | Big O |
| :---------------------------------------------: | :----------------------------------------------------------: | :---: |
|   `LineManager(const Vector<Line *> & lines)`   | The constructor should store the lines internally in order of their y-coordinates, from least to most. `lines` is a Vector of pointers to `Lines` **sorted** in reading order. | O(N)  |
|                `~LineManager()`                 | The destructor. You should be sure not to leak any memory. (Hint: did you allocate any memory in your implementation that needs to be deleted?) | O(1)  |
|             `contentHeight() const`             | This function should return the vertical space that all the lines occupy (i.e. how tall the browser would need to be to be able to fit all the lines at once). You may assume that the first line is at y-coordinate 0. | O(1)  |
| `linesInRange(double lowY, double highY) const` | This function should return a Vector of pointers to all `Lines` that are partially or fully within the bounds of `lowY` to `highY` (inclusive). That is to say, `linesInRange(60, 80)` should include a `Line` with lowY of 45 and a highY of 65, a line with a lowY of 80 and highY of 100, as well as a line with a lowY of 20 and a highY of 85, but it would not include a line with a lowY of 20 and highY of 40. The Vector should be sorted from lowest to highest y value. | O(N)  |
|            `lineAt(double y) const`             | This function should return a pointer to the Line that contains the given y-value. You can assume that there is at most one such line. If no line exists at that y-value, you should return `nullptr`. | O(N)  |

The members listed above represent your class's required behavior. But you may add other member functions to help you implement all of the appropriate behavior. <u>Any other member functions you provide must be private.</u> Remember that each member function of your class should have a clear, coherent purpose. You should provide private helper members for common repeated operations. Make a member function and/or parameter const if it does not perform modification of the object's state.

## Browser History

Once you complete this part of the assignment, your browser should be able to navigate forwards and backwards through page history using the forwards and backwards buttons. The buttons will be grayed out if you cannot go forwards and backwards from a particular page. If left unimplemented, those buttons will always be grayed out.

A history allows a user to navigate forwards and backwards between pages that they've already viewed. You will implement the `History` class using a **doubly-linked list**, where <u>one end of the list is the title of the most recently viewed **new** page</u> (i.e. the one that should be loaded after hitting the forwards button as many times as permitted), and the other is the title of the least recently viewed page (i.e. the first page that the user visited). You will need to maintain a "curr" pointer that represents the current page in the History (**the diagrams below include labels for the front and back of the list below the list, though you may find you don't need pointers to one or both ends of the list**?).

To create the doubly-linked list of article titles, you can use the `Node` struct defined in **History.h**:

```
struct Node {
    std::string title;  // the title of the article
    Node *prev;  // the node representing the article the user visited before this one
    Node *next;  // the node representing the article the user visited after this one
};
```

You will implement the following methods by editing **History.cpp** and **History.h**:

|            Function Name            |                         Description                          | Big-Oh |
| :---------------------------------: | :----------------------------------------------------------: | :----: |
|        `History::History()`         |    Constructor to create an <u>empty History object.</u>     |  O(1)  |
|        `History::~History()`        | Destructor for History. You should make sure not to leak any memory. |  O(N)  |
|   `History::hasPrevious() const`    | Returns whether the user visited a page prior to this one (whether there is a page before curr). |  O(1)  |
|     `History::hasNext() const`      | Returns whether the user visited a page after this one (whether there is a page after curr). |  O(1)  |
|          `History::next()`          | <u>Returns the string title</u> of the page the user visited after the current page. The <u>curr pointer should move to the next page.</u> The History should update itself to reflect that the next page is the new current page. This method should <u>throw an error</u> using the `error()` function if there is no next page. |  O(1)  |
|        `History::previous()`        | Returns the string title of the page the user visited before the current page. The curr pointer should move to the previous page. The History should update itself to reflect that the previous page is the new current page. This method should throw an error using the `error()` function if there is no previous page. |  O(1)  |
| `History::goTo(const string &page)` | ?The name of the page the user searched for. After this function, `hasNext()` should return `false`. All pages after the current page **before** goTo was called should be removed from the History (make sure not to leak memory). **The page visited should be added to the History as the current page.** The curr pointer should point to this new page, which should be the end of the linked list. You can assume that this function will only be called if the page is changed for a reason other than hitting the next/previous button. The effects of hitting next/ previous will be implemented by calling `next()` and `previous()`, not this function. |  O(N)  |

None of these methods should leak memory if you need to rewire pointers.

As a more concrete example of how the History object should function, consider a series of user actions and the resulting History object.

|                         User Action                          |                      Resulting History                       |                            Image                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|                 A History object is created.                 | The History should be empty. `hasNext()` and `hasPrevious()` should both return `false`. |                                                              |
| User opens the "Stanford University" page, then the "Stanford Band" page, and finally, the "The Play (American football)". | The current page should be "The Play (American football)". `hasNext()` should return `false`, but `hasPrevious()` should return `true`. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/History1.png) |
| The user presses the back button (calling `previous()` on the History object). The call to previous returned "Stanford Band". | The current page should be "Stanford Band". `hasNext()` and `hasPrevious()` should both return `true`. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/History2.png) |
|              The user searches "Scramble band".              | The current page should be "Scramble band". `hasNext()` should be false, but `hasPrevious()` should be true. Note: "The Play (American football)" should no longer be in the user's history. If the user had visited any pages after "The Play (American football)", those should be removed as well. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/History3.png) |



## Cache

Once you complete this part of the assignment, your browser should be able to load cached pages instead of having to re-fetch them each time. Instead of seeing the loading text at the bottom of the screen and waiting several seconds, the page should load instantaneously. If left unimplemented, you will still be able to navigate pages, but each page change will take several seconds to load.

<u>The History component only stores **article titles**,</u> meaning that as is, when the user returns to a previously loaded page, they still have to wait for the page to be downloaded from Wikipedia.

You will implement <u>a cache to save previously loaded pages</u> to avoid having to completely reload the page. You can't indefinitely store all articles a user loads - your computer would run out of memory! As a result, <u>our cache will have a fixed capacity and will choose an article to remove when it gets too full</u> (so that the total number of articles in the cache never exceeds the capacity). There are many ways to choose which article to remove, but we'll be implementing a common version called a **[Least-Recently Used (LRU) cache](https://en.wikipedia.org/wiki/Cache_replacement_policies)**, meaning that that the article that was accessed the least recently should be the one removed.

Because <u>Least-Recently Used caches</u> are incredibly useful, we will create a **template class**. See the LinkedListClass example from lecture for an example of how to implement a templatized class. While this browser will have each node store an article, you could store anything as the value - that's the power of templates!

To keep track of the order in which elements in our cache were accessed, we'll use a **doubly-linked list** of `Nodes` structs ordered by how recently the element was accessed (i.e. the <u>most recently loaded article should be at the end of the list</u>, and the <u>least recently viewed article **will be** at the start of the linked list</u>). You can think of this as conceptually matching the order for the history part of this assignment - newest at the right, oldest at the left.

The `Node` struct is defined as follows (in **Cache.h**):

```
struct Node {
    std::string key; // the key associated with this entry. For articles, it's the article title
    ValueType value; // the actual element stored in the cache
    Node* prev; // the node with the element visited less recently than this element
    Node* next; // the node with the element visited more recently than this element

};
```

In creating the cache, you'll need to implement the following methods by editing **Cache.cpp**.

|                      Method                       |                         Description                          |
| :-----------------------------------------------: | :----------------------------------------------------------: |
|               `Cache(int maxSize)`                | The constructor should create an empty cache of the given capacity. |
|                     `~Cache`                      |      The destructor. Make sure not to leak any memory.       |
| `put(const string & key, const ValueType& value)` | The put method should add an element to the cache with the associated key. This element should now be <u>the most recently viewed</u> element in the cache. If the cache is full, the <u>least-recently accessed item should be removed.</u> Note: if the element <u>already existed in the cache, it shouldn't be added again; rather, you should just ensure that the element is the most recently viewed in the cache (move it to the end of the list).</u> You should be careful that you never exceed the capacity of the cache. |
|      `containsKey(const string &key) const`       | Returns true if any of the elements in the cache have that string key, otherwise false. |
|             `get(const string& key)`              | This method should return the element with the given title. <u>The requested element should now be the most recently viewed page in the cache (i.e. at the end of the list).check and move to the end.</u> If no element exists in the cache with that string key, you should throw an error using the `error(string message)` function. |

Because Cache is a template class and Node is a template struct, you may have difficulty in the .cpp file if you want to create any helper functions that return a Node or take a node as a parameter. You should use the following syntax to do so:

```
// returning a Node *
template <typename ValueType>
typename Cache<ValueType>::Node* Cache<ValueType>::myAwesomeFunction() {
    ...
}

// Node * as parameter
template <typename ValueType>
void Cache<ValueType>::myAwesomeFunction(typename Cache<ValueType>::Node* node) {
    ...
}
```

You may have realized while our cache works as described above, determining if an article is in the cache requires an O(N) search. To optimize, **after you have completed the doubly-linked list implementation described above**, you should add a [`HashMap`](https://stanford.edu/~stepp/cppdoc/HashMap-class.html) to the cache that maps string keys to where they are stored in the doubly-linked list. Think about what data types might be useful to achieve this.

You should be careful to test your doubly-linked list implementation thoroughly before adding the HashMap. Additionally, make sure that your HashMap and the linked list always have the same articles stored.

For a more concrete example of how the HashMap and LinkedList work together in the Cache, consider a series of user actions and the resulting Cache object. The Article is omitted from the image below, for clarity.

|                         User Action                          |                       Resulting Cache                        |                            Image                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|       A Cache object is created with a capacity of 3.        | The Cache should be empty but will be constrained to hold no more than 3 items at a time. `containsKey` for any article title should return false. |                                                              |
| User searches for and opens the "Stanford University" page.  | The browser first tries to call `containsKey("Stanford University")`. Since the cache does not contain "Stanford University," the browser will download the page and then `put` it in the cache. Afterwards, the cache should have one element, "Stanford University", which is also the most-recently seen element. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/Cache1.png) |
| User searches for and opens the "Stanford Band" page, followed by "The Play (American Football)". | With both articles, the browser first tries to call `containsKey` on the article titles. Since the cache does not contain either title, the browser will download the page and then `put` it in the cache. After both searches, the cache should have three elements, with "The Play (American Football)" as the most-recently accessed, and "Stanford University" as the least recently accessed. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/Cache2.png) |
|       The user presses the back button in the browser.       | The browser knows from the History object that the user wants to load the page "Stanford Band", so the browser calls `containsKey("Stanford Band")`, which returns true. Therefore, the browser tries to `get("Stanford Band")`. At this point, the article "Stanford Band" is the most recently viewed article. The articles in the cache (and, therefore, the HashMap) have not changed, but the order of the nodes in the linked list should be updated to reflect this change. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/Cache3.png) |
|              The user searches "Scramble band".              | The browser first tries to call `containsKey("Scramble band")`, which returns false. Just as before, the browser downloads the article and then `puts` it in the Cache. Since the cache is now at capacity, the cache should remove the least-recently accessed element ("Stanford University") from the cache (<u>both from the HashMap and from the linked list</u>). "Scramble band" is the most recently used article, whereas "The Play (American Football)" is now the least-recently viewed article. `containsKey("Stanford University")` should now return false. | ![img](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/minibrowser/Cache4.png) |

### Implementation Order

This part can be daunting if you attempt to solve it all at once. Instead, try breaking the problem down as follows:

1. **Doubly-Linked List**: Implement the methods above with just a doubly-linked list. Don't worry about keeping the cache under the maximum size or about the HashMap; just make sure you have an implementation that can find articles in the cache.
2. **Move to End**: A key component of the least-recently used cache is that we need to keep the elements in order of when they were accessed, with the most recently accessed articles at the end. Implement a method to move an element in the linked list to the end, and modify your doubly-linked list to keep the elements in order of when they were accessed.
3. **Evict from Cache(move the front node)**: Now that your doubly-linked list is in sorted order, determine how to ensure that the size of the cache never exceeds the maximum size.
4. **Add the HashMap**: Add a HashMap mapping from the string article titles to where their nodes are in the doubly-linked list. You may find you don't need some of your doubly-linked list code anymore after doing so.

With the HashMap and linked list, your cache implementation should have the following speedy method runtimes:

|                      Method                       | Big-Oh |
| :-----------------------------------------------: | :----: |
|               `Cache(int maxSize)`                |  O(1)  |
|                     `~Cache`                      |  O(N)  |
| `put(const string & key, const ValueType& value)` |  O(1)  |
|      `containsKey(const string &key) const`       |  O(1)  |
|          `get(const string& key) const`           |  O(1)  |

As with History, be sure that your implementation does not leak any memory.