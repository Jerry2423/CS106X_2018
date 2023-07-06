/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellView.cpp
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - split Stanford123Gui into separate controller and view portions
  **/

#include "CS106XCellView.h"
#include "gfilechooser.h"
#include "goptionpane.h"
#include "CS106XCellUtil.h"
#include "filelib.h"
#include "CellRange.h"

using namespace std;

// Constants for fonts, label text, and other GUI specifications
const string FONT_PLAIN = "SansSerif-Plain-12";
const string EMPTY_STATUS_MESSAGE = "<html>&nbsp;</html>";
const int FORMULA_FIELD_WIDTH = 40;
const string LOAD_BUTTON_TEXT = "Load";
const string SAVE_BUTTON_TEXT = "Save";
const string CLEAR_BUTTON_TEXT = "Clear";
const string FORMULA_FIELD_PLACEHOLDER = "cell value/formula editor (or double-click on a cell)";

CS106XCellView::CS106XCellView(int rowsToDisplay, int columnsToDisplay,
                               int rowHeight, int columnWidth, int columnHeaderHeight) {
    // create window
    window = new GWindow((columnsToDisplay + 1) * columnWidth,
                         columnHeaderHeight + (rowsToDisplay + 2) * rowHeight + 1,
                         /* visible */ false);
    window->setCloseOperation(GWindow::CLOSE_DO_NOTHING);
    setTitle("Untitled");
    window->setResizable(true);

    // buttons
    loadButton = new GButton(LOAD_BUTTON_TEXT);
    loadButton->setIcon("icons/icon_load.gif");
    saveButton = new GButton(SAVE_BUTTON_TEXT);
    saveButton->setIcon("icons/icon_save.gif");
    clearButton = new GButton(CLEAR_BUTTON_TEXT);
    clearButton->setIcon("icons/icon_clear.gif");

    // formula text field
    formulaField = new GTextField(FORMULA_FIELD_WIDTH);
    formulaField->setPlaceholder(FORMULA_FIELD_PLACEHOLDER);
    formulaField->addActionListener();

    // bottom label
    statusLabel = new GLabel(EMPTY_STATUS_MESSAGE);

    // table configuration
    table = new GTable(rowsToDisplay, columnsToDisplay + 1);
    table->setEditable(true);
    table->setColumnHeaderStyle(GTable::COLUMN_HEADER_EXCEL);
    table->setRowColumnHeadersVisible(true);
    table->setFont(FONT_PLAIN);
    table->setHorizontalAlignment(GTable::Alignment::LEFT);

    // do layout
    window->addToRegion(table, GWindow::REGION_CENTER);
    window->setRegionAlignment(GWindow::REGION_NORTH, GWindow::ALIGN_LEFT);
    window->addToRegion(loadButton, GWindow::REGION_NORTH);
    window->addToRegion(saveButton, GWindow::REGION_NORTH);
    window->addToRegion(clearButton, GWindow::REGION_NORTH);
    window->addToRegion(formulaField, GWindow::REGION_NORTH);
    window->addToRegion(statusLabel, GWindow::REGION_SOUTH);
    window->center();
    window->setVisible(true);
    table->requestFocus();
    table->select(0, 0);
}

CS106XCellView::~CS106XCellView() {
    delete loadButton;
    delete saveButton;
    delete clearButton;
    delete formulaField;
    delete statusLabel;
    delete table;
    delete window;
}

/** USER PROMPTING **/

string CS106XCellView::promptUserToLoadFile(bool unsavedChanges) const {
    std::string filename = GFileChooser::showOpenDialog("", "*" + CS106XCellUtil::APPLICATION_FILE_EXTENSION);
    if (filename.empty() || !fileExists(filename)) {
        return "";
    }

    if (unsavedChanges && GOptionPane::showConfirmDialog(
                "You have unsaved changes. Really load?", "", GOptionPane::YES_NO)
            != GOptionPane::YES) {
        return "";
    }

    return filename;
}

