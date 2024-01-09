/******************** (C) COPYRIGHT 2021 ORION EE ********************************
* File Name          : main.h
* Author             : ONUR KAYIKCI
* Version            : V1.0.0
* Date               : 21/01/2021
* Description        : main header
********************************************************************************/
#ifndef MAIN_H_
#define MAIN_H_

#include <msp430.h>



#define BUZZER_MAX_RUN_TIME 350000



typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed short int s16;
typedef signed long int s32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int vu32;

typedef volatile signed char vs8;
typedef volatile signed short int vs16;
typedef volatile signed long int vs32;


#define ENABLE  1
#define DISABLE 0

#define TRUE    1
#define FALSE   0


typedef struct system_status_s
{
    u32 timer_tick;
    u32 timer_tick2;
    u32 timer_internal_fault;
    u16 Threshold_Control;
    u8 channelState;                      // Hangi case'de oldu?umuzu belirleyen de?i?ken.
    u8  Led_state_Transition;             // LED state'ler  aras?ndaki geçis degiskeni (100 ms)
    u8  channel_Select;                   // Channel select fonksiyonu için geçiþ deðiþleni
    u8 test_horn_started;                 // Controlling TEST and MUTE buttons are pressed for 3 seconds
    u8 Mute_state;                        // Selecting mode (Trip, Alarm)
}system_status_t;


system_status_t system_status;



extern void hardware_init(void);
extern void software_init(void);
extern void CheckSignalState();
extern void task_manager(void);
extern void buzzer_control();
extern void input_process(void);
extern void All_Relay_Close();
extern void Test_All_Relay();
extern void input_button_control();       // Controlling button inputs
extern void led_control();
extern void process_timeouts();
 
//extern void input_control_one_by_one(u8 input_name,u8 input_to);


extern void reset_pressed_flags();
extern void horn_pin_status(u8 status);
extern void buzzer_select_pin_status(u8 status);
extern void buzzer_alarm(u16 alarm_ms, u8 repeat_cnt);
extern void Trip_pin_status(u8 status);
//extern void LED_pin_status(u8 led_port,u8 led_pin, u8 status);
extern void channel_test();      // starting channel test


// Last added functions for channels.

extern void Channel_Set_mode();             // Entering channel setting mode. 
extern void Channel_Select();               // Selecting a channel to set 
extern void set_Channel_default();          // Setting all channels to alarm as default.          
extern void save_Channel_settings();        // Saving all channels settings
extern void Input_channel_disapp(u8 channel_num);   // If signal is suddenly disappeared inside the channel.
extern void output_reset();           // Reset all outputs.
extern void Release_horn_test();        // When these buttons are released go back to previous channel status (ALARM or HORN).  

/// Input control functions.

extern void Input_Channel1();
extern void Input_Channel2();
extern void Input_Channel3();
extern void Input_Channel4();
extern void Input_Channel5();
extern void Input_Channel6();
extern void Input_Channel7();
extern void Input_Channel8();





#endif /* MAIN_H_ */
