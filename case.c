/******************** (C) COPYRIGHT 2023 ORION EE ********************************
* File Name          : spi.c
* Author             : Burak Ozsahin
* Version            : V1.0.0
* Date               : 09/11/2023
* Description        : case source package for DKT08
********************************************************************************/



#include"case.h"
#include"main.h"
#include "led.h"



/*  Function    : Release_horn_test
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Check TEST or HORN button is released and go back to previous channel status (ALARM or HORN)
 *  NOT         :
 */

void Release_horn_test() 
{
        volatile u8 status_input;
        u8 name;

        //// A?a??daki yapt???m i?lemleri tek bir fonksiyon ?eklinde önceki a?ama fonksiyonu olarak tan?mlayabilirim. Ona göre gerekli i?lemler yap?l?yor.     

            for(name = 0 ; name < 8 ; name++)
            {
                status_input = Button_State_Func(&input_check_point[name]);   
                
                if((channel_flag[(2*name)+1] == TRUE) && (channel_flag[(2*name)] == FALSE))                        /// If the signal is alarm.
                {
                    if(status_input == AGAIN_PRESSED)                                                     /// If each channel is active.
                    {
                        LED_flag[(2*name)+1] = LED_ON;
                        mute_button_flag = TRUE;
                        HORN_RELAY_OUT_PORT   |=  HORN_RELAY_OUT_PIN;

                        // Channel is alarm that's why we need yellow blink 
                        
                        ledsBlink(name);        // Blinks leds with 2hz freq yellow
                    }
                
                    else if(status_input == AGAIN_RELEASED)                                                    /// If each channel is inactive.
                    {
                        LED_flag[(2*name)+1] = LED_OFF;
                        ledsPassive(name);               // All leds off
                    }

                }
                
                else if((channel_flag[(2*name)+1] == FALSE) && (channel_flag[(2*name)] == TRUE))                   /// If the signal is Trip
                {
                    
                    if(status_input == AGAIN_PRESSED)                                                     /// If each channel is active.
                    {
                        LED_flag[(2*name)] = LED_ON;
                        mute_button_flag = TRUE;
                        HORN_RELAY_OUT_PORT   |=  HORN_RELAY_OUT_PIN;
                        TRIP1_PORT  |=  TRIP1_PIN;
                        
                        // Channel is alarm that's why we need red blink 
                        
                        ledsBlink(name);        // Blinks leds with 2hz freq red
                    }
                
                    else if(status_input == AGAIN_RELEASED)                                                    /// If each channel is inactive.
                    {
                        LED_flag[(2*name)] = LED_OFF;
                        ledsPassive(name);               // All leds off

                    }
              }
       }
}



/*  Function    : Input_Channel1

 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */

void Input_Channel1()
{

        /// Signal is Active

        if((Button_State_Func(&input_check_point[I1]) == PRESSED) || (Button_State_Func(&input_check_point[I1]) == AGAIN_PRESSED))
        {
            caseFlag[Channel1] = SIGNAL_PASSIVE;           // Signal is Passive right now.
        }


        else if((Button_State_Func(&input_check_point[I1]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.

            caseFlag[Channel1] = SIGNAL_ACTIVE;           // Signal is active right now.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel1);                // Blinking the desired  channel led.
        }

        /// Signal is disappeared

        else if((Button_State_Func(&input_check_point[I1]) == STILL_RELEASED))
        {

            if(caseFlag[Channel1] == SIGNAL_ACTIVE)
            {
                caseFlag[Channel1] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
                ledsActive(Channel1);                         // Led is  activated.
            }

        }

        else
        {
            ledsPassive(Channel1);
        }
    
}



/*  Function    : Input_Channel2
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */

void Input_Channel2()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I2]) == PRESSED) || (Button_State_Func(&input_check_point[I2]) == AGAIN_PRESSED))
    {
        caseFlag[Channel2] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I2]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel2] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel2);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I2]) == STILL_RELEASED))
    {

        if(caseFlag[Channel2] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel2] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel2);                         // Led is  activated.
        }
    }

    else
    {
        ledsPassive(Channel2);

    }
    
}



/*  Function    : Input_Channel3
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */

void Input_Channel3()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I3]) == PRESSED) || (Button_State_Func(&input_check_point[I3]) == AGAIN_PRESSED))
    {
        caseFlag[Channel3] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I3]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel3] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel3);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I3]) == STILL_RELEASED))
    {

        if(caseFlag[Channel3] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel3] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel3);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel3);

    }
    
}



/*  Function    : Input_Channel4
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */

void Input_Channel4()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I4]) == PRESSED) || (Button_State_Func(&input_check_point[I4]) == AGAIN_PRESSED))
    {
        caseFlag[Channel4] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I4]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel4] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel4);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I4]) == STILL_RELEASED))
    {

        if(caseFlag[Channel4] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel4] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel4);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel4);

    }
    
}



/*  Function    : Input_Channel5
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */

void Input_Channel5()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I5]) == PRESSED) || (Button_State_Func(&input_check_point[I5]) == AGAIN_PRESSED))
    {
        caseFlag[Channel5] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I5]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel5] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel5);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I5]) == STILL_RELEASED))
    {
        if(caseFlag[Channel5] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel5] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel5);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel5);

    }
    
}


/*  Function    : Input_Channel6
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */


void Input_Channel6()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I6]) == PRESSED) || (Button_State_Func(&input_check_point[I6]) == AGAIN_PRESSED))
    {
        caseFlag[Channel6] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I6]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel6] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel6);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I6]) == STILL_RELEASED))
    {

        if(caseFlag[Channel6] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel6] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel6);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel6);

    }

}



/*  Function    : Input_Channel7
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */


void Input_Channel7()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I7]) == PRESSED) || (Button_State_Func(&input_check_point[I7]) == AGAIN_PRESSED))
    {
        caseFlag[Channel7] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I7]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel7] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel7);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I7]) == STILL_RELEASED))
    {
        if(caseFlag[Channel7] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel7] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel7);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel7);

    }
    
}



/*  Function    : Input_Channel8
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Read the channel settings from External EEPROM, check the input and decide what to do with input
 *  NOT         :
 */


void Input_Channel8()
{
    
    /// Signal is Active

    if((Button_State_Func(&input_check_point[I8]) == PRESSED) || (Button_State_Func(&input_check_point[I8]) == AGAIN_PRESSED))
    {
        caseFlag[Channel8] = SIGNAL_PASSIVE;           // Signal is Passive right now.
    }


    else if((Button_State_Func(&input_check_point[I8]) == STILL_PRESSED))
    {
        // Open up Horn relay
        // Blinking the red led.

        caseFlag[Channel8] = SIGNAL_ACTIVE;           // Signal is active right now.
        HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
        ledsBlink(Channel8);                // Blinking the desired  channel led.
    }

    /// Signal is disappeared

    else if((Button_State_Func(&input_check_point[I8]) == STILL_RELEASED))
    {
        if(caseFlag[Channel8] == SIGNAL_ACTIVE)
        {
            caseFlag[Channel8] = SIGNAL_DISAPPEARED;      // Signal is passive right now.
            ledsActive(Channel8);                         // Led is  activated.
        }

    }

    else
    {
        ledsPassive(Channel8);

    }

}
