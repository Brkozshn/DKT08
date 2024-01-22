/*
 * DS1302.h
 *
 *  Created on: Apr 10, 2023
 *      Author: umut.kaya
 */

#ifndef DS1302_H_
#define DS1302_H_

#include <msp430.h>
#include <time.h>
#include "bsp.h"
#include "main.h"


#define  ADR_WR_CREG    0x8E  //Control Register Write
#define  ADR_RD_CREG    0x8F  //Control Register Read
#define  ADR_WR_TCR     0x90  //Trickle Charge Register Write
#define  ADR_RD_TCR     0x91  //Trickle Charge Register Read
#define  ADR_WR_BURST   0xBE  //Burst Write
#define  ADR_RD_BURST   0xBF  //Burst Read

#define  ADR_WR_SEC    0x80  //Seconds Write
#define  ADR_RD_SEC    0x81  //Seconds Read
#define  ADR_WR_MIN    0x82  //Mins Write
#define  ADR_RD_MIN    0x83  //...
#define  ADR_WR_HR    0x84
#define  ADR_RD_HR    0x85
#define  ADR_WR_DATE    0x86
#define  ADR_RD_DATE    0x87
#define  ADR_WR_MON    0x88
#define  ADR_RD_MON    0x89
#define  ADR_WR_DAY    0x8A
#define  ADR_RD_DAY    0x8B
#define  ADR_WR_YR    0x8C
#define  ADR_RD_YR    0x8D

enum {
    SEC_REG = ADR_WR_SEC,
    MIN_REG = ADR_WR_MIN,
    HR_REG = ADR_WR_HR,
    DATE_REG = ADR_WR_DATE,
    MON_REG = ADR_WR_MON,
    YR_REG = ADR_WR_YR,
};

void SCLK_Pulse (void);  //To create a clock pulse high low
void send_bit (u8 value);     //For sending 1 or zero
void CE_On (void);  //Chip enable
void CE_Off (void);  //Chip disable
void write_byte (u8 value);
u8 read_byte (u8 addr);

//
extern void set_RTC(u8 date, u8 month, u8 year, u8 hour, u8 min, u8 sec);
extern void set_any_time_val(u8 addr_reg, u8 value);
extern time_ds_t read_time(void);
//

extern u8 read_sec();
extern u8 read_min();
extern u8 read_hour();
extern u8 read_date();
extern u8 read_month();
extern u8 read_day();
extern u8 read_year();

#endif /* DS1302_H_ */
