/******************** (C) COPYRIGHT 2023 ORION EE ********************************
* File Name          : led.h
* Author             : Burak Ozsahin
* Version            : V1.0.0
* Date               : 05/12/2023
* Description        : led header
********************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "fram.h"

static u8 NUM_LEDS = 8;               // Number of leds to use
static u16 blinkDuration = 1000;
static u32 ERROR_THRESHOLD_TIME = 1000;     // Replace with your desired threshold time (in milliseconds).
static u16 ledBetween_Duration = 500;


// Checking the signal functions

extern void TriggerInternalFault();
extern void CheckSignalState();


// LED Driver functions  ///

extern void LP5860_ClearAllLEDs();
extern void ledsBlink(u8 channelNumber);
extern void ledsPassive(u8 channelNumber);
extern void ledsActive(u8 channelNumber);
//extern void LP5860_BlinkLED(u8 ledNumber, u16 blinkDuration);
extern void LP5860_OpenAllLEDs();                                   // Opening all leds



#endif /* LED_H_ */
