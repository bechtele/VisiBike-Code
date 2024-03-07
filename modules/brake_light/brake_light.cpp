//=====[Libraries]=============================================================
#include "arm_book_lib.h"
#include "brake_light.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

DigitalIn leftBrakeButton(PC_8);
DigitalIn rightBrakeButton(PC_9);

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
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

void shittyBrakeLightDisplay() {
            if(leftBrakeButton) {
                uartUsb.write("leftBrake\n", 10);
            }
            if(rightBrakeButton) {
                uartUsb.write("rightBrake\n", 11);
            }
}
//=====[Implementations of private functions]==================================
