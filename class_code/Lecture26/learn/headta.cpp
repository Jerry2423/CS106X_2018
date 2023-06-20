
/*
 * CS 106X, Nick Troccoli
 * This file implements the members of the HeadTA class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#include "headta.h"
#include "employee.h"

using namespace std;

HeadTA::HeadTA(const string& name, int yearsWorked, const string& className)
	: Employee(name, yearsWorked) {
		this->className = className;
}

string HeadTA::getFavoriteProgrammingLanguage() const {
	if (className == "CS106X" || className == "CS106B") {
		return "C++";
	} else if (className == "CS106A") {
		return "Java";
	} else if (className == "CS106AJ") {
		return "JavaScript";
    } else if (className == "CS106AP") {
		return "Python";
	}

    return "";
}

int HeadTA::getHoursWorkedPerWeek() const {
	return Employee::getHoursWorkedPerWeek() / 2;
}

string HeadTA::getName() const {
	return "Head TA " + Employee::getName();
}

void HeadTA::speak() {
    cout << "ta" << endl;
}

double HeadTA::salary() const {
    return 0.5*Employee::salary();
}
