/*
 * CS 106X Pathfinder
 * This file implements functions to perform drawing in the graphical user
 * interface (GUI).
 * See the .h for documentation of each public function.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, based on past code by Keith Schwarz
 * @version 2018/11/16
 * - 18au version
 * @version 2017/11/16
 * - 17au version; fixed minor compiler warnings
 * @version 2015/06/08
 * - refactored / improved pathVerify, runPathSearch code
 * @version 2014/11/19
 * - initial version for 14au
 */

#include "PathfinderGUI.h"
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "error.h"
#include "filelib.h"
#include "gevents.h"
#include "gfilechooser.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gwindow.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "timer.h"
#include "vector.h"
#include "console.h"

#include "PathfinderAlgorithms.h"
#include "World.h"
#include "WorldMap.h"
#include "WorldMaze.h"
#include "WorldTerrain.h"
#include "PathfinderUtil.h"

const int PathfinderGUI::ANIMATION_DELAY_MIN = 1;
const int PathfinderGUI::ANIMATION_DELAY_MAX = 2000;
const int PathfinderGUI::ANIMATION_DELAY_DEFAULT = 200;

// internal constants
static bool pathSearchInProgress = false;
static const bool SHOW_RUNTIMES = false;

// various UI strings and settings
const std::string GUI_STATE_FILE("pathfinder-gui-state.sav");
const std::string OTHER_FILE_LABEL("Other file ...");
const std::string INITIALLY_SELECTED_FILE("map-stanford.txt");

const bool SHOULD_SAVE_GUI_STATE = true;

// function implementations

/*
 * Initializes state of the GUI subsystem.
 */
PathfinderGUI::PathfinderGUI(std::string windowTitle) {
    world = nullptr;
    animationDelay = 0;
    gtfPositionText = " ";
    
    // Calculate the intended width and height of the window based on the content
    // area size, the margin size, and the adjustment amount.
    int windowWidth = WorldGrid::WINDOW_WIDTH + 2 * WorldAbstract::WINDOW_MARGIN;
    int windowHeight = WorldGrid::WINDOW_HEIGHT + 2 * WorldAbstract::WINDOW_MARGIN;

    gWindow = new GWindow(windowWidth, windowHeight);
    gWindow->setWindowTitle(windowTitle);
    gWindow->setExitOnClose(true);

    // Add the algorithms list.
    gcAlgorithm = new GChooser();
    gcAlgorithm->addItem("DFS");
    gcAlgorithm->addItem("BFS");
    gcAlgorithm->addItem("Dijkstra");
    gcAlgorithm->addItem("A*");
    gcAlgorithm->addItem("Alternate Path");
#ifdef BIDIRECTIONAL_SEARCH_ALGORITHM_ENABLED
    gcAlgorithm->addItem("Bidirectional");
#endif // BIDIRECTIONAL_SEARCH_ALGORITHM_ENABLED

    gcbDelay = new GCheckBox("Delay");
    gcbDelay->setChecked(true);
    gcbDelay->setActionCommand("Delay");
    gcbDelay->addActionListener();
    gsDelay = new GSlider(ANIMATION_DELAY_MIN, ANIMATION_DELAY_MAX, ANIMATION_DELAY_DEFAULT);

    gtfPosition = new GTextField(7);
    gtfPosition->setText(gtfPositionText);
    gtfPosition->setEditable(false);

    // Add in the list of existing world files.
    gcWorld = new GChooser();
    Set<std::string> worldFiles =
            getFiles("maze") +
            getFiles("terrain") +
            getFiles("map");
    for (std::string worldFile : worldFiles) {
        gcWorld->addItem(worldFile);
    }
    gcWorld->addItem(OTHER_FILE_LABEL);
    gcWorld->setSelectedItem(INITIALLY_SELECTED_FILE);

    // north layout
    gWindow->addToRegion(gcAlgorithm, "NORTH");
    gWindow->addToRegion(gcbDelay, "NORTH");
    gWindow->addToRegion(gsDelay, "NORTH");
    gbRun = new GButton("Run");
    gbRun->setIcon("play.gif");
    gWindow->addToRegion(gbRun, "NORTH");
    gbClear = new GButton("Clear");
    gbClear->setIcon("cancel.gif");
    gWindow->addToRegion(gbClear, "NORTH");

    // south layout
    glWorld = new GLabel("World:");
    gWindow->addToRegion(glWorld, "SOUTH");
    gWindow->addToRegion(gcWorld, "SOUTH");
    gbLoad = new GButton("Load");
    gbLoad->setIcon("load.gif");
    gWindow->addToRegion(gbLoad, "SOUTH");
    // gWindow->addToRegion(new GButton("Exit"), "SOUTH");
    gWindow->addToRegion(gtfPosition, "SOUTH");

    setAnimationDelay(ANIMATION_DELAY_DEFAULT);
    gsDelay->setValue(animationDelay);
    if (SHOULD_SAVE_GUI_STATE) {
        stateLoad();
    }
    
    pause(100);
    gWindow->pack();   // correct the window size
    
    loadCurrentlySelectedWorld();
}

