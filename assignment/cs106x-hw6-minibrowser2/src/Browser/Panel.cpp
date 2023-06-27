#include "Panel.h"
#include "Browser.h"

/***** Panel Implementation *****/

/* Default action behavior is nothing. */
void Panel::actionPerformed(GObject *) {

}

/* Default behavior on a page change is nothing. */
void Panel::pageChanged(const std::string &) {

}

/* Default action is nothing. */
void Panel::changeOccurredIn(GObject *) {

}

/***** GraphicsPanel Implementation *****/


/* Constructor just stores the bounding rectangle. */
GraphicsPanel::GraphicsPanel(const GRectangle& bounds, Browser* browser) : theBounds(bounds), theBrowser(browser) {

}

/* Default mouse handlers all do nothing. */
void GraphicsPanel::mouseClicked(double, double) {

}
void GraphicsPanel::mouseDragged(double, double) {

}
void GraphicsPanel::mouseEntered() {

}
void GraphicsPanel::mouseExited() {

}
void GraphicsPanel::mouseMoved(double, double) {

}
void GraphicsPanel::mousePressed(double, double) {

}
void GraphicsPanel::mouseScrolled(int) {

}

/* Area functions. */
GRectangle GraphicsPanel::bounds() const {
    return theBounds;
}
bool GraphicsPanel::contains(double x, double y) const {
    return visible && theBounds.contains(x, y);
}

/* Visibility. */
bool GraphicsPanel::isVisible() const {
    return visible;
}

/* Toggling visibility requires a graphics update. */
void GraphicsPanel::setVisible(bool active) {
    bool changed = (visible != active);

    visible = active;
    if (changed) browser()->requestRepaint();
}

/* Underlying browser. */
Browser* GraphicsPanel::browser() const {
    return theBrowser;
}
