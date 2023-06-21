## Solution Note



### Decision and Options

Boggle这道题的有趣之处在于第一次decision和相应的options与之后的decision和options不一样：

第1次:

Decision: pick up a letter **in the board**

Options: any letter in the 4*4 grid

之后：

Decision: pick up a letter **adjacent to the chosen letter**

Options: up to 8 letters around the chosen letter

所以这道题在`human/computerSearch`中是这样的：外面有一层循环，里面再用helper函数

```c++
bool humanWordSearch(const Grid<char>& board, const Lexicon& dictionary, const string& word) {
    // ...
    //first decision: go through the whole board
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (board_copy[i][j] == word[0]) {
            		//choose
                curr_word += board_copy[i][j];
                board_copy[i][j] = '.';
                //...explore
                //unchoose
                board_copy[i][j] = curr_word.back();
                curr_word.pop_back();
            }
        }
    }
    return false;
}

```



### Pruning

这道题的`humanSearch` 中有2处可以prune优化的地方：见代码

- 首字母和目标不相符的直接返回false
- 如果要加入的字母和目标word对应位置的字母不相符，没必要choose and explore