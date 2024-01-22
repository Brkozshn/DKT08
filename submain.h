/*
 * submain.h
 *
 *  Created on: 5 Eyl 2022
 *      Author: onur.kayikci
 */

#ifndef SUBMAIN_H_
#define SUBMAIN_H_

#include "cnc.h"
#include "main.h"

#define REPORT_ELEMENT_SIZE 15


/// DKT08 Submain.c Functions /////


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
//extern void set_Channel_default();          // Setting all channels to alarm as default.
extern void save_Channel_settings();        // Saving all channels settings
//extern void Input_channel_disapp(u8 channel_num);   // If signal is suddenly disappeared inside the channel.
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



/// End of DKT08 Submain.c Functions /////


#endif /* SUBMAIN_H_ */
