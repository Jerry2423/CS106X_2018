/*
 * CS 106B/X Fractal Recursion Problems
 * This instructor-provided file defines the members of a class representing the
 * overall graphical user interface (GUI) for this part of the program.
 * See fractalgui.h for the class and member declarations.
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

#include "fractalgui.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "io/filelib.h"
#include "graphics/gfilechooser.h"
#include "graphics/goptionpane.h"
#include "collections/grid.h"
#include "util/random.h"
#include "util/strlib.h"
#include "util/timer.h"
#include "fractals.h"

void FractalGUI::clear() {
    window->clearCanvas();
    if (dragRect) {
        delete dragRect;
        dragRect = nullptr;
    }
    window->repaint();
}

void FractalGUI::doMandelbrot() {
    if (!hasAllCoords()) {
        setStatusText("Error: You must set an x, y, size, and # iterations first.", /* isError */ true);
        return;
    }
    int x = xField->getValueAsInteger();
    int y = yField->getValueAsInteger();
    int size = sizeField->getValueAsInteger();          // TODO: size => incX/Y?
    int iterations = orderField->getValueAsInteger();   // "order" == iterations here
    std::string colorStr = colorChooser->getSelectedItem();
    int color = getColorMap()[colorStr];

    // try to read and parse complex number range
    Complex min(-2, -1);
    Complex max(1, 1);
    if (!readComplexRange(min, max)) {
        return;
    }

    std::string statusText = "Mandelbrot Set: x=" + integerToString(x)
            + " y=" + integerToString(y)
            + " size=" + integerToString(size)
            + " iterations=" + integerToString(iterations)
            + " color=" + colorStr;
    setStatusText(statusText + " ...");
    loadingLabel->setVisible(true);
    window->setColor(0x0);   // black

    Timer timmy;
    timmy.start();

    drawMandelbrotSet(*window, x, y, size,
                      min, max,
                      iterations, color);

    long elapsed = timmy.stop();
    statusText += " (" + longToString(elapsed) + "ms)";
    setStatusText(statusText);
    loadingLabel->setVisible(false);
}

void FractalGUI::doSierpinski() {
    if (!hasAllCoords()) {
        setStatusText("Error: You must set an x, y, size, and order first.", /* isError */ true);
        return;
    }
    int x = xField->getValueAsInteger();
    int y = yField->getValueAsInteger();
    int size = sizeField->getValueAsInteger();
    int order = orderField->getValueAsInteger();
    std::string statusText = "Sierpinski triangle: x=" + integerToString(x)
            + " y=" + integerToString(y)
            + " size=" + integerToString(size)
            + " order=" + integerToString(order);
    setStatusText(statusText + " ...");
    loadingLabel->setVisible(true);
    window->setColor(0x0);   // black

    Timer timmy;
    timmy.start();

    drawSierpinskiTriangle(*window, x, y, size, order);

    long elapsed = timmy.stop();
    statusText += " (" + longToString(elapsed) + "ms)";
    setStatusText(statusText);
    loadingLabel->setVisible(false);
}

void FractalGUI::doTree() {
    if (!hasAllCoords()) {
        setStatusText("Error: You must set an x, y, size, and order first.", /* isError */ true);
        return;
    }
    int x = xField->getValueAsInteger();
    int y = yField->getValueAsInteger();
    int size = sizeField->getValueAsInteger();
    int order = orderField->getValueAsInteger();

    std::string statusText = "Recursive tree: x=" + integerToString(x)
            + " y=" + integerToString(y)
            + " size=" + integerToString(size)
            + " order=" + integerToString(order);
    setStatusText(statusText + " ...");
    loadingLabel->setVisible(true);
    window->setColor(0x0);   // black; drawTree should change it

    Timer timmy;
    timmy.start();

    drawTree(*window, x, y, size, order);

    long elapsed = timmy.stop();
    statusText += " (" + longToString(elapsed) + "ms)";
    setStatusText(statusText);
    loadingLabel->setVisible(false);
}

void FractalGUI::doPlasma() {
    if (!hasAllCoords()) {
        setStatusText("Error: You must set an x, y, and size first.", /* isError */ true);
        return;
    }
    int x = xField->getValueAsInteger();
    int y = yField->getValueAsInteger();
    int size = sizeField->getValueAsInteger();

    std::string statusText = "Plasma Fractal: x=" + integerToString(x)
            + " y=" + integerToString(y)
            + " size=" + integerToString(size);
    setStatusText(statusText + " ...");
    loadingLabel->setVisible(true);
    window->setColor(0x0);   // black; drawPlasmaFractal should change it

    Timer timmy;
    timmy.start();

    drawPlasma(*window, x, y, size);

    long elapsed = timmy.stop();
    statusText += " (" + longToString(elapsed) + "ms)";
    setStatusText(statusText);
    loadingLabel->setVisible(false);
}

