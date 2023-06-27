#pragma once

#include "Line.h"

/* A struct that represents a single node in the line manager BST. */
struct LineManagerNode {
    Line* line;					// line being represented by this node
    LineManagerNode* left;		// left subtree (nullptr if empty)
    LineManagerNode* right;		// right subtree (nullptr if empty)

    /*
     * Constructs a new node to store the given line,
     * along with the given child pointers.
     */
    LineManagerNode(Line* line = nullptr,
                LineManagerNode* left = nullptr, LineManagerNode* right = nullptr);
    ~LineManagerNode();

    /*
     * Returns true if this node is a leaf (has nullptr children).
     */
    bool isLeaf() const;

    /* These functions let you access the total count of nodes that have
     * been created and deleted over the lifetime of the program. */
    static int getCreatedCount();
    static int getDeletedCount();

    /* This function returns the number of nodes that were created but
     * not yet freed. */
    static int getNodesStillCreatedCount();

    /* This function returns whether there are nodes that were created but
     * not yet freed. */
    static bool hasNodesStillCreated();

    /* Resets the counters of nodes created and deleted to 0. */
    static void resetCreatedDeletedCounts();

private:
    static int s_createdCount;
    static int s_deletedCount;
};
