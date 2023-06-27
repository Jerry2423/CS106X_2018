#include "vector.h"
#include <string>
#include "goptionpane.h"
#include "Browser.h"
#include "gevents.h"
#include "EncodingTests.h"
#include "AutocompleteTests.h"
#include "LineManagerTests.h"
#include "TestDriver.h"
#include "console.h"
#include "huffmanmain.h"

using namespace std;

[[ noreturn ]] void runBrowser();
void runTests();

int main() {
    Vector<string> options {"C: Run Shrink-It", "B: Run MiniBrowser", "A: Run Tests"};
    string choice = GOptionPane::showOptionDialog("Welcome to MiniBrowser!", options);
    if (choice == options[2]) {
        runTests();
    } else if (choice == options[1]) {
        runBrowser();
    } else if (choice == options[0]) {
        huffmanMain();
    }

    return 0;
}

void runBrowser() {
    Browser browser;
    browser.setPage("special:welcome");

    /* Run the main event loop. */
    while (true) {
        /* This won't actually do anything unless the browser has been asked to repaint itself. */
        browser.repaint();

        /* Forward all events to the browser. */
        GEvent e = waitForEvent(ACTION_EVENT | MOUSE_EVENT | CHANGE_EVENT);
        browser.handleEvent(e);
    }
}

void runTests() {
    runTestsIn("LineManager", gLineManagerTests);
    runTestsIn("Autocomplete", gAutocompleteTests);
    runTestsIn("Encoding", gEncodingTests);
}


