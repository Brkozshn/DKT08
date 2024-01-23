/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : submain.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 15/04/2022
* Description        : submain
********************************************************************************/


#include <msp430.h>
#include "define.h"
#include "bsp.h"
#include "lcd.h"
#include "main.h"
#include "submain.h"
#include <math.h>
#include "cnc.h"
#include "button.h"
#include "ram.h"
#include "timeout.h"
#include "display.h"
#include "utilities.h"
#include "uart_A0.h"
#include "uart_A1.h"
#include "DS1302.h"
#include "ATM90E32.h"
#include "fram.h"
#include "led.h"



void Software_Trim();

/*  Function    : initHardware
 *  Inputs      : -
 *  Return      : -
 *  Desc        : HW initialization.
 */
void initHardware(void)
{

    /* Watchdog Init */

    WDTCTL = WDTPW + WDTHOLD;       // Stop WDT

    SFRRPCR |= SYSNMIIES | SYSNMI;            // Select NMI function for the RST/NMI pin,
                                                // interrupt on falling edge

    /*All Port Close*/
    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    P5OUT = 0x00;


      /* OUTPUTS */


      HORN_RELAY_OUT_DIR    |= HORN_RELAY_OUT_PIN;
      TRIP1_DIR    |= TRIP1_PIN;

      RED1_LED_DIR |= RED1_LED_PIN;
      Yellow1_LED_DIR |= Yellow1_LED_PIN;

      RED2_LED_DIR |= RED2_LED_PIN;
      Yellow2_LED_DIR |= Yellow2_LED_PIN;

      RED3_LED_DIR |= RED3_LED_PIN;
      Yellow3_LED_DIR |= Yellow3_LED_PIN;

      RED4_LED_DIR |= RED4_LED_PIN;
      Yellow4_LED_DIR |= Yellow4_LED_PIN;

      RED5_LED_DIR |= RED5_LED_PIN;
      Yellow5_LED_DIR |= Yellow5_LED_PIN;

      RED6_LED_DIR |= RED6_LED_PIN;
      Yellow6_LED_DIR |= Yellow6_LED_PIN;

      RED7_LED_DIR |= RED7_LED_PIN;
      Yellow7_LED_DIR |= Yellow7_LED_PIN;

      RED8_LED_DIR |= RED8_LED_PIN;
      Yellow8_LED_DIR |= Yellow8_LED_PIN;


      /* END OF OUTPUTS*/


      /*INPUTS*/

      I1_DIR &= ~I1_PIN;   // Set as input
      I1_REN |= I1_PIN;    // Enable pull-up/pull-down resistor on the input
      I1_PORT |= I1_PIN;    // Set the pull-up resistor

      I2_DIR &= ~I2_PIN;   // Set as input
      I2_REN |= I2_PIN;    // Enable pull-up/pull-down resistor on the input
      I2_PORT |= I2_PIN;    // Set the pull-up resistor

      I3_DIR &= ~I3_PIN;   // Set as input
      I3_REN |= I3_PIN;    // Enable pull-up/pull-down resistor on the input
      I3_PORT |= I3_PIN;    // Set the pull-up resistor

      I4_DIR &= ~I4_PIN;   // Set as input
      I4_REN |= I4_PIN;    // Enable pull-up/pull-down resistor on the input
      I4_PORT |= I4_PIN;    // Set the pull-up resistor

      I5_DIR &= ~I5_PIN;   // Set as input
      I5_REN |= I5_PIN;    // Enable pull-up/pull-down resistor on the input
      I5_PORT |= I5_PIN;    // Set the pull-up resistor

      I6_DIR &= ~I6_PIN;   // Set as input
      I6_REN |= I6_PIN;    // Enable pull-up/pull-down resistor on the input
      I6_PORT |= I6_PIN;    // Set the pull-up resistor

      I7_DIR &= ~I7_PIN;   // Set as input
      I7_REN |= I7_PIN;    // Enable pull-up/pull-down resistor on the input
      I7_PORT |= I7_PIN;    // Set the pull-up resistor

      I8_DIR &= ~I8_PIN;   // Set as input
      I8_REN |= I8_PIN;    // Enable pull-up/pull-down resistor on the input
      I8_PORT |= I8_PIN;    // Set the pull-up resistor



      MUTE_BUTTON_DIR    &= ~MUTE_BUTTON_PIN;
      RESET_DIR   &= ~RESET_PIN;
      TEST_DIR    &= ~TEST_PIN;
      ACK_BUTTON_DIR  &= ~ACK_BUTTON_PIN;

      /* END Of INPUTS*/


       // Configure reference
    PMMCTL0_H = PMMPW_H;                     // Unlock the PMM registers
//    PMMCTL2 |= INTREFEN  | REFVSEL_2;        // Enable internal and 2.5V reference  Check cnc.h for ADC_VREF values
    __delay_cycles(400);                     // Delay for reference settling


//    UART_A0_init();

    UART_A1_init();

    PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode

    __bis_SR_register(SCG0);                 // disable FLL
    CSCTL3 |= SELREF__REFOCLK;               // Set REFO as FLL reference source
    CSCTL1 = DCOFTRIMEN_1 | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_5;// DCOFTRIM=5, DCO Range = 16MHz
    CSCTL2 = FLLD_0 + 487;
    //       CSCTL1 = DCOFTRIMEN_1 | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_3;// DCOFTRIM=3, DCO Range = 8MHz
    //       CSCTL2 = FLLD_0 + 243;                  // DCODIV = 8MHz
    __delay_cycles(3);
    __bic_SR_register(SCG0);                // enable FLL

    Software_Trim();                        // Software Trim to get the best DCOFTRIM value

    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
                                            // default DCODIV as MCLK and SMCLK source

    __bis_SR_register(GIE);


    __delay_cycles(10000);                     // Delay for settings

}


