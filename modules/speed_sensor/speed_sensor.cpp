//=====[Libraries]=============================================================
#include "speed_sensor.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "smart_bike_system.h"
#include <cstdint>

//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME 10
#define INTEGER_MAX 9999;


//=====[Declaration of private data types]=====================================
DigitalIn reedSwitchSensor(PF_7);

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} reedState_t;


//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============
static reedState_t reedState = BUTTON_UP;
static bool reedStateBoolean = false;

Timer sensorTimer; //Timer that will continuously run

uint32_t lastTriggerTime = 0; 

float storeSpeed[3];

//=====[Declarations (prototypes) of private functions]========================
static bool debounceReedInput();

//=====[Implementations of public functions]===================================
void speedSensorInit() {
    reedSwitchSensor.mode(PullDown);
    sensorTimer.start();
}

void speedSensorUpdate() {
    if (debounceReedInput()) {
        float currentSpeed;
        uint32_t timeDifference = 0;
        // Get the current time
        uint32_t currentTime = sensorTimer.read_ms();
        timeDifference = currentTime - lastTriggerTime;

            // Update the last trigger time
        lastTriggerTime = currentTime;

            // Now 'timeDifference' holds the time elapsed since the last trigger

        currentSpeed = (1.0/timeDifference)*4283.98;

        static int index = 0;
        storeSpeed[index%3] = currentSpeed;
        index++;

        if(sensorTimer.read_ms() >= 3600000){
        sensorTimer.reset();
        sensorTimer.start();
        lastTriggerTime = 0;

        if(index == 9999){
            index = 0;
        }

        }    

    }
}

float readSpeed(){
   return  (storeSpeed[0] + storeSpeed[1] + storeSpeed[2])/3;
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