#pragma once

#include "Panel.h"
#include "History.h"
#include "ginteractors.h"

/**
 * Panel that keeps track of the browser history. Exposes the forward/backward buttons.
 */
class HistoryPanel: public Panel {
public:
    HistoryPanel(Browser* browser, GWindow& window);

    /* Initiate a page change, if appropriate. */
    void actionPerformed(GObject* source) override;

    /* Update the browser history if we didn't initiate the change. */
    void pageChanged(const std::string& title) override;

private:
    Browser* const browser;

    GButton* next;
    GButton* prev;

    History history;
    bool weInitiatedChange = false; // So we don't double-update the history.
};
