/*
 * CS 106B/X, Marty Stepp, Julie Zelenski
 * This file implements the GUI for the 8 Queens.
 */

#include "gui.h"
#include "console.h"
#include "gwindow.h"
#include "gobjects.h"
#include "gslider.h"
#include "glabel.h"
#include "map.h"


namespace GUI {

static const int kWindowSize = 600, kMargin = 30;
static GWindow* gWindow = nullptr;
static GSlider *gSpeedSlider = nullptr;
static GLabel *gLabel = nullptr;
static GPoint gUpperLeft;
static int gCellSize;
static Map<string, string> gColors {{"Q", "Black"}, {"?", "Red"}, {"⇧", "Blue"}};

static void delay();
static void drawCell(int row, int col, string s = "", bool outside = false);

void initialize(int dimension)
{
    if (!gWindow) {
        gWindow = new GWindow(kWindowSize, kWindowSize);
        gWindow->setLocation(0, 0);
        gWindow->setTitle("CS 106B/X Queens Demo");
        gWindow->setResizable(false);
        GObject::setAntiAliasing(false);
        gWindow->setRepaintImmediately(false);
        setConsoleLocation(0, kWindowSize + 75);
        setConsoleSize(kWindowSize, 150);
        gSpeedSlider = new GSlider(1, 10, 1);
        double w = gWindow->getCanvasWidth();
        gSpeedSlider->setBounds(w/4, 0, w/2, gSpeedSlider->getHeight());
        gLabel = new GLabel("Click on board to step");
        gWindow->addToRegion(gLabel, "SOUTH");
        gWindow->addToRegion(gSpeedSlider, "SOUTH");
    }
    gCellSize = min((gWindow->getWidth() - kMargin)/(dimension+1), (gWindow->getHeight()- kMargin)/dimension);
    gUpperLeft = {kMargin, kMargin};
    int pointSize = gCellSize*.70;
    gWindow->setFont("Helvetica-" + integerToString(pointSize));
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            drawCell(row, col);
        }
    }
    gWindow->repaint();
    gWindow->show();
}


static void delay()
{
    gWindow->repaint();
    // speed = 1 (wait for click) 2 slowest - 10 fastest
    int speed = gSpeedSlider->getValue();
    if (speed == 1) {
        gLabel->setText("Click on board to step");
        waitForClick();
    } else {
        gLabel->setText("                                     ");
        if (speed != 10) {
            pause(1000/speed);
        }
    }
}

static void drawCell(int row, int col, string label, bool outside)
{
    double x = gUpperLeft.getX() + col*gCellSize + outside;
    double y = gUpperLeft.getY() + row*gCellSize;
    int alternating[] = {0xffffff, 0xcccccc};
    int fill = outside ? alternating[0] : alternating[(row + col) % 2];
    int border = outside ? alternating[0] : alternating[1];
    gWindow->setColor(border);
    gWindow->setFillColor(fill);
    gWindow->fillRect(x, y, gCellSize , gCellSize);
    if (!label.empty()) {
        gWindow->setColor(gColors.containsKey(label) ? gColors[label] : "Black");
        double delta = gCellSize/5;
        gWindow->drawString(label, x + delta, y + delta*4);
    }
}

void backtrack(int row, int col)
{
    drawCell(row, col + 1, "⇧", true); // admittedly cheezy use of col + 1
    delay();
    drawCell(row, col + 1, "", true);
    gWindow->repaint();
}

void consider(int row, int col)
{
   drawCell(row, col, "?");
   delay();
   drawCell(row, col, "");
}

void occupy(int row, int col)
{
    drawCell(row, col, "Q");
    delay();
}

void leave(int row, int col)
{
    drawCell(row, col, "");
    gWindow->repaint();
}

void showSolution(Grid<bool> & board)
{
    string what[] = {"", "Q", "", "Q","", "🏆", "Q"}; // blink board
    int last = sizeof(what)/sizeof(*what) - 1;
    for (int i = 0; i <= last; i++) {
        for (int r = 0; r < board.numRows(); r++) {
            for (int c = 0; c < board.numCols(); c++) {
                string label = board[r][c] ? what[i] : "";
                drawCell(r, c, label);
            }
        }
        gWindow->repaint();
        if (i == last-1) {
            waitForClick();
        } else {
            pause(200);
        }
    }
}

} // end namespace
