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
    for (ledNumber = 0; ledNumber < NUM_LEDS; ++ledNumber)
    {
        ledsPassive(ledNumber);
        delay_ms(ledBetween_Duration); // Adjust the delay as needed

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
    for (ledNumber = 0; ledNumber < NUM_LEDS; ++ledNumber)
    {
        ledsActive(ledNumber);
        delay_ms(ledBetween_Duration); // Adjust the delay as needed

    }
}


///////   Driving LEDs via SPI Functions    ////////


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

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {
                RED1_LED_PORT |= RED1_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                Yellow2_LED_PORT |= Yellow2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                RED2_LED_PORT |= RED2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {
                Yellow3_LED_PORT |= Yellow3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {
                RED3_LED_PORT |= RED3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                Yellow4_LED_PORT |= Yellow4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel1 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                RED4_LED_PORT |= RED4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {
                Yellow5_LED_PORT |= Yellow5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {
                RED5_LED_PORT |= RED5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                Yellow6_LED_PORT |= Yellow6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                RED6_LED_PORT |= RED6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                Yellow7_LED_PORT |= Yellow7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                RED7_LED_PORT |= RED7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                Yellow8_LED_PORT |= Yellow8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel1 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                RED8_LED_PORT |= RED8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
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

                // Blink the LED by toggling between the specified intensity and 0

                Yellow1_LED_PORT |= Yellow1_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow1_LED_PORT  &= ~Yellow1_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED1_LED_PORT |= RED1_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED1_LED_PORT &= ~RED1_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }


            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow2_LED_PORT |= Yellow2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow2_LED_PORT  &= ~Yellow2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED2_LED_PORT |= RED2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED2_LED_PORT  &= ~RED2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow3_LED_PORT |= Yellow3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow3_LED_PORT  &= ~Yellow3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED3_LED_PORT |= RED3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED3_LED_PORT  &= ~RED3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow4_LED_PORT |= Yellow4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow4_LED_PORT  &= ~Yellow4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel4 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED4_LED_PORT |= RED4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED4_LED_PORT  &= ~RED4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow5_LED_PORT |= Yellow5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow5_LED_PORT  &= ~Yellow5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED5_LED_PORT |= RED5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED5_LED_PORT  &= ~RED5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow6_LED_PORT |= Yellow6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow6_LED_PORT  &= ~Yellow6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED6_LED_PORT |= RED6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED6_LED_PORT  &= ~RED6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow7_LED_PORT |= Yellow7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow7_LED_PORT  &= ~Yellow7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED7_LED_PORT |= RED7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED7_LED_PORT  &= ~RED7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                Yellow8_LED_PORT |= Yellow8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                Yellow8_LED_PORT  &= ~Yellow8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

            }

            // If channel8 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {

                // Blink the LED by toggling between the specified intensity and 0

                RED8_LED_PORT |= RED8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed

                RED8_LED_PORT  &= ~RED8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
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

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel1 signal is Trip

            else if((channel_flag[I1_Alarm] == FALSE) && (channel_flag[I1_Trip] == TRUE))
            {
                RED1_LED_PORT  &= ~RED1_LED_PIN;   // Closing LED1 for channel1

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel2:

            // If channel2 signal is alarm

            if((channel_flag[I2_Alarm] == TRUE) && (channel_flag[I2_Trip] == FALSE))
            {
                Yellow2_LED_PORT  &= ~Yellow2_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel2 signal is Trip

            else if((channel_flag[I2_Alarm] == FALSE) && (channel_flag[I2_Trip] == TRUE))
            {
                RED2_LED_PORT  &= ~RED2_LED_PIN;   // Closing LED2 for channel2

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel3:

            // If channel3 signal is alarm

            if((channel_flag[I3_Alarm] == TRUE) && (channel_flag[I3_Trip] == FALSE))
            {
                Yellow3_LED_PORT  &= ~Yellow3_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel3 signal is Trip

            else if((channel_flag[I3_Alarm] == FALSE) && (channel_flag[I3_Trip] == TRUE))
            {
                RED3_LED_PORT  &= ~RED3_LED_PIN;   // Closing LED3 for channel3

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel4:

            // If channel4 signal is alarm

            if((channel_flag[I4_Alarm] == TRUE) && (channel_flag[I4_Trip] == FALSE))
            {
                Yellow4_LED_PORT  &= ~Yellow4_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel4 signal is Trip

            else if((channel_flag[I4_Alarm] == FALSE) && (channel_flag[I4_Trip] == TRUE))
            {
                RED4_LED_PORT  &= ~RED4_LED_PIN;   // Closing LED4 for channel4

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel5:

            // If channel5 signal is alarm

            if((channel_flag[I5_Alarm] == TRUE) && (channel_flag[I5_Trip] == FALSE))
            {
                Yellow5_LED_PORT  &= ~Yellow5_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel5 signal is Trip

            else if((channel_flag[I5_Alarm] == FALSE) && (channel_flag[I5_Trip] == TRUE))
            {
                RED5_LED_PORT  &= ~RED5_LED_PIN;   // Closing LED5 for channel5

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel6:

            // If channel6 signal is alarm

            if((channel_flag[I6_Alarm] == TRUE) && (channel_flag[I6_Trip] == FALSE))
            {
                Yellow6_LED_PORT  &= ~Yellow6_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel6 signal is Trip

            else if((channel_flag[I6_Alarm] == FALSE) && (channel_flag[I6_Trip] == TRUE))
            {
                RED6_LED_PORT  &= ~RED6_LED_PIN;   // Closing LED6 for channel6

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel7:

            // If channel7 signal is alarm

            if((channel_flag[I7_Alarm] == TRUE) && (channel_flag[I7_Trip] == FALSE))
            {
                Yellow7_LED_PORT  &= ~Yellow7_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel7 signal is Trip

            else if((channel_flag[I7_Alarm] == FALSE) && (channel_flag[I7_Trip] == TRUE))
            {
                RED7_LED_PORT  &= ~RED7_LED_PIN;   // Closing LED7 for channel7

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            break;

        case Channel8:

            // If channel8 signal is alarm

            if((channel_flag[I8_Alarm] == TRUE) && (channel_flag[I8_Trip] == FALSE))
            {
                Yellow8_LED_PORT  &= ~Yellow8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }

            // If channel8 signal is Trip

            else if((channel_flag[I8_Alarm] == FALSE) && (channel_flag[I8_Trip] == TRUE))
            {
                RED8_LED_PORT  &= ~RED8_LED_PIN;

                delay_ms(blinkDuration); // Adjust the delay as needed
            }


            break;
        default:
            break;
    }

}



/*  Function    : LP5860_BlinkLED
 *  Inputs      : ledNumber, blinkDuration
 *  Return      : -
 *  Desc        : Blink a led
 */

/*
void LP5860_BlinkLED(u8 ledNumber, u16 blinkDuration)
{

    start_timeout_ms(LED_BLINK_TO, blinkDuration);

    while (check_timeout(LED_BLINK_TO) != TO_OCCURED)
    {
        // Blink the LED by toggling between the specified intensity and 0

        LP5860_SetLED(ledNumber);

        delay_ms(blinkDuration); // Adjust the delay as needed

        LP5860_SetLED(ledNumber);

        delay_ms(blinkDuration); // Adjust the delay as needed


        if(check_timeout(LED_BLINK_TO) == TO_OCCURED)
        {

            break;
        }

    }

    // Turn off the LED after the blink duration

    LP5860_SetLED(ledNumber);

}

*/
