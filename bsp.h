/******************** (C) COPYRIGHT 2020 ORION EE ********************************
* File Name          : bsp.h
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 18/03/2020
* Description        : bsp.h
********************************************************************************/


#include "define.h" //gerekli fonksiyonlarï¿½ ï¿½alï¿½ï¿½tï¿½rmak diï¿½erlerini kapatmak iï¿½in

#include "main.h"

#ifndef HEADERS_BSP_H_
#define HEADERS_BSP_H_

#define PROGRAM_VERS    "v1.4"

#define MCLK_FREQ_MHZ 16
#define CPU_CLK     16000000 //Hz
//#define MCLK_FREQ_MHZ 8
//#define CPU_CLK     8000000 //Hz
#define TIMER_CLK CPU_CLK/4 //  /4 ID_2 TACCRv ayarï¿½ndan gelecek
#define TIMERB_CLK CPU_CLK //  /4 ID_2 TACCRv ayarï¿½ndan gelecek
#define TIMER_FREQ  1000 //Hz  : kullanï¿½cï¿½ ayarï¿½            // en fazla 9009 Hz ile 20 ms'de 36 ï¿½rnek alarak
#define TIMERB_FREQ  19200 //Hz  : kullanï¿½cï¿½ ayarï¿½

////////UART PINS//////////
#define UART1_RX_PIN  BIT5  //P2.5
#define UART1_TX_PIN  BIT6  //P2.6
#define UART1_SEL_0   P2SEL0
#define UART1_SEL_1   P2SEL1

#define UART0_RX_PIN  BIT1  //P5.1
#define UART0_TX_PIN  BIT2  //P5.2
#define UART0_SEL_0   P5SEL0
#define UART0_SEL_1   P5SEL1



/////////// INPUTs  /////////


///////// DKT 08    ///////////

#define DKT08

#ifdef DKT08


/* Port Name    :   P2.2
 * Pin Number   :   16
 * Net Name     :   ACK
 */

#define ACK_BUTTON_PIN    BIT2
#define ACK_BUTTON_PORT   P2OUT
#define ACK_BUTTON_IN     P2IN
#define ACK_BUTTON_DIR    P2DIR
#define ACK_BUTTON_REN    P2REN

//// HORN butonunun hangi pin oldugu sorulacak.


/* Port Name    :   P1.1
 * Pin Number   :   13
 * Net Name     :   Mute
 */

#define MUTE_BUTTON_PIN    BIT1
#define MUTE_BUTTON_PORT   P1OUT
#define MUTE_BUTTON_IN     P1IN
#define MUTE_BUTTON_DIR    P1DIR
#define MUTE_BUTTON_REN    P1REN


/* Port Name    :   P1.2
 * Pin Number   :   14
 * Net Name     :   Reset
 */

#define RESET_PIN    BIT2
#define RESET_PORT   P1OUT
#define RESET_IN     P1IN
#define RESET_DIR    P1DIR
#define RESET_REN    P1REN


/* Port Name    :   P1.3
 * Pin Number   :   15
 * Net Name     :   Test
 */
#define TEST_PIN    BIT3
#define TEST_PORT   P1OUT
#define TEST_IN     P1IN
#define TEST_DIR    P1DIR
#define TEST_REN    P1REN


/* Port Name    :   P6.1
 * Pin Number   :   40
 * Net Name     :   I1
 */
#define I1_PIN    BIT1
#define I1_PORT   P6OUT
#define I1_IN     P6IN
#define I1_DIR    P6DIR
#define I1_REN    P6REN


/* Port Name    :   P6.2
 * Pin Number   :   41
 * Net Name     :   I2
 */
#define I2_PIN    BIT2
#define I2_PORT   P6OUT
#define I2_IN     P6IN
#define I2_DIR    P6DIR
#define I2_REN    P6REN


/* Port Name    :   P4.7
 * Pin Number   :   42
 * Net Name     :   I3
 */
