#pragma once

#include "note.h"
#include <string>
using std::string;

/**
 * A type representing a browser history. This type is responsible for supporting the
 * "next" and "previous" operations.
 */
class History {
public:
    /**
     * Constructs a new, empty browser history.
     *
     * This function should run in time O(1).
     */
    History();

    /**
     * Cleans up all memory allocated by this class.
     */
    ~History();

    /**
     * Returns whether there is a previous page before the current one.
     *
     * This function should run in time O(1).
     *
     * @return Whether there is a previous page before the current one.
     */
    bool hasPrevious() const;

    /**
     * Returns whether there is a next page after the current one.
     *
     * This function should run in time O(1).
     *
     * @return Whether there is a next page after the current one.
     */
    bool hasNext() const;

    /**
     * Returns the title of the next page after the current one, then advances
     * forward to that page.
     *
     * If there is no next page, this function should report an error by calling
     * the error() function.
     *
     * This function should run in time O(1).
     *
     * @return The title of the next page.
     */
    std::string next();

    /**
     * Returns the title of the previous page before the current one, then advances
     * backward to that page.
     *
     * If there is no previous page, this function should report an error by calling
     * the error() function.
     *
     * This function should run in time O(1).
     *
     * @return The title of the previous page.
     */
    std::string previous();

    /**
     * Records that we have gone to the specified page. This function should discard all
     * browser history after the current page, then append this current page to the history
     * and set it as the active page.
     *
     * You can assume that this function will only be called if the page is changed for a
     * reason other than hitting the next/previous button. The effects of hitting next/
     * previous will be implemented by calling next() and previous(), not this function.
     *
     * This function should run in time O(n), where n is the number of items in the history.
     *
     * @param page The name of the page to go do.
     */
    void goTo(const std::string& page);

private:
    /* Type representing a node in a doubly-linked list. Feel free to add whatever fields
     * you'd like.
     */
    struct Node {
        std::string title;
        Node*       prev;
        Node*       next;
    };
    Node* front_;
    Node* curr_;
    // TODO: add any helper functions and instance variables you need
    void delete_from(Node*& head);
    void add_back(const string& title);
    bool empty() const;
    void print() const;
};
