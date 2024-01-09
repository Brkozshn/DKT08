/******************** (C) COPYRIGHT 2021 ORION EE ********************************
* File Name          : utilities.c
* Author             : ONUR KAYIKCI
* Version            : V1.0.0
* Date               : 17/02/2021
* Description        : utilities file
********************************************************************************/


#include "main.h"
#include "timeout.h"
#include "utilities.h"



void delay_ms(u16 milliseconds) 
{
    // Assuming a 8 MHz instruction frequency
    // Adjust this value based on your actual frequency
    const u16 FREQ_FACTOR = 8;  // Modify this based on your clock frequency
    u16 i = 0;

    // Each NOP takes about 1 µs
    // Assuming FREQ_FACTOR is set correctly for the actual frequency
    for ( i = 0; i < (milliseconds * FREQ_FACTOR); ++i) {
        __asm__("nop");
    }
}


