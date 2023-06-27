#pragma once

#include "hashmap.h"
#include "set.h"
#include <string>
using std::string;

/**
 * An object that can provide autocomplete responses given a string prefix.
 *
 * Your job is to implement this class so that you can add in new words via the add()
 * function and retrieve a list of candidate autocomplete options via the
 * suggestionsFor() member function.
 */
class Autocomplete {
public:
    /**
     * Constructs a new, empty Autocomplete object.
     */
    Autocomplete();

    /**
     * Cleans up all memory allocated by this Autocomplete object.
     */
    ~Autocomplete();

    /**
     * Adds a word into the Autocomplete structure. You should keep the word capitalized in
     * the same way that you found it. If the word already exists, this function should have
     * no effect.
     *
     * You should not assume that the string is composed of just the basic letters A - Z. There
     * may be spaces, and if you're storing text from languages outside of English there might
     * even be words in there that use non-English letters.
     *
     * @param word The word to insert.
     */
    void add(const std::string& word);

    /**
     * Given a string representing what the user has typed in, returns a list of candidate
     * pages that start with that string. This function is case-sensitive, so looking up
     * "Dik" and "dik" should produce different candidates.
     *
     * Your function should return at most maxHits total hits. For efficiency's sake, you
     * should stop generating matches as soon as you've found the right number. If you find
     * fewer than the expected number of matches, that's also fine.
     *
     * @param prefix The prefix of an article title that the user has entered.
     * @param maxHits The maximum number of suggestions to return.
     * @return A list of suggested articles that start with the given prefix.
     */
    Set<std::string> suggestionsFor(const std::string& prefix, int maxHits) const;
    struct TrieNode {
        bool isWord;
        HashMap<string, TrieNode*> children;

        TrieNode(bool isWord=false) : isWord(isWord) {}
    };

private:
    // TODO: add any helper functions and instance variables you need
    TrieNode* root;

    void delete_from(TrieNode*& curr);
    void addHelper(TrieNode* curr, const string& text, int pos);

    TrieNode* find_prefix(TrieNode* curr, const string& prefix, int pos) const;
    void suggestionsHelper(TrieNode* curr, string& prefix, int& maxHits, Set<string>& result) const;
};