PathfinderGUI::~PathfinderGUI() {
    if (gWindow) {
        delete gcAlgorithm;
        delete gcWorld;
        delete gsDelay;
        delete gtfPosition;
        delete glDelay;
        delete glWorld;
        delete gbClear;
        delete gbLoad;
        delete gbRun;
        delete gWindow;
    }
    if (world) {
        delete world;
    }
}

GWindow* PathfinderGUI::getGWindow() const {
    return gWindow;
}

void PathfinderGUI::loadCurrentlySelectedWorld() {
    std::string worldFile = gcWorld->getSelectedItem();
    std::cout << std::endl;
    if (worldFile == OTHER_FILE_LABEL) {
        // prompt for file name
        worldFile = GFileChooser::showOpenDialog(getCurrentDirectory());
    }

    loadWorld(worldFile);
}

void PathfinderGUI::processActionEvent(GActionEvent e) {
    if (pathSearchInProgress) {
        return;
    }
    std::string cmd = e.getActionCommand();
    if (cmd == "Load") {
        // load a world and update the UI
        loadCurrentlySelectedWorld();
    } else if (cmd == "Delay") {
        // turn animation delay on/off
        if (gcbDelay->isChecked()) {
            setAnimationDelay(gsDelay->getValue());
        } else {
            setAnimationDelay(0);
        }
    } else if (cmd == "Run") {
        // rerunning the search is only possible if we already did a search
        if (world) {
            if (ensureStartEndVerticesSelected()) {
                if (gcAlgorithm->getSelectedItem() != "Alternate Path") {
                    world->clearPath();
                }
                runPathSearch();
            } else {
                std::cout << "You must select a start and end vertex first." << std::endl;
            }
        } else {
            std::cout << "You must load a graph from a file first." << std::endl;
        }
    } else if (cmd == "Clear") {
        // clearing the display just sets us back to the fresh state
        if (world) {
            world->clearSelection(/* redraw */ false);
            world->clearPath(/* redraw */ true);
        }
    } else if (cmd == "Exit") {
        shutdown();
    }
}

void PathfinderGUI::processMouseEvent(GMouseEvent e) {
    if (!world) {
        return;
    }
    if (e.getEventType() == MOUSE_CLICKED) {
        world->handleClick(e.getX(), e.getY());
    } else if (e.getEventType() == MOUSE_MOVED) {
        // update display of current mouse row/col position to aid testing
        world->handleMove(e.getX(), e.getY());
        std::string desc = world->getDescription(e.getX(), e.getY());
        if (desc != gtfPositionText) {
            gtfPositionText = desc;
            gtfPosition->setText(desc);
        }
    }
}