void defaultCaseFlag()
{

    caseFlag[Channel1] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel2] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel3] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel4] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel5] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel6] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel7] = SIGNAL_PASSIVE;      // Signal is passive right now.
    caseFlag[Channel8] = SIGNAL_PASSIVE;      // Signal is passive right now.

}



void initSoftware()
{

    // DKT 08 //

    system_status.timer_tick=0;
    system_status.timer_tick2=0;
    system_status.timer_internal_fault = 0;
    system_status.channelState = Channel1;


    if(system_Run_number == 0)
    {
        set_Channel_default();     // Set all channels to "ALARM" for first time
        SYSCFG0 = FRWPPW | FRWPOA0 | DFWP | PFWP;// Configure 1024 bytes for FRAM write

        system_Run_number = 1;     // System run time

        SYSCFG0 = FRWPPW | DFWP | PFWP;     // Program FRAM write protected (not writable)

    }


    output_reset();       // Resetting outputs.
    defaultCaseFlag();    // Starting the signal state from Passive

    system_status.Threshold_Control = 1000;                 // 100 ms approx.


    input_check_point[I1].LASTVALUE                  =   UNKNOWN;
    input_check_point[I1].BUTTON_RELEASED_CONFIG     =   I1_RELEASED_CFG ;
    input_check_point[I1].BUTTON_PRESSED_CONFIG      =   I1_PRESSED_CFG;
    input_check_point[I1].BUTTON_MASK                =   I1_MASK;
    input_check_point[I1].BUTTON_PORT_IN             =   &I1_IN;

    input_check_point[I2].LASTVALUE                  =   UNKNOWN;
    input_check_point[I2].BUTTON_RELEASED_CONFIG     =   I2_RELEASED_CFG ;
    input_check_point[I2].BUTTON_PRESSED_CONFIG      =   I2_PRESSED_CFG;
    input_check_point[I2].BUTTON_MASK                =   I2_MASK;
    input_check_point[I2].BUTTON_PORT_IN             =   &I2_IN;

    input_check_point[I3].LASTVALUE                  =   UNKNOWN;
    input_check_point[I3].BUTTON_RELEASED_CONFIG     =   I3_RELEASED_CFG;
    input_check_point[I3].BUTTON_PRESSED_CONFIG      =   I3_PRESSED_CFG ;
    input_check_point[I3].BUTTON_MASK                =   I3_MASK;
    input_check_point[I3].BUTTON_PORT_IN             =   &I3_IN;

    input_check_point[I4].LASTVALUE                  =   UNKNOWN;
    input_check_point[I4].BUTTON_RELEASED_CONFIG     =   I4_RELEASED_CFG ;
    input_check_point[I4].BUTTON_PRESSED_CONFIG      =   I4_PRESSED_CFG;
    input_check_point[I4].BUTTON_MASK                =   I4_MASK;
    input_check_point[I4].BUTTON_PORT_IN             =   &I4_IN;

    input_check_point[I5].LASTVALUE                  =   UNKNOWN;
    input_check_point[I5].BUTTON_RELEASED_CONFIG     =   I5_RELEASED_CFG ;
    input_check_point[I5].BUTTON_PRESSED_CONFIG      =   I5_PRESSED_CFG;
    input_check_point[I5].BUTTON_MASK                =   I5_MASK;
    input_check_point[I5].BUTTON_PORT_IN             =   &I5_IN;

    input_check_point[I6].LASTVALUE                  =   UNKNOWN;
    input_check_point[I6].BUTTON_RELEASED_CONFIG     =   I6_RELEASED_CFG ;
    input_check_point[I6].BUTTON_PRESSED_CONFIG      =   I6_PRESSED_CFG;
    input_check_point[I6].BUTTON_MASK                =   I6_MASK;
    input_check_point[I6].BUTTON_PORT_IN             =   &I6_IN;

    input_check_point[I7].LASTVALUE                  =   UNKNOWN;
    input_check_point[I7].BUTTON_RELEASED_CONFIG     =   I7_RELEASED_CFG ;
    input_check_point[I7].BUTTON_PRESSED_CONFIG      =   I7_PRESSED_CFG;
    input_check_point[I7].BUTTON_MASK                =   I7_MASK;
    input_check_point[I7].BUTTON_PORT_IN             =   &I7_IN;

    input_check_point[I8].LASTVALUE                  =   UNKNOWN;
    input_check_point[I8].BUTTON_RELEASED_CONFIG     =   I8_RELEASED_CFG ;
    input_check_point[I8].BUTTON_PRESSED_CONFIG      =   I8_PRESSED_CFG;
    input_check_point[I8].BUTTON_MASK                =   I8_MASK;
    input_check_point[I8].BUTTON_PORT_IN             =   &I8_IN;

    input_check_point[MUTE_BUTTON].LASTVALUE                =   UNKNOWN;
    input_check_point[MUTE_BUTTON].BUTTON_RELEASED_CONFIG   =   MUTE_BUTTON_RELEASED_CFG ;
    input_check_point[MUTE_BUTTON].BUTTON_PRESSED_CONFIG    =   MUTE_BUTTON_PRESSED_CFG;
    input_check_point[MUTE_BUTTON].BUTTON_MASK              =   MUTE_BUTTON_MASK;
    input_check_point[MUTE_BUTTON].BUTTON_PORT_IN           =   &MUTE_BUTTON_IN;

    input_check_point[RESET_BUTTON].LASTVALUE               =   UNKNOWN;
    input_check_point[RESET_BUTTON].BUTTON_RELEASED_CONFIG  =   RESET_RELEASED_CFG ;
    input_check_point[RESET_BUTTON].BUTTON_PRESSED_CONFIG   =   RESET_PRESSED_CFG;
    input_check_point[RESET_BUTTON].BUTTON_MASK             =   RESET_MASK;
    input_check_point[RESET_BUTTON].BUTTON_PORT_IN          =   &RESET_IN;

    input_check_point[TEST].LASTVALUE                =   UNKNOWN;
    input_check_point[TEST].BUTTON_RELEASED_CONFIG   =   TEST_RELEASED_CFG ;
    input_check_point[TEST].BUTTON_PRESSED_CONFIG    =   TEST_PRESSED_CFG;
    input_check_point[TEST].BUTTON_MASK              =   TEST_MASK;
    input_check_point[TEST].BUTTON_PORT_IN           =   &TEST_IN;

    input_check_point[ACK_BUTTON].LASTVALUE                =   UNKNOWN;
    input_check_point[ACK_BUTTON].BUTTON_RELEASED_CONFIG   =   ACK_BUTTON_RELEASED_CFG ;
    input_check_point[ACK_BUTTON].BUTTON_PRESSED_CONFIG    =   ACK_BUTTON_PRESSED_CFG;
    input_check_point[ACK_BUTTON].BUTTON_MASK              =   ACK_BUTTON_MASK;
    input_check_point[ACK_BUTTON].BUTTON_PORT_IN           =   &ACK_BUTTON_IN;


    mute_button_flag = FALSE;
    test_button_flag = FALSE;
    ack_button_flag = FALSE;
    reset_button_flag = FALSE;

    TRIP1_PORT  &=  ~TRIP1_PIN;
    HORN_RELAY_OUT_PORT   &=  ~HORN_RELAY_OUT_PIN;


    // DKT 08 //


    system_status.growing_factor = 1;
    system_status.reset_func_flag &= FALSE;

    system_status.relay1_fault_flag = FALSE;

    system_status.repeat_cnter &= 0;
    system_status.telemetry_period_ms = TM_PERIOD_MS;

    system_status.modbus_session_timeout_ms = MODBUS_TIMEOUT_MS;

    system_status.system_program_vers = PROGRAM_VERS;

    system_status.display_mode = DISPLAY_RESULTS_MODE;
    system_status.system_battery_active_flag = FALSE;

    system_status.sub_menu_lcd_cursor_pos = TOP;
    system_status.main_menu_lcd_cursor_pos = TOP;

    system_status.lcd_flag = TRUE;
    system_status.last_lcd_flag = FALSE;

    system_status.button_task_delay     = 10; // *10 ms

    system_status.button_low_timeout    = 50;//125;

    system_status.auto_increase_scaler  = 10;

    system_status.main_menu_index &= 0;
    system_status.date_menu_index &= 0;

    system_status.screen_freeze_flag &= DISABLE;


    __no_operation();


    _delay_cycles(20000);

}


