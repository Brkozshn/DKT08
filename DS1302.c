/*
 * DS1302.h
 *
 *  Created on: Apr 10, 2023
 *      Author: umut.kaya
 */

#include "DS1302.h"



u8 x;
u8 i;
u8 j;


//void write_byte(u8 value)
//{
//    RTC_SDA_PIN_DIR |= RTC_SDA_PIN_BIT;
//    for (i=0;i<8;i++){
//        x = (value & (1 << i));  //Write to Address
//        send_bit(x);
//        SCLK_Pulse();
//    }
//}
//u8 read_byte(u8 addr)
//{
//
//    u8 temp = 0;
//    write_byte(addr);
//    RTC_SDA_PIN_OUT &= ~RTC_SDA_PIN_BIT;
//    RTC_SDA_PIN_DIR &= ~RTC_SDA_PIN_BIT;
//    for (j=0;j<8;j++){
//        temp >>= 1;
//        if (RTC_SDA_PIN_IN & RTC_SDA_PIN_BIT){
//            temp |= 0b10000000;
//       }
//       else {
//           temp  &= 0b01111111;
//       }
//
//    SCLK_Pulse();
//    }
//    return temp;
//}
//time_ds_t read_time (void)
//{
//    time_ds_t time;
//    time.year = read_year();
//    time.month = read_month();
//    time.date = read_date();
//    time.hour = read_hour();
//    time.min = read_min();
//    time.sec = read_sec();
//    return time;
//}
//
//void SCLK_Pulse (void)
//{
//  RTC_SCL_PIN_OUT |= RTC_SCL_PIN_BIT;
//  RTC_SCL_PIN_OUT &= ~RTC_SCL_PIN_BIT;
//}
//
//void send_bit (u8 value)
//{
//    if (value != 0){
//        RTC_SDA_PIN_OUT |= RTC_SDA_PIN_BIT;}
//    else {
//        RTC_SDA_PIN_OUT &= ~RTC_SDA_PIN_BIT;
//    }
//}

void CE_On (void)
{
//    RTC_EN_PIN_OUT |= RTC_EN_PIN_BIT;
}

void CE_Off (void)
{
//    RTC_EN_PIN_OUT &= ~RTC_EN_PIN_BIT;
}

u8 read_sec(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_SEC);
    CE_Off();
    return (tmp>>4 & 0x07)*10 + (tmp & 0x0F);
}
u8 read_min(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_MIN);
    CE_Off();
    return (tmp>>4 & 0x07)*10 + (tmp & 0x0F);
}
u8 read_hour(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_HR);
    CE_Off();
    return (tmp>>4 & 0x03)*10 + (tmp & 0x0F);
}
u8 read_date(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_DATE);
    CE_Off();
    return (tmp>>4 & 0x03)*10 + (tmp & 0x0F);
}
u8 read_month(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_MON);
    CE_Off();
    return (tmp>>4 & 0x01)*10 + (tmp & 0x0F);
}
u8 read_year(){
    CE_On();
    u8 tmp = read_byte(ADR_RD_YR);
    CE_Off();
    return ((tmp>>4 & 0x0F)*10) + (tmp & 0x0F);
}


void set_RTC(u8 date, u8 month, u8 year, u8 hour, u8 min, u8 sec){
//    CE_On();
//    write_byte(ADR_WR_CREG);  //goto control register
//    write_byte(0x00);         //disable write protect
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_SEC);  //Go to seconds register
//    write_byte(((u8)(sec/10)<<4) + (sec % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_MIN);  //Go to minute register
//    write_byte(((u8)(min/10)<<4) + (min % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_HR);  //Go to hour register
//    write_byte(((u8)(hour/10)<<4) + (hour % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_DATE);  //Go to date register
//    write_byte(((u8)(date/10)<<4) + (date % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_MON);  //Go to month register
//    write_byte(((u8)(month/10)<<4) + (month % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_YR);  //Go to year register
//    write_byte(((u8)(year/10)<<4) + (year % 10));  //set as..
//    CE_Off();
//    CE_On();
//    write_byte(ADR_WR_CREG);  //goto control register
//    write_byte(0xFF);         //disable write protect
//    CE_Off();
}
