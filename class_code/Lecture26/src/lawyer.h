/*
 * CS 106X, Nick Troccoli
 * This file declares the Lawyer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#pragma once

#include <string>
#include "employee.h"
#include "vector.h"

class Lawyer : public Employee {
public:
    Lawyer(const std::string& name, int yearsWorked, const std::string& lawSchool);
    void assignToClient(const std::string& clientName);
    void unassignToClient(const std::string& clientName);
    int getNumberOfClients() const;

private:
	int indexOfClient(const std::string& clientName) const;
    std::string lawSchool;
    Vector<std::string> clientNames;
};
