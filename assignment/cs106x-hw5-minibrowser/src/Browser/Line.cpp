#include "Line.h"
using namespace std;

Line::Line(double lowY, double highY) : theLowY(lowY), theHighY(highY) {
    // Handled in initializer list
}

Line::~Line() {
    clear();
}

double Line::lowY() const {
    return theLowY;
}

double Line::highY() const {
    return theHighY;
}

void Line::clear() {
    for (auto frame: theFrames) {
        delete frame;
    }
    theFrames.clear();
}

void Line::setFrames(const vector<Frame *>& frames) {
    clear();
    theFrames = frames;
}

const vector<Frame *>& Line::frames() const {
    return theFrames;
}
