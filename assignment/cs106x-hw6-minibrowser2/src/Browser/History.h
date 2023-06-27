#pragma once

#include <string>
#include "vector.h"

/**
 * A type representing a browser history. This type is responsible for supporting the
 * "next" and "previous" operations.
 */
class History {
public:
    /**
     * Constructs a new, empty browser history.
     */
    History();

    /**
     * Returns whether there is a previous page before the current one.
     *
     * @return Whether there is a previous page before the current one.
     */
    bool hasPrevious() const;

    /**
     * Returns whether there is a next page after the current one.
     *
     * @return Whether there is a next page after the current one.
     */
    bool hasNext() const;

    /**
     * Returns the title of the next page after the current one, then advances
     * forward to that page.
     *
     * If there is no next page, this function reports an error by calling
     * the error() function.
     *
     * @return The title of the next page.
     */
    std::string next();

    /**
     * Returns the title of the previous page before the current one, then advances
     * backward to that page.
     *
     * If there is no previous page, this function reports an error by calling
     * the error() function.
     *
     * @return The title of the previous page.
     */
    std::string previous();

    /**
     * Records that we have gone to the specified page. This function discards all
     * browser history after the current page, then appends this current page to the history
     * and sets it as the active page.
     *
     * This function assumes that it will only be called if the page is changed for a
     * reason other than hitting the next/previous button. The effects of hitting next/
     * previous should be implemented by calling next() and previous(), not this function.
     *
     * @param page The name of the page to go to.
     */
    void goTo(const std::string& page);

private:
    Vector<std::string> historyList;
    int currIndex;
};