void Software_Trim()
{
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do
    {
        CSCTL0 = 0x100;                         // DCO Tap = 256
        do
        {
            CSCTL7 &= ~DCOFFG;                  // Clear DCO fault flag
        }while (CSCTL7 & DCOFFG);               // Test DCO fault flag

        __delay_cycles((unsigned int)3000 * MCLK_FREQ_MHZ);// Wait FLL lock status (FLLUNLOCK) to be stable
                                                           // Suggest to wait 24 cycles of divided FLL reference clock
        while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;                   // Read CSCTL0
        csCtl1Read = CSCTL1;                   // Read CSCTL1

        oldDcoTap = newDcoTap;                 // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;       // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070)>>4;// Get DCOFTRIM value

        if(newDcoTap < 256)                    // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;     // Delta value between DCPTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }
        else                                   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;     // Delta value between DCPTAP and 256
            if(oldDcoTap < 256)                // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }

        if(newDcoDelta < bestDcoDelta)         // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }

    }while(endLoop == 0);                      // Poll until endLoop == 1

    CSCTL0 = csCtl0Copy;                       // Reload locked DCOTAP
    CSCTL1 = csCtl1Copy;                       // Reload locked DCOFTRIM
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
}



/////// DKT08 Functions //////////

void input_reset()
{

    I1_PORT       &= ~I1_PIN;
    I2_PORT       &= ~I2_PIN;
    I3_PORT       &= ~I3_PIN;
    I4_PORT       &= ~I4_PIN;
    I5_PORT       &= ~I5_PIN;
    I6_PORT       &= ~I6_PIN;
    I7_PORT       &= ~I7_PIN;
    I8_PORT       &= ~I8_PIN;


    MUTE_BUTTON_PORT    &= ~MUTE_BUTTON_PIN;
    RESET_PORT   &= ~RESET_PIN;
    TEST_PORT    &= ~TEST_PIN;
    ACK_BUTTON_PORT  &= ~ACK_BUTTON_PIN;

}


