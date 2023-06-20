/*
 * CS 106X, Nick Troccoli
 * This file declares the Employee class, the superclass or base class in
 * our inheritance hierarchy.
 */

#pragma once

#include <string>
#include <iostream>

// A class to represent employees in general.
class Employee {
public:
    Employee(const std::string& name, int yearsWorked);
    ~Employee();
    virtual int getHoursWorkedPerWeek() const;
    virtual std::string getName() const;
    int getYearsWorked() const;
    virtual double salary() const;
    virtual void speak() = 0; //pure virtual function, must be overridden in subclass

private:
    std::string name;
    int yearsWorked;
};
