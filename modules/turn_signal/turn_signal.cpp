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
    DECIDE,
    WAIT,
    BUTTON_PRESSED,
    BUTTON_RELEASED
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn leftTurnsignal(PD_14); //Make sure these are acceptable GPIO ports
DigitalIn rightTurnsignal(PE_12);

buttonState_t buttonState = DECIDE;
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

static bool debounceInput()
{
    static int timeElap = 0;
    static bool buttonTracker;

    switch( buttonState ) {

    case BUTTON_RELEASED:
        if( leftTurnsignal ) {
            buttonState = WAIT;
        }
        break;

    case BUTTON_PRESSED:
        if (timeElap > DEBOUNCE_BUTTON_TIME_MS) {
            timeElap=0;
            if (buttonTracker == LEFT && leftTurnsignal) {
                buttonState =
            }
            else if (buttonTracker == RIGHT && rightTurnsignal) {
                return 2;
            }
            else{

            }

        }
        
        
        break;

    case WAIT:
            if( leftTurnsignal || rightTurnsignal ) { 
                buttonTracker = leftTurnsignal;
                buttonState = BUTTON_PRESSED;
            } 
            else {
                buttonState = WAIT;
            }   
    break; 

    case WAIT_RELEASE : //fix this shit; what if glitch happen after press; controller think button go up 
        if(!leftTurnsignal){
            buttonState = BUTTON_RELEASED;
        }
    break;  
        
    
    return false;
    }
}

//VERSION 03

static bool debounceInput()
{
    static int timeElap = 0;
    static bool buttonTracker;

    switch( buttonState ) {

    case DECIDE:
        if(leftTurnsignal){
            buttonTracker = LEFT;
            buttonState = WAIT;
        }
        if(rightTurnsignal){
            buttonTracker = RIGHT;
            buttonState = WAIT;
        }


        break;

    case WAIT:
        if (timeElap > DEBOUNCE_BUTTON_TIME_MS) {
            timeElap=0;
            if (buttonTracker == LEFT && leftTurnsignal || buttonTracker == RIGHT && rightTurnsignal) {
                buttonState = BUTTON_PRESSED;
            }
            else{
                buttonState = DECIDE;
            }
        }
        
        break;

    case BUTTON_PRESSED:
            if( buttonTracker ) { 
                outLeft = !outLeft;
                outRight = false;
            } 
            if( !buttonTracker ) {
                outLeft = false;
                outRight = !outRight;
            }

        if (buttonTracker == LEFT && !leftTurnsignal || buttonTracker == RIGHT && !rightTurnsignal) {
            buttonState = WAIT;
        }

    break;    
    
    return false;
    }
}