//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"
#include "display.h"
#include "brake_light.h"
#include "speed_sensor.h"
#include "turn_signal.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut turnsignalL(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static void displaySystemInit();

static void displayUpdate();
static void turnSignalUpdate();

//=====[Implementations of public functions]===================================

void smartbikesystemInit(){
    turnSignalInit();
    displayInit();
}

void smartbikesystemUpdate(){
    displayUpdate();
    
    delay(10);
}

//=====[Implementations of private functions]==================================
static void turnSignalUpdate(){

}

static void displaySystemInit(){

}

static void displayUpdate(){

}