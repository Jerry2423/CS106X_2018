#include "StatusPanel.h"
using namespace std;

StatusPanel::StatusPanel(GWindow& window) {
    statusIndicator = new GLabel(" ");
    window.addToRegion(statusIndicator, "SOUTH");
}

void StatusPanel::setText(const string& message) {
    statusIndicator->setText(message + " ");
}
