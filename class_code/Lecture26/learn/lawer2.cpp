
#include "lawer2.h"
using namespace std;
Lawer2::Lawer2(const std::string& name, int yearsWorked, std::string& school) : Employee(name, yearsWorked) //first use superclass initiliazer
{
    /*wrong
     * this->name = name
     * this->yearsWorked = yearsWorked
     * subclass is not allowed to access private member in the superclass
     */
    this->school = school;
}

double Lawer2::salary() const  {
    return Employee::salary() * 2; // use the superclass
}

void Lawer2::speak() {
    cout << "Lawer" << endl;
}

int Lawer2::getHoursWorkedPerWeek() const {
    return 2 * Employee::getHoursWorkedPerWeek();
}

std::string Lawer2::getName() const {
    return "Lawer " + Employee::getName();
}
