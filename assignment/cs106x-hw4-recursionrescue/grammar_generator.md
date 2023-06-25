## Grammar Generator

### Overview

For this part of the assignment you will write a function to generate random sentences from what linguists, programmers, and logicians refer to as a “grammar.” Let’s begin with some definitions. A [formal language](https://en.wikipedia.org/wiki/Formal_language) is a <u>set of words</u> and/or symbols <u>along with a set of rules</u>, collectively called the syntax of the language, that define how those symbols may be used together—programming languages like Java and C++ are formal languages, as are certain mathematical or logical notations. A grammar, in this context, is a way of describing the syntax and symbols of a formal language. All programming languages then have grammars; here is a link to a [formal grammar for the Java language](http://java.sun.com/docs/books/jls/third_edition/html/grammars.html). Your task for this problem will be to write a function that <u>accepts a reference to an input file representing a language’s grammar</u> (in a format that we will explain below), along with <u>a symbol to randomly generate</u>, and the <u>number of times to generate it</u>. Your function should generate the given number of random expansions of the given symbol and return them as a `Vector` of `strings`.

```
Vector<string> generateGrammar(istream& input, string symbol,
                          int times)
```

#### Sample Output

Your program should exactly reproduce the format and general behavior demonstrated in these logs, although it may not exactly recreate these particular scenarios because of the randomness inherent in your code. But your function should return valid random results as per the grammar that was given to it. You can use the [output comparison tool](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/assignments/diff.html) on the course website with these files.

[
sentence.txt](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/resources/recursion/expected-output/grammarsolver-expected-output-1.txt)

[
sentence2.txt](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/resources/recursion/expected-output/grammarsolver-expected-output-2.txt)

[
expression.txt](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/resources/recursion/expected-output/grammarsolver-expected-output-3.txt)

We have also written a [Grammar Verifier web tool](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/assignments/grammarverifier.html) where you can paste in the randomly generated sentences and phrases from your program, and our page will do its best to validate that they are legal phrases that could have come from the original grammar file. This isn't a perfect test, but it is useful for finding some common types of mistakes.

### Reading BNF Grammars

Many language grammars are described in a format called [Backus-Naur Form (BNF)](http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form), which is what we'll use in this assignment. In BNF, some symbols in a grammar are called <u>terminals</u> because they represent fundamental words of the language (i.e., symbols that cannot be transformed or reduced beyond their current state). A terminal in English might be "dog" or "run" or "Chris". Other symbols of the grammar are called non-terminals and represent higher-level parts of the language syntax, such as a noun phrase or a sentence in English. Every non-terminal consists of one or more terminals; for example, the verb phrase "throw a ball" consists of three terminal words. (terminal words似乎是base case，一个non-terminal的句子可以被divide成一些小的部分)

The BNF description of a language consists of a set of derivation rules, where each rule names <u>a symbol</u> and the <u>legal transformations</u> that can be performed between that symbol and other constructs in the language. You might think of these rules as <u>providing translations between terminals and other elements, either terminals or non-terminals.</u> For example, a BNF grammar for the English language might state that a sentence consists of a noun phrase and a verb phrase, and that a noun phrase can consist of an adjective followed by a noun or just a noun. <u>Note that rules can be described recursively (i.e., in terms of themselves). For example, a noun phrase might consist of an adjective followed by another noun phrase,</u> such as the phrase "big green tree" which consists of the adjective "big" followed by the noun phrase "green tree".

A BNF grammar is specified as an input file containing one or more rules, each on its own line, of the form:

```
non-terminal::=rule|rule|rule|...|rule
```

A separator of `::=` (colon colon equals) divides the non-terminal from its transformation/expansion rules. There will be exactly one such ::= separator per line. A | (pipe) separates each rule; if there is only one rule for a given non-terminal, there will be no pipe characters. **<u>Each rule will consist of one or more whitespace-separated tokens.</u>（?）** To illustrate how to read a BNF grammar, let’s consider a very simple example. Suppose that we had the BNF input file below, which describes a language comprising a tiny subset of English. The non- terminal symbols `<s>`, `<pn>`, and `<iv>` are short for grammatical elements: sentences, proper nouns, and intransitive verbs (i.e., verbs that do not take an object). Note that in the following two examples, non-terminal elements are contained in angle brackets, while terminal elements (here, valid English words, such as “Lupe”, “Camillo”, “laughed”, etc.) are not. **check base case: token not in the map keys**

```
<s>::=<pn> <iv>
<pn>::=Lupe|Camillo
<iv>::=laughed|wept
```

<u>To transform a symbol into a valid output string (that is, into a sentence described by this grammar’s rules), we recursively expand the non-terminal symbols contained in its transformation rules until we have an output made up entirely of terminals—at that point our transformation is complete, and we’re done.</u> So in our trivial example of a grammar, if we are given the symbol `<s>`, which represents the non-terminal for “sentence”, we examine the rules that describe how to expand the sentence non- terminal, and discover that it is comprised of a proper noun followed by an intransitive verb (`<s>::=<pn> <iv>`). We can begin by transforming the `<pn>` symbol, which we do by choosing at random from among the available transformations provided on the right-hand side of the `<pn>` rule (here, “Lupe” and “Camillo”). After this transformation, our sentence-in-progress might look like this:

```
Camillo <iv>
```

<u>At each step of our transformation, we perform a single transformation on one of the remaining non- terminal symbols.</u> In this simple example, there is only one non-terminal left, `<iv>`. We accordingly transform that symbol by choosing randomly among the transformations provided for it, which could produce the following output:

```
Camillo laughed
```

Since there are no more non-terminal symbols remaining, our transformation is complete. Note that other valid sentences in this language (i.e., other valid transformations of the symbol `<s>`) include the sentences “Camillo wept”, “Lupe laughed”, and “Lupe wept”. Because we can choose at random from the transformations provided for each non-terminal symbol, all of these variations are possible and valid for this very simple language.

Now let’s look at an example of a more complex BNF input file, `sentence.txt`, which describes a slightly larger subset of the English language. Here, the non-terminal symbols `<np>`, `<dp>`, and `<tv>` are short for the linguistic elements noun phrase, determinate article, and transitive verb.

```
<s>::=<np> <vp>
<np>::=<dp> <adjp> <n>|<pn>
<dp>::=the|a
<adjp>::=<adj>|<adj> <adjp>
<adj>::=big|fat|green|wonderful|faulty|subliminal|pretentious
<n>::=dog|cat|man|university|father|mother|child|television
<pn>::=John|Jane|Sally|Spot|Fred|Elmo
<vp>::=<tv> <np>|<iv>
<tv>::=hit|honored|kissed|helped
<iv>::=died|collapsed|laughed|wept
```

Following the rules provided by this input file for expanding non-terminals, this grammar's language can represent sentences such as "The fat university laughed" and "Elmo kissed a green pretentious television". This grammar cannot describe the sentence "Stuart kissed the teacher", because the words "Stuart" and "teacher" are not part of the grammar. It also cannot describe "fat John collapsed Spot" because there are no rules that permit an adjective before the proper noun "John", nor an object after intransitive verb "collapsed".

Though the non-terminals in the previous two example languages are surrounded by **< >**, this is not required. By definition any token that **ever** appears on the left side of the `::=` of any line is considered a non-terminal, and any token that appears **only** on the right-hand side of `::=` in any line(s) is considered a terminal (so for the above example, as we have noted, `<np>` is a non- terminal, but “John” is a terminal). **<u>Do not assume that non-terminals will be surrounded by `< >` in your code. Each line's non-terminal will be a non-empty string that does not contain any whitespace.</u>？**

You may assume that individual tokens in a rule are separated by a single space, and that there will be no outer whitespace surrounding a given rule or token.

Your `generateGrammar` function will perform two major tasks:

1. <u>read an input file with a grammar in Backus-Naur Form and turns its contents into a data structure</u>
2. <u>randomly generate elements of the grammar (recursively)</u>

<u>You may want to separate these steps into one or more helper function(s), each of which performs one step. It is important to separate the recursive part of the algorithm from the non-recursive part.</u> You are given a client program that handles the user interaction. The `main` function supplies you with an input file stream to read the BNF file. Your code must read in the file's contents and break each line into its symbols and rules so that it can generate random elements of the grammar as output. When you generate random elements, you store them into a `Vector` to be returned. The provided main program loops over the vector and prints the elements stored inside it.



------

### Part 1: Reading the Input File

For this program you must store the contents of the grammar input file into a `Map`. As you know, maps keep track of key/value pairs, where each key is associated with a particular value. In our case, <u>we want to store information about each non-terminal symbol, such that the non-terminal symbols become keys and their rules become values.</u> Other than the `Map` requirement, you are allowed to use whatever constructs you need from the Stanford C++ libraries. You don't need to use recursion on this part of the algorithm; just loop over the file as needed to process its contents.

One problem you will have to deal with early in this program is breaking strings into various parts. To make it easier for you, the Stanford library's `"strlib.h"` library provides a `stringSplit` function that you can use on this assignment:

```
Vector<string> stringSplit(string s, string delimiter)
```

This function breaks a large string into a `Vector` of smaller string tokens; it accepts a delimiter string parameter and looks for that delimiter as the divider between tokens. Here is an example call to this function:

```
string s = "example;one;two;;three";
Vector<string> v = stringSplit(s, ";");
// now v = {"example", "one", "two", "", "three"}
```

The parts of a rule will be separated by whitespace, but once you've split the rule by spaces, the spaces will be gone. If you want spaces between words when generating strings to return, you must concatenate those yourself. If you find that a string has unwanted spaces around its edges, you can remove them by calling the `trim` function, also from `"strlib.h"`:

```
string s2 = " hello there sir ";
s2 = trim(s2); // "hello there sir"
```

### Part 2: Generating Random Expansions from the Grammar

As we mentioned, producing random grammar expansions is a two-step process. The first step, which we’ve just outlined, requires reading the input grammar file and turning it into an appropriate data structure (non-recursively). The second step requires your program to recursively walk that data structure to generate elements by successively expanding them.

The **recursive algorithm** that your program will use to generate a random occurrence of a symbol **S** should have the following logic:

- If **S** is a terminal symbol, there is nothing to do; the result is the symbol itself.
- If **S** is a non-terminal symbol, choose a random expansion rule **R** for **S**, and for each of the symbols in that rule **R**, generate a random occurrence of that symbol.



For example, the example grammar given in the Problem Description above could be used to randomly generate an `<s>` non-terminal for the sentence, "Fred honored the green wonderful child", as shown in the following diagram.

![screenshot](https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/images/recursion/grammar-screenshot.png)

If the string passed to your function is a non-terminal in your grammar, use the grammar's rules to recursively expand that symbol fully into a sequence of terminals. For example, using the grammar on the previous pages, `<np>` might potentially expand to the string "the green wonderful child".

Generating a non-terminal involves picking one of its rules at random and then generating each part of that rule, which might involve more non-terminals to recursively generate. For each of these you pick rules at random and generate each part, etc.

<u>When you encounter a terminal, simply include it in your string. This becomes a base case.</u> If the string passed to your function is not a non-terminal in your grammar, you should assume that it is a terminal symbol and simply return it. For example, "green" should just cause "green" to be returned (without any spaces around it).

*Special cases to handle:* You should throw an **exception** if the grammar contains more than one line for the same non-terminal. For example, if two lines both specified rules for symbol "<s>", this would be illegal and should result in the exception being thrown. You should throw an exception if the symbol parameter passed to your function is empty, "". You can do this by calling the built-in `throw` function, which takes a `string` parameter containing a description of the error that occurred. The `throw` function will terminate the program.

*Testing:* The provided input files and main may not test all of the above cases; it is your job to come up with tests for them.

Your function may assume that the input file exists, is non-empty, and is in a proper valid format otherwise. If the number of times passed is 0 or less, return an empty vector.

------

### Implementation Details

The hardest part of this problem is the recursive generation, so make sure you have read the input file and built your data structure properly before tackling the recursive part. Loops are not forbidden in this part of the assignment. In fact, you should definitely use loops for some parts of the code where they are appropriate. For example, the directory crawler example from section uses a for-each loop. This is perfectly acceptable; if you find that part of this problem is easily solved with a loop, please use one. In the directory crawler, the hard part was traversing all of the different sub-directories, and that's where we used recursion. For this program, the hard part is following the grammar rules to generate all the parts of the grammar, so that is the place to use recursion. If your recursive function has a bug, try putting a `cout` statement at the start of your recursive function to print its parameter values; this will let you see the calls being made. As a final tip: look up the `randomInteger` function from `"random.h"` to help you make random choices between rules.





​	