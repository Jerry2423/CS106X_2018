#pragma once

#include "Panel.h"
#include "AutocompletePanel.h"
#include "ginteractors.h"
#include <string>

/**
 * Type representing an address bar. Typing an article here and hitting ENTER
 * or clicking "Search" will change which article is currently displayed.
 */
class AddressPanel: public Panel {
public:
    /* Constructs an AddressPanel wired into the specified AutocompletePanel. */
    AddressPanel(Browser* browser, GWindow& window, AutocompletePanel* autoPanel);

    /* If we trigger an action event, handle that event by changing the page. */
    virtual void actionPerformed(GObject* source) override;

    /* When the text changes, we need to notify the autocomplete panel. */
    virtual void changeOccurredIn(GObject* source) override;

    /* Change the title bar when the page changes. */
    virtual void pageChanged(const std::string& title) override;

    /* Reports the currently-displayed text. */
    std::string text() const;

private:
    Browser* const browser;
    AutocompletePanel* const autocomplete;
    GTextField* searchBar;
    GButton* searchButton;

    /* Last text displayed, used to filter extra changeEvents. */
    std::string lastText;
};
