#pragma once

#include "Panel.h"
#include "ginteractors.h"
#include <string>

/**
 * Type representing an address bar. Typing an article here and hitting ENTER
 * or clicking "Search" will change which article is currently displayed.
 */
class AddressPanel: public Panel {
public:
    /* Constructs an AddressPanel */
    AddressPanel(Browser* browser, GWindow& window);

    /* If we trigger an action event, handle that event by changing the page. */
    virtual void actionPerformed(GObject* source) override;

    /* Change the title bar when the page changes. */
    virtual void pageChanged(const std::string& title) override;

private:
    Browser* const browser;
    GTextField* searchBar;
    GButton *searchButton;
};
