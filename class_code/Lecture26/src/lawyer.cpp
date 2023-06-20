/*
 * CS 106X, Nick Troccoli
 * This file implements the Lawyer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#include "lawyer.h"
#include <iostream>

using namespace std;

Lawyer::Lawyer(const string& name, int yearsWorked, const string& lawSchool)
    : Employee(name, yearsWorked) {
    this->lawSchool = lawSchool;
}

void Lawyer::assignToClient(const string& clientName) {
	clientNames.add(clientName);
}

int Lawyer::indexOfClient(const string& clientName) const {
	for (int i = 0; i < clientNames.size(); i++) {
		if (clientNames[i] == clientName) {
			return i;
		}
	}

	return -1;
}

void Lawyer::unassignToClient(const string& clientName) {
	int clientIndex = indexOfClient(clientName);
	if (clientIndex >= 0) {
		clientNames.remove(clientIndex);
	}
}

int Lawyer::getNumberOfClients() const {
	return clientNames.size();
}

void Lawyer::speak() {
    cout << "Lawer!" << endl;
}
