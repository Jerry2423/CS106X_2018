## Problem 3: DNA Detective

You're working in a hospital and, to your dismay, there's been an outbreak of the antibiotic-resistant bacterium [MRSA](https://en.wikipedia.org/wiki/Methicillin-resistant_Staphylococcus_aureus). You're not sure where the disease came from, whether it's endemic in the community, or whether it's a well-known strain. Fortunately, you've got <u>a number of DNA samples</u> from the bug, and your handy gene sequencer has returned back to you a rough copy of its genome. <u>If you can figure out whether the different samples you're getting from different patients are all from the same strain of MRSA, you can take specific actions to try to [end the spread quickly](https://www.cam.ac.uk/research/news/bacterial-dna-sequence-used-to-map-an-infection-outbreak).</u>

DNA consists of paired strands of nucleotides. The nucleotides used in DNA are adenine, cytosine, guanine, and thymine, usually just abbreviated A, C, G, and T, and <u>DNA strands are often represented as strings made from these letters.</u>

When DNA sequencing machines return back the specific sequence of nucleotides that make up a particular strand of DNA, they often have a <u>small number of errors.</u> For example, if there's a part of a DNA strand that actually reads [GTGTC](http://www.girlsteachinggirlstocode.org/), then the sequencer might report it as GTGTA (substituting one letter for another), GTGT (dropping a letter), or GTGTAC (inserting a letter). One way of quantifying how “close” two DNA strands are to one another is to use a measure called *edit distance*. Specifically, the edit distance between two strings is defined as <u>the number of single-letter insertions, deletions, and replacements needed to turn the first string into the second.</u> For example:

- The strings `cat` and `dog` have edit distance 3. The <u>fastest way</u> to turn `cat` into `dog` is to replace each letter in `cat` with the corresponding letter from `dog`.
- The strings `table` and `maple` have edit distance 2. The fastest way to turn `table` into `maple` is to replace the `t` in `table` with an `m` and the `b` in `table` with a `p`.
- The strings `rate` and `pirate` have edit distance 2. The fastest way to turn `rate` into `pirate` is to prepend a `p` and an `i`.
- The strings `edit` and `distance` have edit distance 6. Specifically, delete the `e` from `edit`, insert an `s` between the `i` and the `t`, and append the letters `ance` onto the back.

Let's jump back to our outbreak example. Imagine you sequence the DNA of a sample of MRSA that you've found in one patient and the DNA of a sample of MRSA you found in another patient. The sequencer will likely come back with some small number of errors in it. <u>If the edit distance between the two DNA strands is low, it likely means that you're looking at essentially the same organism, meaning that the patients either got the bug from the same source or one gave it to another. On the other hand, if the edit distance is large, it likely means you're looking at two independent sources of infection.</u>

Your task is to write a function

```
bool approximatelyMatch(const string& one, const string& two, int maxDistance)
```

that takes as input two strings representing strands of DNA and a number `maxDistance`, then returns whether the edit distance between the two DNA strands is `maxDistance` or less.

As a hint for this problem, look at the first characters of `one` and `two` and think about what you might do with what you find. What happens if they match? If they don’t match, you have three possible ways that you can get them to match – what are they, and how might you try them? And what happens if either input string is empty?

Some notes on this problem:

- You can assume the strings passed as input consist purely of the letters A, C, T, and G.
- It’s entirely possible to solve this problem without using loops of any kind. In fact, if you do find yourself writing loops in your solution to this particular problem, it might indicate that you’re missing a much easier line of reasoning.

### Unit Testing

(Covered on Monday 10/22) As part of this problem, you should also implement unit tests to help test whether your implementation is correct. Specifically, you must implement **at least 5** tests *in addition to the ones provided in the starter code*. These tests must cover distinct test cases.

Each test should have a detailed comment explaining what it's testing for as well as a descriptive test name. Moreover, each test you add should test different aspects than the existing tests. Refer to the notes on good testing practices from Lecture 13 (on Monday 10/22) for ideas about what sorts of tests you should write. Each of your tests should be a function in `DNADetectiveTests.cpp`. To create a test, you will use the following format, adding both your description and a body of the test. You can see the examples in that file for further reference.

```
/* Comment here with more info about the test */
ADD_TEST("Put your description of the test here") {
	/* body of the test */
}
```

You should submit your expanded testing file with your assignment.