void output_reset()
{
   LP5860_ClearAllLEDs();              // All leds are off.
   HORN_RELAY_OUT_PORT   &= ~HORN_RELAY_OUT_PIN;
   TRIP1_PORT    &= ~ TRIP1_PIN;
}



/*  Function    : reset_LED_flags
*  Inputs      : -
*  Return      : -
*  Desc        : All LED flags OFF.
*/

void reset_LED_flags()
{
   LED_flag[I1_Trip]=LED_OFF;
   LED_flag[I1_Alarm]=LED_OFF;

   LED_flag[I2_Trip]=LED_OFF;
   LED_flag[I2_Alarm]=LED_OFF;

   LED_flag[I3_Trip]=LED_OFF;
   LED_flag[I3_Alarm]=LED_OFF;

   LED_flag[I4_Trip]=LED_OFF;
   LED_flag[I4_Alarm]=LED_OFF;

   LED_flag[I5_Trip]=LED_OFF;
   LED_flag[I5_Alarm]=LED_OFF;

   LED_flag[I6_Trip]=LED_OFF;
   LED_flag[I6_Alarm]=LED_OFF;

   LED_flag[I7_Trip]=LED_OFF;
   LED_flag[I7_Alarm]=LED_OFF;

   LED_flag[I8_Trip]=LED_OFF;
   LED_flag[I8_Alarm]=LED_OFF;

}



/*  Function    : system_reset
*  Inputs      : -
*  Return      : -
*  Desc        : Resets the system.
*/

void system_reset()
{
   input_reset();     // Reset all inputs
   output_reset();    // Reset all output
   reset_LED_flags();     // Reset all led flags.
   LP5860_ClearAllLEDs();  // Reset all leds.

   if(system_Run_number == 0)
   {
       set_Channel_default();     // Set all channels to "ALARM" for first time
       system_Run_number = 1;     // System run time
   }
}



/*  Function    : input_button_control
 *  Inputs      : -
 *  Return      : -
 *  Desc        : All button inputs controls at here.
 */

