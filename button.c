/******************** (C) COPYRIGHT 2019 ORION EE ********************************
* File Name          : button.c
* Author             : Onur Kayýkcý
* Version            : V1.0
* Date               : 09/08/2019
* Description        : Get buttons state
********************************************************************************/


#include "main.h"
#include "stdint.h"
#include "bsp.h"
#include "button.h"
#include "timeout.h"



#ifdef BUTTON

button_t input_check_point[NUM_OF_INPUT_POINT];

//u8 channel_flag[NUM_OF_CHANNEL];            /// Flag for channel set (Trip or Alarm).

u8 caseFlag[NUM_OF_CASE];                   /// Flag for cases.

u8 LED_flag[NUM_OF_LEDS];
u8 mute_button_flag;
u8 test_button_flag;
u8 ack_button_flag;
u8 reset_button_flag;


u8 led_pins_PB;

u8 Button_State_Func(button_t *button_ptr)
{
    u8 button_status;

    if((BUTTON_READ_PIN(button_ptr) & button_ptr->BUTTON_MASK)==button_ptr->BUTTON_PRESSED_CONFIG)
        button_ptr->VALUE = PRESSED;
    else if((BUTTON_READ_PIN(button_ptr) & button_ptr->BUTTON_MASK)==button_ptr->BUTTON_RELEASED_CONFIG)
        button_ptr->VALUE = RELEASED;
    else{
        button_status=BUTTON_STATUS_FAIL;
        return button_status;
    }

    if((button_ptr->LASTVALUE == UNKNOWN)&&(button_ptr->VALUE == PRESSED))
        {
            button_status = PRESSED;
        }
    else if((button_ptr->LASTVALUE == UNKNOWN)&&(button_ptr->VALUE == RELEASED))
        {
            button_status = RELEASED;
        }
    else if((button_ptr->LASTVALUE == RELEASED)&&(button_ptr->VALUE == PRESSED))
        {
            button_status = AGAIN_PRESSED;
        }
    else if((button_ptr->LASTVALUE == PRESSED)&&(button_ptr->VALUE == RELEASED))
        {
            button_status = AGAIN_RELEASED;
        }
    else if((button_ptr->LASTVALUE == PRESSED)&&(button_ptr->VALUE == PRESSED))
        {
            button_status = STILL_PRESSED;
        }
    else if((button_ptr->LASTVALUE == RELEASED)&&(button_ptr->VALUE == RELEASED))
        {
            button_status = STILL_RELEASED;
        }


    button_ptr->LASTVALUE = button_ptr->VALUE;

    return button_status;
}

#endif /*BUTTON */

