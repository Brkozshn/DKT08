/*
 * fram.h
 *
 *  Created on: 15 Eyl 2023
 *      Author: burak.ozsahin
 */

#ifndef FRAM_H_
#define FRAM_H_

#include "main.h"

extern u8 channel_flag[NUM_OF_CHANNEL];            /// Flag for channel set (Trip or Alarm).
extern u32 system_Run_number;                /// Number of times to system runs


extern void Fram_Channel_flag(u8 channel, u8 status_HORN);      // Mode Changes function and write into Fram
//extern void set_Channel_default();                              // Default channel modes


#endif /* FRAM_H_ */
