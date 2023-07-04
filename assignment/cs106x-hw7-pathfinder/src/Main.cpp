/*
 * CS 106X Pathfinder
 * This file contains the main method to run the overall program.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, Keith Schwarz, et al
 * @version 2018/11/16
 * - 18au version
 * @version 2017/11/16
 * - 106X 17au version; minor output changes
 * @version 2014/11/19
 * - initial version for 14au
 */

#include "gevents.h"
#include "gwindow.h"
#include "PathfinderGUI.h"
#include "WorldGrid.h"
#include "console.h"
#include "goptionpane.h"
#include "TestDriver.h"
#include "PathfinderAlgorithmsTests.h"

static const std::string WINDOW_TITLE = "CS 106X Pathfinder";

/*
 * Prints an introductory text message on the screen.
 */
static void intro();

[[ noreturn ]] static void runPathfinder();

int main() {
    Vector<std::string> options {"A: Run Tests", "B: Run Pathfinder"};
    std::string choice = GOptionPane::showOptionDialog("Welcome to Pathfinder!", options);
    if (choice == options[0]) {
        runTestsIn("PathfinderAlgorithms", gPathfinderAlgorithmsTests);
    } else if (choice == options[1]) {
        runPathfinder();
    }

    return 0;
}

/*
 * Main program.
 */
void runPathfinder() {
    intro();

    // create GUI window and position the console to its right
    setConsoleLocation(WorldGrid::WINDOW_WIDTH + 6 * WorldAbstract::WINDOW_MARGIN,
                       WorldAbstract::WINDOW_MARGIN);   // temporary
    // setConsoleSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    setConsoleEventOnClose(true);
    
    PathfinderGUI gui(WINDOW_TITLE);
    pause(100);
    gui.snapConsoleLocation();

    // main event loop to process events as they happen
    while (true) {
        GEvent e = waitForEvent(ACTION_EVENT | MOUSE_EVENT | WINDOW_EVENT);
        if (e.getEventType() == MOUSE_CLICKED || e.getEventType() == MOUSE_MOVED) {
            gui.processMouseEvent(GMouseEvent(e));
        } else if (e.getEventClass() == ACTION_EVENT) {
            gui.processActionEvent(GActionEvent(e));
        } else if (e.getEventClass() == WINDOW_EVENT) {
            gui.processWindowEvent(GWindowEvent(e));
        }
    }
}

static void intro() {
    std::cout << "Welcome to CS 106X Pathfinder!" << std::endl;
    std::cout << "This program searches for paths through graphs" << std::endl;
    std::cout << "representing maps, mazes, and rocky terrains." << std::endl;
    std::cout << "It demonstrates several graph algorithms for" << std::endl;
    std::cout << "finding paths, such as depth-first search (DFS)," << std::endl;
    std::cout << "breadth-first search (BFS), Dijkstra's Algorithm," << std::endl;
    std::cout << "A* search, and Alternate Path search." << std::endl;
}
