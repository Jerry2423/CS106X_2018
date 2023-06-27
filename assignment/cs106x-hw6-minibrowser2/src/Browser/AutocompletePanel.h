#pragma once

#include "Panel.h"
#include "Autocomplete.h"
#include "gobjects.h"
#include <vector>

/**
 * A panel that displays autocomplete results.
 */
class AutocompletePanel: public GraphicsPanel {
public:
    AutocompletePanel(const GRectangle& bounds, Browser* browser);

    /* Draws the suggestions. */
    virtual void draw(GWindow& window) override;

    /* If the page changes, add whatever was seen to our list. */
    virtual void pageChanged(const std::string& title) override;

    /* If they click on a suggestion, warp to that page. */
    virtual void mouseClicked(double x, double y) override;

    /* Sets which string to suggest completions for. */
    void setPrefix(const std::string& prefix);

    /* Disables the AutocompletePanel, hiding its results. */
    void disable();

private:
    Autocomplete autocomplete;
    Vector<std::string> suggestions;
    std::vector<GLabel> suggestionLabels;

    /* Internal constants used to control the display. */
    static constexpr int kMaxSuggestions = 10;
    static constexpr double kFontHeight  = 24;

    /* Sets the list of suggestions to the specified list. This may trigger a cascade
     * of other graphic events.
     */
    void updateSuggestions(const Vector<std::string>& hits);

    /* Sets the text of the given label, adjusting it as appropriate so that it fits into the
     * display.
     */
    void setLabel(std::size_t i, const std::string& text);

public:
    static constexpr double kAutocompleteWidth = 400;
    static constexpr double kAutocompleteHeight = kMaxSuggestions * kFontHeight + 10; // A little buffer space
};
