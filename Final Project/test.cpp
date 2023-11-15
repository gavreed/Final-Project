/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;
void test_Person();
void test_Floor();

// declare your test functions here

void start_tests() {
    // call your test functions here
    test_Person();
    test_Floor();
    return;
}

// write test functions here

void test_Person() {
    string things = "7f4t8a3";
    
    Person p1(things);
    cout << p1.getTurn() << p1.getCurrentFloor() << p1.getTargetFloor() << p1.getAngerLevel() << endl;
    
}

void test_Floor() {

    int arr[10] = {0, 2, 0, 4, 5, 0, 7, 8, 9, 0};
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++)
    }
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
}
