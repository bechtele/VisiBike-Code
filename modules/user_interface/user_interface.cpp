//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "brake_light.h"

#include "user_interface.h"
#include "turn_signal.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
bool turnSignalLeftTracker = false;
bool turnSignalRightTracker = true;

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================
static void displaySystemInit();
static void displaySystemUpdate();
static void turnSignalUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit() {
    displaySystemInit();
}

void userInterfaceUpdate() {
    displaySystemUpdate();
    turnSignalUpdate();
}


//=====[Implementations of private functions]==================================

static void displaySystemInit(){
    displayInit();
    //Position of SPEED: 
    displayCharPositionWrite(0,0);
    displayStringWrite("SPEED:   MPH");

    //TURN SIGNAL
    displayCharPositionWrite(0,1);
    displayStringWrite("TS:");

    //BRAKE
    displayCharPositionWrite(9,1);
    displayStringWrite("BRK:");
}

static void displayUpdate(){
    //Update Speed
    displayCharPositionWrite(7,0);
    displayStringWrite("99");

    //Update Turn Signal
    displayCharPositionWrite(3,1);
    if(turnSignalLeftTracker){
        displayStringWrite("LEFT ");
    }
    else if(turnSignalRightTracker){
        displayStringWrite("RIGHT");
    } else {
        displayStringWrite("OFF  ");
    }
    //displayStringWrite()

    //Update Brake
    displayCharPositionWrite(13,1);
    if(brakeLightUpdate()){
        displayStringWrite("ON ");
    }
    else{
        displayStringWrite("OFF");
    }

}

static void turnSignalUpdate(){
    if(readLeftTurnSignal()){
        turnSignalLeftTracker = !turnSignalLeftTracker;

    }
    if(readRightTurnSignal()){
        turnSignalRightTracker = !turnSignalRightTracker;

    }
}