string CS106XCellView::promptUserToSaveFile() const {
    std::string filename = GFileChooser::showSaveDialog("", "*" + CS106XCellUtil::APPLICATION_FILE_EXTENSION);
    if (filename.empty()) {
        return "";
    }
    if (fileExists(filename)) {
        if (GOptionPane::showConfirmDialog("File exists. Overwrite?") != GOptionPane::YES) {
            return "";
        }
    }

    return filename;
}

bool CS106XCellView::promptUserToConfirmCloseWindowWithUnsavedChanges() const {
    return GOptionPane::showConfirmDialog(
                        "You have unsaved changes. Really exit?", "", GOptionPane::YES_NO)
                    == GOptionPane::YES;
}

/** STATUS MESSAGE **/

void CS106XCellView::setStatusMessage(const std::string& message, bool isError) {
    static int STATUS_COLOR = 0x0;        // black
    static int ERROR_COLOR  = 0xbb0000;   // red
    statusLabel->setText(message == "" ? EMPTY_STATUS_MESSAGE : message);
    statusLabel->setColor(isError ? ERROR_COLOR : STATUS_COLOR);
}

/** TITLE **/

void CS106XCellView::setTitle(const std::string& title) {
    window->setTitle(CS106XCellUtil::APPLICATION_NAME + " - " + title);
}

string CS106XCellView::getTitle() const {
    return window->getTitle();
}

/** CELL TEXT **/

void CS106XCellView::setCellText(int row, int column, const std::string& text) {
    if (table->inBounds(row, column)) {
        table->set(row, column, text);
    } else {
        error("setCellText: cell out of range: R" + integerToString(row)
              + "C" + integerToString(column));
    }
}

void CS106XCellView::setCellText(const std::string& cellname, const std::string& text) {
    int row, col;
    if (CS106XCellUtil::toRowColumn(cellname, row, col)) {
        setCellText(row, col, text);
    } else {
        error("setCellText: invalid cell name: \"" + cellname + "\"");
    }
}

/** CELL EDITING TEXT **/

void CS106XCellView::setCellEditingText(int row, int column, const std::string& text) {
    if (table->inBounds(row, column)) {
        table->setEditorValue(row, column, text);
    } else {
        error("setCellEditingText: cell out of range: R" + integerToString(row)
              + "C" + integerToString(column));
    }
}

void CS106XCellView::setCellEditingText(const std::string& cellname, const std::string& text) {
    int row, col;
    if (CS106XCellUtil::toRowColumn(cellname, row, col)) {
        setCellEditingText(row, col, text);
    } else {
        error("setCellEditingText: invalid cell name: \"" + cellname + "\"");
    }
}

/** FORMULA FIELD TEXT **/

void CS106XCellView::setFormulaFieldText(const std::string& text) {
    formulaField->setText(text);
}

string CS106XCellView::getFormulaFieldText() const {
    return formulaField->getText();
}

/** IDENTIFYING AND PERFORMING ACTIONS **/

CS106XCellViewInteractorType CS106XCellView::identifyInteractor(GObject *object) const {
    if (object == loadButton) {
        return LOAD;
    } else if (object == saveButton) {
        return SAVE;
    } else if (object == clearButton) {
        return CLEAR;
    } else if (object == formulaField) {
        return FORMULA;
    } else {
        return NONE;
    }
}

void CS106XCellView::clear() {
    table->clear();
    setStatusMessage("");
    formulaField->setText("");
}

void CS106XCellView::close() {
    window->setCloseOperation(GWindow::CLOSE_HIDE);
    window->close();
}

/** MISCELLANEOUS **/

void CS106XCellView::getSelectedCell(int& row, int& column) const {
    table->getSelectedCell(row, column);
}

void CS106XCellView::requestTableFocus() {
    table->requestFocus();
}

