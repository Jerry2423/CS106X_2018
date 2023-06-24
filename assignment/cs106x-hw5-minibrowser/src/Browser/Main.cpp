#include "vector.h"
#include <string>
#include "goptionpane.h"
#include "Browser.h"
#include "gevents.h"
#include "HistoryTests.h"
#include "CacheTests.h"
#include "LineManagerTests.h"
#include "TestDriver.h"
#include "console.h"

using namespace std;

[[ noreturn ]] void runBrowser();
void runTests();

int main() {
    Vector<string> options {"B: Run MiniBrowser", "A: Run Tests"};
    string choice = GOptionPane::showOptionDialog("Welcome to MiniBrowser!", options);
    if (choice == options[1]) {
        runTests();
    } else if (choice == options[0]) {
        runBrowser();
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
    runTestsIn("LineManager",  gLineManagerTests);
    runTestsIn("History",      gHistoryTests);
    runTestsIn("Cache",        gCacheTests);
}