void FractalGUI::eventLoop() {
    while (true) {
        GEvent event = waitForEvent(ACTION_EVENT | MOUSE_EVENT | WINDOW_EVENT);
        window->setRepaintImmediately(false);

        if (event.getEventClass() == ACTION_EVENT) {
            GActionEvent actionEvent(event);
            handleActionEvent(actionEvent);
        } else if (event.getEventClass() == MOUSE_EVENT) {
            GMouseEvent mouseEvent(event);
            handleMouseEvent(mouseEvent);
        } else if (event.getEventClass() == WINDOW_EVENT) {
            if (event.getEventType() == WINDOW_CLOSED) {
                break;
            }
        }

        window->repaint();
    }
}

const Map<std::string, int>& FractalGUI::getColorMap() {
    static Map<std::string, int> colorMap;
    if (colorMap.isEmpty()) {
        colorMap["Red"]    = 0x8c1515;   // Stanford red
        colorMap["Yellow"] = 0xeeee00;   // yellow
        colorMap["Blue"]   = 0x0000cc;   // blue
        colorMap["Green"]  = 0x00cc00;   // green
        colorMap["Purple"] = 0xcc00cc;   // purple
        colorMap["Orange"] = 0xff8800;   // orange
    }
    return colorMap;
}


void FractalGUI::handleActionEvent(GActionEvent& actionEvent) {
    if (actionEvent.getSource() == sierpinskiButton) {
        doSierpinski();
    } else if (actionEvent.getSource() == treeButton) {
        doTree();
    } else if (actionEvent.getSource() == mandelbrotButton) {
        doMandelbrot();
    } else if (actionEvent.getSource() == plasmaButton) {
        doPlasma();
    } else if (actionEvent.getSource() == diffButton) {
        // save current window to an image
        std::string filename = GFileChooser::showSaveDialog();
        if (!filename.empty()) {
            if (!fileExists(filename)
                    || GOptionPane::showConfirmDialog("File " + getTail(filename) + " exists. Overwrite?") == GOptionPane::YES) {
                window->saveCanvasPixels(filename);
                setStatusText("Graphical output saved to " + getTail(filename) + ".");
            }
        }
    } else if (actionEvent.getSource() == clearButton) {
        clear();
        setStatusText("Graphics cleared.");
    }
}

/*
 * This is probably not decomposed as much as it should be; each kind of mouse
 * event should be in its own function.  Oh well.
 */
void FractalGUI::handleMouseEvent(GMouseEvent& mouseEvent) {
    int mx = (int) mouseEvent.getX();
    int my = (int) mouseEvent.getY();
    if (mouseEvent.getEventType() == MOUSE_MOVED) {
        int px = window->getPixel(mx, my);
        std::string statusText = "(x="
                + integerToString((int) mouseEvent.getX()) + ", y="
                + integerToString((int) mouseEvent.getY()) + "), color="
                + convertRGBToColor(px);
        setStatusText(statusText);
    } else if (mouseEvent.getEventType() == MOUSE_PRESSED) {
        if (!mouseEvent.isLeftClick()) {
            if (dragRect) {
                window->remove(dragRect);
                delete dragRect;
                dragRect = nullptr;
                window->repaint();
                return;
            }
        }

        xField->setValue(mx);
        yField->setValue(my);
    } else if (mouseEvent.getEventType() == MOUSE_DRAGGED) {
        int x = xField->getValueAsInteger();
        int y = yField->getValueAsInteger();
        int mx = (int) mouseEvent.getX();
        int my = (int) mouseEvent.getY();
        if (mx > x && my > y) {
            int size = std::min(mx - x, my - y);
            sizeField->setValue(size);
            if (dragRect) {
                dragRect->setBounds(x, y, size, size);
            } else {
                dragRect = new GRect(x, y, size, size);
                dragRect->setColor(DRAG_RECT_COLOR);
                // dragRect->setLineWidth(2);
                window->add(dragRect);
            }
        }
    } else if (mouseEvent.getEventType() == MOUSE_RELEASED) {
        if (dragRect) {
            window->remove(dragRect);
            delete dragRect;
            dragRect = nullptr;
        }
    }
}

