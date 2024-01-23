/******************** (C) COPYRIGHT 2023 ORION EE ********************************
* File Name          : submain.c
* Author             : Burak Ozsahin
* Version            : V1.0
* Date               : 15/09/2023
* Description        : Fram functions
********************************************************************************/


#include <msp430.h>
#include "bsp.h"
#include "main.h"
#include "button.h"
#include "fram.h"
#include "timeout.h"

// u8 channel_flag[NUM_OF_CHANNEL];            /// Flag for channel set (Trip or Alarm).


// Statically-initialized variable
//#ifdef __TI_COMPILER_VERSION__
#pragma PERSISTENT(channel_flag)
#pragma LOCATION(channel_flag, 0x8162)


 u8 channel_flag[NUM_OF_CHANNEL] = {0};            /// Flag for channel set (Trip or Alarm).

//#elif __IAR_SYSTEMS_ICC__
//__persistent unsigned char channel_flag[NUM_OF_CHANNEL];
//#else
//// Port the following variable to an equivalent persistent functionality for the specific compiler being used
//unsigned char channel_flag[NUM_OF_CHANNEL];
//#endif



 // Statically-initialized variable
// #ifdef __TI_COMPILER_VERSION__
 #pragma PERSISTENT(system_Run_number)
#pragma LOCATION(system_Run_number, 0x8172)

  u32 system_Run_number = 0;                                       // Number of times to system runs

// #elif __IAR_SYSTEMS_ICC__
// __persistent unsigned long system_Run_number = 0;
// #else
// // Port the following variable to an equivalent persistent functionality for the specific compiler being used
// unsigned long system_Run_number = 0;
// #endif



void Fram_Channel_flag(u8 channel, u8 status_HORN)
{

    SYSCFG0 = FRWPPW | FRWPOA0 | DFWP | PFWP;// Configure 1024 bytes for FRAM write


        // Döngü içinde switch'i kaldır. Yerine if koy

        // En aşağıda ise To_occured yap if ile sonra return veya break.

        switch(channel)
        {
            case Channel1:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I1_Alarm] = TRUE;
                     channel_flag[I1_Trip] = FALSE;
                }

                else if(status_HORN == PRESSED)
                {
                    /// Set channel 1 to Trip

                    channel_flag[I1_Trip] = TRUE;
                    channel_flag[I1_Alarm] = FALSE;
                }

                 break;


            case Channel2:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I2_Alarm] = TRUE;
                     channel_flag[I2_Trip] = FALSE;
                }

                else if(status_HORN == PRESSED)
                {
                    /// Set channel 2 to Trip

                    channel_flag[I2_Trip] = TRUE;
                    channel_flag[I2_Alarm] = FALSE;
                }

                break;


            case Channel3:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I3_Alarm] = TRUE;
                     channel_flag[I3_Trip] = FALSE;
                }


                else if(status_HORN == PRESSED)
                {
                    /// Set channel 3 to Trip

                    channel_flag[I3_Trip] = TRUE;
                    channel_flag[I3_Alarm] = FALSE;
                }

                break;


            case Channel4:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I4_Alarm] = TRUE;
                     channel_flag[I4_Trip] = FALSE;
                }

                else if(status_HORN == PRESSED)
                {
                    /// Set channel 4 to Trip

                    channel_flag[I4_Trip] = TRUE;
                    channel_flag[I4_Alarm] = FALSE;
                }

                break;


            case Channel5:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I5_Alarm] = TRUE;
                     channel_flag[I5_Trip] = FALSE;
                }


                else if(status_HORN == PRESSED)
                {
                    /// Set channel 5 to Trip

                    channel_flag[I5_Trip] = TRUE;
                    channel_flag[I5_Alarm] = FALSE;
                }

                break;


            case Channel6:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I6_Alarm] = TRUE;
                     channel_flag[I6_Trip] = FALSE;
                }


                else if(status_HORN == PRESSED)
                {
                    /// Set channel 6 to Trip

                    channel_flag[I6_Trip] = TRUE;
                    channel_flag[I6_Alarm] = FALSE;
                }

                break;


            case Channel7:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I7_Alarm] = TRUE;
                     channel_flag[I7_Trip] = FALSE;
                }


                else if(status_HORN == PRESSED)
                {
                    /// Set channel 7 to Trip

                    channel_flag[I7_Trip] = TRUE;
                    channel_flag[I7_Alarm] = FALSE;
                }

                break;


            case Channel8:

                // Signal is in the alarm mode.

                if(status_HORN == AGAIN_PRESSED)
                {
                    // Default mode is alarm and blinks yellow.

                     channel_flag[I8_Alarm] = TRUE;
                     channel_flag[I8_Trip] = FALSE;
                }


                else if(status_HORN == PRESSED)
                {
                    /// Set channel 8 to Trip

                    channel_flag[I8_Trip] = TRUE;
                    channel_flag[I8_Alarm] = FALSE;
                }

                break;
            default:
                break;
        }

/*
        if(check_timeout(FRAM_TIMEOUT) == TO_OCCURED)
        {
            return;
        }
        */

    //}

        SYSCFG0 = FRWPPW | DFWP | PFWP;     // Program FRAM write protected (not writable)
}



/*  Function    : set_Channel_default
 *  Inputs      : -
 *  Return      : -
 *  Desc        :  Setting all Channels as default.
 */


void set_Channel_default()
{
  // Reset every settings to default.

    channel_flag[I1_Alarm] = TRUE;
    channel_flag[I1_Trip] = FALSE;
    channel_flag[I2_Alarm] = TRUE;
    channel_flag[I2_Trip] = FALSE;
    channel_flag[I3_Alarm] = TRUE;
    channel_flag[I3_Trip] = FALSE;
    channel_flag[I4_Alarm] = TRUE;
    channel_flag[I4_Trip] = FALSE;
    channel_flag[I5_Alarm] = TRUE;
    channel_flag[I5_Trip] = FALSE;
    channel_flag[I6_Alarm] = TRUE;
    channel_flag[I6_Trip] = FALSE;
    channel_flag[I7_Alarm] = TRUE;
    channel_flag[I7_Trip] = FALSE;
    channel_flag[I8_Alarm] = TRUE;
    channel_flag[I8_Trip] = FALSE;

}


