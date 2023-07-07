/**
 * File: mazegui.cpp
 * -----------------
 * Provides the implementation of the graphics routines needed to help animate
 * the construction of a maze.
 * This file also contains the 'main' function to run the project.
 *
 * @author Marty Stepp, based on previous maze-graphics.cpp by Jerry Cain
 * @version 2016/10/12
 * - made GUI window resizable as workaround for some sizing issues on Mac
 * @version 2016/10/07
 * - 16au 106X initial version
 */

#include "mazegui.h"
#include <iostream>
#include <string>
#include "gevents.h"
#include "gobjects.h"
#include "strlib.h"
#include "timer.h"

// define static constants and variables
const std::string MazeGUI::WINDOW_TITLE = "CS 106X Maze Generator";
const std::string MazeGUI::WALL_COLOR = "Blue";
const std::string MazeGUI::BLANK_COLOR = "white";
GButton* MazeGUI::resizeButton = nullptr;
GButton* MazeGUI::generateButton = nullptr;
GCheckBox* MazeGUI::animation = nullptr;
GLabel* MazeGUI::statusLabel = nullptr;
GTextField* MazeGUI::rowsColsField = nullptr;
GWindow* MazeGUI::window = nullptr;
Vector<Cell> MazeGUI::allCells;
Vector<Wall> MazeGUI::allWalls;
double MazeGUI::ulx = 0;
double MazeGUI::uly = 0;
double MazeGUI::wallLength = 0;
int MazeGUI::wallsRemoved = 0;

// forward declaration of student's code
extern void generateMaze();

// define static member functions
void MazeGUI::buildAllCells(int numRowsCols) {
    allCells.clear();
    for (int row = 0; row < numRowsCols; row++) {
        for (int col = 0; col < numRowsCols; col++) {
            Cell cell { row, col };
            allCells.add(cell);
        }
    }
}

void MazeGUI::buildAllWalls(int numRowsCols) {
    allWalls.clear();
    for (int row = 0; row < numRowsCols; row++) {
        for (int col = 0; col < numRowsCols - 1; col++) {
            Cell base = { row, col };
            Cell eastNeighbor = { row, col + 1 };
            Wall eastWall = { base, eastNeighbor };
            allWalls.add(eastWall);
        }
    }

    for (int col = 0; col < numRowsCols; col++) {
        for (int row = 0; row < numRowsCols - 1; row++) {
            Cell base = { row, col };
            Cell northNeighbor = { row + 1, col };
            Wall northWall = { base, northNeighbor };
            allWalls.add(northWall);
        }
    }
    shuffle(allWalls);
}

void MazeGUI::drawBorder() {
    double mazeSize = getMazeSize();
    drawColoredLine(ulx, uly, ulx, uly + mazeSize, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx, uly + mazeSize, ulx + mazeSize - wallLength, uly + mazeSize, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + mazeSize - wallLength, uly + mazeSize, ulx + mazeSize, uly + mazeSize, WALL_WIDTH, BLANK_COLOR);
    drawColoredLine(ulx + mazeSize, uly + mazeSize, ulx + mazeSize, uly, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + mazeSize, uly, ulx + wallLength, uly, WALL_WIDTH, WALL_COLOR);
    drawColoredLine(ulx + wallLength, uly, ulx, uly, WALL_WIDTH, BLANK_COLOR);
}

void MazeGUI::drawColoredLine(double startx, double starty, double endx, double endy,
                              double lineWidth, const std::string& color) {
    GLine line(startx, starty, endx, endy);
    line.setLineWidth(lineWidth);
    line.setColor(color);
    window->draw(line);
}

void MazeGUI::drawWall(const Wall& wall) {
    drawWall(wall, WALL_COLOR, 0);
}

void MazeGUI::drawWall(const Wall& w, const std::string& color, double inset) {
    double startx = ulx + w.one.col * MazeGUI::wallLength;
    double starty = uly + w.one.row * MazeGUI::wallLength;

    double wallLength = MazeGUI::wallLength;
    double lineWidth = WALL_WIDTH;
    if (color == BLANK_COLOR) {
        wallLength -= 2 * inset;
        lineWidth += 2;
    }

    if (w.one.row == w.two.row) {
        startx += MazeGUI::wallLength;
        starty += inset;
        drawColoredLine(startx, starty, startx, starty + wallLength, lineWidth, color);
    } else {
        starty += MazeGUI::wallLength;
        startx += inset;
        drawColoredLine(startx, starty, startx + wallLength, starty, lineWidth, color);
    }
}

void MazeGUI::drawWalls(const Vector<Wall>& walls) {
    initialize();
    for (const Wall& wall : walls) {
        drawWall(wall);
    }
    repaint();
}

const Vector<Cell>& MazeGUI::getAllCells() {
    return allCells;
}

const Vector<Wall>& MazeGUI::getAllWalls() {
    return allWalls;
}

double MazeGUI::getMazeSize() {
    initialize();
    double w = window->getCanvasWidth() - 20;
    double h = window->getCanvasHeight() - 20;
    return w < h ? w : h;
}

