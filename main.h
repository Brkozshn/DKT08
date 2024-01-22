/*
 * main.h
 *
 *  Created on: 11 May 2022
 *      Author: onur.kayikci
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include <stdlib.h>
#include <msp430.h>


#define SOFTWARE_VERSION 10000
#define HARDWARE_VERSION 2355

#define _TIMER_VECTOR TIMER0_A0_VECTOR

#define CLEAR_INTERRUPTS    _BIC_SR(GIE)
#define RESTORE_INTERRUPTS  _BIS_SR(GIE)

typedef volatile unsigned char vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int vu32;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

#define TRUE    1
#define FALSE   0


#define INCREASE_WITH_LIMIT(val, limit) if(++val>limit) val = limit
#define DECREASE_WITH_LIMIT(val, limit) if(val>limit) val--

#define PREPARE_SETBIT_B(bit_no, set_val) (u8)(set_val ? 1<<bit_no : ~(1<<bit_no)  )
#define PREPARE_SETBIT_W(bit_no, set_val) (u32)(set_val ? 1<<bit_no : ~(1<<bit_no)  )

#define _SETBIT(bit_no) (u8)(bit_no)
#define _GETBIT(value, bit_no) (u8)((value & bit_no)==bit_no ? 1 : 0 )

#define EMPTY -1


enum{
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
};


enum
{
    DISPLAY_SLEEP_MODE,
    DISPLAY_RESULTS_MODE,
    DISPLAY_MAIN_MENU_MODE,
    DISPLAY_MEASUREMENTS_MENU_MODE,
    DISPLAY_FAULT_RESET_MENU_MODE,
    DISPLAY_FAULT_REPORT_MENU_MODE,
    DISPLAY_SETTINGS_MENU_MODE,
    DISPLAY_TEST_MENU_MODE,
    DISPLAY_INFO_MENU_MODE,
    DISPLAY_EXIT_INFORMATION,

    DISPLAY_LIST_REPORTS,
    DISPLAY_DELETE_REPORT,

    DISPLAY_REPORT,

    DISPLAY_REPORT_INFORMATION,

    DISPLAY_CONFIG_MENU_MODE,
    DISPLAY_DATE_MENU_MODE,
    DISPLAY_COMMUNICATION_MENU_MODE,
    DISPLAY_PASSWORD_MENU_MODE,

    DISPLAY_ENTER_PASSWORD_MODE,
    DISPLAY_REQUEST_OLD_PASSWORD_MODE,
    DISPLAY_REQUEST_NEW_PASSWORD_MODE,
    DISPLAY_PASSWORD_INFORMATION_MODE,
    
    DISPLAY_SAVED_MODE,
    DISPLAY_TEST_DONE_MODE,
    DISPLAY_TEST_TEST_MODE,

    DISPLAY_DATE_CONFIG_MENU_MODE,

    DISPLAY_NUM_OF_MODES,
};


enum{
    DISABLE = 0,
    ENABLE
};

enum{
    TOP = 0,
    BOTTOM
};



typedef struct NODE{
    //Dï¿½ï¿½ï¿½me ait veri.
    //Farklï¿½ tipte deï¿½iï¿½kenler burada tanï¿½mlanabilir.
    char* str;
    //Bir sonraki dï¿½ï¿½ï¿½mï¿½n adresi.
    struct NODE * next;
    //Bir ï¿½nceki dï¿½ï¿½ï¿½mï¿½n adresi.
    struct NODE * previous;
}NODE;


//ï¿½ift yï¿½nlï¿½ baï¿½lï¿½ liste dï¿½ï¿½ï¿½mï¿½.
typedef struct NODE_FOR_CONFIG{

//Dï¿½ï¿½ï¿½me ait veri.
//Farklï¿½ tipte deï¿½iï¿½kenler burada tanï¿½mlanabilir.
char* str;
//dï¿½ï¿½ï¿½mdeki min ve max deï¿½iï¿½ken
u8 min_value;
u8 max_value;
//deï¿½erlerin artï¿½ï¿½ azalï¿½ï¿½ miktarï¿½
u8 rate_value;

//ayarlanacak deï¿½er
u8 node_value;

//Bir sonraki dï¿½ï¿½ï¿½mï¿½n adresi.
struct NODE_FOR_CONFIG * next;
//Bir ï¿½nceki dï¿½ï¿½ï¿½mï¿½n adresi.
struct NODE_FOR_CONFIG * previous;
}NODE_FOR_CONFIG;

typedef struct{
    u8 year;
    u8 month;
    u8 date;
    u8 hour;
    u8 min;
    u8 sec;
}time_ds_t;

union {
  int data_int16;
  s16 data_s16;
  u16 data_u16;
  u8 data_u8[2];
  s8 data_s8[2];
} u_16byte;

union {
  u32 data_u32;
  s32 data_s32;
  float f;
  u16 data_u16[2];
  s16 data_s16[2];
  u8 data_u8[4];
  s8 data_s8[4];
} u_32byte;


typedef struct system_status_s
{

    /////// DKT08  ////////

    u32 timer_tick2;
    u32 timer_internal_fault;
    u16 Threshold_Control;
    u8 channelState;                      // Hangi case'de oldu?umuzu belirleyen de?i?ken.
    u8  Led_state_Transition;             // LED state'ler  aras?ndaki geçis degiskeni (100 ms)
    u8  channel_Select;                   // Channel select fonksiyonu için geçiþ deðiþleni
    u8 test_horn_started;                 // Controlling TEST and MUTE buttons are pressed for 3 seconds
    u8 Mute_state;                        // Selecting mode (Trip, Alarm)

    /////// DKT08 /////

    u32 timer_tick;
    u8 growing_factor;

    u8 repeat_cnter;

    char* system_program_vers;

    u16 phase_current_limit_value;
    u32 phase_detection_time_value;
    u16 earth_current_limit_value;
    u32 earth_detection_time_value;
    u32 auto_reset_time_value;
    u16 dreset_in_time_value;
    u8 relay1_setting;
    u8 relay2_setting;
    u8 phase_frequency;
    u8 password_flag;
    u8 password[4];
    u8 password_input[4];

    u8 relay1_fault_flag;
    u8 relay2_fault_flag;

    time_ds_t last_system_time;
    time_ds_t system_time;

    u8 system_language;

    u8 temp_system_second;
    u8 temp_system_minute;
    u8 temp_system_hour;
    u8 temp_system_day;
    u8 temp_system_month;
    u8 temp_system_year;

    u8 temp_address;
    u8 temp_baudrate;


    u16 button_up_low_cntr;
    u16 button_down_low_cntr;
    u16 button_enter_low_cntr;
    u16 button_esc_low_cntr;

    u16 button_low_timeout;
    u16 auto_increase_scaler;

    u8 button_state;

    u16 button_task_delay;


    u16 fault_signal_period;
    u16 fault_signal_state;

    u16 mode_counter;
    u16 mode_timeout;
    u8 display_mode;
    u8 display_last_mode;

    u8 main_menu_index;
    u8 fault_report_submenu_index;
    u8 list_report_index;
    u8 report_screen_index;
    u8 settings_menu_index;
    u8 date_menu_index;
    u8 comm_menu_index;
    u8 password_menu_index;
    u8 password_input_index;
    u8 test_menu_index;

    u8 test_menu_flag;

    u8 screen_freeze_flag;
    u8 sub_menu_lcd_cursor_pos;
    u8 main_menu_lcd_cursor_pos;

    u8 config_menu_lcd_cursor_pos;

    u8 Relay1_MODBUS_Control_Enable_Flag;
    u8 Relay2_MODBUS_Control_Enable_Flag;
    u8 Relay3_MODBUS_Control_Enable_Flag;
    u8 Relay4_MODBUS_Control_Enable_Flag;

    u8 last_relay_status_1;
    u8 last_relay_status_2;
    u8 last_relay_status_3;
    u8 last_relay_status_4;



    u8 update_alarm_flag ;

    u8 is_relay1_sw_active;
    u8 is_relay2_sw_active;
    u8 is_relay3_sw_active;
    u8 is_relay4_sw_active;
    u32 relay_temp_comp_st_time;
    u32 relay_switch_active_time;
    u32 relay_switch_deactive_time;
    float relay_temperature_compansation_value;
    float relay_temperature_compansation_diff;
    float relay_temp_comp_sample;
    u8 relay_cooling_started;
    u8 relay_warming_started;


    u8 com_error_flag;
    u8 Last_com_error_flag;

    u8 com_error_cnt1;
    u8 com_error_cnt2;
    u8 com_error_cnt3;
    u8 com_error_flag2;
    u8 Last_com_error_flag2;
    u8 com_error_flag3;
    u8 Last_com_error_flag3;

      u8 orteq_protocol_state;

      u8 orteq_protocol_curr_msg_len;
      u8 orteq_protocol_curr_rx_cnt;
      u8 orteq_protocol_expcted_packet_no;
      u8 orteq_protocol_curr_tx_no;

      u32 orteq_session_timeout_ms;
      u32 orteq_session_start_time;

      u8 orteq_protocol_msg_no_err;
      u8 orteq_protocol_crc_err;
      u8 orteq_protocol_func_no_err;
      u8 orteq_protocol_header1_err;
      u8 orteq_protocol_header2_err;
      u16 orteq_protocol_rx_msg_cnt;
      u16 orteq_protocol_tx_msg_cnt;

      u8  uart_tx_state;
      u8  uart_tx_busy_A0;
      u8  uart_tx_busy_A1;
      u8  uart_tx_index;
      u8  *uart_frame_ptr;
      u32 uart_tx_len;
      u8  uart_tx_busy_err;

      u8  modbus_tx_state;
      u8  modbus_tx_busy;
      u8  modbus_tx_index;
      u8  *modbus_frame_ptr;
      u32 modbus_tx_len;
      u8  modbus_tx_busy_err;

      u8  modbus_tx_error_state;

      u8  modbus_tx_flag;

      u8  modbus_rx_write_index;
      //MODBUS

      u8 modbus_protocol_state;

    u8 modbus_protocol_curr_msg_len;
    u8 modbus_protocol_curr_rx_cnt;
    u8 modbus_protocol_expcted_packet_no;
    u8 modbus_protocol_curr_tx_no;

    u32 modbus_session_timeout_ms;
    u32 modbus_session_start_time;

    u8 modbus_protocol_address_err;
    u8 modbus_protocol_func_no_err;
    u8 modbus_protocol_order_no_err;
    u8 modbus_protocol_crc_err;

    u16 modbus_protocol_rx_msg_cnt;
    u16 modbus_protocol_tx_msg_cnt;



      //OPTION VALUES
      u8 before_option_mode_counter;

      u8 option_mode_counter;
      int choose_mode_counter;

      u8 option_offset_counter;
      u8 option_max_counter_number;

      //YAZILIM VERSIYONUNUN GORULMESI
      u8 P9v;

      //FABRIKA AYARLARINA DONME
      u8 dEF; // 57 olarak ayarlanï¿½rsa fabrika ayarlarï¿½na dï¿½ner, diï¿½er deï¿½erlerde etkisi yoktur



      u8 com_error_alarm_flag_cntrl;

      // operating system

      u32 telemetry_period_ms;

      u8 reset_func_flag;

      u32 adc_time_ms;

      //hatlarï¿½n faz sï¿½rasï¿½
      u8 sensor_1_row;
      u8 sensor_2_row;
      u8 sensor_3_row;

      u32 L1_L2_time_ms;
      u32 L3_L2_time_ms;


      u32 L1_L2_Angle;
      u32 L3_L2_Angle;

      u32 r1;
      u32 r2;
      u32 r3;
      u32 r4;

      u32 earth_angle;
      u8 system_battery_active_flag;
      u8 battery_low_flag;
        u8 system_active_flag;
        u8 lcd_flag;
        u8 last_lcd_flag;
        u8 report_information_index;
        u8 password_information_index;
        u8 info_index;

}system_status_t;


system_status_t system_status;


extern void system_deFAULT_Larameters();
extern void taskManager(void);
extern void Software_Trim();
extern void initHardware(void);
extern void initSoftware();



////////// DKT08  //////////



#define DKT08

#ifdef DKT08

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

#endif /*DKT08*/



#endif /* MAIN_H_ */
