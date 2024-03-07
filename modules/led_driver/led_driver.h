//=====[#include guards - begin]===============================================

#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void ledDriverInit();
void ledDriverUpdate();

void brakeLightOn();
void brakeLightOff();

void leftTurnSignalOn();
void rightTurnSignalOn();
void turnSignalsOff();
//=====[#include guards - end]=================================================

#endif // _LED_DRIVER_H_