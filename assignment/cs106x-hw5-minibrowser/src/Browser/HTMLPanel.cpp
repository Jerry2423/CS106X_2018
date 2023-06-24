#include "HTMLPanel.h"
#include "Browser.h"
#include "Downloader.h"
#include "GraphicsConstants.h"
#include "LineConstructor.h"
using namespace std;

namespace {
    const string kFont = GraphicsConstants::kBrowserFont + "-" + to_string(GraphicsConstants::kBrowserFontSize);
    const string kLinkFont = GraphicsConstants::kBrowserFont + "-BOLD-" + to_string(GraphicsConstants::kBrowserFontSize);
    const string kActiveLinkFont = GraphicsConstants::kBrowserFont + "-BOLD-" + to_string(GraphicsConstants::kBrowserFontSize);

    const string kFontColor = "Black";
    const string kLinkColor = "Blue";
    const string kActiveLinkColor = "Red";

    /* Amount the scroll needs to change before we change the view. Used to collapse multiple
     * scroll events into a single one.
     */
    const double kScrollTolerance = 0.5;

    /* Content-space number of pixels to jump up or down on a scroll. */
    const double kScrollAmount = Frame::kFrameHeight * 2.75;

    const size_t kCacheSize = 128;
}

HTMLPanel::HTMLPanel(const GRectangle& bounds, Browser* browser,
                     GWindow& window, StatusPanel* statusPanel)
    : GraphicsPanel(bounds, browser), cache(kCacheSize), statusPanel(statusPanel) {
    /* Set up labels for rendering text later on. */
    link.setFont(kLinkFont);
    link.setColor(kLinkColor);

    text.setFont(kFont);
    text.setColor(kFontColor);

    active.setFont(kActiveLinkFont);
    active.setColor(kActiveLinkColor);

    /* Set up our scrollbar. */
    scrollbar = new GScrollBar(GScrollBar::VERTICAL, 0, 10, 0, window.getCanvasHeight());
    window.addToRegion(scrollbar, "EAST");
}

void HTMLPanel::draw(GWindow& window) {
    /* Determine the range to draw in content space. */
    double lowY  = currentView().getY();
    double highY = currentView().getY() + currentView().getHeight();

    /* Conversion factor from content space to window space. */
    double dx = bounds().getX();
    double dy = bounds().getY() - currentView().getY();

    /* Draw all lines in range. */
    for (auto line: currentPage->linesInRange(lowY, highY)) {
        for (auto frame: line->frames()) {
            GLabel* label;
            if (frame == hovered) {
                label = &active;
            } else if (frame->isLink()) {
                label = &link;
            } else {
                label = &text;
            }

            label->setLocation(frame->x() + dx, frame->y() + frame->height() - label->getFontDescent() + dy);
            label->setText(frame->text());

            window.draw(label);
        }
    }
}

shared_ptr<LineManager> HTMLPanel::pageContents(const string& title) {
    if (!cache.containsKey(title)) {
        statusPanel->setText("Downloading article...");
        auto page   = downloadPage(title);

        statusPanel->setText("Laying out page...");
        auto pageLayout = layOutPage(page, bounds().getWidth());
        cache.put(title, pageLayout);

        statusPanel->setText("");
        return pageLayout;
    }
    return cache.get(title);
}

/* When the page changes, we need to overhaul the layout. */
void HTMLPanel::pageChanged(const string& title) {
    /* Build up the frames necessary to display everything, then update our content height
     * based on where the final frame ended up.
     */
    currentPage = pageContents(title);

    /* Reset the scrollbar. */
    recomputeScrollbar();

    /* Reset our view to the top of the page. */
    scrollTo(0);

    /* Whatever we were hovering over is no longer valid. */
    hovered = nullptr;
}

/* When the scrollbar moves, recompute our view. */
void HTMLPanel::changeOccurredIn(GObject* source) {
    if (source == scrollbar) {
        double alpha = scrollbar->getValue() / static_cast<double>(scrollbar->getMax() - scrollbar->getExtent());
        double y     = alpha * currentPage->contentHeight();

        /* Avoid rescrolling to a spot we're already at. */
        if (fabs(y - currentView().getY()) > kScrollTolerance) {
            scrollTo(alpha * currentPage->contentHeight());
        }
    }
}

void HTMLPanel::mouseClicked(double x, double y) {
    /* Convert from screen coordinates to content coordinates. */
    y += currentView().getY();

    if (auto line = currentPage->lineAt(y)) {
        for (auto frame: line->frames()) {
            if (frame->contains(x, y) && frame->isLink()) {
                browser()->setPage(frame->linksTo());
            }
        }
    }
}

void HTMLPanel::mouseMoved(double x, double y) {
    /* Remember what we used to be hovering over. */
    auto oldHovered = hovered;
    hovered = nullptr;

    /* Convert from screen space to content space. */
    y += currentView().getY();

    if (auto line = currentPage->lineAt(y)) {
        for (auto frame: line->frames()) {
            if (frame->contains(x, y) && frame->isLink()) {
                hovered = frame;
                break;
            }
        }
    }

    if (oldHovered != hovered) browser()->requestRepaint();
}

void HTMLPanel::mouseExited() {
    hovered = nullptr;
    browser()->requestRepaint();
}

void HTMLPanel::mouseScrolled(int direction) {
    /* Convert from logical scroll distance to scrollbar distance. */
    int scrollMax = scrollbar->getMax() - scrollbar->getExtent();
    int delta = direction * kScrollAmount * (scrollMax / currentPage->contentHeight());

    /* We need to move at least one pixel. */
    if (delta == 0) delta = direction;

    /* Convert back from logical space to scrollSpace. */
    int target = min(max(0, scrollbar->getValue() + delta), scrollMax);

    scrollbar->setValue(target);
    changeOccurredIn(scrollbar);
}

GRectangle HTMLPanel::currentView() const {
    return view;
}

GRectangle HTMLPanel::contentSpace() const {
    return { 0, 0, bounds().getWidth(), currentPage->contentHeight() };
}

void HTMLPanel::scrollTo(double y) {
    view = { 0, y, bounds().getWidth(), bounds().getHeight() };
    browser()->requestRepaint();
}

void HTMLPanel::recomputeScrollbar() {
    scrollbar->setValue(0);
    double windowHeight = scrollbar->getMax();
    scrollbar->setExtent(min(windowHeight, windowHeight * windowHeight / currentPage->contentHeight()));
}
