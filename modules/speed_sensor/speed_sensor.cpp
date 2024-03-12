//=====[Libraries]============================================================
#include "speed_sensor.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "smart_bike_system.h"
#include <cstdint>

//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME 10
#define NUMBER_OF_AVGS 3
#define TIMER_MAX 1000000
#define TIME_TIL_SPEED_RESET 5000


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

Timer sensorTimer;

uint32_t lastTriggerTime = 0; 

float storeSpeed[NUMBER_OF_AVGS];

//=====[Declarations (prototypes) of private functions]========================
static bool debounceReedInput();

//=====[Implementations of public functions]===================================
void speedSensorInit() {
    reedSwitchSensor.mode(PullDown);
    sensorTimer.start();
    for (int i=0; i<NUMBER_OF_AVGS; i++) { // initializes the array with zeros (good coding practice)
        storeSpeed[i]=0;
    }
}

//this updates the storeSpeed array with the values from the speed sensor
void speedSensorUpdate() {

    if (debounceReedInput()) { //sensor input detected
        float currentSpeed;
        uint32_t timeDifference;
        uint32_t currentTime = sensorTimer.read_ms(); // Get the current time
        timeDifference = currentTime - lastTriggerTime;
        lastTriggerTime = currentTime; // Update the last trigger time
        currentSpeed = (1.0/timeDifference)*4283.99;

        static int index = 0;
        storeSpeed[index%NUMBER_OF_AVGS] = currentSpeed; //store current speed
        index++;

        if(sensorTimer.read_ms() >= TIMER_MAX){ //protection from the timer variables overflowing
            sensorTimer.reset();
            lastTriggerTime = 0;
        }

        if(index == INT16_MAX){ // protection from the index variable from overflowing
            index = 0;
        }

    } else{ // no sensor input detected
        if (sensorTimer.read_ms()-lastTriggerTime>TIME_TIL_SPEED_RESET){ //if the system goes too long with out sensor input set speed to zero
            for (int i=0; i<NUMBER_OF_AVGS; i++) { 
                storeSpeed[i]=0;
            }
        }
    }

}

//get the values from the speed array and average them
float readSpeed(){
    float totalSpeed=0;
    for (int i=0; i<NUMBER_OF_AVGS; i++) {
        totalSpeed += storeSpeed[i];
    }
    return  totalSpeed/NUMBER_OF_AVGS;
}

//=====[Implementations of private functions]==================================

//fsm to debounce sensor input
static bool debounceReedInput(){
    bool sensorFallingEvent = false;
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
                sensorFallingEvent = true;
            } else {
                reedState = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return sensorFallingEvent;
}
