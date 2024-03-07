//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h" 
#include "smart_bike_system.h"

//=====[Declaration of private defines]========================================
#define TURN_SIGNAL_MS 500;
//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
DigitalOut brakeLedLine(PE_15);
DigitalOut turnSignalLineOne(PB_11);
DigitalOut turnSignalLineTwo(PB_10);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============
static bool leftTurnSignal = OFF;
static bool rightTurnSignal = OFF;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void ledDriverInit() {

}

void ledDriverUpdate() {
    static int timeElap = 0;

    if (leftTurnSignal) {
        turnSignalLineOne = ON;
        turnSignalLineOne = OFF;
    } else if (rightTurnSignal) {
        turnSignalLineOne = OFF;
        turnSignalLineOne = ON;
    } else {
        turnSignalLineOne = OFF;
        turnSignalLineOne = OFF;
    }
}

void brakeLightOn() {
    brakeLedLine = ON;
}

void brakeLightOff() {
    brakeLedLine = OFF;
}

void leftTurnSignalOn() {
    leftTurnSignal = ON;
    rightTurnSignal = OFF;
}

void rightTurnSignalOn() {
    rightTurnSignal = ON;
    leftTurnSignal = OFF;
}

void turnSignalsOff() {
    rightTurnSignal = OFF;
    leftTurnSignal = ON;
}