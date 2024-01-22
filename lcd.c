/******************** (C) COPYRIGHT 2020 ORION EE ********************************
* File Name          : lcd.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 11/03/2020
* Description        : lcd functions
********************************************************************************/

#include <msp430.h>
#include "lcd.h"
#include "bsp.h"
#include "main.h"
#include "ram.h"

unsigned int i;
unsigned int j;


void delay(unsigned int k)
{
    for(j=0;j<=k;j++)
    {
        for(i=0; i < 125 ; i++);
    }
}

void delay_us(unsigned int k)
{
    for(j=0;j<=k;j++)
    {
        for(i=0; i < 5 ; i++);
    }
}



void lcd_init(void)
{

//lcd_pin_init();
//send_command(0x33);
//send_command(0x32);
//send_command(0x28); // 4 bit mode
////send_command(0x0E); // display on cursor on
//send_command(0x0C); // display on cursor off blink off
//send_command(0x01); // clear the screen
//send_command(0x06); // increment to right cursor
//send_command(0x80); // row 1 column 1
//delay_us(80);
}


