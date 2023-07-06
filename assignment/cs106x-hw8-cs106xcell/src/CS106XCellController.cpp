/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellController.cpp
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - split Stanford123Gui into separate controller and view portions
  **/

#include "CS106XCellController.h"
#include "Expression.h"
#include <iostream>
#include "filelib.h"
#include "private/platform.h"
#include "CS106XCellUtil.h"

using namespace std;

/**
 * Constants that control the number of visible rows/cols
 * in the graphics window.
 */
const int ROWS_TO_DISPLAY_COUNT = 20;
const int COLS_TO_DISPLAY_COUNT = 10;
const int COL_WIDTH = 75;
const int COL_HEADER_HEIGHT = 5;
const int ROW_HEIGHT = 15;

CS106XCellController::CS106XCellController()
    : view(ROWS_TO_DISPLAY_COUNT, COLS_TO_DISPLAY_COUNT, ROW_HEIGHT, COL_WIDTH, COL_HEADER_HEIGHT) {
    // Listen for events coming from the model (cell updates) - triggers our update() method
    model.addObserver(this);
}

CS106XCellController::~CS106XCellController() {}

void CS106XCellController::run() {
    while (true) {
        GEvent event = waitForEvent(ACTION_EVENT | KEY_EVENT | TABLE_EVENT | WINDOW_EVENT);
        if (event.getEventClass() == ACTION_EVENT) {
            GActionEvent actionEvent(event);
            processActionEvent(actionEvent);
        } else if (event.getEventClass() == KEY_EVENT) {
            GKeyEvent keyEvent(event);
            processKeyEvent(keyEvent);
        } else if (event.getEventClass() == TABLE_EVENT) {
            GTableEvent tableEvent(event);
            processTableEvent(tableEvent);
        } else if (event.getEventClass() == WINDOW_EVENT) {
            GWindowEvent windowEvent(event);
            // Stop listening for events if the window is closing
            if (!processWindowEvent(windowEvent)) {
                break;
            }
        }
    }

    exitGraphics();
}

/** PROCESSING ACTION EVENTS **/

void CS106XCellController::processActionEvent(GActionEvent& actionEvent) {
    CS106XCellViewInteractorType type = view.identifyInteractor(actionEvent.getSource());
    if (type == LOAD) {
        // The load button was clicked in the View
        load();
    } else if (type == SAVE) {
        // The save button was clicked in the View
        save();
    } else if (type == CLEAR) {
        // The clear button was clicked in the View
        clear();
    } else if (type == FORMULA) {
        // The ENTER key was pressed in the formula bar in the View
        int row, col;
        view.getSelectedCell(row, col);
        if (row != -1 && col != -1) {
            string exprText = view.getFormulaFieldText();
            string cellname = CS106XCellUtil::toCellName(row, col);

            try {
                model.setCell(cellname, exprText);
                view.setStatusMessage("");
                setHasBeenModifiedSinceLastSave(true);
            } catch (ErrorException& ex) {
                view.setStatusMessage(ex.getMessage(), /* isError */ true);
            }
        }
    }
}

void CS106XCellController::processKeyEvent(GKeyEvent& keyEvent) {
    /** Support common keyboard shortcuts such as CTL-L/CTL-O (open),
      * CTL-S (save) and CTL-DELETE (clear).
      **/
    if (keyEvent.getEventType() == KEY_PRESSED) {
        int code = keyEvent.getKeyCode();
        bool ctrl = keyEvent.isCtrlOrCommandKeyDown();
        if (ctrl && code == DELETE_KEY) {
            clear();
        } else if (ctrl && (code == 'L' || code == 'O')) {
            load();
        } else if (ctrl && code == 'S') {
            save();
        }
    }
}

