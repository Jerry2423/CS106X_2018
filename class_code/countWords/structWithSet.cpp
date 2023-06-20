#include<iostream>
#include"set.h"
#include<fstream>
using namespace std;

struct Date
{
    int month;
    int day;
};

bool operator <(Date a, Date b) {
    return (a.month < b.month) || (a.month == b.month && a.day < b.day);
}

ostream& operator <<(ostream& output, Date a) {
    output << a.month << "/" << a.day;
    return output;
}

int mainDate() {
    Date xmas = {12, 25};
    Date bday = {1, 18};
    Set<Date> dates;
    dates.add(xmas);
    dates.add(bday);
    //loop over a set
    for (Date day:dates) {
        day.day += 1;
    }
    cout << dates;
    return 0;
}
