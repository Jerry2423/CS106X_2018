#include "LineManager.h"
#include "Line.h"
#include "vector.h"
using namespace std;

LineManager::LineManager(const Vector<Line *>& lines) {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    add_vec(lines, root);
    (void) lines;
}

LineManager::~LineManager() {
    /* TODO: Delete this line and implement this member function. */
    clear_from(root);
    root = nullptr;
}

double LineManager::contentHeight() const {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    return getMax(root);
}

Vector<Line *> LineManager::linesInRange(double lowY, double highY) const {
    /* TODO: Delete this line, delete the next three lines, and implement this member function. */
    Vector<Line*> result;
    linesInRangeHelper(root, result, lowY, highY);
    return result;
}

Line* LineManager::lineAt(double y) const {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    return lineAtHelper(y, root);
}

void LineManager::add_vec(const Vector<Line*>& v, Node*& curr) {
    if (v.isEmpty()) {
        curr = nullptr; // avoid dangling ptr!
        return;
    } else {
        // add the middle element
        curr = new Node(v[v.size()/2]); 
        // set the left and right
        add_vec(v.subList(0, v.size()/2), curr->left);
        add_vec(v.subList(v.size()/2+1, v.size()-v.size()/2-1), curr->right);
    }
}

void LineManager::clear_from(Node* curr) {
    if (!curr) {
        return;
    } else {
        clear_from(curr->left);
        clear_from(curr->right);
        delete curr;
    }
}

double LineManager::getMax(Node* curr) const {
    if (!curr->right) {
        return curr->line->highY();
    } else {
        return getMax(curr->right);
    }

}


// traverse order matters!
void LineManager::linesInRangeHelper(Node* curr, Vector<Line*>& result, double lowY, double highY) const {
    if (curr) {
        // totally out of boundary: choose one side
        if (curr->line->highY() < lowY) {
            linesInRangeHelper(curr->right, result, lowY, highY);
        } else if (curr->line->lowY() > highY) {
            linesInRangeHelper(curr->left, result, lowY, highY);
        } else { // otherwise: left -> add curr to the vec -> right
            linesInRangeHelper(curr->left, result, lowY, highY);
            result.push_back(curr->line);
            linesInRangeHelper(curr->right, result, lowY, highY);
        }
    }
}

Line* LineManager::lineAtHelper(double y, Node* curr) const {
    if (!curr) {
        return nullptr;
    } else {
        if (y >= curr->line->lowY() && y <= curr->line->highY()) {
            return curr->line;
        } else if (y < curr->line->lowY()) {
            return lineAtHelper(y, curr->left);
        } else {
            return lineAtHelper(y, curr->right);
        }
    }
}
