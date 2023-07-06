/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellController.h
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - split Stanford123Gui into separate controller and view portions
  **/

#pragma once

#include "observable.h"
#include <string>
#include "CS106XCellModel.h"
#include "CS106XCellView.h"
#include "gevents.h"

/**
 * This class is the hub of the CS106XCell spreadsheet program; it manages
 * the model (which keeps track of the spreadsheet data) and the view (which
 * displays the spreadsheet data) and responds to user interactions (e.g.
 * buttons, table edits, closing the window, etc.).
 *
 * It sends messages to the model by calling methods on it; the model sends messages
 * to the controller (telling it when a cell changes content) by notifying it
 * via the Observer/Observable pattern (the controller observes the model).
 *
 * It sends messages to the view by calling methods on it; the view doesn't send messages
 * to the controller.  The controller directly receives and processes GEvents itself.
 **/
class CS106XCellController : public Observer<std::string> {
public:

    /**
     * Creates a new controller object.  Does not start the object running and
     * listening for events; for that, you must call the run() method.
     **/
    CS106XCellController();

    /** Frees any dynamically allocated memory. **/
    virtual ~CS106XCellController();

    /**
     * This function is called whenever our model (which we observe)
     * sends out an update that a cellname had its value updated.
     * It updates the display to show this new calculated value.
     */
    void update(Observable<std::string> *, const std::string& cellname);

    /**
     * Runs a main loop to process graphical events that occur in the window, such
     * as key events (keyboard) or action events (buttons).
     * This method will call the appropriate processing function as each event comes in.
     * This method will terminate when it detects a WINDOW_CLOSING event and the user confirms
     * they would like to close the window.
     */
    void run();

private:
    CS106XCellModel model;
    CS106XCellView view;

    /**
     * Handles one action event in the window's event loop.
     */
    void processActionEvent(GActionEvent& actionEvent);

    /**
     * Handles one keyboard event in the window's event loop.
     */
    void processKeyEvent(GKeyEvent& keyEvent);

    /**
     * Handles one table event in the window's event loop.
     */
    void processTableEvent(GTableEvent& tableEvent);

    /**
     * Handles one window event in the window's event loop.
     * Returns true if the event loop should continue, or false
     * if it should stop (which happens when the window is closed).
     */
    bool processWindowEvent(GWindowEvent& windowEvent);

    /**
     * Initiates a load action to load a spreadsheet from file.
     */
    void load();

    /**
     * Initiates a save action to save the spreadsheet contents to file.
     */
    void save();

    /**
     * Initiates a clear action to clear the spreadsheet.
     */
    void clear();

    /**
     * Returns true if the current spreadsheet document has been modified since
     * it was last saved.
     */
    bool getHasBeenModifiedSinceLastSave() const;

    /**
     * Sets whether the current spreadsheet has been modified since it was last
     * saved. This is shown via a * (asterisk) in the window title bar.
     */
    void setHasBeenModifiedSinceLastSave(bool modified);

    /**
     * Sets the text to display in the top formula display field.
     */
    void updateFormulaFieldText();
};
