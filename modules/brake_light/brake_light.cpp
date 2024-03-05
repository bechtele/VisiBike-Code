//=====[Libraries]=============================================================
#include "arm_book_lib.h"
#include "brake_light.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

DigitalIn leftBrakeButton(D4);
DigitalIn rightBrakeButton(D3);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void brakeLightInit() {
    leftBrakeButton.mode(PullUp);
    rightBrakeButton.mode(PullUp);
}

bool brakeLightUpdate() {
    return leftBrakeButton || rightBrakeButton;
}
//=====[Implementations of private functions]==================================