bool FractalGUI::hasAllCoords() {
    return stringIsInteger(xField->getText())
            && stringIsInteger(yField->getText())
            && stringIsInteger(sizeField->getText())
            && stringIsInteger(orderField->getText());
}


/*
 * Helper to create one button in the GUI.
 */
static GButton* createButton(const std::string& cmd, const std::string& icon) {
    GButton* button = new GButton();
    if (!cmd.empty()) {
        button->setText(cmd);
    }
    button->setTextPosition(SwingConstants::SWING_CENTER, SwingConstants::SWING_BOTTOM);
    button->setActionCommand(cmd);
    button->setTooltip(cmd);
    if (!icon.empty()) {
        button->setIcon(icon);
    }
    return button;
}

void FractalGUI::initialize() {
    dragRect = nullptr;
    lastComplexRange = "(-2-1i) .. (1+1i)";

    // create window
    window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT, /* visible */ false);
    window->setResizable(true);
    window->setTitle("CS 106X Fractals");
    window->setExitOnClose(true);
    // create controls
    sierpinskiButton = createButton("Sierpinski Triangle", "triangle-icon.png");
    treeButton = createButton("Recursive Tree", "tree-icon.png");
    mandelbrotButton = createButton("Mandelbrot Set", "mandelbrot-icon.png");
    plasmaButton = createButton("Plasma", "paintbrush-icon.png");
    diffButton = createButton("Save Output", "diff-icon.png");
    clearButton = createButton("Clear", "recycle-icon.png");
    colorChooser = new GChooser();
    colorChooser->setTooltip("Fill Color");
    colorChooser->addItems(getColorMap().keys());
    statusBar = new GLabel(" ");
    xField = new GTextField(4);
    xField->setPlaceholder("x");
    yField = new GTextField(4);
    yField->setPlaceholder("y");
    sizeField = new GTextField(4);
    sizeField->setPlaceholder("size");
    loadingLabel = new GTextLabel();
    loadingLabel->setIcon("progress.gif");
    loadingLabel->setEnabled(false);
    loadingLabel->setVisible(false);
    orderField = new GTextField(4);
    orderField->setValue(1);
    orderField->setPlaceholder("order");

    // perform layout
    window->addToRegion(new GLabel("x"), "North");
    window->addToRegion(xField, "North");
    window->addToRegion(new GLabel("y"), "North");
    window->addToRegion(yField, "North");
    window->addToRegion(new GLabel("size"), "North");
    window->addToRegion(sizeField, "North");
    window->addToRegion(new GLabel("order/iterations"), "North");
    window->addToRegion(orderField, "North");
    window->addToRegion(loadingLabel, "North");
    loadingLabel->setVisible(false);

    window->addToRegion(sierpinskiButton, "West");
    window->addToRegion(treeButton, "West");
    window->addToRegion(mandelbrotButton, "West");
    window->addToRegion(plasmaButton, "West");
    window->addToRegion(colorChooser, "West");
    window->addToRegion(diffButton, "West");
    window->addToRegion(clearButton, "West");

    window->addToRegion(statusBar, "South");

    window->pack();
    window->setWidth(WINDOW_WIDTH);
    window->center();
    window->setVisible(true);
}

bool FractalGUI::readComplexRange(Complex& min, Complex& max) {
    std::string complexRange = GOptionPane::showInputDialog(
                "Complex number range, in (min .. max) format?",
                /* title */ "",
                /* initial value */ lastComplexRange);
    if (complexRange.empty()) {
        return false;   // canceled
    }

    // add a bit of spacing to the complex number string;
    // this seems to help with istream parsing inconsistencies on Mac OS
    complexRange = stringReplace(complexRange, "i", " i");
    complexRange = stringReplace(complexRange, "+", " +");
    complexRange = stringReplace(complexRange, "-", " -");

    std::string throwaway;   // for ".."
    std::istringstream rangeInput(complexRange);
    if (!(rangeInput >> min >> throwaway >> max) || min.real() >= max.real() || min.imag() >= max.imag()) {
        std::string status = "Error: Invalid complex number range; using default of "
                + min.toString() + " .. " + max.toString();
        setStatusText(status, /* isError */ true);
        std::cout << status << std::endl;
        return false;
    } else {
        lastComplexRange = complexRange;
    }

    return true;
}

void FractalGUI::setStatusText(const std::string& text, bool isError) {
    statusBar->setColor(isError ? 0xbb0000 : 0x0);
    statusBar->setText(text);
}

/*
 * Main function to run the program.
 */
// int main() {
//     FractalGUI gui;
//     gui.initialize();
//     gui.eventLoop();
//     return 0;
// }
