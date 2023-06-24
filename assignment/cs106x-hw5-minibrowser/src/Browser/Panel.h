#pragma once
#include "gobjects.h"
#include "gwindow.h"
#include "gtimer.h"

class Browser;

/* Base Class: Panel
 *
 * A type representing something that shows up in the graphics system. This could be something
 * like the text area (drawn in the canvas) or a URL bar (drawn in the chrome). The only interesing
 * things about them is that they react to events.
 */

class Panel {
public:
    virtual ~Panel() = default;

    /* React to an action command. Default is to do nothing. */
    virtual void actionPerformed(GObject* source);

    /* React to a change event. */
    virtual void changeOccurredIn(GObject* source);

    /* Reacts to the page changing. */
    virtual void pageChanged(const std::string& title);
};

/* A panel that appears in the graphics system. */
class GraphicsPanel: public Panel {
public:
    /* Bounding rectangle and hit test in global space. */
    GRectangle bounds() const;
    bool contains(double x, double y) const;

    /* Whether this panel is visible. Invisible panels don't
     * render and always fail hit tests.
     * */
    bool isVisible() const;
    void setVisible(bool active);

    /* All of these member functions expect x/y inputs within their local
     * coordinate space, with (0, 0) being the upper-left corner.
     */
    virtual void mousePressed(double x, double y);
    virtual void mouseDragged(double x, double y);
    virtual void mouseMoved  (double x, double y);
    virtual void mouseClicked(double x, double y);

    /* Mouse enter/exit events don't receive any arguments. */
    virtual void mouseEntered();
    virtual void mouseExited ();

    /* Scroll receives +1 if the scroll was down and -1 if the scroll was us. */
    virtual void mouseScrolled(int direction);

    /* Draws the component within the specified window. */
    virtual void draw(GWindow& window) = 0;

protected:
    GraphicsPanel(const GRectangle& bounds, Browser* browser);
    Browser* browser() const;

private:
    const GRectangle theBounds;
    Browser* const theBrowser;

    bool visible = true;
};
