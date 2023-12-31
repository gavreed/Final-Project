/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Gavin Reed, Evan Zhoa, Alex Temnorod, Matthew Leguizamo
 * gavreed, efz, alextemn, mleguiza
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

void elevtorChoose(int& elev1, int& elev2, int elevatorNum);

string closestPerson(const BuildingState& buildingState, int elevatorNum) {
    int elev1;
    int elev2;
    elevtorChoose(elev1, elev2, elevatorNum);
    
    int numPeop[NUM_FLOORS] = {};
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        numPeop[floor] = buildingState.floors[floor].numPeople;
    }
    
    if(buildingState.floors[buildingState.elevators[elevatorNum].currentFloor].numPeople > 0) {
        return "e" + to_string(elevatorNum) + "p";
    } else {
        int curFloor = buildingState.elevators[elevatorNum].currentFloor;
        int min = NUM_FLOORS;
        int sub = 0;
        int floorPick = -1;
        for(int floor = 0; floor < NUM_FLOORS; floor++) {
            if(numPeop[floor] != 0) {
                sub = abs(curFloor - floor);
                if(min > sub && (buildingState.elevators[elev1].targetFloor != floor)
                   && (buildingState.elevators[elev2].targetFloor != floor)) {
                    min = sub;
                    floorPick = floor;
                }
            }
        }
        
        if(floorPick == -1) {
            return "";
        }
        
        return "e" + to_string(elevatorNum) + "f" + to_string(floorPick);
    }
}

string mostPeople(const BuildingState& buildingState, int elevatorNum) {
    int elev1;
    int elev2;
    elevtorChoose(elev1, elev2, elevatorNum);
    
    int numPeop[10] = {};
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        numPeop[floor] = buildingState.floors[floor].numPeople;
    }
    
    int max = 0;
    int floorPick = 0;
    bool picked = false;
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        if(max < numPeop[floor] && (buildingState.elevators[elev1].targetFloor != floor)
           && (buildingState.elevators[elev2].targetFloor != floor)) {
            max = numPeop[floor];
            floorPick = floor;
            picked = true;
        }
    }
    
    if(!picked) {
        return "";
    }
    
    if(buildingState.elevators[1].currentFloor == floorPick) {
        return "e" + to_string(elevatorNum) + "p";
    } else {
        return "e" + to_string(elevatorNum) + "f" + to_string(floorPick);
    }
}

string maxAnger(const BuildingState& buildingState, int elevatorNum) {
    int elev1;
    int elev2;
    elevtorChoose(elev1, elev2, elevatorNum);
    
    int anger = 0;
    int max = 0;
    int floorPick = 0;
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        for(int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
            anger += buildingState.floors[floor].people[i].angerLevel;
        }
        if(max < anger && (buildingState.elevators[elev1].targetFloor != floor)
           && (buildingState.elevators[elev2].targetFloor != floor)) {
            max = anger;
            floorPick = floor;
        }
        anger = 0;
    }
    
    if(max == 0) {
        return closestPerson(buildingState, elevatorNum);
    }
    
    if(buildingState.elevators[elevatorNum].currentFloor == floorPick) {
        return "e" + to_string(elevatorNum) + "p";
    } else {
        return "e" + to_string(elevatorNum) + "f" + to_string(floorPick);
    }
}

void elevtorChoose(int& elev1, int& elev2, int elevatorNum) {
    if(elevatorNum == 0) {
        elev1 = 1;
        elev2 = 2;
    } else if(elevatorNum == 1) {
        elev1 = 0;
        elev2 = 2;
    } else {
        elev1 = 0;
        elev2 = 1;
    }
}
                    
string getAIMoveString(const BuildingState& buildingState) {
    
    int numPeop[10] = {};
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        numPeop[floor] = buildingState.floors[floor].numPeople;
    }
    bool empty = true;
    for(int i = 0; i < NUM_FLOORS; i++) {
        if(numPeop[i] != 0) {
            empty = false;
        }
    }
    
    if(empty) {
        return "";
    }
    
    if(!buildingState.elevators[0].isServicing) {
       return  closestPerson(buildingState, 0);
    } else if(!buildingState.elevators[1].isServicing) {
       return mostPeople(buildingState, 1);
    } else if(!buildingState.elevators[2].isServicing) {
       return maxAnger(buildingState, 2);
    }
    
    return "";
}


string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    if(floorToPickup.getHasUpRequest() && floorToPickup.getHasDownRequest()) {
        int sumUp = 0;
        int numUp = 0;
        int PeopUp[MAX_PEOPLE_PER_FLOOR] = {};
        int sumDown = 0;
        int numDown = 0;
        int PeopDown[MAX_PEOPLE_PER_FLOOR] = {};
        double avgUp = 0;
        double avgDown = 0;
        
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
            if((floorToPickup.getPersonByIndex(i).getTargetFloor() - floorToPickup.getPersonByIndex(i).getCurrentFloor()) > 0) {
                sumUp += floorToPickup.getPersonByIndex(i).getAngerLevel();
                PeopUp[numUp] = i;
                numUp++;
            } else {
                sumDown += floorToPickup.getPersonByIndex(i).getAngerLevel();
                PeopDown[numDown] = i;
                numDown++;
            }
        }
        
        avgUp = (double)sumUp / numUp;
        avgDown = (double)sumDown / numDown;
        string Pickup;
        if(avgUp > avgDown) {
            for(int i = 0; i < numUp; i++) {
                Pickup += to_string(PeopUp[i]);
            }
        } else {
            for(int i = 0; i < numDown; i++) {
                Pickup += to_string(PeopDown[i]);
            }
        }
        
        cout << "Pick Up List: " << Pickup << endl;
        return Pickup;
    } else {
        string Pickup;
        for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
            Pickup += to_string(i);
        }
        
        return Pickup;
    }
}
