/*
 * ram.c
 *
 *  Created on: 13 Haz 2019
 *      Author: MSIGE60
 */

#include <msp430.h>
#include "main.h"
#include "submain.h"
#include "bsp.h"
#include "cnc.h"
#include "timeout.h"
#include "ram.h"
#include "buffer.h"
#include "button.h"
#include "modbus.h"
#include "telemetry.h"



#pragma PERSISTENT(modbus_adress)
#pragma PERSISTENT(baudrate_A0)
#pragma PERSISTENT(baudrate_A1)

#pragma LOCATION(modbus_adress, 0x8160)
#pragma LOCATION(baudrate_A0, 0x815E)
#pragma LOCATION(baudrate_A1, 0x815F)



u8 modbus_adress = 1;

u8 baudrate_A0 = UCA0_BAUDRATE;
u8 baudrate_A1 = UCA1_BAUDRATE;


system_status_t system_status;
buffer_t uart_rx_buffer;
button_t button[NUM_OF_BUTTONS];
adc_buffer_t adc_buffer[NUM_OF_ADC_PORTS];

NODE * tmp_config = NULL;
NODE * last_config_menu_index = NULL;
NODE * root_config_menu_index = NULL;


// UNKNOWN

modbus_in_msg_t      modbus_in_msg;
modbus_out_msg_t     modbus_out_msg;
modbus_out_error_msg_t  modbus_out_error_msg;
modbus_in_write_msg_t modbus_in_write_msg;
modbus_out_write_msg_t modbus_out_write_msg;
modbus_protocol_t    modbus_protocol_file;


