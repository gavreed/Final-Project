/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Gavin Reed, Evan Zhoa, Alex Temnorod, Matthew Leguizamo
 * gavreed, efz, alextemn, mleguiza
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;

void Elevator::tick(int currentTime) {
    if(currentTime % TICKS_PER_ELEVATOR_MOVE == 0 && servicing) {
        if(targetFloor - currentFloor > 0) {
            currentFloor++;
        }
        else if(targetFloor - currentFloor < 0) {
            currentFloor--;
        }
    }
    if(targetFloor == currentFloor) {
        servicing = false;
    }
}

void Elevator::serviceRequest(int floorNum) {
    //TODO: Implement serviceRequest
    servicing = true;
    targetFloor = floorNum;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
