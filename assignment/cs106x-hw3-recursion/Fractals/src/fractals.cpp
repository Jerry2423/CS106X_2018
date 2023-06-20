/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106X.
 */


#include "fractals.h"
#include <cmath>
#include "gbufferedimage.h"
#include "plasmacolor.h"
#include "complex.h"

using namespace std;
const double pi = 3.1415926;

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * bottom-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the bottom-left corner of the triangle.
 * @param y - The y coordinate of the bottom-left corner of the triangle.
 * @param sideLength - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
void drawSierpinskiTriangle(GWindow& window, double x, double y, double sideLength, int order) {
    // TODO: remove the lines below and write this function
    (void) window;
    (void) x;
    (void) y;
    (void) sideLength;
    (void) order;
    int x2 = x+sideLength, y2 = y;
    int x3 = x+sideLength/2, y3 = y-sin(pi/3) * sideLength;
    if (order < 0) {
        throw "illegal order input; input must be non-negative";
    } else if (order == 0) {
        window.drawLine(x, y, x2, y2);
        window.drawLine(x, y, x3, y3);
        window.drawLine(x2, y2, x3, y3);
    } else {
        drawSierpinskiTriangle(window, x, y, sideLength/2, order-1);
        drawSierpinskiTriangle(window, (x+x3)/2, (y+y3)/2, sideLength/2, order-1);
        drawSierpinskiTriangle(window, (x+x2)/2, (y+y2)/2, sideLength/2, order-1);
    }
}

/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */

/*
 * x, y: the trunk center of the tree
 * length: the length of the tree trunk
 */

//斜着画树
void drawTreeHelper(GWindow& window, double baseX, double baseY, double length, int index, int order, double lastAngle) {
    double k = -45+(index-1)*15;
    if (order == 1) {
        window.setColor("#2e8b57");
        window.drawPolarLine(baseX, baseY, length, k+lastAngle);
    } else {
        window.setColor("#8b7765");
        double newAngle = k+lastAngle;
        window.drawPolarLine(baseX, baseY, length, newAngle);

        for (int i = 1; i <= 7; i++) {
            double newBaseX = baseX + length*cos(newAngle*pi/180);
            double newBaseY = baseY - length*sin(newAngle*pi/180);
            drawTreeHelper(window, newBaseX, newBaseY, length/2, i, order-1, newAngle);
        }
    }
}


void drawTree(GWindow& window, double x, double y, double size, int order) {
    // TODO: remove the lines below and write this function
    (void) window;
    (void) x;
    (void) y;
    (void) size;
    (void) order;
    if (order == 1) {
        window.setColor("#2e8b57");
        window.drawPolarLine(x+size/2, y+size, size/2, 90);
    } else {
        drawTreeHelper(window, x+size/2, y+size, size/2, 4, order, 90);
    }
}


double rangeMapping(double num, double low, double high, double low1, double high1) {
    double interval = num - low;
    double mapDistance = (high1 - low1) / (high - low);
    return low1 + interval * mapDistance;
}

bool isMandelbrotHelper(const Complex c, int& times, Complex& z, const int maxTime) {
    if (z.abs() > 4) {
        return false;
    } else if (times > maxTime) {
        return true;
    } else {
        times += 1;
        z = z*z+c;
        return isMandelbrotHelper(c, times, z, maxTime);
    }
}

bool isMandelbrot(const Complex c, const int maxTime) {
    int times = 0;
    Complex z = (0, 0);
    return isMandelbrotHelper(c, times, z, maxTime);
}


//cout << isMandelbrot(c, maxTimes) << endl;

/**
 * Draws a Mandelbrot Set in the graphical window at the specified location/size,
 * with maxIterations and in a given color.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Mandelbrot set.
 * @param leftX - The x coordinate of the top-left corner of the bounding box.
 * @param topY - The y coordinate of the top-left corner of the bounding box.
 * @param min - the minimum Complex number you should examine
 * @param max - the maximum Complex number you should examine
 * @param iterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal
 */
void drawMandelbrotSet(GWindow& window, double leftX, double topY, double size,
                       const Complex& min, const Complex& max,
                       int iterations, int color) {
    GBufferedImage image(size+1, size+1, 0xffffff);
    window.add(&image, leftX, topY);
    Grid<int> pixels = image.toGrid(); // Convert image to grid
    cout << pixels.numRows() << endl;
    cout << pixels.numCols() << endl;
    //cout << isMandelbrot(Complex(0.2, 0.5), 200) << endl;
    // TODO: Remove these lines and put your Mandelbrot Set code here that
    // fills in the pixels in the grid (e.g. pixels[0][0] will display at (x, y) in the window)
    (void) window;
    (void) leftX;
    (void) topY;
    (void) size;
    (void) min;
    (void) max;
    (void) iterations;
    (void) color;


    for (int i = leftX; i <= leftX+size; i++) {
        for (int j = topY; j <= topY+size; j++) {
            double real = rangeMapping(i, leftX, leftX+size, min.real(), max.real());
            double imag = rangeMapping(j, topY, topY+size, min.imag(), max.imag());
            if (isMandelbrot(Complex(real, imag), iterations))
                pixels[j-topY][i-leftX] = color;
        }
    }



    // END (YOUR CODE)

    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}

