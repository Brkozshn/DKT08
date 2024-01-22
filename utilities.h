/******************** (C) COPYRIGHT 2020 ORION EE ********************************
* File Name          : utilities.h
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 18/03/2020
* Description        : utilities.h
********************************************************************************/


#ifndef UTILITIES_H_
#define UTILITIES_H_


#include "main.h"

extern u8 generate_crc(u8 *data_ptr, u32 len);

//extern void delay_ms(u16 milliseconds);
extern void delay_ms_raw(u32 ms);

extern void CopyArray(u8 *source, u8 *dest, u8 count);

extern void delay_ms_raw(u32 ms);

extern u8 generate_crc(u8 *data_ptr, u32 len);

extern NODE * CreateNode(NODE * previous,char* str);

extern NODE_FOR_CONFIG * CreateNode_For_Config(NODE_FOR_CONFIG * previous,
                                               char* str,
                                               u16 min_value,
                                               u16 max_value,
                                               u16 rate_value);

#endif /* UTILITIES_H_ */
