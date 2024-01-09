/******************** (C) COPYRIGHT 2021 ORION EE ********************************
* File Name          : main.c
* Author             : Burak Ozsahin
* Version            : V1.0
* Date               : 04/12/2023
* Description        : main functions
********************************************************************************/

#include <msp430.h>
#include "bsp.h"
#include "main.h"
#include "button.h"
#include "fram.h"
#include "led.h"



int main(void)
{
    hardware_init();
    software_init();

    __delay_cycles(1000000);


    task_manager();


    __bis_SR_register(GIE);       // Enter LPM0, enable interrupts


    return 0;
}