void MazeGUI::initialize() {
    // ensure that this code runs only once
    static bool _initialized = false;
    if (_initialized) {
        return;
    }
    _initialized = true;

    // initialize window and graphical interactors
    window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT, /* visible */ false);
    window->setTitle(WINDOW_TITLE);
    window->setResizable(true);
    window->setRepaintImmediately(false);
    window->setExitOnClose(true);

    rowsColsField = new GTextField(4);
    rowsColsField->setText(integerToString(MAZE_DEFAULT_ROWS_COLS));

    statusLabel = new GLabel("??????");

    animation = new GCheckBox("Animation?");
    animation->setSelected(true);
    resizeButton = new GButton("Resize");
    generateButton = new GButton("Generate");

    window->addToRegion(rowsColsField, "North");
    window->addToRegion(resizeButton, "North");
    window->addToRegion(generateButton, "North");
    window->addToRegion(animation, "North");
    window->addToRegion(statusLabel, "South");

    window->setVisible(true);
    window->center();
}

bool MazeGUI::isAnimated() {
    initialize();
    return animation->isSelected();
}

void MazeGUI::removeWall(const Wall& wall) {
    initialize();
    wallsRemoved++;
    drawWall(wall, BLANK_COLOR, wallLength / 5);
    if (isAnimated()) {
        setStatus("Removing wall between " + wall.one.toString() + " and "
                  + wall.two.toString() + ".");
        pause(ANIMATION_DELAY_MS);
        window->repaint();
    }
}

void MazeGUI::repaint() {
    initialize();
    window->repaint();
}

void MazeGUI::resize() {
    initialize();
    std::string rowsColsText = rowsColsField->getText();
    if (!stringIsInteger(rowsColsText)) {
        return;
    }
    int numRowsCols = stringToInteger(rowsColsText);
    if (numRowsCols >= MAZE_MIN_ROWS_COLS && numRowsCols <= MAZE_MAX_ROWS_COLS) {
        resize(numRowsCols);
    }
}

void MazeGUI::resize(int numRowsCols) {
    if (!(numRowsCols >= MAZE_MIN_ROWS_COLS && numRowsCols <= MAZE_MAX_ROWS_COLS)) {
        error("Value passed to MazeGUI::resize is out of range.");
    }

    initialize();
    resizeButton->setEnabled(false);
    generateButton->setEnabled(false);
    wallsRemoved = 0;
    setStatus("Resizing maze to size " + integerToString(numRowsCols) + " x "
              + integerToString(numRowsCols) + ".");
    window->clearCanvas();
    wallLength = getMazeSize() / numRowsCols;
    ulx = (window->getCanvasWidth() - getMazeSize()) / 2;
    uly = (window->getCanvasHeight() - getMazeSize()) / 2;

    buildAllCells(numRowsCols);
    buildAllWalls(numRowsCols);

    drawBorder();
    drawWalls(allWalls);
    resizeButton->setEnabled(true);
    generateButton->setEnabled(true);
}

void MazeGUI::setAnimated(bool animated) {
    initialize();
    animation->setSelected(animated);
}

void MazeGUI::setEnabled(bool /*enabled*/) {
    // TODO
}

void MazeGUI::setStatus(const std::string& text) {
    initialize();
    statusLabel->setText(text);
}

void MazeGUI::shutdown() {
    if (window) {
        window->setVisible(false);
        window->close();
        delete window;
        delete rowsColsField;
        delete statusLabel;
        delete animation;
        delete resizeButton;
        delete generateButton;
        window = nullptr;
        rowsColsField = nullptr;
        statusLabel = nullptr;
        animation = nullptr;
        resizeButton = nullptr;
        generateButton = nullptr;
    }
}

void MazeGUI::startMazeGeneration() {
    initialize();
    wallsRemoved = 0;
    resizeButton->setEnabled(false);
    generateButton->setEnabled(false);
    setStatus("Generating maze ...");
    Timer timer;
    timer.start();
    generateMaze();
    timer.stop();
    setStatus("Generation complete. Removed "
              + integerToString(wallsRemoved)
              + " of " + integerToString(allWalls.size())
              + " walls. (took "
              + longToString(timer.elapsed()) + " ms)");
    repaint();
    resizeButton->setEnabled(true);
}

int main() {
    MazeGUI::initialize();
    MazeGUI::resize(MazeGUI::MAZE_DEFAULT_ROWS_COLS);
    pause(200);
    MazeGUI::resize(MazeGUI::MAZE_DEFAULT_ROWS_COLS);

    // event loop
    while (true) {
        GEvent event = waitForEvent(ACTION_EVENT | WINDOW_EVENT);
        if (event.getEventClass() == ACTION_EVENT) {
            GActionEvent actionEvent(event);
            std::string cmd = actionEvent.getActionCommand();
            if (cmd == "Resize") {
                MazeGUI::resize();
            } else if (cmd == "Generate") {
                MazeGUI::startMazeGeneration();
            }
        } else if (event.getEventClass() == WINDOW_EVENT) {
            if (event.getEventType() == WINDOW_CLOSED) {
                break;
            }
        }
    }

    return 0;
}