void input_button_control()
{

   volatile u8 status = 0;
   volatile u8 status_input;
   u8 name;

   status=Button_State_Func(&input_check_point[MUTE_BUTTON]);

   switch(status)
   {
       case STILL_PRESSED:

           mute_button_flag = TRUE;
           HORN_RELAY_OUT_PORT   |=  HORN_RELAY_OUT_PIN;

           break;

       case AGAIN_RELEASED:
       case RELEASED:
       case STILL_RELEASED:

           //Release_horn_test();     // Going back to previous status for all channels.
           mute_button_flag = FALSE;
           break;
   }

   status=Button_State_Func(&input_check_point[RESET_BUTTON]);

   switch(status)
   {
       case PRESSED:
       case AGAIN_PRESSED:
       case STILL_PRESSED:

           // switch case for signals are active or not

           reset_button_flag=TRUE;
           output_reset();       // Resetting outputs.


           for(name = 0 ; name < 8 ; name++)
           {
               status_input = Button_State_Func(&input_check_point[name]);

               /// Signal is disappeared

               if(status_input == STILL_RELEASED)
               {
                   if(caseFlag[name] == SIGNAL_DISAPPEARED)
                   {
                       caseFlag[name] = SIGNAL_PASSIVE;           // Signal is Passive right now.

                   // Since we have 16 led flags we implement the logic below.

                       LED_flag[(2*name)+1] = LED_OFF;
                       LED_flag[(2*name)] = LED_OFF;
                   }

               }

           }

       case STILL_RELEASED:
            break;
       default:
           break;

    }

   status=Button_State_Func(&input_check_point[TEST]);

   switch(status)
   {
       case PRESSED:
       case STILL_PRESSED:

           LP5860_OpenAllLEDs();       // Opening all leds
           test_button_flag = TRUE;
           TRIP1_PORT |=  TRIP1_PIN ;
           HORN_RELAY_OUT_PORT   |=  HORN_RELAY_OUT_PIN;

           break;

       case STILL_RELEASED:
       case AGAIN_RELEASED:
       case RELEASED:

           //Release_horn_test();     // Going back to previous status for all channels.

           if(test_button_flag == TRUE)
           {
               LP5860_ClearAllLEDs();              // All leds off
               test_button_flag = FALSE;
               TRIP1_PORT   &=  ~TRIP1_PIN;
               HORN_RELAY_OUT_PORT  &=  ~HORN_RELAY_OUT_PIN;
           }


            break;
       default:
           break;
     }

   status = Button_State_Func(&input_check_point[ACK_BUTTON]);

   switch(status)
   {
       case PRESSED:
       case STILL_PRESSED:

           ack_button_flag = TRUE;

           // switch case for signals are active or not

           for(name = 0 ; name < 8 ; name++)
           {
               status_input = Button_State_Func(&input_check_point[name]);

               if((status_input == RELEASED) || (status_input == AGAIN_RELEASED) || (status_input == STILL_RELEASED))
               {
                   // Since we have 16 led flags we implement the logic below.

                       LED_flag[(2*name)+1] = LED_OFF;
                       LED_flag[(2*name)] = LED_OFF;

                       ledsPassive(name);              // Required leds off
               }

           }

               HORN_RELAY_OUT_PORT  &=  ~HORN_RELAY_OUT_PIN;
               //reset_LED_flags();

       case AGAIN_PRESSED:
       case STILL_RELEASED:
            break;
       default:
           break;
   }

}



/*  Function    : Channel_Set
 *  Inputs      : -
 *  Return      : -
 *  Desc        :  Entering Channel settings.
 */

void Channel_Set_mode() {

    system_status.test_horn_started = FALSE;
    volatile u8 status_TEST = 0;
    volatile u8 status_HORN = 0;
//    system_status.timer_tick2 = 0;


   startTimeout_ms(TEST_HORN_TIMEOUT, TEST_HORN_Time);      // Press for 3 seconds

   process_timeouts();             // decreases the value of timeout

  while(checkTimeout(TEST_HORN_TIMEOUT) == TO_COUNTING_DOWN)
  {

        process_timeouts();             // decreases the value of timeout


//    while(system_status.timer_tick2 < 3*30000)
//    {

//        system_status.timer_tick2++;

        status_TEST = Button_State_Func(&input_check_point[TEST]); // Get the status of the TEST button
        status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]); // Get the status of the HORN button

        // Check if both TEST and HORN buttons are STILL_PRESSED


        if ((status_TEST == STILL_PRESSED) && (status_HORN == STILL_PRESSED))
        {

//             if (system_status.timer_tick2 == 3*30000)
//             {

              if(checkTimeout(TEST_HORN_TIMEOUT) ==  TO_OCCURED)
              {
                 // Perform the desired action when both buttons are held for 3 seconds

//                 system_status.timer_tick2=0;
                 LP5860_OpenAllLEDs();       // Opening all LEDs
                 system_status.test_horn_started = TRUE;            // TEST and MUTE buttons are pressed for 3 seconds
                 test_button_flag = TRUE;    // Test button is pressed.
                 mute_button_flag = TRUE;    // Mute button is pressed.
                 HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;   // Horn relay is activated.


                 __delay_cycles(100000);            // 100ms approx

                 LP5860_ClearAllLEDs();          // Closing all LEDs

                 __delay_cycles(100000);            // 100ms approx


                 /// Channel Select function.

                 Channel_Select();


                 __no_operation();

                if(system_status.channelState == FAIL)                      // FAIL State'ine gidecek.
                {
                    return;
                }

                 break;
             }
        }

        else
        {
            // If the buttons are not both pressed, reset the timeout

            system_status.test_horn_started = FALSE;
            //test_button_flag = FALSE;    // Test button is NOT pressed.
            mute_button_flag = FALSE;    // Mute button is NOT pressed.
            return;
        }

    }

    __no_operation();

}



/*  Function    : save_Channel_settings
 *  Inputs      : -
 *  Return      : -
 *  Desc        :  Saving all Channels.
 */


