#include "LineManager.h"
#include "Line.h"
#include "vector.h"
using namespace std;

LineManager::LineManager(const Vector<Line *>& lines) : lines_(lines) {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    (void) lines;
}

LineManager::~LineManager() {
    /* TODO: Delete this line and implement this member function. */
}

double LineManager::contentHeight() const {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    return lines_.back()->highY() - lines_.front()->lowY();
}

Vector<Line *> LineManager::linesInRange(double lowY, double highY) const {
    /* TODO: Delete this line, delete the next three lines, and implement this member function. */
    (void) lowY;
    (void) highY;
    Vector<Line*> result;
    for (const auto& i : lines_) {
        if (!(i->highY() < lowY || i->lowY() > highY)) {
            result.push_back(i);
        }
    }
    return result;
}

Line* LineManager::lineAt(double y) const {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    for (const auto& i : lines_) {
        if (inRange(i->lowY(), i->highY(), y)) {
            return i;
        }
    }
    return nullptr;
}

bool LineManager::inRange(double low, double high, double num) const {
    return num >= low && num <= high;
}
