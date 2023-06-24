#pragma once

#include "GraphicsConstants.h"
#include "Downloader.h"
#include "gobjects.h"
#include <string>

/**
 * Type representing a rectangular region of the screen that can optionally have a piece of
 * text associated with it. In the browser, each Frame holds one unit of text, and the browser
 * draws its text by selecting which frames to render through the FrameManager and drawing
 * each one in turn.
 */
class Frame {
public:
    /* Constructs a new frame at the specified x/y location, with the specified width. Since
     * all frames have the same height, the height will be Frame::kFrameHeight. The Frame is
     * also associated with an underlying HTML token.
     */
    Frame(double x, double y, double width, const HTMLToken& token);

    /* Constant representing the height of each frame. */
    static constexpr double kFrameHeight = GraphicsConstants::kLineSpacing;

    /* Accessors to get the position of the frame. */
    double x() const;
    double y() const;
    double width() const;
    double height() const;

    /* Returns whether the specified point is contained inside of the rectangle defined
     * by this frame.
     */
    bool contains(double x, double y) const;
    bool contains(const GPoint& pt) const;

    /* Returns the display text, whether this is a link, and what it links to. */
    std::string text() const;
    bool isLink() const;
    std::string linksTo() const;

private:
    GRectangle theBounds;
    std::string theText;
    std::string theLink;
};
