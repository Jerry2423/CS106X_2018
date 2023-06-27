#include "AutocompletePanel.h"
#include "Browser.h"
#include "GraphicsConstants.h"
#include <fstream>
#include "error.h"
using namespace std;

namespace {
    /* Graphics constants. */
    const string kSuggestionsFile = "TopArticles.txt";

    const int kAutocompleteFontSize = 18;

    const string kAutocompleteFont  = GraphicsConstants::kBrowserFont + "-BOLD-" + to_string(kAutocompleteFontSize);
    const string kAutocompleteColor = "Black";

    const string kBackgroundColor = "#E0E0FF";
    const string kBorderColor = "Blue";

    /* Converts a Set<string> to a Vector. */
    Vector<string> toVector(const Set<string>& words) {
        Vector<string> result;
        for (const string& word: words) {
            result += word;
        }
        return result;
    }
}

AutocompletePanel::AutocompletePanel(const GRectangle& bounds, Browser* browser)
  : GraphicsPanel(bounds, browser), suggestionLabels(size_t(kMaxSuggestions))
{
    /* Fill in our autocomplete with some good suggestions. */
    ifstream input(kSuggestionsFile);
    if (!input) error("Can't open articles file " + kSuggestionsFile);
    for (string line; getline(input, line); ) {
        autocomplete.add(line);
    }

    /* Initialize the labels so that they're properly-placed and ready to go. */
    for (size_t i = 0; i < suggestionLabels.size(); i++) {
        /* Offset everything by one position, since we draw on the baseline. */
        suggestionLabels[i].setLocation(bounds.getX(), bounds.getY() + kFontHeight * (i + 1));
        suggestionLabels[i].setFont(kAutocompleteFont);
        suggestionLabels[i].setColor(kAutocompleteColor);
    }

    /* By default, we are not visible. */
    setVisible(false);
}

void AutocompletePanel::setPrefix(const string& prefix) {
    /* Otherwise, get some hits. If they're new, update our recommendations. */
    auto hits = toVector(autocomplete.suggestionsFor(prefix, kMaxSuggestions));
    if (hits != suggestions) {
        updateSuggestions(hits);
    }
}

/* Disables the autocomplete panel. This both hides us (so we don't appear anywhere) and clears
 * out the list of suggestions (so that we don't confuse ourselves into thinking we have
 * suggestions to provide.
 */
void AutocompletePanel::disable() {
    suggestions.clear();
    setVisible(false);
}

/* Changes the text of one of the displayed suggestions to a new value. Because the
 * value might be quite long, we may need to trim it. We'll use a modified binary search
 * to determine how to do this.
 */
void AutocompletePanel::setLabel(size_t i, const string& text) {
    /* Change the text and optimistically hope it fits. */
    suggestionLabels[i].setLabel(text);

    double maxX = bounds().getX() + bounds().getWidth();
    if (suggestionLabels[i].getX() + suggestionLabels[i].getWidth() <= maxX) {
        return;
    }

    /* Oh great. We don't fit. If that happens, we need to do our best to make things fit
     * anyway. That requires a binary search.
     *
     * The problem is that we're working with UTF-8-encoded strings, so we can't just
     * arbitrarily chop the string. That might chop right in the middle of a multibyte
     * character. Instead, we can only cut at positions corresponding to character boundaries.
     *
     * Begin by making a list of where all those boundaries are.
     */
    vector<size_t> charStarts;
    for (size_t i = 0; i < text.size(); ) {
        charStarts.push_back(i);

        /* Scan until we hit the end of the string or find a character whose top two bits
         * aren't the "continuation" pattern 10xxxxxx.
         */
        do {
            i++;
        } while (i < text.size() && (text[i] & 0b11000000) == 0b10000000);
    }

    /* Bisect over this to find the largest string that fits with an ellipsis tacked on. The
     * invariant is that nothing before index low works, and everything from index high or
     * above doesn't work.
     */
    size_t low = 0, high = charStarts.size();
    while (low < high) {
        int mid = low + (high - low) / 2;

        string probeText = text.substr(0, charStarts[mid]) + "...";
        suggestionLabels[i].setLabel(probeText);

        /* If this doesn't fit, bisect down. */
        if (suggestionLabels[i].getX() + suggestionLabels[i].getWidth() > maxX) {
            high = mid;
        }
        /* Otherwise, we know that this works. Bisect up. */
        else {
            low = mid + 1;
        }
    }

    /* At this point, low == high and the index right before them was the last that worked. In
     * the bizarre case that NOTHING fits, use an empty label.
     */
    if (low == 0) suggestionLabels[i].setLabel("");
    else suggestionLabels[i].setLabel(text.substr(0, charStarts[low - 1]) + "...");
}

/* Updates the suggestions to display, and recomputes the graphics accordingly. */
void AutocompletePanel::updateSuggestions(const Vector<string>& hits) {
    if (hits.size() > kMaxSuggestions) error("Too many suggestions returned.");

    /* If we have no suggestions, don't display anything. */
    if (hits.isEmpty()) {
        disable();
        return;
    }

    /* Copy suggestions over to our labels. */
    for (int i = 0; i < hits.size(); i++) {
        setLabel(i, hits[i]);
    }

    suggestions = hits;
    setVisible(true);
    browser()->requestRepaint();
}

void AutocompletePanel::draw(GWindow& window) {
    /* Redraw the background, wiping whatever was here. */
    window.setColor(kBackgroundColor);
    window.fillRect(bounds());

    /* Redraw the border. */
    window.setColor(kBorderColor);
    window.drawRect(bounds());

    /* Draw each label. */
    for (int i = 0; i < suggestions.size(); i++) {
        window.draw(&suggestionLabels[i]);
    }
}

void AutocompletePanel::pageChanged(const string& title) {
    /* Put what the user typed in into the autocomplete window so that they can find it
     * later on.
     */
    autocomplete.add(title);
}

void AutocompletePanel::mouseClicked(double x, double y) {
    /* Oddly enough, this is one of those times where we do want to be in global space,
     * since our labels are in global space and they know where they are.
     */
    x += bounds().getX();
    y += bounds().getY();

    /* See if any of the labels contain us. */
    for (int i = 0; i < suggestions.size(); i++) {
        if (suggestionLabels[i].contains(x, y)) {
            browser()->setPage(suggestions[i]);
        }
    }
}
