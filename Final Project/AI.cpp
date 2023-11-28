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

string getAIMoveString(const BuildingState& buildingState) {
    
    int numPeop[10] = {};
    for(int floor = 0; floor < NUM_FLOORS; floor++) {
        numPeop[floor] = buildingState.floors[floor].numPeople;
    }
    
    if(!buildingState.elevators[0].isServicing) {
        if(buildingState.floors[buildingState.elevators[0].currentFloor].numPeople > 0) {
            return "e0p";
        } else {
            int curFloor = buildingState.elevators[0].currentFloor;
            int min = MAX_PEOPLE_PER_FLOOR;
            int sub = 0;
            for(int i = 0; i < 10; i++) {
                if(numPeop[i] != 0) {
                    sub = abs(curFloor - i);
                    if(min > sub) {
                        min = sub;
                    }
                }
            }
            return "e0f" + to_string(min);
        }
    } else if(!buildingState.elevators[1].isServicing) {
        int max = 0;
        int floorPick = 0;
        for(int i = 0; i < 10; i++) {
            if(max < numPeop[i]) {
                max = numPeop[i];
                floorPick = i;
            }
        }
        
        if(buildingState.elevators[1].currentFloor == floorPick) {
            return "e1p";
        } else {
            return "e1f" + to_string(floorPick);
        }
    } else if(!buildingState.elevators[2].isServicing) {
        int anger = 0;
        int max = 0;
        int floorPick = 0;
        for(int floor = 0; floor < NUM_FLOORS; floor++) {
            for(int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
                anger += buildingState.floors[floor].people[i].angerLevel;
            }
            if(max < anger) {
                max = anger;
                floorPick = floor;
            }
            anger = 0;
        }
        if(buildingState.elevators[2].currentFloor == floorPick) {
            return "e2p";
        } else {
            return "e2f" + to_string(floorPick);
        }
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