void PathfinderGUI::processWindowEvent(GWindowEvent e) {
    if (e.getEventType() == WINDOW_CLOSED
            || e.getEventType() == CONSOLE_CLOSED) {
        shutdown();
    }
}

Set<std::string> PathfinderGUI::getFiles(std::string substr) {
    substr = toLowerCase(substr);
    Vector<std::string> files;
    listDirectory(".", files);
    Set<std::string> result;
    for (std::string file : files) {
        std::string fileLC = toLowerCase(file);
        if (startsWith(fileLC, substr) && endsWith(fileLC, ".txt")) {
            result.add(file);
        }
    }
    return result;
}

WorldSize PathfinderGUI::getWorldSize(std::string worldText) {
    std::string worldLC = toLowerCase(worldText);
    if (worldLC.find("tiny") != std::string::npos) {
        return TINY_WORLD;
    } else if (worldLC.find("small") != std::string::npos) {
        return SMALL_WORLD;
    } else if (worldLC.find("medium") != std::string::npos) {
        return MEDIUM_WORLD;
    } else if (worldLC.find("large") != std::string::npos) {
        return LARGE_WORLD;
    } else if (worldLC.find("huge") != std::string::npos) {
        return HUGE_WORLD;
    } else {
        error("Invalid world size provided.");
        return SMALL_WORLD;
    }
}

bool PathfinderGUI::ensureStartEndVerticesSelected() {
    Vertex* start = world->getSelectedStart();
    Vertex* end = world->getSelectedEnd();
    return (start && end);
}

bool PathfinderGUI::loadWorld(std::string worldFile) {
    if (worldFile.empty() || !fileExists(worldFile)) {
        std::cout << "File not found; aborting." << std::endl;
        return false;
    }

    if (world) {
        delete world;
        world = nullptr;
        setCurrentWorld(nullptr);
        gWindow->repaint();
    }
    
    std::cout << "Loading world from " << getTail(worldFile) << " ..." << std::endl;
    gbLoad->setIcon("progress.gif");
    if (stringContains(worldFile, "maze")) {
        WorldSize size = getWorldSize(worldFile);
        world = new WorldMaze(gWindow, size);
    } else if (stringContains(worldFile, "terrain")) {
        WorldSize size = getWorldSize(worldFile);
        world = new WorldTerrain(gWindow, size);
    } else if (stringContains(worldFile, "map")) {
        // WorldSize not needed for maps
        world = new WorldMap(gWindow);
    }
    setCurrentWorld(world);
    
    Timer tim;
    if (SHOW_RUNTIMES) {
        tim.start();
    }
    
    bool result = true;
    bool readSuccessful = world->read(worldFile);
    if (readSuccessful) {
        if (SHOW_RUNTIMES) {
            tim.stop();
            std::cout << "Finished loading file in " << tim.elapsed() << " ms." << std::endl;
            std::cout << "Drawing graphical display of world ..." << std::endl;
            tim.start();
        } else {
            std::cout << "Preparing world model ..." << std::endl;
        }
        snapConsoleLocation();
        
        gWindow->clearCanvas();
        world->addObserver(this);
        //        world->clearSelection(/* redraw */ false);
        //        world->clearPath(/* redraw */ true);
        world->draw();
        if (SHOW_RUNTIMES) {
            tim.stop();
            std::cout << "Finished drawing in " << tim.elapsed() << " ms." << std::endl;
        }
        // std::cout << "Finished loading file and drawing world." << std::endl;
        std::cout << "World model completed." << std::endl;
        result = true;
    } else {
        std::cerr << worldFile << " is not a valid world file." << std::endl;
        result = false;
    }
    
    gbLoad->setIcon("load.gif");
    return result;
}

double PathfinderGUI::pathComputeCost(Vector<Vertex*>& path) {
    BasicGraph* graph = world->getGraph();
    double result = 0.0;
    for (int i = 1; i < path.size(); i++) {
        Edge* edge = graph->getEdge(path[i - 1], path[i]);
        result += edge->cost;
    }
    return result;
}

