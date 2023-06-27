#pragma once

#include "Panel.h"
#include "gwindow.h"
#include <string>

/* A type representing a status indicator for displaying update progress. */
class StatusPanel: public Panel {
public:
    StatusPanel(GWindow& window);

    /* Sets the currently-displayed text. */
    void setText(const std::string& message);

private:
    GLabel* statusIndicator;
};
