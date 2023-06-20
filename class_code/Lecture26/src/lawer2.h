#ifndef LAWER2_H
#define LAWER2_H
#include "employee.h"
#include <string>

class Lawer2 : public Employee
{
public:
    Lawer2(const std::string& name, int yearsWorked, std::string& school);
private:
    std::string school;
};

#endif // LAWER2_H
