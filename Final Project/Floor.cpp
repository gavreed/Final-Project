/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Gavin Reed, Evan Zhoa, Alex Temnorod, Matthew Leguizamo
 * gavreed, efz, alextemn, mleguiza
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int sum = 0;
    int rmPeople[MAX_PEOPLE_PER_FLOOR] = {};
    
    for(int i = 0; i < numPeople; i++) {
        if(people[i].tick(currentTime)){
            rmPeople[sum] = i;
            sum++;
        }
    }
    removePeople(rmPeople, sum);
    return sum;
}

void Floor::addPerson(Person newPerson, int request) {
    if(numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
    }
    if(request > 0) {
        hasUpRequest = true;
    } else {
        hasDownRequest= true;
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    Person norm;
    for(int i = 0; i < numPeopleToRemove; i++) {
        people[indicesToRemove[i]] = norm;
        numPeople--;
    }
    for(int i = 0; i < MAX_PEOPLE_PER_FLOOR - 1; i++) {
        for(int j = 0; j < MAX_PEOPLE_PER_FLOOR - 1; j++) {
            if(people[j].getTargetFloor() == norm.getTargetFloor() && people[j].getCurrentFloor() == norm.getCurrentFloor()) {
                people[j] = people[j + 1];
                people[j + 1] = norm;
            }
        }
    }
    resetRequests();
}

void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    for(int i = 0; i < numPeople; i++) {
        if(people[i].getTargetFloor() - people[i].getCurrentFloor() > 0) {
            hasUpRequest = true;
        } else if(people[i].getTargetFloor() - people[i].getCurrentFloor() < 0) {
            hasDownRequest = true;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
