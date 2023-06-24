#pragma once

#include "Frame.h"
#include <memory>
#include <vector>

/* Type representing a line that can be rendered in the display window.
 *
 * Each line is represented by a range of Y values. The assumption is that each
 * line takes up the entirety of the width of the window, so no information is
 * stored about the width of a given line.
 *
 * Each line may optionally be associated with a collection of frames, where
 * each frame actually represents an individually renderable unit of text. The
 * browser internally will tag each line with some frames, but in the course of
 * your work on the LineManager and the tests for the LineManager you aren't
 * expected to do this.
 */
class Line {
public:
    /**
     * Constructs a new line spanning the indicated range of Y values, which are
     * assumed to be inclusive.
     *
     * If lowY > highY, this will report an error.
     *
     * @param lowY  The low end of the range occupied by this line.
     * @param highY The high end of the range occupied by this line.
     */
    Line(double lowY, double highY);

    /**
     * Deallocates all memory used by this Line.
     */
    ~Line();

    /**
     * Returns the low end of the range occupied by this line. This value is inclusive.
     *
     * @return The low end of the range occupied by this line.
     */
    double lowY() const;

    /**
     * Returns the high end of the range occupied by this line. This value is inclusive.
     *
     * @return The high end of the range occupied by this line.
     */
    double highY() const;

    /**
     * Associates a list of frames (individually renderable text units) with this given
     * line. This is used internally by the browser and you won't need to use this
     * function when implementing the LineManager.
     *
     * Any existing frames will be discarded.
     *
     * @param frames The list of frames to associate with this line.
     */
    void setFrames(const std::vector<Frame *>& frames);

    /**
     * Returns the underlying list of frames associated with this line. This is used
     * internally by the browser, and you won't need to call this function when implementing
     * the LineManager.
     *
     * @return The frames that comprise this line.
     */
    const std::vector<Frame *>& frames() const;

private:
    /* Range along the Y axis used by this line. These values are inclusive. */
    const double theLowY, theHighY;

    /* An optional, associated list of frames. */
    std::vector<Frame *> theFrames;

    /* Deallocates all memory used by the list of frames. */
    void clear();
};
