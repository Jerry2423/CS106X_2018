#include "AddressPanel.h"
#include "Browser.h"
using namespace std;

/* Graphics constants. */
namespace {
    const string kSearchTitle = "Article: ";
    const string kSearchButtonTitle = "Search";
    const int kSearchWidth = 30;
    const string kButtonFont = "Monospaced-16";

}

AddressPanel::AddressPanel(Browser* browser, GWindow& window)
    : browser(browser) {

    searchBar = new GTextField(kSearchWidth);
    window.addToRegion(new GLabel(kSearchTitle), "NORTH");
    window.addToRegion(searchBar, "NORTH");
    searchBar->addChangeListener();

    searchButton = new GButton(kSearchButtonTitle);
    searchButton->setFont(kButtonFont);
    window.addToRegion(searchButton, "NORTH");
}

/* If an action is performed that was spawned by the search bar, go and change
 * the page to refer to that new article.
 */
void AddressPanel::actionPerformed(GObject* source) {
    if (source == searchBar || source == searchButton) {
        browser->setPage(searchBar->getText());
    }
}

/* Keep the address bar text in sync with the current page. */
void AddressPanel::pageChanged(const string& title) {
    searchBar->setText(title);
}