#define I3_PIN    BIT7
#define I3_PORT   P4OUT
#define I3_IN     P4IN
#define I3_DIR    P4DIR
#define I3_REN    P4REN


/* Port Name    :   P5.0
 * Pin Number   :   43
 * Net Name     :   I4
 */
#define I4_PIN    BIT0
#define I4_PORT   P5OUT
#define I4_IN     P5IN
#define I4_DIR    P5DIR
#define I4_REN    P5REN



/* Port Name    :   P5.1
 * Pin Number   :   44
 * Net Name     :   I5
 */
#define I5_PIN    BIT1
#define I5_PORT   P5OUT
#define I5_IN     P5IN
#define I5_DIR    P5DIR
#define I5_REN    P5REN



/* Port Name    :   P5.2
 * Pin Number   :   45
 * Net Name     :   I6
 */
#define I6_PIN    BIT2
#define I6_PORT   P5OUT
#define I6_IN     P5IN
#define I6_DIR    P5DIR
#define I6_REN    P5REN



//// DKT-08 için eklenenler


/* Port Name    :   P2.0
 * Pin Number   :   46
 * Net Name     :   I7
 */
#define I7_PIN    BIT0
#define I7_PORT   P2OUT
#define I7_IN     P2IN
#define I7_DIR    P2DIR
#define I7_REN    P2REN



/* Port Name    :   P2.1
 * Pin Number   :   47
 * Net Name     :   I8
 */
#define I8_PIN    BIT1
#define I8_PORT   P2OUT
#define I8_IN     P2IN
#define I8_DIR    P2DIR
#define I8_REN    P2REN



/******************************************OUTPUTs Manage Pins***************************/



/// DKT-08 için eklendi.


// Internal Fault LED

/* Port Name    :   RA1
 * Pin Number   :   3
 * Net Name     :   LED4
 */
#define FAULT_LED_PIN     BIT1
#define FAULT_LED_PORT    P3OUT
#define FAULT_LED_IN      P3IN
#define FAULT_LED_DIR     P3DIR



////////// All leds must be separated for blinking different colors (red, red+green)    //////////////



/* Port Name    :   P5.7
 * Pin Number   :   21
 * Net Name     :   TRIP1
 */

#define TRIP1_PIN     BIT7
#define TRIP1_PORT    P5OUT
#define TRIP1_DIR     P5DIR



/* Port Name    :   P3.0
 * Pin Number   :   23
 * Net Name     :   HORN_RELAY_OUT
 */

#define HORN_RELAY_OUT_PIN     BIT0
#define HORN_RELAY_OUT_PORT    P3OUT
#define HORN_RELAY_OUT_DIR     P3DIR


///////////////// LEDS for DKT08   //////////////



// Red1 LED

/* Port Name    :   P1.5
 * Pin Number   :   5
 * Net Name     :   RED1_LED
 */
#define RED1_LED_PIN     BIT5
#define RED1_LED_PORT    P1OUT
#define RED1_LED_IN      P1IN
#define RED1_LED_DIR     P1DIR


// Yellow1 LED

/* Port Name    :   P1.6
 * Pin Number   :   6
 * Net Name     :  Yellow1_LED
 */
#define Yellow1_LED_PIN     BIT6
#define Yellow1_LED_PORT    P1OUT
#define Yellow1_LED_IN      P1IN
#define Yellow1_LED_DIR     P1DIR



// Red2 LED


/* Port Name    :   P3.6
 * Pin Number   :   3
 * Net Name     :   LED2
 */
#define RED2_LED_PIN     BIT6
#define RED2_LED_PORT    P3OUT
#define RED2_LED_IN      P3IN
#define RED2_LED_DIR     P3DIR



// Yellow2 LED


/* Port Name    :   P3.2
 * Pin Number   :   38
 * Net Name     :   Yellow2
 */
#define Yellow2_LED_PIN     BIT2
#define Yellow2_LED_PORT    P3OUT
#define Yellow2_LED_IN      P3IN
#define Yellow2_LED_DIR     P3DIR



