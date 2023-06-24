#pragma once

#include "Line.h"
#include "vector.h"

/**
 * A type that stores all the lines that comprise a webpage. It supports a number of
 * features that make the UI work correctly. Until you've implemented these features, the
 * UI will not display any text.
 */
class LineManager {
public:
    /**
     * Constructs a new LineManager to manage the specified lines. The lines will be sorted
     * from lowest Y values to highest. You can assume that none of the lines overlap one
     * another.
     *
     * This function should run in time O(n), where n is the number of lines in the input
     * list.
     *
     * @param lines The lines to manage.
     */
    LineManager(const Vector<Line *>& lines);

    /**
     * Cleans up all memory associated with this LineManager, if any.
     */
    ~LineManager();

    /**
     * Returns the total vertical space that the lines occupy. This is the total vertical space
     * required to draw all the lines, from the line starting at 0 up
     * through the line with the highest Y coordinate.
     *
     * This function should run in time O(1).
     *
     * @return The total vertical space occupied by all the lines.
     */
    double contentHeight() const;

    /**
     * Given a range [lowY, highY], returns a Vector containing pointers to all of the lines
     * that fall within that range. A line falls within the range if any part of it would
     * overlap with the Y-value range [lowY, highY], so, for example, a line spanning the
     * range [30, 75] would be returned in a search for [60, 120].
     *
     * Although you're returning a Vector of pointers here, you should almost certainly not do
     * any custom allocations in the course of implementing this function. Instead, just return
     * pointers to the existing lines.
     *
     * This function should run in time O(n), where n is the total number of lines.
     *
     * The lines returned by this function should be sorted in increasing order of Y value.
     *
     * @param lowY The minimum Y value of the range.
     * @param highY The maximum Y value of the range.
     * @return A list of pointers to all the lines in that range.
     */
    Vector<Line *> linesInRange(double lowY, double highY) const;

    /**
     * Given a Y coordinate, returns a pointer to the line at that Y coordinate, or nullptr
     * if there is no line there.
     *
     * You can assume that the lines don't overlap one another.
     *
     * This function should run in time O(n), where n is the total number of lines.
     *
     * @param y The y coordinate to test.
     * @return The line at that position, or nullptr if no line is there.
     */
    Line* lineAt(double y) const;

private:
    Vector<Line*> lines_;
    // TODO: add any helper functions and instance variables you need
    bool inRange(double low, double high, double num) const;
    
};
