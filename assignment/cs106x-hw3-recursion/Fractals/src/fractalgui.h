/*
 * CS 106B/X Fractal Recursion Problems
 * This instructor-provided file declares a class representing the overall
 * graphical user interface (GUI) for this part of the program.
 * See fractalgui.cpp for the implementation of each member.
 *
 * You don't need to modify this file.
 * Your recursive functions should work with an unmodified version of this file.
 *
 * @author Marty Stepp
 * @version 2017/10/14
 * - modified Complex parse logic to use default on failure
 *   (addresses unusual parsing failures on some systems)
 * @version 2017/10/12
 * - initial 17au version;
 *   modified with additional fractals (Mandelbrot Set) based on cgregg 17wi/sp version
 * - added spinner to show while graphics are drawing
 * @version 2016/10/16
 * - modified for 16au with additional fractals (tree)
 * @version 2015/04/24
 * - modified for 15sp version, including exception-handling
 * @version 2014/10/13
 * - modified for 14au version, including new version of floodFill
 */

#ifndef _fractalgui_h
#define _fractalgui_h

#include <string>
#include "complex.h"
#include "gevents.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gwindow.h"
#include "map.h"

class FractalGUI {
public:
    /*
     * Removes all shapes from the screen.
     */
    void clear();

    /*
     * The GUI's main loop that waits for events and handles them.
     */
    void eventLoop();

    /*
     * Creates and configures all graphical controls in the GUI.
     */
    void initialize();

private:
    /*
     * Initiates a plasma fractal operation on the window.
     */
    void doPlasma();

    /*
     * Initiates a Mandelbrot Set operation on the window.
     */
    void doMandelbrot();

    /*
     * Initiates a draw Sierpinski triangle operation on the window.
     */
    void doSierpinski();

    /*
     * Initiates a recursive tree operation on the window.
     */
    void doTree();

    /*
     * Returns a map of available colors for flood fill.
     */
    const Map<std::string, int>& getColorMap();

    /*
     * Processes one action event (button click) in the GUI window.
     */
    void handleActionEvent(GActionEvent& actionEvent);

    /*
     * Processes one mouse event in the GUI window.
     */
    void handleMouseEvent(GMouseEvent& mouseEvent);

    /*
     * Returns true if all text fields have valid integer coordinates entered into them.
     */
    bool hasAllCoords();

    /*
     * Tries to read a complex number range for Mandelbrot Set
     * and store it in the given two Complex number objects.
     * Returns true if the GUI should proceed with drawing the set.
     */
    bool readComplexRange(Complex& min, Complex& max);

    /*
     * Sets the bottom status bar text to display in the southern area.
     * If isError is true, shows it in a red error color.
     */
    void setStatusText(const std::string& text, bool isError = false);

    // constants
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 650;
    static const int DRAG_RECT_COLOR = 0xaa8822;

    // overall window
    GWindow* window;

    // west buttons to draw fractals
    GButton* sierpinskiButton;
    GButton* treeButton;
    GButton* mandelbrotButton;
    GButton* plasmaButton;
    GButton* diffButton;
    GButton* clearButton;

    // flood fill / Mandelbrot colors drop-down
    GChooser* colorChooser;

    // north text fields for figure parameters
    GTextField* xField;
    GTextField* yField;
    GTextField* sizeField;
    GTextField* orderField;
    GTextLabel* loadingLabel;

    // south status bar
    GLabel* statusBar;

    // temporary dragging rectangle for figure size
    GRect* dragRect;

    // last complex number range typed for Mandelbrot Set
    std::string lastComplexRange;
};

#endif // _fractalgui_h
