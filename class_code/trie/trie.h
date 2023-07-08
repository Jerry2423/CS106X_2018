#ifndef TRIE_H__
#define TRIE_H__

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Trie {
public:
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        clean_from(root);
    }
    
    void printAllWord() {
        string prefix;
        printAllWordHelper(root, prefix);
    }

    void insert(string word) {
        std::transform(word.begin(), word.end(), word.begin(),::tolower); // make it case insensitive
        insertHelper(root, word, 0);
    }
    
    bool search(string word) {
        return wordSearchHelper(root, word, 0);
    }
    
    bool startsWith(string prefix) {
        return prefixSearchHelper(root, prefix, 0);    
    }

private:
    struct TrieNode {
        bool isWord;
        TrieNode* children[26];
        TrieNode(bool isWord=false) : isWord(isWord) {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

    TrieNode* root;

    void clean_from(TrieNode*& curr) {
        if (!curr) {
            return;
        } else {
            for (int i = 0; i < 26; i++) {
                clean_from(curr->children[i]);
            }
            delete curr;
            curr = nullptr;
        }
    }

    void printAllWordHelper(TrieNode* curr, string& prefix) {
        if (!curr) {
            return;
        } else {
            if (curr->isWord) {
                cout << prefix << endl;
            }
            for (int i = 0; i < 26; i++) {
                char ch = 'a' + i;
                prefix += ch;
                printAllWordHelper(curr->children[i], prefix);
                prefix.pop_back();
            }
        }
    }
    
    // use pos to denote where we are at the current word
    bool prefixSearchHelper(TrieNode* curr, const string& word, int pos) {
        if (!curr) {
            return false;
        } else if (pos == word.size()) {
            return true;
        } else {
            int index = word[pos] - 'a';
            return prefixSearchHelper(curr->children[index], word, pos+1);
        }
    }

    bool wordSearchHelper(TrieNode* curr, const string& word, int pos) {
        if (!curr) {
            return false;
        } else if (pos == word.size()) {
            return curr->isWord; // the only differences between search prefix and word is that when word is empty, we need check whether the current node is word or not
        } else {
            int index = word[pos] - 'a';
            return wordSearchHelper(curr->children[index], word, pos+1);
        }
        
    }

    void insertHelper(TrieNode*& curr, const string& word, int pos) {
        if (pos == word.size()) {
            curr->isWord = true;
        } else {
            // find the leading letter ptr
            int index = word[pos] - 'a';
            // check if it's nullptr
            if (!curr->children[index]) {
                // if so create one for the ptr
                curr->children[index] = new TrieNode();
            }
            // follow the ptr and shrink the str
            insertHelper(curr->children[index], word, pos+1);
        }
    } 
};

#endif // !DEBUG
