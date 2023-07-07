/**
 * File: mazegui.h
 * ---------------
 * Provides the declarations of the graphics routines needed to help animate
 * the construction of a maze.
 * See mazegui.cpp for the bodies of each static member function.
 *
 * @author Marty Stepp, based on previous maze-graphics.cpp by Jerry Cain
 * @version 2016/10/07
 * - 16au 106X initial version
 */

#ifndef _mazegui_h
#define _mazegui_h

#include <string>
#include "ginteractors.h"
#include "gwindow.h"
#include "hashset.h"
#include "linkedhashset.h"
#include "linkedlist.h"
#include "set.h"
#include "vector.h"
#include "mazetypes.h"

class MazeGUI {
public:
    /** Default starting number of rows and columns. */
    static const int MAZE_DEFAULT_ROWS_COLS = 10;

    /** Maximum number of rows and columns. */
    static const int MAZE_MAX_ROWS_COLS = 50;

    /** Minimum number of rows and columns. */
    static const int MAZE_MIN_ROWS_COLS = 2;

    /**
     * Returns all cells of the maze as a vector.
     */
    static const Vector<Cell>& getAllCells();

    /**
     * Returns all walls of the maze as a vector.
     */
    static const Vector<Wall>& getAllWalls();

    /**
     * Sets up the GUI and makes the window appear on screen.
     * Should be called once at program startup.
     */
    static void initialize();

    /**
     * Returns true if the Animation checkbox is checked.
     */
    static bool isAnimated();

    /**
     * Removes the given wall from the GUI, if present.
     */
    static void removeWall(const Wall& wall);

    /**
     * Instructs the GUI to redraw itself.
     * Clients generally do not need to ever call this.
     */
    static void repaint();

    /**
     * Tells the GUI to display the number of rows and columns as typed into
     * the text box at the top of the window.
     */
    static void resize();

    /**
     * Tells the GUI to display the given number of rows and columns.
     */
    static void resize(int numRowsCols);

    /**
     * Turns on/off animation delay when removing walls.
     */
    static void setAnimated(bool animated = true);

    /**
     * Turns the GUI on/off.
     * Generally clients should not need to call this method, but we have
     * included it to facilitate grading scripts and other private features.
     */
    static void setEnabled(bool enabled = true);

    /**
     * Shuts down the GUI and closes the window.
     * Clients generally do not need to call this.
     */
    static void shutdown();

    /**
     * Tells the GUI to begin generating a new maze.
     */
    static void startMazeGeneration();

private:
    /*
     * Private constructor prevents client construction.
     * This class is meant to be accessed via static methods.
     */
    MazeGUI();

    /* Creates Cell objects for all rows and columns in the maze. */
    static void buildAllCells(int numRowsCols);

    /* Creates Wall objects between all rows and columns in the maze. */
    static void buildAllWalls(int numRowsCols);

    /* Draws a border around the confines of the maze. */
    static void drawBorder();

    /* Draws a line of the given color and thickness between the two given points. */
    static void drawColoredLine(double startx, double starty, double endx, double endy,
                                double lineWidth, const std::string& color);

    /* Draws the given wall on the maze. */
    static void drawWall(const Wall& wall);

    /* Draws the given wall on the maze in the given color and the given amount of spacing. */
    static void drawWall(const Wall& w, const std::string& color, double inset);

    /* Draws all walls in the given vector. */
    static void drawWalls(const Vector<Wall>& walls);

    /* Returns the maze's size in pixels. */
    static double getMazeSize();

    /* Displays a status label in the bottom of the GUI window. */
    static void setStatus(const std::string& text);

    /**
     * Global constants that help provide more
     * meaningful names for what will otherwise be
     * magic values.
     */
    static const int ANIMATION_DELAY_MS = 100;

    static const int WINDOW_WIDTH  = 700;   // w/h of window in pixels
    static const int WINDOW_HEIGHT = 500;
    static const int WALL_WIDTH = 2;        // 2px thick wall lines
    static const std::string WINDOW_TITLE;  // window title text
    static const std::string WALL_COLOR;    // color of walls in maze
    static const std::string BLANK_COLOR;   // color of blank area behind walls

    /* private internal data; clients should not use/modify these */
    static GButton* resizeButton;
    static GButton* generateButton;
    static GCheckBox* animation;
    static GLabel* statusLabel;
    static GTextField* rowsColsField;
    static GWindow* window;
    static Vector<Cell> allCells;
    static Vector<Wall> allWalls;
    static double wallLength;
    static double ulx;
    static double uly;
    static int wallsRemoved;
}; // class MazeGUI

#endif // _mazegui_h
