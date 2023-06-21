// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "shuffle.h"
using namespace std;

Grid<char> generateRandomBoard(int size, const Vector<std::string>& letterCubes) {
    // TODO: write this function
    if (size < 4 || size > 6) {
        throw "invalid board size";
    }
    if (letterCubes.size() != size*size) {
        throw "invalid number of cubes";
    }
    Grid<char> todo(size, size);// this is only here so it will compile
    Vector<string> letter_cube_copy = letterCubes;
    shuffle(letter_cube_copy);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto letters = letter_cube_copy.removeBack();
            shuffle(letters);
            todo[i][j] = letters[0];
        }
    }

    return todo;       // this is only here so it will compile
}

bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& word) {
    // TODO: write this function
    return false;   // this is only here so it will compile
}

Set<string> computerWordSearch(const Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords) {
    // TODO: write this function
    Set<string> todo;   // this is only here so it will compile
    return todo;        // this is only here so it will compile
}
