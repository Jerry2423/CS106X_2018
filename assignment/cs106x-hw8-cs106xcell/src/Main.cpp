/**
  * CS106XCell, Autumn 2018
  *
  * File: Main.cpp
  * --------------
  * This file is the main entry point for the CS106XCell spreadsheet program.
  * It creates a controller object and tells it to run its main program and
  * listen for events.  When it terminates and the window is closed, the main
  * method will finish.
  *
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - refactor to M/V/C pattern
  **/

#include "CS106XCellController.h"
#include "TestDriver.h"
#include "CS106XCellModelTests.h"
#include "ExpressionTests.h"
#include "CS106XCellUtil.h"
#include "goptionpane.h"
#include "console.h"

using namespace std;

int main() {
    Vector<std::string> options {"A: Run CS106XCellModel Tests", "B: Run Expression Tests", "C: Run " + CS106XCellUtil::APPLICATION_NAME};
    std::string choice = GOptionPane::showOptionDialog("Welcome to " + CS106XCellUtil::APPLICATION_NAME + "!", options);
    if (choice == options[0]) {
        runTestsIn("CS106XCellModel", gCS106XCellModelTests);
    } else if (choice == options[1]) {
        runTestsIn("Expression", gExpressionTests);
    } else if (choice == options[2]) {
        CS106XCellController controller;
        controller.run();
    }

    return 0;
}
