//=====[Libraries]=============================================================

#include "turn_signal.h"
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_BUTTON_TIME_MS 40 //ms to wait when the button state changes to confirm actual intention

#define LEFT true
#define RIGHT false
//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn leftTurnsignal(PD_14); //Make sure these are acceptable GPIO ports
DigitalIn rightTurnsignal(PE_12);

buttonState_t buttonState = BUTTON_UP;
//buttonState_t buttonStateRight = BUTTON_RELEASED;

bool outLeft = false;
bool outRight = false;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static bool debounceInput();

//=====[Implementations of public functions]===================================

bool readLeftTurnsignal(){ //Replace with FSM to debounce 
    return debounceInput();
}

//=====[Implementations of private functions]==================================

//VERSION 02