void PathfinderGUI::pathDisplayInfo(Vector<Vertex*>& path) {
    std::cout << "Path length: " << path.size() << std::endl;
    std::cout << "Path cost: " << pathComputeCost(path) << std::endl;
    int greenGray = 0;
    int yellow = 0;
    for (Vertex* v : *(world->getGraph())) {
        Color color = v->getColor();
        if (color == GREEN || color == GRAY) {
            greenGray++;
        } else if (color == YELLOW) {
            yellow++;
        }
    }
    std::cout << "Locations visited: " << greenGray << std::endl;
}

Vector<Vertex*> PathfinderGUI::runPathSearch() {
    updateAnimationDelayFromSlider();

    Vector<Vertex*> path;
    Vertex* start = world->getSelectedStart();
    Vertex* end = world->getSelectedEnd();
    if (!start || !end) {
        return path;
    }
    
    pathSearchInProgress = true;
    std::string algorithmLabel = gcAlgorithm->getSelectedItem();
    
    std::cout << std::endl;
    std::cout << "Looking for a path from " << start->name
              << " to " << end->name << "." << std::endl;

    world->getGraph()->resetData();

    if (algorithmLabel == "DFS") {
        std::cout << "Executing depth-first search algorithm ..." << std::endl;
        path = depthFirstSearch(*world->getGraph(), start, end);
    } else if (algorithmLabel == "BFS") {
        std::cout << "Executing breadth-first search algorithm ..." << std::endl;
        path = breadthFirstSearch(*world->getGraph(), start, end);
    } else if (algorithmLabel == "Dijkstra") {
        std::cout << "Executing Dijkstra's algorithm ..." << std::endl;
        path = dijkstrasAlgorithm(*world->getGraph(), start, end);
    } else if (algorithmLabel == "Alternate Path") {
        std::cout << "Executing alternate path algorithm ..." << std::endl;
        path = alternatePath(*world->getGraph(), start, end);
    } else if (algorithmLabel == "A*") {
        std::cout << "Executing A* algorithm ..." << std::endl;
        path = aStar(*world->getGraph(), start, end);
#ifdef BIDIRECTIONAL_SEARCH_ALGORITHM_ENABLED
    } else if (algorithmLabel == "Bidirectional") {
        std::cout << "Executing Bidirectional Search algorithm ..." << std::endl;
        path = bidirectionalSearch(*world->getGraph(), start, end);
#endif
    }
    std::cout << "Algorithm complete." << std::endl;
    
    bool shouldDraw = true;
    if (path.isEmpty()) {
        std::cout << "No path was found. (The returned path is empty.)" << std::endl;
        shouldDraw = false;
    } else {
        shouldDraw = verifyPath(*world->getGraph(), path, start, end);
    }
    
    if (shouldDraw) {
        world->drawPath(path, /* alt path color */ algorithmLabel == "Alternate Path");
    }
    
    pathSearchInProgress = false;
    
    pathDisplayInfo(path);
    if (animationDelay == 0) {
        // GUI will not have repainted itself to show the path being drawn;
        // manually repaint it
        gWindow->repaint();
    }
    
    return path;
}

void PathfinderGUI::setAnimationDelay(int delayMS) {
    int oldDelay = animationDelay;
    animationDelay = delayMS;

    // tell the window whether or not to repaint on every square colored
    if ((animationDelay == 0) != (oldDelay == 0)) {
        if (gWindow) {
            gWindow->setRepaintImmediately(animationDelay != 0);
        }
    }
}

