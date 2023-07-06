/**
  * CS106XCell, Autumn 2018
  *
  * File: CS106XCellView.h
  * --------------
  * Please do not modify this provided file. Your turned-in files should work
  * with an unmodified version of all provided code files.
  *
  * @author Nick Troccoli, based on code from Marty Stepp, Julie Zelenski and Jerry Cain
  * @version 2018/11/28
  *     - split Stanford123Gui into separate controller and view portions
  **/

#pragma once

#include <string>
#include "gobjects.h"
#include "gtable.h"

/** A type that represents the different interactors visible in this view:
 * the load, save, and clear buttons; the formula text field; or NONE, which
 * represents no interactor (used in identifyInteractor if the passed-in
 * interactor doesn't match any interactor onscreen).
 **/
enum CS106XCellViewInteractorType { LOAD, SAVE, CLEAR, FORMULA, NONE };

/** A class that represents the user interface for the CS106XCell spreadsheet
 * program.  This view displays a graphical window with a cell table, and with
 * load, save, and clear buttons across the top as well as a formula bar for
 * filling in formulas.  This view is also able to display various modal prompts
 * for saving and loading files.
 **/
class CS106XCellView {
public:

    /** Initializes a new view displaying the given number of rows/columns,
     * with the given sizes.
     **/
    CS106XCellView(int rowsToDisplay, int columnsToDisplay,
                   int rowHeight, int columnWidth, int columnHeaderHeight);

    /** Frees all dynamically allocated memory. **/
    ~CS106XCellView();

    /** Updates a cell at the given row/column, or with the given name,
     * to display the provided string content.
     **/
    void setCellText(int row, int column, const std::string& text);
    void setCellText(const std::string& cellname, const std::string& text);

    /** Updates a cell at the given row/column, or with the given name,
     * to display the provided string content in editing mode.
     **/
    void setCellEditingText(int row, int column, const std::string& text);
    void setCellEditingText(const std::string& cellname, const std::string& text);

    /** Clears all cells in the displayed table, the status message, and the
     * formula text field.
     **/
    void clear();

    /** Identifies which of this view's interactors (if any) this object is.
     * If it is none of them, returns NONE.
     **/
    CS106XCellViewInteractorType identifyInteractor(GObject *object) const;

    /** Displays a prompt to the user to select a file to load, and returns
     * the selected filename, or the empty string if the selected filename
     * is invalid or no file was selected.
     *
     * If unsavedChanges is true, if the user selects a valid file to load,
     * this view will display an additional prompt verifying that the user wants
     * to load the file and lose any unsaved changes.
     **/
    std::string promptUserToLoadFile(bool unsavedChanges) const;

    /** Displays a prompt to the user to select where to save the spreadsheet,
     * and returns the selected filename, or the empty string if the selected filename
     * is invalid or no file was selected.
     *
     * If the user selects an existing file to overwrite, this view will display an
     * additional prompt verifying that the user wants to overwrite the file.
     **/
    std::string promptUserToSaveFile() const;

    /** Displays a prompt to the user to confirm that they would like to close the
     * GUI window and lose any unsaved changes.  Returns true if the user selects
     * "Yes", or false otherwise.
     **/
    bool promptUserToConfirmCloseWindowWithUnsavedChanges() const;

    /**
     * Sets the status message text to show in the window's bottom status bar.
     * If isError is true, shows the text in red; otherwise the text is black.
     */
    void setStatusMessage(const std::string& message, bool isError = false);

    /**
     * Sets/gets the title text shown in the window's top status bar.
     */
    void setTitle(const std::string& title);
    std::string getTitle() const;

    /**
      * Sets/gets the text displayed in the formula text field at the top of the window.
      **/
    void setFormulaFieldText(const std::string& text);
    std::string getFormulaFieldText() const;

    /**
     * Requests that the UI focus go to the displayed table.
     */
    void requestTableFocus();

    /**
     * Returns the row and column of the cell that is currently selected
     * by filling the given reference parameters.
     * Sets both row and column to -1 if no cell is currently selected.
     */
    void getSelectedCell(int& row, int& column) const;


    /**
     * Closes the graphical window displaying the view.
     **/
    void close();

private:
    // Graphical interactor elements
    GWindow* window;
    GTable* table;
    GButton* loadButton;
    GButton* saveButton;
    GButton* clearButton;
    GTextField* formulaField;
    GLabel* statusLabel;
};