void save_Channel_settings()
{
    volatile u8 status_ACK;
    volatile u8 status_Reset;


//    startTimeout_ms(ACK_Save_TIMEOUT, ACK_Save_Time);           // Timeout for 5 seconds
//
//    process_timeouts();             // decreases the value of timeout
//
//
//    while(checkTimeout(ACK_Save_TIMEOUT) == TO_COUNTING_DOWN)
//    {
//        process_timeouts();             // decreases the value of timeout

        status_ACK = Button_State_Func(&input_check_point[ACK_BUTTON]);

        if((status_ACK == PRESSED) ||(status_ACK == AGAIN_PRESSED) || (status_ACK == STILL_PRESSED))
        {
            // No need to call FRAM function to save all settings because they are already saved.

            /*
            if (system_status.Mute_state == TRIP_MODE)
            {
                Fram_Channel_flag(Channel1, PRESSED);
                return;
            }

            else if (system_status.Mute_state == ALARM_MODE)
            {
                Fram_Channel_flag(Channel1, AGAIN_PRESSED);
                return;
            }
            */

        }


        status_Reset = Button_State_Func(&input_check_point[RESET_BUTTON]);

        if((status_Reset == PRESSED) ||(status_Reset == AGAIN_PRESSED) || (status_Reset == STILL_PRESSED))
        {
             set_Channel_default();             // Reset all channels to default.
             LP5860_ClearAllLEDs();             // Reset all leds. All leds are off

             //system_reset();                    // Resets everything

            return;
        }

                // Break the ACK_Save_TIMEOUT  loop

//         if (checkTimeout(ACK_Save_TIMEOUT) == TO_OCCURED)
//         {
//             // Default settings are loaded for each channel
//
//             //Fram_Channel_flag(system_status.channel_Select, RELEASED);        // Writing settings into FRAM
//
//             return;
//         }

                 // If Previous timeout is occurred
         /*
         if (checkTimeout(Alarm_Blink_TIMEOUT) == TO_OCCURED)
         {
             // Default settings are loaded for each channel

             Fram_Channel_flag(system_status.channel_Select, RELEASED);        // Writing settings into FRAM
             break;
         }
            */
//        }

    }



/*  Function    : Channel_Select
 *  Inputs      : -
 *  Return      : -
 *  Desc        :  Setting all Channels as desired.
 */