void PathfinderGUI::snapConsoleLocation() {
    gtfPositionText = " ";
    gtfPosition->setText(gtfPositionText);
    GDimension size = world->getPreferredSize();
    gWindow->setCanvasSize(size.getWidth(), size.getHeight());
    // gWindow->pack();

    Point guiLoc = gWindow->getLocation();
    GDimension guiSize = gWindow->getSize();
    setConsoleLocation(
                guiLoc.getX() + guiSize.getWidth() + WorldAbstract::WINDOW_MARGIN,
                guiLoc.getY());
}

void PathfinderGUI::shutdown() {
    std::cout << std::endl;
    std::cout << "Exiting." << std::endl;
    if (SHOULD_SAVE_GUI_STATE) {
        stateSave();
    }
    exitGraphics();
}

bool PathfinderGUI::stateLoad() {
    std::ifstream input;
    input.open(GUI_STATE_FILE.c_str());
    if (input.fail()) {
        return false;
    }
    std::string algorithm;
    getline(input, algorithm);
    if (input.fail()) {
        return false;
    }

    std::string line;
    getline(input, line);
    if (input.fail()) {
        return false;
    }
    setAnimationDelay(stringToInteger(line));

    std::string worldFile;
    getline(input, worldFile);
    if (input.fail()) {
        return false;
    }
    input.close();

    // delete the save state file in case there is a crash loading a world
    deleteFile(GUI_STATE_FILE);

    gcAlgorithm->setSelectedItem(algorithm);
    gsDelay->setValue(animationDelay);
    if (worldFile != OTHER_FILE_LABEL) {
        gcWorld->setSelectedItem(worldFile);
    }
    
    return true;
}

bool PathfinderGUI::stateSave() {
    std::string algorithm = gcAlgorithm->getSelectedItem();
    int delay = gsDelay->getValue();
    std::string worldFile = gcWorld->getSelectedItem();
    std::ofstream output;
    output.open(GUI_STATE_FILE.c_str());
    if (output.fail()) {
        return false;
    }
    output << algorithm << std::endl;
    output << delay << std::endl;
    output << worldFile << std::endl;
    if (output.fail()) {
        return false;
    }
    output.flush();
    output.close();
    return true;
}

void PathfinderGUI::update(Observable<WorldEvent>* /*obs*/, const WorldEvent& arg) {
    if (arg == EVENT_VERTEX_COLORED) {
        if (animationDelay > 0) {
            updateAnimationDelayFromSlider();
            pause(animationDelay);
        }
    } else if (arg == EVENT_PATH_SELECTION_READY) {
        if (ensureStartEndVerticesSelected()) {
            runPathSearch();
        }
    }
}

void PathfinderGUI::updateAnimationDelayFromSlider() {
    // don't set delay from slider if user doesn't want delay
    if (!gcbDelay->isChecked()) {
        setAnimationDelay(0);
        return;
    }
    int delay = gsDelay->getValue();
    double percent = 100.0 * delay / ANIMATION_DELAY_MAX;
    
    // convert scale so delays don't increase so rapidly
    if (percent <= 0.0) {
        delay = 1;
    } else if (percent <= 10) {
        delay = ANIMATION_DELAY_MAX / 1000;
    } else if (percent <= 20) {
        delay = ANIMATION_DELAY_MAX / 500;
    } else if (percent <= 30) {
        delay = ANIMATION_DELAY_MAX / 200;
    } else if (percent <= 40) {
        delay = ANIMATION_DELAY_MAX / 100;
    } else if (percent <= 50) {
        delay = ANIMATION_DELAY_MAX / 50;
    } else if (percent <= 60) {
        delay = ANIMATION_DELAY_MAX / 25;
    } else if (percent <= 70) {
        delay = ANIMATION_DELAY_MAX / 10;
    } else if (percent <= 80) {
        delay = ANIMATION_DELAY_MAX / 5;
    } else if (percent <= 90) {
        delay = ANIMATION_DELAY_MAX / 2;
    } else {  // percent > 90
        delay = ANIMATION_DELAY_MAX;
    }

    setAnimationDelay(delay);
}
