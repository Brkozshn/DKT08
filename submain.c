/******************** (C) COPYRIGHT 2021 ORION EE ********************************
* File Name          : submain.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 16/08/2021
* Description        : submain functions
********************************************************************************/

#include <msp430.h>
#include "main.h"
#include "bsp.h"
#include "button.h"
#include "stdint.h"
#include "led.h"
#include "case.h"
#include "cnc.h"
#include "timeout.h"
#include "fram.h"



 /*  Function    : init_GPIO
  *  Inputs      : -
  *  Return      : -
  *  Desc        : all I/O pins's initialization called here.
  */

 void init_GPIO()
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
     /*
     I1_DIR       &= ~I1_PIN;
     I2_DIR       &= ~I2_PIN;
     I3_DIR       &= ~I3_PIN;
     I4_DIR       &= ~I4_PIN;
     I5_DIR       &= ~I5_PIN;
     I6_DIR       &= ~I6_PIN;
     I7_DIR       &= ~I7_PIN;
     I8_DIR       &= ~I8_PIN;
*/


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


     //LP5860_ClearAllLEDs();              // All leds are off.
      
     PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode

 }


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



 /*  Function    : hardware_init
  *  Inputs      : -
  *  Return      : -
  *  Desc        : all hardware initialization called here.
  */

 void hardware_init(void)
 {
   init_GPIO();
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
 
 
  /*  Function    : software_init
  *  Inputs      : -
  *  Return      : -
  *  Desc        : all software initialization called here.
  */
 
 void software_init(void)
 {

    system_status.timer_tick=0;
    system_status.timer_tick2=0;
    system_status.timer_internal_fault = 0;
    system_status.channelState = Channel1;
    

    if(system_Run_number == 0)
    {
        set_Channel_default();     // Set all channels to "ALARM" for first time
        system_Run_number = 1;     // System run time
    }

    system_status.Threshold_Control = 700;                 // 100 ms approx.


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
    
    TRIP1_PORT =   0;
    HORN_RELAY_OUT_PORT   &= ~HORN_RELAY_OUT_PIN;


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
          
            //// A?a??daki yapt???m i?lemleri tek bir fonksiyon ?eklinde önceki a?ama fonksiyonu olarak tan?mlayabilirim. Ona göre gerekli i?lemler yap?l?yor.
            
            Release_horn_test();     // Going back to previous status for all channels.  
            
            mute_button_flag = FALSE;
            HORN_RELAY_OUT_PORT   |=  HORN_RELAY_OUT_PIN;
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
            LP5860_ClearAllLEDs();              // All leds off

            
            for(name = 0 ; name < 8 ; name++)
            {
                status_input = Button_State_Func(&input_check_point[name]);   
                
                if((status_input == RELEASED) || (status_input == AGAIN_RELEASED) || (status_input == STILL_RELEASED))
                {
                        HORN_RELAY_OUT_PORT  &=  ~HORN_RELAY_OUT_PIN;
                        TRIP1_PORT   &=  ~TRIP1_PIN;
                        LED_flag[name] = LED_OFF;
                        
                        LP5860_ClearAllLEDs();              // All leds off

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
            
            // B?rak?ld???nda eski haline geri dönmesi laz?m.
            
            break;
            
        case STILL_RELEASED:
        case AGAIN_RELEASED:
        case RELEASED:
            
            Release_horn_test();     // Going back to previous status for all channels.  
            LP5860_ClearAllLEDs();              // All leds off
            test_button_flag = FALSE;
            TRIP1_PORT   &=  ~TRIP1_PIN;
            HORN_RELAY_OUT_PORT  &=  ~HORN_RELAY_OUT_PIN;
            
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
                        LED_flag[name] = LED_OFF;
                        
                        LP5860_ClearAllLEDs();              // All leds off
                }
                    
            }
                HORN_RELAY_OUT_PORT  &=  ~HORN_RELAY_OUT_PIN;
                reset_LED_flags();
            
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

    start_timeout_ms(TEST_HORN_TIMEOUT, TEST_HORN_Time);        // Timeout for 3 seconds


    process_timeouts();             // Decrease the timeouts value


    while(check_timeout(TEST_HORN_TIMEOUT) == TO_COUNTING_DOWN)
    {

        process_timeouts();             // Decrease the timeouts value

        status_TEST = Button_State_Func(&input_check_point[TEST]); // Get the status of the TEST button
        status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]); // Get the status of the HORN button

        // Check if both TEST and HORN buttons are STILL_PRESSED


        if ((status_TEST == STILL_PRESSED) && (status_HORN == STILL_PRESSED))
        {
            // Break the Alarm_Blink_TIMEOUT  loop

             if (check_timeout(TEST_HORN_TIMEOUT) == TO_OCCURED)
             {
                 // Perform the desired action when both buttons are held for 3 seconds

                 LP5860_OpenAllLEDs();       // Opening all LEDs
                 system_status.test_horn_started = TRUE;            // TEST and MUTE buttons are pressed for 3 seconds
                 test_button_flag = TRUE;    // Test button is pressed.
                 mute_button_flag = TRUE;    // Mute button is pressed.
                 HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;   // Horn relay is activated.

                 __delay_cycles(1000000);            // 1s approx

                 LP5860_ClearAllLEDs();          // Closing all LEDs

                 __delay_cycles(100000);            // 100ms approx


                 /// Channel Select function.

                 Channel_Select();

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
            test_button_flag = TRUE;    // Test button is NOT pressed.
            mute_button_flag = TRUE;    // Mute button is NOT pressed.
            check_timeout(TEST_HORN_TIMEOUT);
            return;
        }

    }

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
    
    
    start_timeout_ms(ACK_Save_TIMEOUT, ACK_Save_Time);           // Timeout for 5 seconds

    process_timeouts();             // decreases the value of timeout

                          
    while(check_timeout(ACK_Save_TIMEOUT) == TO_COUNTING_DOWN)
    {
        process_timeouts();             // decreases the value of timeout

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

         if (check_timeout(ACK_Save_TIMEOUT) == TO_OCCURED)
         {
             // Default settings are loaded for each channel

             //Fram_Channel_flag(system_status.channel_Select, RELEASED);        // Writing settings into FRAM

             return;
         }

                 // If Previous timeout is occurred
         /*
         if (check_timeout(Alarm_Blink_TIMEOUT) == TO_OCCURED)
         {
             // Default settings are loaded for each channel

             Fram_Channel_flag(system_status.channel_Select, RELEASED);        // Writing settings into FRAM
             break;
         }
            */
        }

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


    start_timeout_ms(Channel_Select_TIMEOUT, Channel_Select_Time);      // Timeout for 60 seconds
    
    process_timeouts();             // decreases the value of timeout
    
    while(check_timeout(Channel_Select_TIMEOUT) == TO_COUNTING_DOWN) 
    {
        
    switch(system_status.channel_Select)
    {
        case Channel1:
            
            // Default mode is alarm and blinks yellow.
             
             process_timeouts();             // decreases the value of timeout

            // Alarm is active blink the leds as yellow for  seconds.

             ledsBlink(Channel1);               // Blinking the desired channel yellow led.

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
                            ledsBlink(Channel1);
                        }

                        else if (system_status.Mute_state == ALARM_MODE)
                        {
                            // Set channel 1 to Trip if HORN button is pressed again

                            system_status.Mute_state = TRIP_MODE;
                            Fram_Channel_flag(Channel1, PRESSED);
                            ledsBlink(Channel1);
                        }

                        // Reset button press count after two presses

                        if (hornButtonPressCount == 2)
                        {
                            hornButtonPressCount = 0;
                        }
                    }


                status_TEST = Button_State_Func(&input_check_point[TEST]);  
                
                delay_ms(blinkDuration); // Adjust the delay as needed


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

               ledsBlink(Channel2);               // Blinking the desired channel yellow led.

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
                       ledsBlink(Channel2);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 2 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel2, PRESSED);
                       ledsBlink(Channel2);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed


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

               ledsBlink(Channel3);               // Blinking the desired channel yellow led.

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
                       ledsBlink(Channel3);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 3 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel3, PRESSED);
                       ledsBlink(Channel3);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed


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

               ledsBlink(Channel4);               // Blinking the desired channel yellow led.

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
                       ledsBlink(Channel4);
                   }

                   else if (system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 4 to Trip if HORN button is pressed again

                       system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel4, PRESSED);
                       ledsBlink(Channel4);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed


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

           ledsBlink(Channel5);               // Blinking the desired channel yellow led.

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
                   ledsBlink(Channel5);
               }

               else if ( system_status.Mute_state == ALARM_MODE)
               {
                   // Set channel 5 to Trip if HORN button is pressed again

                    system_status.Mute_state = TRIP_MODE;
                   Fram_Channel_flag(Channel5, PRESSED);
                   ledsBlink(Channel5);
               }

               // Reset button press count after two presses

               if (hornButtonPressCount == 2)
               {
                   hornButtonPressCount = 0;
               }
           }


           status_TEST = Button_State_Func(&input_check_point[TEST]);

           delay_ms(blinkDuration); // Adjust the delay as needed


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

               ledsBlink(Channel6);               // Blinking the desired channel yellow led.

                           // Choosing Channel features

               status_HORN = Button_State_Func(&input_check_point[MUTE_BUTTON]);

                   // Checking status of HORN button

               if (status_HORN == AGAIN_PRESSED)
               {
                   // Increment the button press count

                   hornButtonPressCount++;

                   if ( system_status.Mute_state == TRIP_MODE)
                   {
                       // Set channel 6 to Alarm if HORN button is pressed again

                        system_status.Mute_state = ALARM_MODE;
                       Fram_Channel_flag(Channel6, AGAIN_PRESSED);
                       ledsBlink(Channel6);
                   }

                   else if ( system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 6 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel6, PRESSED);
                       ledsBlink(Channel6);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed

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

               ledsBlink(Channel7);               // Blinking the desired channel yellow led.

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
                       ledsBlink(Channel7);
                   }

                   else if ( system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 7 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel7, PRESSED);
                       ledsBlink(Channel7);
                   }

                   // Reset button press count after two presses

                   if (hornButtonPressCount == 2)
                   {
                       hornButtonPressCount = 0;
                   }
               }


               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed


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

               ledsBlink(Channel8);               // Blinking the desired channel yellow led.

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
                       ledsBlink(Channel8);
                   }

                   else if ( system_status.Mute_state == ALARM_MODE)
                   {
                       // Set channel 8 to Trip if HORN button is pressed again

                        system_status.Mute_state = TRIP_MODE;
                       Fram_Channel_flag(Channel8, PRESSED);
                       ledsBlink(Channel8);
                   }

               }

               status_TEST = Button_State_Func(&input_check_point[TEST]);

               delay_ms(blinkDuration); // Adjust the delay as needed


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


        if (check_timeout(Channel_Select_TIMEOUT) == TO_OCCURED)
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
            
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                                
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel1();         // Check if right inputs are active for channel1.
                
                Input_channel_disapp(Channel1);      // If signal is suddenly disappeared.


                if(caseFlag[Channel1] == TRUE)
                {

                 system_status.channelState = Channel2;
                 break;

                }

                else if (caseFlag[Channel1] == FALSE)
                {

                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;

                }
              

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel1)
                {
                    system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                    break;
                }


            }
           
                break;
            
            
        case Channel2:
            
                      
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                               
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel2();                   // Check if right inputs are active for channel2.
                
                Input_channel_disapp(Channel2);      // If signal is suddenly disappeared.

                
                if(caseFlag[Channel2] == TRUE)
                {

                 system_status.channelState = Channel3;
                 break;

                }

                else if (caseFlag[Channel2] == FALSE)
                {
                    
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }
              

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel2)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }

                break;


        case Channel3:

                                
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                

                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel3();             // Check if right inputs are active for channel3.
                
                Input_channel_disapp(Channel3);      // If signal is suddenly disappeared.
                

                if(caseFlag[Channel3] == TRUE)
                {

                 system_status.channelState = Channel4;
                 break;

                }

                else if (caseFlag[Channel3] == FALSE)
                {
                    
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel3)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }



                break;


        case Channel4:

            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value

                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                                
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel4();                  // Check if right inputs are active for channel4.
                
                Input_channel_disapp(Channel4);      // If signal is suddenly disappeared.

                if(caseFlag[Channel4] == TRUE)
                {

                 system_status.channelState = Channel5;
                 break;

                }

                else if (caseFlag[Channel4] == FALSE)
                {
                    
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }
              

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel4)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }

                break;


        case Channel5:

            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                                
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel5();                      // Check if right inputs are active for channel5.               
                
                Input_channel_disapp(Channel5);      // If signal is suddenly disappeared.


                if(caseFlag[Channel5] == TRUE)
                {

                 system_status.channelState = Channel6;
                 break;

                }

                else if (caseFlag[Channel5] == FALSE)
                {
                    
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }
              
                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

                if(system_status.channelState != Channel5)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }


                break;


        case Channel6:
            
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel6();                    // Check if right inputs are active for channel6.   
                
                Input_channel_disapp(Channel6);      // If signal is suddenly disappeared.


                if(caseFlag[Channel6] == TRUE)
                {
                 system_status.channelState = Channel7;
                 break;
                }

                else if (caseFlag[Channel6] == FALSE)
                {
                    
                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

                if(system_status.channelState != Channel6)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }


                break;


        case Channel7:
            
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                

                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                Input_Channel7();                       // Check if right inputs are active for channel7.
                
                Input_channel_disapp(Channel7);      // If signal is suddenly disappeared.


                if(caseFlag[Channel7] == TRUE)
                {
                 system_status.channelState = Channel8;
                 break;
                }

                else if (caseFlag[Channel7] == FALSE)
                {

                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;
              
                }
              

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel7)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


             }


                break;


        case Channel8:

            
            start_timeout_ms(CASE_TIMEOUT, CASE_Time); // Timeout for 0.5 seconds

            process_timeouts();             // Decrease the timeouts value
                          
            while(check_timeout(CASE_TIMEOUT) == TO_COUNTING_DOWN)
            {                
                
                process_timeouts();             // Decrease the timeouts value

                input_button_control();         // Buttons are controlling each case

                // Input reset eklenebilir.

                Input_Channel8();                     // Check if right inputs are active for channel8.
                
                Input_channel_disapp(Channel8);      // If signal is suddenly disappeared.


                if(caseFlag[Channel8] == TRUE)
                {
                 system_status.channelState = Channel1;
                 break;
                }

                else if (caseFlag[Channel8] == FALSE)
                {

                system_status.channelState = FAIL;                     // FAIL State'ine gidecek.
                return;

                }

                if(check_timeout(CASE_TIMEOUT) ==  TO_OCCURED)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }


                if(system_status.channelState != Channel8)
                {
                    system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
                    break;
                }

            }

                break;
            
            
        case FAIL:
            
            // Buraya hata case'inde neler olmas? gerekiyorsa onlar? koy.

            system_reset();          /// Resetting the system. 
            system_status.channelState = Channel1;

                break;
            default:
                break;
            
        }       
}



/*  Function    : task_manager
 *  Inputs      : -
 *  Return      : -
 *  Desc        : All task run at here.
 */

void task_manager()
{
    while(1)
    {

        /*
        system_status.timer_tick2++;
        system_status.timer_tick++;
        system_status.timer_internal_fault++;
        */

        //__delay_cycles(1000000);


        channel_test();             // If some input recieved from channels.
        
        //Channel_Select();
        
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
