/******************** (C) COPYRIGHT 2014 ORION EE ********************************
* File Name          : timeout.h
* Author             : Sercan Tunçay
* Version            : V1.0
* Date               : 01/10/2014
* Description        : timeouts
********************************************************************************/
#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "main.h" //u32 ler için

#define OneSecond_Time 72
#define Alarm_Blink_Time   (OneSecond_Time*5)         // 5 seconds
#define CASE_Time  (OneSecond_Time/2)                 // 0,5 seconds
#define TEST_HORN_Time  (OneSecond_Time*3)            // 3 seconds
#define ACK_Save_Time  (OneSecond_Time*5)             // 5 seconds
#define Channel_Select_Time (OneSecond_Time*600)       // 60 seconds
#define FRAM_Time    (OneSecond_Time*6)               // 6 seconds
#define Button_Press_Time  (OneSecond_Time)         // 1  milliseconds



/* TIMEOUT */
typedef struct timeout_file_s
{
    u8 timeout_activated;
    u8 timeout_status;
//  u32 start_time;  //start-finish ram yetmezliðinden kapandý þimdilik
//  u32 finish_time;
    u32 countdown;

}timeout_file_t;



enum
{
    TO_IDLE =0,
    TO_LOADED,
    TO_COUNTING_DOWN,
    TO_OCCURED
};



enum
{
    I1_TO=0,
    TEST_HORN_TIMEOUT,
    Channel_Select_TIMEOUT,
    Alarm_Blink_TIMEOUT,
    Trip_Blink_TIMEOUT,
    ACK_Save_TIMEOUT,
    CASE_TIMEOUT,
    LED_BLINK_TO,
    FRAM_TIMEOUT,
    BUTTON_TIMEOUT,
   /* I2_TO,
    I3_TO,
    I4_TO,
    I5_TO,
    I6_TO,
    MUTE_TO,
    RESET_TO,
    TEST_TO,
    TRIPPING_TO,*/
    NUM_OF_TIMEOUTS
};



#define I1_INPUT_MS 1
#define I2_INPUT_MS 1
#define I3_INPUT_MS 1
#define I4_INPUT_MS 1
#define I5_INPUT_MS 1
#define I6_INPUT_MS 1
#define MUTE_INPUT_MS  1
#define RESET_INPUT_MS 1
#define TEST_INPUT_MS  1
#define TRIPPING_INPUT_MS  1



extern timeout_file_t timeouts[];

extern void process_timeouts();
extern void start_timeout_ms(u8 to_no, u32 to_val_ms);
extern u32 check_timeout(u8 to_no);
extern u32 get_time_ms();
extern u32 calc_time_diff_ms(u32 prev_time);



#endif /*TIMEOUT_H_*/
