
/*
 * CS 106X, Nick Troccoli
 * This file declares the Head TA class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#pragma once

#include "employee.h"

class HeadTA : public Employee {
public:
	HeadTA(const std::string& name, int yearsWorked, const std::string& className);
	std::string getFavoriteProgrammingLanguage() const;
    int getHoursWorkedPerWeek() const;
    std::string getName() const;
    void speak();
    double salary() const;
private:
	std::string className;
};
