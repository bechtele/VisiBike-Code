//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"
#include "display.h"
#include "brake_light.h"
#include "speed_sensor.h"
#include "turn_signal.h"
#include "user_interface.h"
#include "user_interface/user_interface.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============



//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

void smartbikesystemInit(){
    displayInit();
    turnSignalInit();
    userInterfaceInit();
    speedSensorInit();
    ledDriverInit();
    brakeLightInit();
}

void smartbikesystemUpdate(){
    userInterfaceUpdate();
    turnSignalUpdate();
    speedSensorUpdate();
    ledDriverUpdate();
    
    //shittyBrakeLightDisplay();
 }

//=====[Implementations of private functions]==================================




