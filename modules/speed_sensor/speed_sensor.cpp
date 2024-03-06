//=====[Libraries]=============================================================
#include "speed_sensor.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "smart_bike_system.h"

//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME 10

//=====[Declaration of private data types]=====================================
DigitalIn reedSwitchSensor(PF_7);

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} reedState_t;

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============
static reedState_t reedState = BUTTON_UP;
static bool reedStateBoolean = false;
//=====[Declarations (prototypes) of private functions]========================
static bool debounceReedInput();

//=====[Implementations of public functions]===================================
void speedSensorInit() {
    reedSwitchSensor.mode(PullDown);
}

void speedSensorUpdate() {
    static bool asdf = false;
    if (debounceReedInput()) {
            if(asdf) {
                uartUsb.write("Input<>\n", 8);
                asdf = !asdf;
            }
            else {
                uartUsb.write("Input[]\n", 8);
                asdf=!asdf;
            }
    }
}

int readSpeed() {
    return -1;
}
//=====[Implementations of private functions]==================================

static bool debounceReedInput(){
    bool leftButtonReleasedEvent = false;
    static int timeElap = 0;
    switch( reedState ) {

    case BUTTON_UP:
        if( reedSwitchSensor ) {
            reedState = BUTTON_FALLING;
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( reedSwitchSensor ) {
                reedState = BUTTON_DOWN;
            } else {
                reedState = BUTTON_UP;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !reedSwitchSensor ) {
            reedState = BUTTON_RISING;
            timeElap = 0;
        }
        break;

    case BUTTON_RISING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( !reedSwitchSensor ) {
                reedState = BUTTON_UP;
                leftButtonReleasedEvent = true;
            } else {
                reedState = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return leftButtonReleasedEvent;
}