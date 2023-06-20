#include "lawer2.h"
#include "headta.h"
using namespace std;

int main() {
    string name = "jr", school = "MIT";
    Lawer2 jr = Lawer2(name, 10, school);
    
    string name2 = "rf", shTech = "shTech";
    HeadTA rf = HeadTA(name2, 2, shTech);

    cout << jr.salary() << endl;
}