/**
 * Generates a random displacement value you can add to a color to randomly shift it.
 *
 * You should call this function when calculating middle color values.
 *
 * @param newWidth - the width of the subdivided rectangles you are creating at that moment
 * @param newHeight - the height of the subdivided rectangles you are creating at that moment
 * @param totalWidth - the width of the entire plasma fractal (not just the part you are filling in at the moment)
 * @param totalHeight - the height of the entire plasma fractal (not just the part you are filling in at the moment)
 */
double displace(double newWidth, double newHeight, double totalWidth, double totalHeight) {
    double max = 3*(newWidth + newHeight) / (totalWidth + totalHeight);
    return (randomReal(0, 1) - 0.5) * max;
}

/**
 * Draws a Plasma Fractal in the graphical window at the specified location/size.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the fractal.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 */

//原版，创建多个图层，慢，图层太多，不过可以显示动画效果
void drawPlasmaHelper(GWindow& window, double x, double y, double size, const double totalSize, PlasmaColor c1, PlasmaColor c2, PlasmaColor c3, PlasmaColor c4) {
    if (size <= 1) {
        GBufferedImage image(1, 1, 0xffffff);
        window.add(&image, x, y);
        Grid<int> pixels = image.toGrid();
        PlasmaColor fillColor = (c1+c2+c3+c4) / 4.0;
        pixels[0][0] = fillColor.toRGBColor();
        image.fromGrid(pixels);
    } else {
        PlasmaColor middleColor = (c1+c2+c3+c4) / 4.0 + displace(size, size, totalSize, totalSize);
        drawPlasmaHelper(window, x, y, size/2, totalSize, c1, (c1+c2)/2, middleColor, (c1+c4)/2);
        drawPlasmaHelper(window, x+size/2, y, size/2, totalSize, (c1+c2)/2, c2, (c2+c3)/2, middleColor);
        drawPlasmaHelper(window, x, y+size/2, size/2, totalSize, (c1+c4)/2, middleColor, (c4+c3)/2, c4);
        drawPlasmaHelper(window, x+size/2, y+size/2, size/2, totalSize, middleColor, (c2+c3)/2, c3, (c4+c3)/2);
    }
}

//改进版，还是在原图层上改进，pixel的下标和x，y的映射是x-originX，y-originY取整即可
void drawPlasmaHelper1(GWindow& window, double x, double y, double size, const double totalSize,const double originX, const double originY,  Grid<int>& pixels, PlasmaColor c1, PlasmaColor c2, PlasmaColor c3, PlasmaColor c4) {
    if (size <= 1) {
        PlasmaColor fillColor = (c1+c2+c3+c4) / 4.0;
        pixels[int(x - originX)][int(y - originY)] = fillColor.toRGBColor();
    } else {
        PlasmaColor middleColor = (c1+c2+c3+c4) / 4.0 + displace(size, size, totalSize, totalSize);
        drawPlasmaHelper1(window, x, y, size/2, totalSize,originX, originY, pixels, c1, (c1+c2)/2, middleColor, (c1+c4)/2);
        drawPlasmaHelper1(window, x+size/2, y, size/2, totalSize,originX, originY, pixels, (c1+c2)/2, c2, (c2+c3)/2, middleColor);
        drawPlasmaHelper1(window, x, y+size/2, size/2, totalSize,originX, originY, pixels, (c1+c4)/2, middleColor, (c4+c3)/2, c4);
        drawPlasmaHelper1(window, x+size/2, y+size/2, size/2, totalSize,originX, originY, pixels, middleColor, (c2+c3)/2, c3, (c4+c3)/2);
    }
}

void drawPlasma(GWindow &window, double x, double y, double size) {
    GBufferedImage image(size, size, 0xffffff);
    window.add(&image, x, y);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    // TODO: Remove these lines and put your Plasma Fractal code here that
    // fills in the pixels in the grid (e.g. pixels[0][0] will display at (x, y) in the window)
    (void) window;
    (void) x;
    (void) y;
    (void) size;
    drawPlasmaHelper1(window, x, y, size, size, x, y, pixels, PlasmaColor(), PlasmaColor(), PlasmaColor(), PlasmaColor());
    // END (YOUR CODE)

    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}
