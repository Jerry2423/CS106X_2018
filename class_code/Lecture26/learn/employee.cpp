
/*
 * CS 106X, Nick Troccoli
 * This file implements the members of the Employee class,
 * the superclass or base class in our inheritance hierarchy.
 */

#include "employee.h"

using namespace std;

Employee::Employee(const string& name, int yearsWorked) {
    this->name = name;
    this->yearsWorked = yearsWorked;
}

Employee::~Employee() {
    cout << "end" << endl;
}

int Employee::getHoursWorkedPerWeek() const {
    return 40;
}

string Employee::getName() const {
    return name;
}

int Employee::getYearsWorked() const {
    return yearsWorked;
}

double Employee::salary() const {
    return 50000 + (500 * yearsWorked);
}
