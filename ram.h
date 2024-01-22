/*
 * ram.h
 *
 *  Created on: 13 Haz 2019
 *      Author: MSIGE60
 */
#ifndef RAM_H_
#define RAM_H_

#include <msp430.h>
#include "main.h"
#include "submain.h"
#include "bsp.h"
#include "cnc.h"
#include "timeout.h"
#include "buffer.h"
#include "button.h"
#include "modbus.h"
#include "telemetry.h"


extern u8 modbus_adress;

extern u8 baudrate_A0 ;
extern u8 baudrate_A1;

extern u8 system_second;
extern u8 system_minute;
extern u8 system_hour;
extern u8 system_day;
extern u8 system_month;
extern u16 system_year;


extern system_status_t system_status;
extern buffer_t uart_rx_buffer;
extern button_t button[NUM_OF_BUTTONS];
extern adc_buffer_t adc_buffer[NUM_OF_ADC_PORTS];



extern modbus_in_msg_t      modbus_in_msg;
extern modbus_out_msg_t     modbus_out_msg;
extern modbus_out_error_msg_t  modbus_out_error_msg;
extern modbus_in_write_msg_t modbus_in_write_msg;
extern modbus_out_write_msg_t modbus_out_write_msg;
extern modbus_protocol_t    modbus_protocol_file;


#endif /* RAM_H_ */