void Channel_Select()
{
    system_status.Mute_state = ALARM_MODE;
    volatile u8 status_HORN;
    volatile u8 status_TEST;
    system_status.channel_Select = Channel1;
    volatile u8 hornButtonPressCount = 0;


    if(system_status.test_horn_started == FALSE)
    {
        return;
    }


    startTimeout_ms(Channel_Select_TIMEOUT, Channel_Select_Time);      // Timeout for 60 seconds

    process_timeouts();             // decreases the value of timeout

  while(checkTimeout(Channel_Select_TIMEOUT) == TO_COUNTING_DOWN)
  {

    switch(system_status.channel_Select)
    {
        case Channel1:

            // Default mode is alarm and blinks yellow.

             process_timeouts();             // decreases the value of timeout

            // Alarm is active blink the leds as yellow for  seconds.


             if((channel_flag[I1_Alarm] == TRUE) && (channel_flag[I1_Trip] == FALSE))
             {
                 // Default mode is alarm and blinks yellow.
                 LedBlink_channelSelect(&Yellow1_LED_PORT, Yellow1_LED_PIN);           /// Default Alarm
             }

             else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
             {
                 // Default mode is alarm and blinks yellow.
                 LedBlink_channelSelect(&RED1_LED_PORT, RED1_LED_PIN);           /// Default Alarm
             }

                            // Choosing Channel features

                status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                    // Checking status of HORN button

                    if (status_HORN == AGAIN_PRESSED)
                    {
                        // Increment the button press count

                        hornButtonPressCount++;

                        if (system_status.Mute_state == TRIP_MODE)
                        {
                            // Set channel 1 to Alarm if HORN button is pressed again

                            system_status.Mute_state = ALARM_MODE;
                            Fram_Channel_flag(Channel1, AGAIN_PRESSED);
                            LedBlink_channelSelect(&RED1_LED_PORT, RED1_LED_PIN);
                            //ledsBlink(Channel1);
                            //delay_ms(blinkDuration); // Adjust the delay as needed

                        }

                        else if (system_status.Mute_state == ALARM_MODE)
                        {
                            // Set channel 1 to Trip if HORN button is pressed again

                            system_status.Mute_state = TRIP_MODE;
                            Fram_Channel_flag(Channel1, PRESSED);
                            LedBlink_channelSelect(&Yellow1_LED_PORT, Yellow1_LED_PIN);
                            //ledsBlink(Channel1);
                            //delay_ms(blinkDuration); // Adjust the delay as needed

                        }

                        // Reset button press count after two presses

                        if (hornButtonPressCount == 2)
                        {
                            hornButtonPressCount = 0;
                        }
                    }


                status_TEST = Button_State_Func(&input_check_point[TEST]);



                if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
                {
                    system_status.channel_Select++;                  // Select next channel
                }

                // Aşağıdaki fonksiyonu Yukarıdaki TEST butonu içine koy

                save_Channel_settings();        // Saving all channels settings

                break;



        case Channel2:


           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&Yellow2_LED_PORT, Yellow2_LED_PIN);           /// Default Alarm
            }

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&RED2_LED_PORT, RED2_LED_PIN);           /// Default Alarm
            }

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button

               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if (system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 2 to Alarm if HORN button is pressed again

                       system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel2, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED2_LED_PORT, RED2_LED_PIN);
                       //ledsBlink(Channel2);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 2 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel2, PRESSED);
                       LedBlink_channelSelect(&Yellow2_LED_PORT, Yellow2_LED_PIN);
                       //ledsBlink(Channel2);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed


               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {
                    // Channel 2 is setted as Alarm.

                   system_status.channel_Select++;                  // Select next channel
               }


               save_Channel_settings();        // Saving all channels settings

               break;


        case Channel3:

           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.


             if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
             {
                 // Default mode is alarm and blinks yellow.
                 LedBlink_channelSelect(&Yellow3_LED_PORT, Yellow3_LED_PIN);           /// Default Alarm
             }

             else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
             {
                 // Default mode is alarm and blinks yellow.
                 LedBlink_channelSelect(&RED3_LED_PORT, RED3_LED_PIN);           /// Default Alarm
             }
                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button

               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if (system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 3 to Alarm if HORN button is pressed again

                       system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel3, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED3_LED_PORT, RED3_LED_PIN);
                       //ledsBlink(Channel3);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 3 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel3, PRESSED);
                       LedBlink_channelSelect(&Yellow3_LED_PORT, Yellow3_LED_PIN);
                       //ledsBlink(Channel3);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed


               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {

                    // Channel 3 is setted as Alarm.

                   system_status.channel_Select++;                  // Select next channel
               }

               save_Channel_settings();        // Saving all channels settings

               break;


        case Channel4:

           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&Yellow4_LED_PORT, Yellow4_LED_PIN);           /// Default Alarm
            }

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&RED4_LED_PORT, RED4_LED_PIN);           /// Default Alarm
            }

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button


               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if ( system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 4 to Alarm if HORN button is pressed again

                       system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel4, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED4_LED_PORT, RED4_LED_PIN);
                       //ledsBlink(Channel4);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 4 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel4, PRESSED);
                       LedBlink_channelSelect(&Yellow4_LED_PORT, Yellow4_LED_PIN);
                       //ledsBlink(Channel4);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed


               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {
                    // Channel 4 is setted as Alarm.

                   system_status.channel_Select++;                  // Select next channel
               }

               save_Channel_settings();        // Saving all channels settings

               break;


        case Channel5:

       // Default mode is alarm and blinks yellow.

        process_timeouts();             // decreases the value of timeout

       // Alarm is active blink the leds as yellow for  seconds.

        if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
        {
            // Default mode is alarm and blinks yellow.
            LedBlink_channelSelect(&Yellow5_LED_PORT, Yellow5_LED_PIN);           /// Default Alarm
        }

        else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
        {
            // Default mode is alarm and blinks yellow.
            LedBlink_channelSelect(&RED5_LED_PORT, RED5_LED_PIN);           /// Default Alarm
        }


                       // Choosing Channel features

           status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

               // Checking status of HORN button

           if (status_HORN == AGAIN_PRESSED)
           {
               // Increment the button press count

               hornButtonPressCount++;

               if ( system_status.Mute_state == TRIP_MODE)
               {
                   // Set channel 5 to Alarm if HORN button is pressed again

                    system_status.Mute_state = ALARM_MODE;
                   Fram_Channel_flag(Channel5, AGAIN_PRESSED);
                   LedBlink_channelSelect(&RED5_LED_PORT, RED5_LED_PIN);
                   //ledsBlink(Channel5);
               }

               else if ( system_status.Mute_state == ALARM_MODE)
               {
                   // Set channel 5 to Trip if HORN button is pressed again

                    system_status.Mute_state = TRIP_MODE;
                   Fram_Channel_flag(Channel5, PRESSED);
                   LedBlink_channelSelect(&Yellow5_LED_PORT, Yellow5_LED_PIN);
                   //ledsBlink(Channel5);
               }

               // Reset button press count after two presses

               if (hornButtonPressCount == 2)
               {
                   hornButtonPressCount = 0;
               }
           }


           status_TEST = Button_State_Func(&input_check_point[TEST]);

