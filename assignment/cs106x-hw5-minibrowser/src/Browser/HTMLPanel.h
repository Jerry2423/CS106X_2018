#pragma once

#include "Panel.h"
#include "Cache.h"
#include "StatusPanel.h"
#include "LineManager.h"
#include "ginteractors.h"
#include <memory>

/**
 * Main content display. This panel is responsible for drawing the actual article contents
 * and for reacting to link clicks.
 */
class HTMLPanel: public GraphicsPanel {
public:
    HTMLPanel(const GRectangle& bounds, Browser* browser, GWindow& window, StatusPanel* statusPanel);

    /* Mouse clicks might trigger a page reload. */
    virtual void mouseClicked(double x, double y) override;

    /* Mouse motion is used to highlight frames. */
    virtual void mouseMoved(double x, double y) override;

    /* If the mouse leaves, we deselect everything. */
    virtual void mouseExited() override;

    /* If the mouse scrolls, adjust the scrollbar. */
    virtual void mouseScrolled(int direction) override;

    /* Draws the text of the page. */
    virtual void draw(GWindow& window) override;

    /* Rerenders the page on a page load. */
    virtual void pageChanged(const std::string& title) override;

    /* Reacts to a scrollbar. */
    virtual void changeOccurredIn(GObject* source) override;

private:
    /* Cached labels to speed up drawing. This eliminates the need to construct labels and set
     * their fonts every time we do a render.
     */
    GLabel text, link, active;

    /* The Y coordinate at the top of the current display. */
    GRectangle view;

    /* Page cache, to speed up navigation. */
    Cache<std::shared_ptr<LineManager>> cache;

    /* Last frame hovered over; used for highlighting. */
    const Frame* hovered = nullptr;

    /* Status panel, used for reporting progress. */
    StatusPanel* const statusPanel;

    /* Scrollbar. We control this internally. */
    GScrollBar* scrollbar;

    /* The current page. Default is an empty page. */
    std::shared_ptr<LineManager> currentPage = std::make_shared<LineManager>(Vector<Line *>());

    /* Given a page name, returns the contents of that page. */
    std::shared_ptr<LineManager> pageContents(const std::string& title);

    /* Returns a GRectangle holding the current view in logical space. */
    GRectangle currentView() const;

    /* Returns a GRectangle holding the full space used by the content. */
    GRectangle contentSpace() const;

    /* Scrolls to the specified logical y coordinate. */
    void scrollTo(double y);

    /* Recomputes the size the scrollbar should use. */
    void recomputeScrollbar();
};
