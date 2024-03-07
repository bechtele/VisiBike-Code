//=====[Libraries]=============================================================
#include "arm_book_lib.h"
#include "brake_light.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

DigitalIn leftBrakeButton(PG_0);
DigitalIn rightBrakeButton(PD_1);

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
    bool brakeLightStatus = leftBrakeButton || rightBrakeButton;
    if (brakeLightStatus) {
        brakeLightOn();
    } else {
        brakeLightOff();
    }
    return brakeLightStatus;
}
//=====[Implementations of private functions]==================================
