#include "LineManagerNode.h"

int LineManagerNode::s_createdCount = 0;
int LineManagerNode::s_deletedCount = 0;

LineManagerNode::LineManagerNode(Line* line, LineManagerNode* left, LineManagerNode* right) {
    this->line = line;
    this->left = left;
    this->right = right;
    s_createdCount++;
}

LineManagerNode::~LineManagerNode() {
    s_deletedCount++;
}

bool LineManagerNode::isLeaf() const {
    return !left && !right;
}

int LineManagerNode::getCreatedCount() {
    return s_createdCount;
}

int LineManagerNode::getDeletedCount() {
    return s_deletedCount;
}

int LineManagerNode::getNodesStillCreatedCount() {
    return getCreatedCount() - getDeletedCount();
}

bool LineManagerNode::hasNodesStillCreated() {
    return getNodesStillCreatedCount() > 0;
}

void LineManagerNode::resetCreatedDeletedCounts() {
    s_createdCount = s_deletedCount = 0;
}
