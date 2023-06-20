#include <iostream>
#include <string>
#include <cmath>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void getInfo(double& height, double& weight, int personIndex);
double bmiCalculator(double height, double weight);
void printBmi(double bmi);

int main()
{
    double bmi[5];

    cout << "This program reads data for two people and computes their Body Mass Index (BMI)." << endl;

    for (int i = 1; i <= 2; i++) {
        double height, weight;
        getInfo(height, weight, i);
        bmi[i] = bmiCalculator(height, weight);
        printBmi(bmi[i]);
    }
    cout << "BMI difference = " << abs(bmi[1] - bmi[2]) << endl;
    return 0;
}

void getInfo(double &height, double &weight, int personIndex) {
    cout << endl <<  "Enter Person " << personIndex << "'s information:" << endl;
    cout << "height (in inches)? ";
    cin >> height;
    cout << "weight (in pounds)? ";
    cin >> weight;

}

double bmiCalculator(double height, double weight) {
    return (weight / (height * height)) * 703;
}

void printBmi(double bmi) {
    cout << "BMI = " << bmi << ", ";
    if (bmi < 18.5) cout << "class1" << endl;
    else if (bmi >= 18.5 && bmi <= 24.9) cout << "class2" << endl;
    else if (bmi >= 25 && bmi <= 29.9) cout << "class3" << endl;
    else cout << "class4" << endl;
}


/* * * * * * Test Cases * * * * * */

