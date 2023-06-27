#include "History.h"
#include "error.h"
using namespace std;

History::History() {
    currIndex = -1;
}

bool History::hasNext() const {
    return currIndex >= 0 && currIndex < historyList.size() - 1;
}

bool History::hasPrevious() const {
    return currIndex > 0 && currIndex < historyList.size();
}

string History::next() {
    if (!hasNext()) {
        error("No next");
    }

    return historyList[++currIndex];
}

string History::previous() {
    if (!hasPrevious()) {
        error("No previous");
    }

    return historyList[--currIndex];
}

void History::goTo(const string& page) {
    int currSize = historyList.size();
    for (int i = 0; i < (currSize - 1 - currIndex); i++) {
        historyList.removeBack();
    }

    historyList.add(page);
    currIndex++;
}