//           delay_ms(blinkDuration); // Adjust the delay as needed


           if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
           {
                // Channel 5 is setted as Alarm.

               system_status.channel_Select++;                  // Select next channel
               break;
           }

           save_Channel_settings();        // Saving all channels settings

           break;


        case Channel6:

           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&Yellow6_LED_PORT, Yellow6_LED_PIN);           /// Default Alarm
            }

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&RED6_LED_PORT, RED6_LED_PIN);           /// Default Alarm
            }

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button

               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if (system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 6 to Alarm if HORN button is pressed again

                        system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel6, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED6_LED_PORT, RED6_LED_PIN);
                       //ledsBlink(Channel6);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 6 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel6, PRESSED);
                       LedBlink_channelSelect(&Yellow6_LED_PORT, Yellow6_LED_PIN);
                       //ledsBlink(Channel6);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed

               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {
                    // Channel 6 is setted as Alarm.

                   system_status.channel_Select++;                  // Select next channel
                   break;
               }

               save_Channel_settings();        // Saving all channels settings

               break;


        case Channel7:

           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&Yellow7_LED_PORT, Yellow7_LED_PIN);           /// Default Alarm
            }

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&RED7_LED_PORT, RED7_LED_PIN);           /// Default Alarm
            }

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button


               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if ( system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 7 to Alarm if HORN button is pressed again

                        system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel7, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED7_LED_PORT, RED7_LED_PIN);
                       //ledsBlink(Channel7);
                   }

                   else if ( system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 7 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel7, PRESSED);
                       LedBlink_channelSelect(&Yellow7_LED_PORT, Yellow7_LED_PIN);
                       //ledsBlink(Channel7);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed


               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {
                    // Channel 7 is setted as Alarm.

                   system_status.channel_Select++;                  // Select next channel
                   break;
               }

               save_Channel_settings();        // Saving all channels settings

               break;


        case Channel8:

           // Default mode is alarm and blinks yellow.

            process_timeouts();             // decreases the value of timeout

           // Alarm is active blink the leds as yellow for  seconds.

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&Yellow8_LED_PORT, Yellow8_LED_PIN);           /// Default Alarm
            }

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                // Default mode is alarm and blinks yellow.
                LedBlink_channelSelect(&RED8_LED_PORT, RED8_LED_PIN);           /// Default Alarm
            }

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button

               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if ( system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 8 to Alarm if HORN button is pressed again

                        system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel8, AGAIN_PRESSED);
                       LedBlink_channelSelect(&RED8_LED_PORT, RED8_LED_PIN);
                       //ledsBlink(Channel8);
                   }

                   else if ( system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 8 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel8, PRESSED);
                       LedBlink_channelSelect(&Yellow8_LED_PORT, Yellow8_LED_PIN);
                       //ledsBlink(Channel8);
                   }

               }

               status_TEST = Button_State_Func(&input_check_point[TEST]);

//               delay_ms(blinkDuration); // Adjust the delay as needed


               if((status_TEST == PRESSED) ||(status_TEST == AGAIN_PRESSED))
               {
                    // Channel 8 is setted as Alarm.

                   system_status.channel_Select = 1;
                   return;
               }

               save_Channel_settings();        // Saving all channels settings

            break;
        default:
            break;
        }


        if (checkTimeout(Channel_Select_TIMEOUT) == TO_OCCURED)
        {
            system_status.channel_Select = Channel1;
            system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
            return;
        }


        if( system_status.channel_Select >= NUM_OF_CASE)
        {
            system_status.channel_Select = Channel1;
            system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
            return;
        }

     }

  }



//////// MAIN Function  ////////



/*  Function    : channel_test
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Starting the tests and check if it is completed or not.
 */

void channel_test()
{

       Channel_Set_mode();         // Controlling "HORN" and "TEST" buttons


        switch(system_status.channelState){

        case Channel1:


            if(system_status.channelState != Channel1)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel1();         // Check if right inputs are active for channel1.

            system_status.channelState = Channel2;


                break;


        case Channel2:


                if(system_status.channelState != Channel2)
                {
                    system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                    break;
                }

                Input_Channel2();                   // Check if right inputs are active for channel2

                system_status.channelState = Channel3;


                break;


        case Channel3:


            if(system_status.channelState != Channel3)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel3();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel4;


                break;


        case Channel4:

            if(system_status.channelState != Channel4)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel4();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel5;


                break;


        case Channel5:

            if(system_status.channelState != Channel5)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel5();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel6;


                break;


        case Channel6:

            if(system_status.channelState != Channel6)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel6();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel7;

                break;


        case Channel7:

            if(system_status.channelState != Channel7)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel7();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel8;


                break;


        case Channel8:


            if(system_status.channelState != Channel8)
            {
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                break;
            }

            Input_Channel8();                   // Check if right inputs are active for channel2

            system_status.channelState = Channel1;

                break;

        case FAIL:

            // Buraya hata case'inde neler olmas? gerekiyorsa onlar? koy.

            //system_reset();          /// Resetting the system.
            system_status.channelState = Channel1;

                break;
            default:
                break;

            }
        }


//////// End of DKT08 Functions    ///////



void taskManager()
{

    while(1)
    {

        system_status.timer_tick++;
        system_status.timer_tick2++;


        /*
        system_status.timer_internal_fault++;
        */


        if( system_status.timer_tick>=1800)
        {
            system_status.timer_tick=0;
        }


        channel_test();             // If some input recieved from channels.

        processModbus();


        if( system_status.timer_tick2>=system_status.Threshold_Control)
        {
            system_status.timer_tick2=0;
            input_button_control();         // Buttons are controlling each case
        }



        //CheckSignalState();         // Internal fault control function

        // Internal Fault Control function needs to be added to the "channel_test()" function with this block below.

        // Internal Fault Control

        /*
        if( system_status.timer_internal_fault>=system_status.Threshold_Control)
        {
            system_status.timer_internal_fault=0;

            // Check signal state for errors

            CheckSignalState();
        }

        */

    }

}
