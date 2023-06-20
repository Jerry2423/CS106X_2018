// This program demonstrates how to write unit tests for the Fraction class

#include <iostream>
#include "console.h"
#include "TestDriver.h"
#include "FractionTests.h"

using namespace std;

int main() {
    runTestsIn("Fraction",  FractionTests);
    return 0;
}


