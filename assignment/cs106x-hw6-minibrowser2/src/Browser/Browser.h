#pragma once

#include "Panel.h"
#include "gwindow.h"
#include "gevents.h"
#include <vector>
#include <string>
#include <memory>

/**
 * Type representing a web browser. The Browser type aggregates the other panels together,
 * forwards requests to them, and tracks top-level state (e.g. what page we are currently
 * visiting.)
 */
class Browser {
public:
    Browser();
    ~Browser();

    /* Changes which page we're on. */
    void setPage(const std::string& page);

    /* Redraws the window. This may be a no-op if there's nothing to do. */
    void repaint();

    /* Processes an event from the event loop. */
    void handleEvent(GEvent e);

    /* Requests a repaint. */
    void requestRepaint();

private:
    GWindow window;
    std::vector<std::shared_ptr<Panel>> panels;

    /* Which graphics panel, if any, has mouse focus. */
    GraphicsPanel* focused = nullptr;
    void setFocus(GraphicsPanel* panel);

    bool isDirty = false;
};
