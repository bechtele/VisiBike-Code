//=====[Libraries]=============================================================

#include "turn_signal.h"
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_TIME 30
#define TIME_INCREMENT_MS 10 //ms to wait when the button state changes to confirm actual intention

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

int timeElap = 0;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static bool debounceLeftInput();
static bool debounceRightInput();


//=====[Implementations of public functions]===================================

bool readLeftTurnSignal(){ //Replace with FSM to debounce 
    return debounceLeftInput();
}

bool readRightTurnSignal(){
    return debounceRightInput();
}

void turnSignalInit(){
    leftTurnSignal.mode(PullUp);
    rightTurnSignal.mode(PullUp);
}

//=====[Implementations of private functions]==================================

static bool debounceLeftInput(){
    bool leftButtonReleasedEvent = false;
    switch( buttonStateLeft ) {

    case BUTTON_UP:
        if( leftTurnSignal ) {
            buttonStateLeft = BUTTON_FALLING;
            timeElap = 0;
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
    switch( buttonStateRight ) {

    case BUTTON_UP:
        if( leftTurnSignal ) {
            buttonStateRight = BUTTON_FALLING;
            timeElap = 0;
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( leftTurnSignal ) {
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
            if( !leftTurnSignal ) {
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

