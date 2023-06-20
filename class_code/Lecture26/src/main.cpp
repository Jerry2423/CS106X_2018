/*
 * CS 106X, Nick Troccoli
 * This client program uses our classes built with inheritance.
 */

#include <iostream>
#include "console.h"
#include "employee.h"
#include "headta.h"
#include "lawyer.h"
#include "lawer2.h"

using namespace std;

int main() {
    Vector<Employee *> emps;
    Employee *lawyer = new Lawyer("Nick", 1, "Stanford");
    Employee *headTA = new HeadTA("Zach", 1, "CS106X");
    Lawer2* jr = new Lawer2("jr", 1, "MIT");
    emps.add(lawyer);
    emps.add(headTA);
    emps.add(jr);

    for (Employee *e : emps) {
        // For lawyer, this will use the version inherited from Employee
        // for HeadTA, even though e is an Employee *, because of polymorphism
        // this will use the overridden version from HeadTA!
        cout << e->getHoursWorkedPerWeek() << endl;
    }

    return 0;
}








