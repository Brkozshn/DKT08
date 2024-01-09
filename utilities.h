/******************** (C) COPYRIGHT 2021 ORION EE ********************************
* File Name          : utilities.h
* Author             : ONUR KAYIKCI
* Version            : V1.0.0
* Date               : 17/02/2021
* Description        : utilities header file
********************************************************************************/

#ifndef UTILITIES_H_
#define UTILITIES_H_


#include "main.h"

extern u8 generate_crc(u8 *data_ptr, u32 len);

extern void delay_ms(u16 milliseconds);
extern void delay_ms_raw(u32 ms);

#endif /* UTILITIES_H_ */
