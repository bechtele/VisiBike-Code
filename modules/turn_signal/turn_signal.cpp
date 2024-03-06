//=====[Libraries]=============================================================

#include "turn_signal.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_TIME 30


//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

DigitalIn leftTurnSignal(PG_1); //Make sure these are acceptable GPIO ports
DigitalIn rightTurnSignal(PF_9);

buttonState_t buttonStateLeft = BUTTON_UP;
buttonState_t buttonStateRight = BUTTON_UP;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//only one should be true at any time
bool leftBlinkerOn = false;
bool rightBlinkerOn = false;

//=====[Declarations (prototypes) of private functions]========================

static bool debounceLeftInput();
static bool debounceRightInput();



//=====[Implementations of public functions]===================================

bool readLeftTurnSignal(){ //Replace with FSM to debounce 
    return leftBlinkerOn;
}

bool readRightTurnSignal(){
    return rightBlinkerOn;
}

void turnSignalInit(){
    leftTurnSignal.mode(PullDown);
    rightTurnSignal.mode(PullDown);
}

void turnSignalUpdate() {
    if (debounceLeftInput()) {
        leftBlinkerOn = !leftBlinkerOn;
        if (leftBlinkerOn == true) {
            rightBlinkerOn = false;
        }
    }
    if (debounceRightInput()) {
        rightBlinkerOn = !rightBlinkerOn;
        if (rightBlinkerOn == true) {
            leftBlinkerOn = false;
        }
    }
}

//=====[Implementations of private functions]==================================

static bool debounceLeftInput(){
    bool leftButtonReleasedEvent = false;
    static int timeElap = 0;
    switch( buttonStateLeft ) {

    case BUTTON_UP:
        if( leftTurnSignal ) {
            buttonStateLeft = BUTTON_FALLING;
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( leftTurnSignal ) {
                buttonStateLeft = BUTTON_DOWN;
            } else {
                buttonStateLeft = BUTTON_UP;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !leftTurnSignal ) {
            buttonStateLeft = BUTTON_RISING;
            timeElap = 0;
        }
        break;

    case BUTTON_RISING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( !leftTurnSignal ) {
                buttonStateLeft = BUTTON_UP;
                leftButtonReleasedEvent = true;
            } else {
                buttonStateLeft = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return leftButtonReleasedEvent;
}

static bool debounceRightInput(){
    bool rightButtonReleasedEvent = false;
    static int timeElap = 0;
    switch( buttonStateRight ) {

    case BUTTON_UP:
        if( rightTurnSignal ) {
            buttonStateRight = BUTTON_FALLING;
            timeElap = 0;
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( rightTurnSignal ) {
                buttonStateRight = BUTTON_DOWN;
            } else {
                buttonStateRight = BUTTON_UP;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !leftTurnSignal ) {
            buttonStateRight = BUTTON_RISING;
            timeElap = 0;
        }
        break;

    case BUTTON_RISING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( !rightTurnSignal ) {
                buttonStateRight = BUTTON_UP;
                rightButtonReleasedEvent = true;
            } else {
                buttonStateRight = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return rightButtonReleasedEvent;
}

void badTurnSignalDisplay() {
    if (leftTurnSignal) {
        uartUsb.write("Left turn signal: true\n", 23);
    }
    if (rightTurnSignal) {
        uartUsb.write("Right turn signal: true\n", 24);
    }
}
