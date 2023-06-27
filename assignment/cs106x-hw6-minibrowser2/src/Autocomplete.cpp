#include "Autocomplete.h"
#include "set.h"
#include <cctype>

using namespace std;

Autocomplete::Autocomplete() : root(new TrieNode()){
    /* TODO: Delete this line and implement this function. */
}

Autocomplete::~Autocomplete() {
    /* TODO: Delete this line and implement this function. */
    delete_from(root);
}

void Autocomplete::add(const string& text) {
    /* TODO: Delete this line, delete the next line, and implement this function. */
    addHelper(root, text, 0);
}

/* Find some recommendations! */
Set<string> Autocomplete::suggestionsFor(const string& prefix, int maxHits) const {
    /* TODO: Delete this line, delete the next three lines, and implement this member function. */
    TrieNode* start = find_prefix(root, prefix, 0);
    if (!start) {
        return {};
    } else {
        string prefix_copy = prefix;
        Set<string> result;
        suggestionsHelper(start, prefix_copy, maxHits, result);
        return result;
    }
}

void Autocomplete::delete_from(TrieNode*& curr) {
    if (curr) {
        for (const auto& i : curr->children) {
            delete_from(curr->children[i]);
        }
        delete curr;
        curr = nullptr;
    }
}

void Autocomplete::addHelper(TrieNode* curr, const string& text, int pos) {
    if (pos == text.size()) {
        curr->isWord = true;
    } else {
        // try to find the test[pos] ptr
        string key;
        key += text[pos];
        if (curr->children.containsKey(key)){
            if (!curr->children[key]) {
                curr->children[key] = new TrieNode();
            }
        } else {
            curr->children[key] = new TrieNode();
        }
        addHelper(curr->children[key], text, pos+1);
        // if find: check whether it's null, if so create one node
        // not find: add one more letter ptr and create one node
        // follow the ptr to the next pos
    }
}

Autocomplete::TrieNode* Autocomplete::find_prefix(TrieNode* curr, const string& prefix, int pos) const{
    if (pos == prefix.size()) {
        return curr;
    } else if (!curr || !curr->children.containsKey(string("")+prefix[pos])) {
        return nullptr;
    } else {
        return find_prefix(curr->children[string("")+prefix[pos]], prefix, pos+1);
    }
} 

void Autocomplete::suggestionsHelper(TrieNode* curr, string& prefix, int& maxHits, Set<string>& result) const{
    if (maxHits == 0 || !curr) {
        return;
    } else {
        if (curr->isWord) {
            maxHits --;
            result.add(prefix);
        }
        for (const auto& i : curr->children) {
            prefix += i;
            suggestionsHelper(curr->children[i], prefix, maxHits, result);
            prefix.pop_back();
        }
    }
}
