// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <cctype>
#include <string>
#include "bogglegui.h"
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "strlib.h"
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
    for (auto& i : letter_cube_copy) {
        i = shuffle(i); //the function for string shuffle is not a inplace function!
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto letters = letter_cube_copy.removeBack();
            todo[i][j] = letters[0];
        }
    }

    return todo;       // this is only here so it will compile
}

bool humanWordSearchHelper(Grid<char>& board, const string& word, string& curr_word, int row, int col) {
    // base case;
    if (curr_word.size() == word.size()) {
        return curr_word == word;
    }
    // if (curr_word.size() > 0 && curr_word[0] != word[0]) {
    //     return false;
    // }
    
    //go to the eight dir
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (board.inBounds(row+i, col+j) && board[row+i][col+j] != '.' && word[curr_word.size()] == board[row+i][col+j]) { // the last condition: pruning
                curr_word += board[row+i][col+j];
                board[row+i][col+j] = '.';
                //TODO graphics
                BoggleGUI::setHighlighted(row+i, col+j, true);
                if (humanWordSearchHelper(board, word, curr_word, row+i, col+j)) {
                    return true;
                }
                board[row+i][col+j] = curr_word.back();
                curr_word.pop_back();
                BoggleGUI::setHighlighted(row+i, col+j, false);
            }
        }
    }
    return false;
    //choose
    //explore
    //unchoose
}

void humanPointAdder(const string& word) {
    switch (word.size()) {
        case 4:
            BoggleGUI::scorePointsHuman(1);
            break;
        case 5:
            BoggleGUI::scorePointsHuman(2);
            break;
        case 6:
            BoggleGUI::scorePointsHuman(3);
            break;
        case 7: BoggleGUI::scorePointsHuman(5);
            break;
        default:
            BoggleGUI::scorePointsHuman(11);
            break;
    }
}

void computerPointAdder(const string& word) {
    switch (word.size()) {
        case 4:
            BoggleGUI::scorePointsComputer(1);
            break;
        case 5:
            BoggleGUI::scorePointsComputer(2);
            break;
        case 6:
            BoggleGUI::scorePointsComputer(3);
            break;
        case 7: BoggleGUI::scorePointsComputer(5);
            break;
        default:
            BoggleGUI::scorePointsComputer(11);
            break;
    }
}

bool isValidWord(const Grid<char>& board, const string& word) {
    return word.size() >= BoggleGUI::MIN_WORD_LENGTH && word.size() <= board.numRows() * board.numCols();
}

bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& word) {
    // TODO: write this function
    //clean the board
    BoggleGUI::clearHighlighting();
    //error case
    if (!dictionary.contains(word)) {
        return false;
    }
    if (!isValidWord(board, word)) {
        return false;
    }
    //switch word to upper
    Grid<char> board_copy = board;
    string curr_word;
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (board_copy[i][j] == word[0]) { // pruning
                curr_word += board_copy[i][j];
                board_copy[i][j] = '.';
                BoggleGUI::setHighlighted(i, j, true);
                if (humanWordSearchHelper(board_copy, toUpperCase(word), curr_word, i, j)) {
                    humanPointAdder(word);
                    return true;
                }
                board_copy[i][j] = curr_word.back();
                curr_word.pop_back();
                BoggleGUI::setHighlighted(i, j, false);
            }
        }
    }
    return false;
}


void computerWordSearchHelper(Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords, Set<string>& computer_words, string& curr_word, int row, int col) {
    //base case
    if (curr_word.size() == board.numRows() * board.numCols()) {
        if (dictionary.contains(curr_word) && !humanWords.contains(curr_word)) {
            computer_words.add(curr_word);
        }
        return;
    }
    //check curr_word in dic?
    if (dictionary.contains(curr_word) && !humanWords.contains(curr_word) && isValidWord(board, curr_word) && !computer_words.contains(curr_word)) {
        //y: check find in human ? n -> add to computer_words; q: scoring?
        computer_words.add(curr_word);
        //TODO scoring
        computerPointAdder(curr_word);

    }
    if (dictionary.containsPrefix(curr_word)) {
        //check curr_word prefix?
        //n: no need to go further
        //y: choose explore unchoose
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                if (board.inBounds(row+i, col+j) && board[row+i][col+j] != '.') {
                    curr_word += board[row+i][col+j];
                    board[row+i][col+j] = '.';
                    //TODO graphics
                    computerWordSearchHelper(board, dictionary, humanWords, computer_words, curr_word, row+i, col+j);
                    board[row+i][col+j] = curr_word.back();
                    curr_word.pop_back();
                }
            }
        }
    }
}

Set<string> computerWordSearch(const Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords) {
    // TODO: write this function
    Set<string> todo;   // this is only here so it will compile
    Grid<char> board_copy = board;
    string curr_word;
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
           curr_word += board_copy[i][j];
           board_copy[i][j] = '.';
           computerWordSearchHelper(board_copy, dictionary, humanWords, todo, curr_word, i, j);
           board_copy[i][j] = curr_word.back();
           curr_word.pop_back();
        }
    }
    return todo;        // this is only here so it will compile
}
