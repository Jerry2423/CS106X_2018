/**
 * CS 106B/X Huffman Encoding
 *
 * This file declares the HuffmanNode structure that you will use in your
 * Huffman encoding tree.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2016/11/12
 * - 16au 106x version
 * @version 2013/11/14
 * - initial version
 */

#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "bitstream.h"

/* Type: HuffmanNode
 * A node inside a Huffman encoding tree.    Each node stores four
 * values - the character stored here (or NOT_A_CHAR if the value
 * is not a character), pointers to the 0 and 1 subtrees, and the
 * character count (weight) of the tree.
 */
struct HuffmanNode {
    int character;       // character being represented by this node
    int count;           // number of occurrences of that character
    HuffmanNode* zero;   // 0 (left) subtree (null if empty)
    HuffmanNode* one;    // 1 (right) subtree (null if empty)

    /*
     * Constructs a new node to store the given character and its count,
     * along with the given child pointers.
     */
    HuffmanNode(int character = NOT_A_CHAR, int count = 0,
                HuffmanNode* zero = nullptr, HuffmanNode* one = nullptr);
    ~HuffmanNode();

    /*
     * Returns true if this node is a leaf (has NULL children).
     */
    bool isLeaf() const;

    /*
     * Returns a string representation of this node for debugging.
     */
    std::string toString() const;

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

/*
 * Prints an indented horizontal view of the tree of HuffmanNodes with the given
 * node as its root.
 * Can optionally show the memory addresses of each node for debugging.
 */
void printSideways(HuffmanNode* node, bool showAddresses = false, std::string indent = "");

/*
 * Stream insertion operator so that a HuffmanNode can be printed for debugging.
 */
std::ostream& operator <<(std::ostream& out, const HuffmanNode& node);
