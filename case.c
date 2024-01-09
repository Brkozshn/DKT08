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




/*  Function    : Input_channel_disapp
 *  Inputs      : channel_num
 *  Return      : -
 *  Desc        : Check Led active state and read from EEPROM decide the channel status (ALARM or HORN)
 *  NOT         :
 */


void Input_channel_disapp(u8 channel_num) 
{
    u8 alarm;
    u8 trip;
    u8 channel;
    
    
    if(channel_num == Channel1) 
    {
        alarm = I1_Alarm;           // Sending the channel1 alarm value to alarm variable.
        trip = I1_Trip;             // Sending the channel1 trip value to trip variable.
        channel = I1;               // Sending channel number.
    }
    else if(channel_num == Channel2) 
    {
        alarm = I2_Alarm;           // Sending the channel2 alarm value to alarm variable. 
        trip = I2_Trip;             // Sending the channel2 trip value to trip variable. 
        channel = I2;               // Sending channel number.
    }
    else if(channel_num == Channel3) 
    {
        alarm = I3_Alarm;           // Sending the channel3 alarm value to alarm variable. 
        trip = I3_Trip;             // Sending the channel3 trip value to trip variable. 
        channel = I3;               // Sending channel number.
    }
    else if(channel_num == Channel4) 
    {
        alarm = I4_Alarm;           // Sending the channel4 alarm value to alarm variable. 
        trip = I4_Trip;             // Sending the channel4 trip value to trip variable. 
        channel = I4;               // Sending channel number.
    }
    else if(channel_num == Channel5) 
    {
        alarm = I5_Alarm;           // Sending the channel5 alarm value to alarm variable. 
        trip = I5_Trip;             // Sending the channel5 trip value to trip variable. 
        channel = I5;               // Sending channel number.
    }
    else if(channel_num == Channel6) 
    {
        alarm = I6_Alarm;           // Sending the channel6 alarm value to alarm variable. 
        trip = I6_Trip;             // Sending the channel6 trip value to trip variable.
        channel = I6;               // Sending channel number.
    }
    else if(channel_num == Channel7) 
    {
        alarm = I7_Alarm;           // Sending the channel7 alarm value to alarm variable. 
        trip = I7_Trip;             // Sending the channel7 trip value to trip variable.
        channel = I7;               // Sending channel number.
    }
    else if(channel_num == Channel8) 
    {
        alarm = I8_Alarm;           // Sending the channel8 alarm value to alarm variable. 
        trip = I8_Trip;             // Sending the channel8 trip value to trip variable.
        channel = I8;               // Sending channel number.
    }
    
    
    
    if((channel_flag[alarm] == TRUE) && (channel_flag[trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[channel]) == AGAIN_RELEASED))                           // Signal was active but right now it is not active anymore.
        {
            // Open up Horn relay
            // Blinking the red led.
               
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsActive(channel);                  // Leds are active for specific channel. 
            caseFlag[channel] = TRUE;           // Case succeeded.
        }
    }
    
    else if((channel_flag[alarm] == FALSE) && (channel_flag[trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[channel]) == AGAIN_RELEASED))                           // Signal was active but right now it is not active anymore.
        {
            // Open up Horn relay 
            // Blinking the red led.
            
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsActive(channel);                  // Leds are active for specific channel. 
            caseFlag[channel] = TRUE;           // Case succeeded.
        }
                
    }
    
    else 
    {
        caseFlag[channel] = FALSE;
        return;
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
    
    if((channel_flag[I1_Alarm] == TRUE) && (channel_flag[I1_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I1]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I1]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I1]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel1] = TRUE;           // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel1);                // Blinking the desired  channel led.
        }
    }
    
    else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I1]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I1]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I1]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel1] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel1);               // Blinking the desired  channel led.
        }
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel1] = FALSE;
        return;
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
    
    if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I2]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I2]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I2]) == STILL_PRESSED))
        {
            // Open up HOrn relay
            // Blinking the red led.
            
            caseFlag[Channel2] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel2);               // Blinking the desired  channel led.
        }
    }
    
    else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I2]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I2]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I2]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel2] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel2);               // Blinking the desired  channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel2] = FALSE;               // Case succeeded.
        return;
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
    
    if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I3]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I3]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I3]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel3] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel3);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I3]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I3]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I3]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel3] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel3);               // Blinking the desired channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel3] = FALSE;               // Case succeeded.   
        return;
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
    
    if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I4]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I4]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I4]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel4] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel4);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I4]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I4]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I4]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel4] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel4);               // Blinking the desired channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel4] = FALSE;               // Case succeeded.
        return;
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
    
    if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I5]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I5]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I5]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel5] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel5);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I5]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I5]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I5]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel5] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel5);               // Blinking the desired channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel5] = FALSE;               // Case succeeded.
        return;
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
    
    if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I6]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I6]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I6]) == STILL_PRESSED))
        {
            // Open up HOrn relay
            // Blinking the red led.
            
            caseFlag[Channel6] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel6);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I6]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I6]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I6]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel6] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel6);               // Blinking the desired channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel6] = FALSE;               // Case succeeded.
        return;
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
    
    if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I7]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I7]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I7]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel7] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel7);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I7]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I7]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I7]) == STILL_PRESSED))
        {
            // Open up HOrn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel7] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel7);               // Blinking the desired channel led.
        }
                
    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel7] = FALSE;               // Case succeeded.
        return;
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
    
    if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))                        /// If the signal is alarm.
    {
            
        if((Button_State_Func(&input_check_point[I8]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I8]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I8]) == STILL_PRESSED))
        {
            // Open up Horn relay
            // Blinking the red led.
            
            caseFlag[Channel8] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            ledsBlink(Channel8);               // Blinking the desired channel led.
        }
    }
    
    else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))                   /// If the signal is Trip 
    {
    
        if((Button_State_Func(&input_check_point[I8]) == PRESSED) || 
           (Button_State_Func(&input_check_point[I8]) == AGAIN_PRESSED) || 
           (Button_State_Func(&input_check_point[I8]) == STILL_PRESSED))
        {
            // Open up Horn relay and Trip relay
            // Blinking the yellow led.
            
            caseFlag[Channel8] = TRUE;               // Case succeeded.
            HORN_RELAY_OUT_PORT |= HORN_RELAY_OUT_PIN;
            TRIP1_PORT  |=  TRIP1_PIN;
            ledsBlink(Channel8);               // Blinking the desired channel led.
        }

    }
    
    else 
    {
        system_status.channelState = FAIL;                      // FAIL State'ine gidecek.
        caseFlag[Channel8] = FALSE;               // Case succeeded.
        return;
    }
    
}
