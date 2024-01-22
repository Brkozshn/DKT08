/******************** (C) COPYRIGHT 2014 ORION EE ********************************
* File Name          : cnc.h
* Author             : Sercan Tun�ay
* Version            : V1.0
* Date               : 01/10/2014
* Description        : control and configuration definitions file
********************************************************************************/
#ifndef CNC_H_
#define CNC_H_

/************************
*   CONSTANTS AREA
*************************/
#define RESET_FUNC_NUM 1
#define  NUM_OF_CONFIG_VALUE 120

#define TM_START_DELAY_MS   2000
#define TM_PERIOD_MS            1000

#define MS_TO_ANGEL   18 // 1ms

#define FRAM_START_ADDR 0x7C00

#define PI_NUMBER   3.14285

#define NOMINAL_CURRENT             5       //Amper

#define PHASE_CURRENT_MIN           50      //Amper
#define PHASE_CURRENT_MAX           600     //Amper
#define PHASE_CURRENT_RATE          50      //Amper

#define PHASE_DETECTION_TIME_MIN    40      //milisecond
#define PHASE_DETECTION_TIME_MAX    520     //milisecond
#define PHASE_DETECTION_TIME_RATE   40      //milisecond

#define EARTH_CURRENT_MIN           20      //Amper
#define EARTH_CURRENT_MAX           300     //Amper
#define EARTH_CURRENT_RATE          20      //Amper

#define EARTH_DETECTION_TIME_MIN    40      //milisecond
#define EARTH_DETECTION_TIME_MAX    520     //milisecond
#define EARTH_DETECTION_TIME_RATE   40      //milisecond

#define AUTO_RESET_TIME_MIN         0//0       //minute
#define AUTO_RESET_TIME_MAX         1440    //minute
#define AUTO_RESET_TIME_RATE        1       //minute

#define DIGITAL_RESET_TIME_MIN    0//0       //second
#define DIGITAL_RESET_TIME_MAX    99      //second
#define DIGITAL_RESET_TIME_RATE   1       //second

#define RELAY1_SETTING_MIN    0//0       //
#define RELAY1_SETTING_MAX    1      //
#define RELAY1_SETTING_RATE   1       //

#define RELAY2_SETTING_MIN    0//0       //
#define RELAY2_SETTING_MAX    1      //
#define RELAY2_SETTING_RATE   1       //

#define PHASE_FREQ_MIN    50//0       //
#define PHASE_FREQ_MAX    60      //
#define PHASE_FREQ_RATE   10       //


#define AFTER_RESET_TIME   1000//ms

#define FIRST_2_HOURS   2000//ms
#define _2_to_3_HOURS   3000//ms
#define _3_to_4_HOURS   4000//ms
#define AFTER_4_HOURS   5000//ms

#define _1_HOURS   3600000//ms
#define _2_HOURS   2*_1_HOURS//ms
#define _3_HOURS   3*_1_HOURS//ms
#define _4_HOURS   4*_1_HOURS//ms


#define MEAN_M    0.6833
#define MEAN_N    2.6208

#define ADC_I_TH    2048    // ak�m�n adc'ye �evrilmi� halini kontrol eden threshold de�eri
#define T_WAIT_MS     40    // thresholdu ge�tikten sonra beklenecek de�er milisaniye cinsinden
#define T_RESET_MS  3000    // thresholdu ge�tikten sonra resetlemek i�in gereken s�re

#define ENDING_ERROR_TIMER 3000

//
#define INITIAL 0
//

#define SAMPLE_BUFFER_LEN 16
#define ADC_SAMPLE_BUFFER_LEN 16

#define MAX_SAMPLE_NUMBER 16
#define MAX_REPORT_NUMBER 20

#define ADC_TO_AMPER 1//0.61 // 2.5V*1000(amper �evirme oran�)/4096
#define KILO (u32)1024
#define ADC_RESOLUTION (u32)(KILO-1) // 10 bits -> 2^10
#define VOLTAGE_mv_TO_ADCREG_VALUE(voltage_mv)  (u32)((u32)(voltage_mv*ADC_RESOLUTION)/(u32)(VCC_mv*DIVISION_RATIO))

/************************
*   USER_DEFINITIONS AREA 
*************************/

#define DISPLAY_INIT_VAL	88.8

// NVM Config
#define FLASH_DEFAULT_CONFIG1_VAL	20
#define FLASH_DEFAULT_CONFIG2_VAL	60
#define  FLASH_SIGN 50

#define SENSOR_MEASURE_PERIOD	3000  //ms
#define SENSOR_INIT_DELAY	    2000//3000 //ms
#define SCREEN_LOOP_DELAY       3500
#define LED_ERROR_LOOP_DELAY    200

#define LCD_OFF_TIMER   30000
#define LCD_BACK_TO_RESULTS_TIMER   300000
#define UPDATE_LCD_TIMER 750
#define RESET_AFTER_NORMAL_VALUE_TIMER 3000
#define LCD_CLEAR_TIMER 20
#define TIM_TIMER 15000
#define TEST_TIMER 3000
#define INFORMATION_TIMER 2000

// Application config



// Timing Config
#define MODE_CHANGE_VAL			100 // *10 = ms  // hold down time to get into config mode
#define MODE_TIMEOUT_VAL		5000 // *10 = ms	//  the time to return normal mode in case of no operation (no push button)
#define CONFIG_BLINK_DELAY	500	// ms

#define TEMP_COMPENSATION_VAL					-3.4//-2
#define TEMP_COMPENSATION_SETTLE_TIME	3600000 // 1800sn, 1.800.000 ms, 30dk
#define TEMP_COMP_COEFF								((float)TEMP_COMPENSATION_VAL/TEMP_COMPENSATION_SETTLE_TIME)

#define RELAY_TEMP_COMPENSATION_VAL					((float)-1.3)
#define RELAY_TEMP_COMPENSATION_SETTLE_TIME 1800000
#define RELAY_TEMP_COMP_COEFF								((float)RELAY_TEMP_COMPENSATION_VAL/RELAY_TEMP_COMPENSATION_SETTLE_TIME)

#define HUMIDITY_CALIBRATION_VAL						2.0
#define TEMPERATURE_CALIBRATION_VAL 				0.0

//#define HUMID_CLB_PERIOD_MS			600000//second
//#define HUMID_CLB_WARMUP_TIME	 	240000//second

#define TM_START_DELAY_MS	2000
#define TM_PERIOD_MS			1000

#define EXTR_VREF 1200 //mV
#define MAX_ADC_VALUE 4095
#define ADC_BIT_RES 12
#define ADC_VREF 2500
#define VREF_ADC_VALUE 1966//(float)(EXTR_VREF*MAX_ADC_VALUE/ADC_VREF) //3276





#define NUM_OF_ADC_PORTS 5
#define NUM_OF_ADC_SAMPLES 128


/************************
*   USER_DEFINITIONS END 
*************************/

#endif /*CNC_H_*/
