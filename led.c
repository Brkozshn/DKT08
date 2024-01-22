/******************** (C) COPYRIGHT 2023 ORION EE ********************************
* File Name          : led.c
* Author             : Burak Ozsahin
* Version            : V1.0.0
* Date               : 05/12/2023
* Description        : led functions
********************************************************************************/



#include "main.h"
#include "stdint.h"
#include "bsp.h"
#include "button.h"
#include "timeout.h"
#include "led.h"
#include"utilities.h"



/*  Function    : TriggerInternalFault
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Function to check the signal state for errors
 *  NOT         :
 */

void TriggerInternalFault()
{

    // For example, you can log the fault, turn off critical components, or
    // take any other appropriate action to handle the fault condition.

    // Toggle the Fault LED

     //FAULT_LED_PORT = 1;

}



/*  Function    : CheckSignalState
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Function to check the signal state for errors
 *  NOT         :
 */

void CheckSignalState()
{
    static u8 previousState = HIGH;
    static u32 lastChangeTime = 0;
    u8 input_state = 0;


    if (input_state == previousState)
    {
        u32 currentTime = get_time_ms(); // Implement this function to get the current time
        if (currentTime - lastChangeTime >= ERROR_THRESHOLD_TIME)
        {
            // Signal has been stuck in the same state for too long, trigger an internal fault
            TriggerInternalFault();
        }
    }

    else
    {
        lastChangeTime = get_time_ms();
        previousState = input_state;
    }
}



/*  Function    : LP5860_ClearAllLEDs
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Close all leds
 *  NOT         :
 */

void LP5860_ClearAllLEDs() {
    u8 ledNumber = 0;

    // Turn off all LEDs
    for (ledNumber = 0; ledNumber < NUM_OF_LEDS; ++ledNumber)
    {
        ledsPassive(ledNumber);
        //delay_ms(ledBetween_Duration); // Adjust the delay as needed

    }
}


/*  Function    : LP5860_OpenAllLEDs
 *  Inputs      : -
 *  Return      : -
 *  Desc        : Open all leds
 *  NOT         :
 */

void LP5860_OpenAllLEDs()
{
    u8 ledNumber = 0;
    // Turn on all LEDs with maximum intensity
    for (ledNumber = 0; ledNumber < NUM_OF_LEDS; ++ledNumber)
    {
        ledsActive(ledNumber);
    }
}



/*  Function    : LED_Blink
 *  Inputs      : u8 led_port,u8 led_pin, u16 blink_ms, u8 repeat_cnt
 *  Return      : -
 *  Desc        :
 *  NOT         :
 */
void LED_Blink(vu8 *led_port,u8 led_pin)
{

    if(system_status.timer_tick<900)
        {
        *(led_port) &= ~led_pin;
        }
        else
        {
            *(led_port) |= led_pin;
        }
}





/*  Function    : LedBlink_channelSelect
 *  Inputs      : u8 led_port,u8 led_pin, u16 blink_ms, u8 repeat_cnt
 *  Return      : -
 *  Desc        :
 *  NOT         :
 */
void LedBlink_channelSelect(vu8 *led_port,u8 led_pin)
{

    // Blink the LED by toggling between the specified intensity and 0

    *(led_port) |= led_pin;

    delay_ms(blinkDuration); // Adjust the delay as needed

    *(led_port) &= ~led_pin;

}





///////   Driving LEDs via Functions    ////////


/*  Function    : ledsActive
 *  Inputs      : channelNumber
 *  Return      : -
 *  Desc        : Open desired leds for specific channel.
 *  NOT         :
 */


