//=====[Libraries]=============================================================

#include "turn_signal.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME 30
#define BLINK_TIME 100
#define TIME_ELAP_RESET 0 


//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn leftTurnSignal(PG_1); //Make sure these are acceptable GPIO ports
DigitalIn rightTurnSignal(PF_9);

buttonState_t buttonStateLeft = BUTTON_UP;
buttonState_t buttonStateRight = BUTTON_UP;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//only one should be true at any time
bool leftBlinker = OFF;
bool rightBlinker = OFF;

//=====[Declarations (prototypes) of private functions]========================

static bool debounceLeftInput();
static bool debounceRightInput();
static int toggleLeftBlinker(int timeElap);
static int toggleRightBlinker(int timeElap);



//=====[Implementations of public functions]===================================

bool readLeftTurnSignal(){
    return leftBlinker;
}

bool readRightTurnSignal(){
    return rightBlinker;
}

void turnSignalInit(){
    leftTurnSignal.mode(PullDown);
    rightTurnSignal.mode(PullDown);
}

// updates the variables that track the state of the blinkers and runs the functions that trigger the blinker leds
void turnSignalUpdate() {
    static int timeElap = 0;
    static bool blinkState = OFF;
    if (debounceLeftInput()) {
        leftBlinker = !leftBlinker;
        if (leftBlinker == ON) {
            rightBlinker = OFF;
        }
    }
    if (debounceRightInput()) {
        rightBlinker = !rightBlinker;
        if (rightBlinker == ON) {
            leftBlinker = OFF;
        }
    }
    if (leftBlinker) {
        timeElap = toggleLeftBlinker(timeElap);
    }
    else if (rightBlinker) {
        timeElap = toggleRightBlinker(timeElap);
    }
    else {
        turnSignalsOff();
    }
    timeElap += TIME_INCREMENT_MS;
}

//=====[Implementations of private functions]==================================

//fsm to debounce left turn signal button
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

//fsm to debounce right turn signal button
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

//makes the left turn signal led blink on and off
static int toggleLeftBlinker(int timeElap) {
    static bool blinkState = OFF;
    if (blinkState == ON) {//the blinker is on and needs to be toggled off
            if (timeElap>=BLINK_TIME) {
                turnSignalsOff();
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    } 
    else { // the blinker is off and needs to be toggled on
            if (timeElap>=BLINK_TIME) {
                leftTurnSignalOn();
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    }
}

//makes the right turn signal led blink on and off
static int toggleRightBlinker(int timeElap) {
    static bool blinkState = OFF;
    if (blinkState == ON) {//the blinker is on and needs to be toggled off
            if (timeElap>=BLINK_TIME) {
                turnSignalsOff();
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    } 
    else { // the blinker is off and needs to be toggled on
            if (timeElap>=BLINK_TIME) {
                rightTurnSignalOn();
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    }
}