void CS106XCellController::processTableEvent(GTableEvent& tableEvent) {
    int row = tableEvent.getRow();
    int col = tableEvent.getColumn();
    string cellname = CS106XCellUtil::toCellName(row, col);

    if (tableEvent.getEventType() == TABLE_CUT || tableEvent.getEventType() == TABLE_COPY) {
        // actually copy the cell's formula, not its displayed value
        const Expression *exp = model.getExpressionForCell(cellname);
        if (exp != nullptr && exp->getRawText().length() > 0) {
            stanfordcpplib::getPlatform()->clipboard_set(exp->getRawText());
        }
    } else if (tableEvent.getEventType() == TABLE_EDIT_BEGIN) {
        // actually edit the cell's formula, not its displayed value
        const Expression *exp = model.getExpressionForCell(cellname);
        if (exp != nullptr && exp->isFormula() && exp->getRawText().length() > 0) {
            view.setCellEditingText(row, col, exp->getRawText());
        }
    } else if (tableEvent.getEventType() == TABLE_SELECTED) {
        // when a cell is clicked on
        updateFormulaFieldText();
    } else if (tableEvent.getEventType() == TABLE_UPDATED) {
        view.setCellText(row, col, "");  // temporary; model must fix
        string value = tableEvent.getValue();

        // when the user clicks on a cell, edits it, and finishes editing
        try {
            model.setCell(cellname, value);
            view.setStatusMessage("");
            setHasBeenModifiedSinceLastSave(true);
            updateFormulaFieldText();
        } catch (ErrorException& ex) {
            view.setStatusMessage(ex.getMessage(), /* isError */ true);
            update(nullptr, cellname);
        }
    }
}

bool CS106XCellController::processWindowEvent(GWindowEvent& windowEvent) {
    if (windowEvent.getEventType() == WINDOW_CLOSING) {
        if (getHasBeenModifiedSinceLastSave() && !view.promptUserToConfirmCloseWindowWithUnsavedChanges()) {
            return true;
        }

        view.close();
        return false;   // stop event loop
    }

    return true;
}

void CS106XCellController::load() {
    string filename = view.promptUserToLoadFile(getHasBeenModifiedSinceLastSave());
    if (filename == "") return;

    ifstream infile;
    infile.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    if (!infile.fail()) {
        view.clear();
        model.load(infile);
        view.setStatusMessage("Data loaded from " + getTail(filename) + ".");
        view.setTitle(getTail(filename));
        infile.close();
        updateFormulaFieldText();
        view.requestTableFocus();
    }
}

void CS106XCellController::save() {
    string filename = view.promptUserToSaveFile();
    if (filename == "") return;

    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ios_base::binary | std::ios_base::out);
    if (!outfile.fail()) {
        model.save(outfile);
        outfile.close();
        view.setStatusMessage("Data saved to " + getTail(filename) + ".");
        view.setTitle(getTail(filename));
        view.requestTableFocus();
    }
}

void CS106XCellController::clear() {
    model.clear();
    view.clear();
    setHasBeenModifiedSinceLastSave(true);
    view.requestTableFocus();
}

/** TRACKING UNSAVED CHANGES **/

bool CS106XCellController::getHasBeenModifiedSinceLastSave() const {
    return endsWith(view.getTitle(), " *");
}

void CS106XCellController::setHasBeenModifiedSinceLastSave(bool modified) {
    string title = view.getTitle();
    if (modified && !getHasBeenModifiedSinceLastSave()) {
        title += " *";
        view.setTitle(title);
    } else if (!modified && getHasBeenModifiedSinceLastSave()) {
        title = title.substr(0, title.length() - 2);
        view.setTitle(title);
    }
}

/** MISCELLANEOUS **/

void CS106XCellController::update(Observable<string> *, const string& cellname) {
    const Expression *expr = model.getExpressionForCell(cellname);
    if (expr == nullptr) {
        view.setCellText(cellname, "");
    } else if (expr->getType() != TEXTSTRING) {
        view.setCellText(cellname, realToString(expr->getValue()));
    } else {
        view.setCellText(cellname, expr->getRawText());
    }

    updateFormulaFieldText();
}

void CS106XCellController::updateFormulaFieldText() {
    int row, col;
    view.getSelectedCell(row, col);
    string text = "";
    if (row != -1 && col != -1) {
        string cellname = CS106XCellUtil::toCellName(row, col);
        const Expression *exp = model.getExpressionForCell(cellname);
        if (exp != nullptr) {
            text = exp->getRawText();
        }
    }

    view.setFormulaFieldText(text);
}