void ledsActive(u8 channelNumber)
{
    switch(channelNumber)
    {
        case Channel1:

            // If channel1 signal is alarm

            if((channel_flag[I1_Alarm] == TRUE) && (channel_flag[I1_Trip] == FALSE))
            {
                Yellow1_LED_PORT |= Yellow1_LED_PIN;

                LED_flag[Yellow1_LED] = LED_ON;
            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {
                RED1_LED_PORT |= RED1_LED_PIN;

                LED_flag[RED1_LED] = LED_ON;
            }

            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                Yellow2_LED_PORT |= Yellow2_LED_PIN;

                LED_flag[Yellow2_LED] = LED_ON;
            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                RED2_LED_PORT |= RED2_LED_PIN;

                LED_flag[RED2_LED] = LED_ON;
            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {
                Yellow3_LED_PORT |= Yellow3_LED_PIN;

                LED_flag[Yellow3_LED] = LED_ON;
            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {
                RED3_LED_PORT |= RED3_LED_PIN;

                LED_flag[RED3_LED] = LED_ON;
            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                Yellow4_LED_PORT |= Yellow4_LED_PIN;

                LED_flag[Yellow4_LED] = LED_ON;
            }

            // If channel1 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                RED4_LED_PORT |= RED4_LED_PIN;

                LED_flag[RED4_LED] = LED_ON;
            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {
                Yellow5_LED_PORT |= Yellow5_LED_PIN;

                LED_flag[Yellow5_LED] = LED_ON;
            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {
                RED5_LED_PORT |= RED5_LED_PIN;

                LED_flag[RED5_LED] = LED_ON;
            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                Yellow6_LED_PORT |= Yellow6_LED_PIN;

                LED_flag[Yellow6_LED] = LED_ON;
            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                RED6_LED_PORT |= RED6_LED_PIN;

                LED_flag[RED6_LED] = LED_ON;
            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                Yellow7_LED_PORT |= Yellow7_LED_PIN;

                LED_flag[Yellow7_LED] = LED_ON;
            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                RED7_LED_PORT |= RED7_LED_PIN;

                LED_flag[RED7_LED] = LED_ON;
            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                Yellow8_LED_PORT |= Yellow8_LED_PIN;

                LED_flag[Yellow8_LED] = LED_ON;
            }

            // If channel1 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                RED8_LED_PORT |= RED8_LED_PIN;

                LED_flag[RED8_LED] = LED_ON;
            }

            break;
        default:
            break;
    }
}


/*  Function    : ledsBlink
 *  Inputs      : channelNumber
 *  Return      : -
 *  Desc        : Blink desired leds for specific channel.
 *  NOT         :
 */


void ledsBlink(u8 channelNumber)
{
    switch(channelNumber)
    {
        case Channel1:

            // If channel1 signal is alarm

            if((channel_flag[I1_Alarm] == TRUE) && (channel_flag[I1_Trip] == FALSE))
            {
                LED_Blink(&Yellow1_LED_PORT, Yellow1_LED_PIN);
                LED_flag[Yellow1_LED] = LED_BLINK;
            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {
                LED_Blink(&RED1_LED_PORT, RED1_LED_PIN);
                LED_flag[RED1_LED] = LED_BLINK;
            }


            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                LED_Blink(&Yellow2_LED_PORT, Yellow2_LED_PIN);
                LED_flag[Yellow2_LED] = LED_BLINK;
            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                LED_Blink(&RED2_LED_PORT, RED2_LED_PIN);
                LED_flag[RED2_LED] = LED_BLINK;
            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {
                LED_Blink(&Yellow3_LED_PORT, Yellow3_LED_PIN);
                LED_flag[Yellow3_LED] = LED_BLINK;
            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {
                LED_Blink(&RED3_LED_PORT, RED3_LED_PIN);
                LED_flag[RED3_LED] = LED_BLINK;
            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                LED_Blink(&Yellow4_LED_PORT, Yellow4_LED_PIN);
                LED_flag[Yellow4_LED] = LED_BLINK;
            }

            // If channel4 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                LED_Blink(&RED4_LED_PORT, RED4_LED_PIN);
                LED_flag[RED4_LED] = LED_BLINK;
            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {
                LED_Blink(&Yellow5_LED_PORT, Yellow5_LED_PIN);
                LED_flag[Yellow5_LED] = LED_BLINK;
            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {
                LED_Blink(&RED5_LED_PORT, RED5_LED_PIN);
                LED_flag[RED5_LED] = LED_BLINK;
            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                LED_Blink(&Yellow6_LED_PORT, Yellow6_LED_PIN);
                LED_flag[Yellow6_LED] = LED_BLINK;
            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                LED_Blink(&RED6_LED_PORT, RED6_LED_PIN);
                LED_flag[RED6_LED] = LED_BLINK;
            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                LED_Blink(&Yellow7_LED_PORT, Yellow7_LED_PIN);
                LED_flag[Yellow7_LED] = LED_BLINK;
            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                LED_Blink(&RED7_LED_PORT, RED7_LED_PIN);
                LED_flag[RED7_LED] = LED_BLINK;
            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                LED_Blink(&Yellow8_LED_PORT, Yellow8_LED_PIN);
                LED_flag[Yellow8_LED] = LED_BLINK;
            }

            // If channel8 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                LED_Blink(&RED8_LED_PORT, RED8_LED_PIN);
                LED_flag[RED8_LED] = LED_BLINK;
            }

            break;
        default:
            break;
    }

}



/*  Function    : ledsPassive
 *  Inputs      : channelNumber
 *  Return      : -
 *  Desc        : Make passive desired leds for specific channel.
 *  NOT         :
 */


void ledsPassive(u8 channelNumber)
{
    switch(channelNumber)
    {
        case Channel1:

            // If channel1 signal is alarm

            if((channel_flag[I1_Alarm] == TRUE) && (channel_flag[I1_Trip] == FALSE))
            {
                Yellow1_LED_PORT  &= ~Yellow1_LED_PIN;
                LED_flag[Yellow1_LED] = LED_OFF;
            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {
                RED1_LED_PORT  &= ~RED1_LED_PIN;   // Closing LED1 for channel1
                LED_flag[RED1_LED] = LED_OFF;
            }

            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                Yellow2_LED_PORT  &= ~Yellow2_LED_PIN;
                LED_flag[Yellow2_LED] = LED_OFF;
            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                RED2_LED_PORT  &= ~RED2_LED_PIN;   // Closing LED2 for channel2
                LED_flag[RED2_LED] = LED_OFF;
            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {
                Yellow3_LED_PORT  &= ~Yellow3_LED_PIN;
                LED_flag[Yellow3_LED] = LED_OFF;
            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {
                RED3_LED_PORT  &= ~RED3_LED_PIN;   // Closing LED3 for channel3
                LED_flag[RED3_LED] = LED_OFF;
            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                Yellow4_LED_PORT  &= ~Yellow4_LED_PIN;
                LED_flag[Yellow4_LED] = LED_OFF;
            }

            // If channel4 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                RED4_LED_PORT  &= ~RED4_LED_PIN;   // Closing LED4 for channel4
                LED_flag[RED4_LED] = LED_OFF;
            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {
                Yellow5_LED_PORT  &= ~Yellow5_LED_PIN;
                LED_flag[Yellow5_LED] = LED_OFF;
            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {
                RED5_LED_PORT  &= ~RED5_LED_PIN;   // Closing LED5 for channel5
                LED_flag[RED5_LED] = LED_OFF;
            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                Yellow6_LED_PORT  &= ~Yellow6_LED_PIN;
                LED_flag[Yellow6_LED] = LED_OFF;
            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                RED6_LED_PORT  &= ~RED6_LED_PIN;   // Closing LED6 for channel6
                LED_flag[RED6_LED] = LED_OFF;
            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                Yellow7_LED_PORT  &= ~Yellow7_LED_PIN;
                LED_flag[Yellow7_LED] = LED_OFF;
            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                RED7_LED_PORT  &= ~RED7_LED_PIN;   // Closing LED7 for channel7
                LED_flag[RED7_LED] = LED_OFF;
            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                Yellow8_LED_PORT  &= ~Yellow8_LED_PIN;
                LED_flag[Yellow8_LED] = LED_OFF;
            }

            // If channel8 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                RED8_LED_PORT  &= ~RED8_LED_PIN;
                LED_flag[RED8_LED] = LED_OFF;
            }


            break;
        default:
            break;
    }

}

