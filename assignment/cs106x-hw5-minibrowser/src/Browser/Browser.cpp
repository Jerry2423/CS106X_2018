#include "Browser.h"
#include "AddressPanel.h"
#include "HistoryPanel.h"
#include "HTMLPanel.h"
#include "StatusPanel.h"
#include "GraphicsConstants.h"
using namespace std;

/* Graphics constants. */
namespace {
    const double kTextAreaWidth  = GraphicsConstants::kWindowWidth;
    const double kTextAreaHeight = GraphicsConstants::kWindowHeight;
    const string kWindowTitle = "MiniBrowser";

    /* Window subdivision areas. */
    GRectangle renderedTextArea() {
        return { 0, 0, kTextAreaWidth, kTextAreaHeight + Frame::kFrameHeight };
    }
}

/* Install all the relevant components. */
Browser::Browser() {
    window.setRepaintImmediately(false);
    window.setExitOnClose();
    window.setTitle(kWindowTitle);

    panels.push_back(make_shared<AddressPanel>(this, window));
    panels.push_back(make_shared<HistoryPanel>(this, window));

    auto statusPanel = make_shared<StatusPanel>(window);
    panels.push_back(statusPanel);

    window.setCanvasSize(GraphicsConstants::kWindowWidth, GraphicsConstants::kWindowHeight);

    /* Assemble the graphics panels. The HTML panel needs to be drawn before the autocomplete
     * panel because the autocomplete panel will overdraw it.
     */
    panels.push_back(make_shared<HTMLPanel>(renderedTextArea(), this, window, statusPanel.get()));

    window.pack();
}

/* Before this object is destroyed, clear out all pointers to panels so that they can
 * dispose of themselves without having a dangling pointer back here.
 */
Browser::~Browser() {
    panels.clear();
}

/* Change the currently-displayed page. */
void Browser::setPage(const string& page) {
    string currentPage = page;
    for (auto panel: panels) {
        panel->pageChanged(currentPage);
    }
}

/* Redraws the browser. */
void Browser::repaint() {
    /* If no one has actually asked us to redraw, don't redraw anything. */
    if (!isDirty) return;

    /* Clear the window contents. */
    window.setColor("White");
    window.fillRect(0, 0, window.getCanvasWidth(), window.getCanvasHeight());

    /* Ask each panel to draw itself. */
    for (auto panel: panels) {
        if (auto gPanel = dynamic_pointer_cast<GraphicsPanel>(panel)) {
            if (gPanel->isVisible()) gPanel->draw(window);
        }
    }

    window.repaint();
    isDirty = false;
}

/* Top-level event dispatching logic. */
void Browser::handleEvent(GEvent e) {
    /* Action events get sent down to all the panels. */
    if (e.getEventClass() == ACTION_EVENT) {
        GActionEvent event(e);
        for (auto panel: panels) {
            panel->actionPerformed(event.getSource());
        }
    }
    /* Mouse events get sent down to all the graphics panels. */
    else if (e.getEventClass() == MOUSE_EVENT) {
        GMouseEvent event(e);

        /* If this is a "mouse-out" event, remove focus from whatever has it. */
        if (event.getEventType() == MOUSE_EXITED) {
            setFocus(nullptr);
            return;
        }

        /* Visit the panels in reverse order so that the topmost panel that we hit absorbs the
         * event.
         */
        for (auto itr = panels.rbegin(); itr != panels.rend(); ++itr) {
            auto panel = *itr;
            if (auto gPanel = dynamic_pointer_cast<GraphicsPanel>(panel)) {
                /* Hit-testing is done in the global coordinate space. */
                if (gPanel->contains(event.getX(), event.getY())) {
                    /* Mouse events are done in the local coordinate space. */
                    double x = event.getX() - gPanel->bounds().getX();
                    double y = event.getY() - gPanel->bounds().getY();

                    /* Handle changes in focus. */
                    setFocus(gPanel.get());

                    switch (event.getEventType()) {
                        case MOUSE_PRESSED:    gPanel->mousePressed(x, y); break;
                        case MOUSE_DRAGGED:    gPanel->mouseDragged(x, y); break;
                        case MOUSE_CLICKED:    gPanel->mouseClicked(x, y); break;
                        case MOUSE_MOVED:      gPanel->mouseMoved(x, y);   break;
                        case MOUSE_ENTERED:    gPanel->mouseEntered();     break;
                        case MOUSE_WHEEL_DOWN: gPanel->mouseScrolled(+1);  break;
                        case MOUSE_WHEEL_UP:   gPanel->mouseScrolled(-1);  break;
                        default: break;
                    }

                    /* Don't continue to have other panels react. */
                    return;
                }
            }
        }

        /* If we got here, nothing received the message. */
        setFocus(nullptr);
    }
    /* Change events are sent to each component. */
    else if (e.getEventClass() == CHANGE_EVENT) {
        GChangeEvent event(e);
        for (auto panel: panels) {
            panel->changeOccurredIn(event.getSource());
        }
    }
    /* Scroll events are sent to each component as changes. */
    else if (e.getEventClass() == SCROLL_EVENT) {
        GScrollEvent event(e);
        for (auto panel: panels) {
            panel->changeOccurredIn(event.getSource());
        }
    }
}

/* Requesting a repaint just sets our internal "dirty" flag. */
void Browser::requestRepaint() {
    isDirty = true;
}

/* A change in focus corresponds to the mouse moving from one panel to another. */
void Browser::setFocus(GraphicsPanel* panel) {
    /* If this window already has focus, there's nothing to do. */
    if (focused != panel) {
        if (focused) focused->mouseExited();

        focused = panel;

        if (focused) focused->mouseEntered();
    }
}
