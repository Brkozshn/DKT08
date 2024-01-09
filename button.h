/******************** (C) COPYRIGHT 2019 ORION EE ********************************
* File Name          : button.h
* Author             : Onur Kayýkcý
* Version            : V1.0
* Date               : 09/08/2019
* Description        : button header
********************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_



#ifndef BUTTON

#define BUTTON

#define BUTTON_MS I1_INPUT_MS

typedef struct button_s
{
    u8 LASTVALUE;
    u8 VALUE;
    u8 BUTTON_PRESSED_CONFIG;
    u8 BUTTON_RELEASED_CONFIG;
    u8 BUTTON_MASK;
    vu8 *BUTTON_PORT_IN;
} button_t;

/*Kullanýlan butonlarýn isimleri buraya yazýlýr, bu sayede otomatik olarak o kadar buton tanýmlanýr*/

enum
{
    NUM_OF_BUTTONS
};

// Enum For Internal fault

enum
{
    LOW = 0,
    HIGH
};



enum{
    LED_OFF = 0,
    LED_ON,
    LED_BLINK
};

/// Enum for all inputs. 

enum
{
    I1=0,
    I2,
    I3,
    I4,
    I5,
    I6,
    I7,
    I8,
    MUTE_BUTTON,
    RESET_BUTTON,
    TEST,
    ACK_BUTTON,

    NUM_OF_INPUT_POINT
};


// Enum for all cases.

enum
{
    Channel1=0,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
    Channel8,
    FAIL,
    
    NUM_OF_CASE
    
};

// enum for channel settings (Trip or alarm)

enum
{
    I1_Trip=0,
    I1_Alarm,
    I2_Trip,
    I2_Alarm,
    I3_Trip,
    I3_Alarm,
    I4_Trip,
    I4_Alarm,
    I5_Trip,
    I5_Alarm,
    I6_Trip,
    I6_Alarm,
    I7_Trip,
    I7_Alarm,
    I8_Trip,
    I8_Alarm,

    NUM_OF_CHANNEL
};



// enum for leds.

enum
{
    RED1_LED=0,
    Yellow1_LED,
    RED2_LED,
    Yellow2_LED,
    RED3_LED,
    Yellow3_LED,
    RED4_LED,
    Yellow4_LED,
    RED5_LED,
    Yellow5_LED,
    RED6_LED,
    Yellow6_LED,
    RED7_LED,
    Yellow7_LED,
    RED8_LED,
    Yellow8_LED,

    NUM_OF_LEDS
};


// Enum for button status

enum {
    PRESSED=0,
    RELEASED,
    AGAIN_PRESSED,
    AGAIN_RELEASED,
    STILL_PRESSED,
    STILL_RELEASED,
    UNKNOWN,
    BUTTON_STATUS_FAIL,

    NUM_OF_BUTTON_STATUS
};


// Enum for Mute Button

enum{
    TRIP_MODE = 0,
    ALARM_MODE,


    NUM_OF_MODE
};




#define BUTTON_READ_PIN(button_ptr) *(button_ptr->BUTTON_PORT_IN)


/* Kullanýlacak butonlarýn veya inputlarýn gerekli ayarlamalarý burada yapýlýr*/

#define I1_MASK                 I1_PIN
#define I1_PRESSED_CFG          0x00
#define I1_RELEASED_CFG         I1_PIN

#define I2_MASK                 I2_PIN
#define I2_PRESSED_CFG          0x00
#define I2_RELEASED_CFG         I2_PIN

#define I3_MASK                 I3_PIN
#define I3_PRESSED_CFG          0x00
#define I3_RELEASED_CFG         I3_PIN

#define I4_MASK                 I4_PIN
#define I4_PRESSED_CFG          0x00
#define I4_RELEASED_CFG         I4_PIN

#define I5_MASK                 I5_PIN
#define I5_PRESSED_CFG          0x00
#define I5_RELEASED_CFG         I5_PIN

#define I6_MASK                 I6_PIN
#define I6_PRESSED_CFG          0x00
#define I6_RELEASED_CFG         I6_PIN

#define I7_MASK                 I7_PIN
#define I7_PRESSED_CFG          0x00
#define I7_RELEASED_CFG         I7_PIN

#define I8_MASK                 I8_PIN
#define I8_PRESSED_CFG          0x00
#define I8_RELEASED_CFG         I8_PIN

#define MUTE_BUTTON_MASK                       MUTE_BUTTON_PIN
#define MUTE_BUTTON_PRESSED_CFG                MUTE_BUTTON_PIN
#define MUTE_BUTTON_RELEASED_CFG               0x00

#define RESET_MASK                      RESET_PIN
#define RESET_PRESSED_CFG               RESET_PIN
#define RESET_RELEASED_CFG              0x00

#define TEST_MASK                       TEST_PIN
#define TEST_PRESSED_CFG                TEST_PIN
#define TEST_RELEASED_CFG               0x00

#define ACK_BUTTON_MASK                       ACK_BUTTON_PIN
#define ACK_BUTTON_PRESSED_CFG                ACK_BUTTON_PIN
#define ACK_BUTTON_RELEASED_CFG               0x00


#define LED_PIN_MASK                    0x3F


extern u8 Button_State_Func(button_t *button_ptr);


extern button_t input_check_point[NUM_OF_INPUT_POINT];
extern u8 LED_flag[NUM_OF_LEDS];
extern u8 mute_button_flag;
extern u8 ack_button_flag;
extern u8 test_button_flag;
extern u8 reset_button_flag;
//extern u8 channel_flag[NUM_OF_CHANNEL];            /// Flag for channel set (Trip or Alarm).
extern u8 caseFlag[NUM_OF_CASE];                   /// Flag for cases.



#endif /*BUTTON */

#endif /* BUTTON_H_ */
