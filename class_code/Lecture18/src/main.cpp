#include <iostream>
#include "console.h"
#include "TestDriver.h"
#include "Tests.h"

using namespace std;

int main() {
    runTestsIn("Array Stack Tests", Tests);
    return 0;
}


