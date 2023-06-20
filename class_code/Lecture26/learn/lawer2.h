
#ifndef LAWER2_H
#define LAWER2_H
#include "employee.h"
#include <string>

class Lawer2 : public Employee
{
public:
    Lawer2(const std::string& name, int yearsWorked, std::string& school);
    double salary() const;

    // int getHoursWorkedPerWeek() const;
    // std::string getName() const;
    // double salary() const;
    void speak()  ; //pure virtual function, must be overridden in subclass
private:
    std::string school;
};

#endif // LAWER2_H