// Red3 LED


/* Port Name    :   P1.7
 * Pin Number   :   7
 * Net Name     :   RED3
 */
#define RED3_LED_PIN     BIT7
#define RED3_LED_PORT    P1OUT
#define RED3_LED_IN      P1IN
#define RED3_LED_DIR     P1DIR



// Yellow3 LED


/* Port Name    :   P4.3
 * Pin Number   :   8
 * Net Name     :   Yellow3
 */
#define Yellow3_LED_PIN     BIT3
#define Yellow3_LED_PORT    P4OUT
#define Yellow3_LED_IN      P4IN
#define Yellow3_LED_DIR     P4DIR



// Red4 LED


/* Port Name    :   P3.5
 * Pin Number   :   37
 * Net Name     :   RED4
 */
#define RED4_LED_PIN     BIT5
#define RED4_LED_PORT    P3OUT
#define RED4_LED_IN      P3IN
#define RED4_LED_DIR     P3DIR



// Yellow4 LED


/* Port Name    :   P2.7
 * Pin Number   :   36
 * Net Name     :   Yellow4
 */
#define Yellow4_LED_PIN     BIT7
#define Yellow4_LED_PORT    P2OUT
#define Yellow4_LED_IN      P2IN
#define Yellow4_LED_DIR     P2DIR



// Red5 LED


/* Port Name    :   P4.4
 * Pin Number   :   9
 * Net Name     :   RED5
 */
#define RED5_LED_PIN     BIT4
#define RED5_LED_PORT    P4OUT
#define RED5_LED_IN      P4IN
#define RED5_LED_DIR     P4DIR



// Yellow5 LED


/* Port Name    :   P5.3
 * Pin Number   :   10
 * Net Name     :   Yellow5
 */
#define Yellow5_LED_PIN     BIT3
#define Yellow5_LED_PORT    P5OUT
#define Yellow5_LED_IN      P5IN
#define Yellow5_LED_DIR     P5DIR



// Red6 LED


/* Port Name    :   P4.2
 * Pin Number   :   35
 * Net Name     :   LED2
 */
#define RED6_LED_PIN     BIT2
#define RED6_LED_PORT    P4OUT
#define RED6_LED_IN      P4IN
#define RED6_LED_DIR     P4DIR



// Yellow6 LED



/* Port Name    :   P4.1
 * Pin Number   :   34
 * Net Name     :   LED2
 */
#define Yellow6_LED_PIN     BIT1
#define Yellow6_LED_PORT    P4OUT
#define Yellow6_LED_IN      P4IN
#define Yellow6_LED_DIR     P4DIR



// Red7 LED


/* Port Name    :   P5.4
 * Pin Number   :   11
 * Net Name     :   RED7
 */
#define RED7_LED_PIN     BIT4
#define RED7_LED_PORT    P5OUT
#define RED7_LED_IN      P5IN
#define RED7_LED_DIR     P5DIR



// Yellow7 LED


/* Port Name    :   P1.0
 * Pin Number   :   12
 * Net Name     :   Yellow7
 */
#define Yellow7_LED_PIN     BIT0
#define Yellow7_LED_PORT    P1OUT
#define Yellow7_LED_IN      P1IN
#define Yellow7_LED_DIR     P1DIR



// Red8 LED


/* Port Name    :   P4.0
 * Pin Number   :   33
 * Net Name     :   RED8
 */
#define RED8_LED_PIN     BIT0
#define RED8_LED_PORT    P4OUT
#define RED8_LED_IN      P4IN
#define RED8_LED_DIR     P4DIR



// Yellow8 LED


/* Port Name    :   P3.7
 * Pin Number   :   32
 * Net Name     :   Yellow8
 */
#define Yellow8_LED_PIN     BIT7
#define Yellow8_LED_PORT    P3OUT
#define Yellow8_LED_IN      P3IN
#define Yellow8_LED_DIR     P3DIR

#endif /*DKT08*/





#endif /* HEADERS_BSP_H_ */
