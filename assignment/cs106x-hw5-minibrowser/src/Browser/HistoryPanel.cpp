#include "HistoryPanel.h"
#include "Browser.h"
using namespace std;

namespace {
    const string kPrevButton = "  \xE2\x86\x90  "; // Unicode left arrow
    const string kNextButton = "  \xE2\x86\x92  "; // Unicode right arrow

    const string kButtonFont = "Monospaced-BOLD-24";
}

HistoryPanel::HistoryPanel(Browser* browser, GWindow& window) : browser(browser) {
    prev = new GButton(kPrevButton);
    next = new GButton(kNextButton);

    prev->setFont(kButtonFont);
    next->setFont(kButtonFont);

    window.addToRegion(prev, "NORTH");
    window.addToRegion(next, "NORTH");
}

void HistoryPanel::actionPerformed(GObject* source) {
    if (source == prev && history.hasPrevious()) {
        weInitiatedChange = true;
        browser->setPage(history.previous());
    } else if (source == next && history.hasNext()) {
        weInitiatedChange = true;
        browser->setPage(history.next());
    }
}

void HistoryPanel::pageChanged(const string& title) {
    if (!weInitiatedChange) {
        history.goTo(title);
    }
    weInitiatedChange = false;

    /* Toggle the button states based on whether we can go forwards or backwards. */
    next->setEnabled(history.hasNext());
    prev->setEnabled(history.hasPrevious());
}
