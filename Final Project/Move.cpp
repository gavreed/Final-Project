/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Gavin Reed
 * gavreed
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if(commandString.length() == 0){
        isPass = true;
        return;
    }
    stringstream ss(commandString);
    
    char type;
    char moveType;
    
    ss >> type;
    
    if(type == 'S') {
        isSave = true;
    } else if(type == 'Q') {
        isQuit = true;
    } else if (type == 'e') {
        ss >> elevatorId;
        ss >> moveType;
        if(moveType == 'f') {
            ss >> targetFloor;
        } else {
            isPickup = true;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if(isPass || isQuit || isSave) {
        return true;
    }
    if(0 <= elevatorId && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {
        return true;
    } else if(0 <= targetFloor && targetFloor < NUM_FLOORS && elevators[elevatorId].getCurrentFloor() != targetFloor) {
        return true;
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int maxFloor = 0;
    for (int  i = 0; i < pickupList.size(); i++ ){
        peopleToPickup[i] = static_cast<int>(pickupList.at(i));
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        numPeopleToPickup ++;
        if(maxFloor < abs((currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()))){
            maxFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
        targetFloor = maxFloor;
    }
    
    
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
