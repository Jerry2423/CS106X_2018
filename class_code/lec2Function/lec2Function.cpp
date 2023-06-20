#include <iostream>
#include <string>
#include <cmath>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

// pass by reference; function decomposition

//function prototype: good norm/style

void getCoefficients(double& a, double& b, double& c);
void computeRoots(double a, double b, double c, double& root1, double& root2);
void printRoots(double root1, double root2);

int main()
{
    double a, b, c, root1, root2;
    getCoefficients(a, b, c);
    computeRoots(a, b, c, root1, root2);
    printRoots(root1, root2);
    return 0;
}

void getCoefficients(double& a, double& b, double& c) {
    cin >> a;
    cin >> b;
    cin >> c;
}

void computeRoots(double a, double b, double c, double& root1, double& root2) {
    root1 = (-b + sqrt(b*b - 4 * a* c)) / 2*a;
    root2 = (-b - sqrt(b*b - 4 * a* c)) / 2*a;
}
// avoid copy large variable while not chainging it. const typename& vname
void printRoots(const double& root1,const double& root2) {
    cout << root1  << " " << root2 << endl;
}


/* * * * * * Test Cases * * * * * */

