#include "trie.h"
#include <vector>
using std::vector;

int main() {
    vector<string> words {"Trie", "insert", "search", "search", "startsWith", "insert", "search"};
    Trie* trie = new Trie();
    for (const auto& i : words) {
        trie->insert(i);
    }
    trie->printAllWord();
    cout << trie->search("trie") << endl;
    return 0;
}
