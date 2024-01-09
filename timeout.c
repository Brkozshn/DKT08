/******************** (C) COPYRIGHT 2014 ORION EE ********************************
* File Name          : timeout.c
* Author             : Sercan Tunçay
* Version            : V1.0
* Date               : 01/10/2014
* Description        : timeouts
********************************************************************************/

#include "timeout.h"
#include "main.h"


timeout_file_t timeouts[NUM_OF_TIMEOUTS];

/*  Function    : process_timeouts
 *  Inputs      : -
 *  Return      : -
 *  Desc        : process timeout structure status
 */

void process_timeouts()
{
     u32 i;

    for(i=0; i < NUM_OF_TIMEOUTS; i++)
    {
        if(timeouts[i].timeout_activated == TRUE)
        {
            if(timeouts[i].countdown > 0)
            {
              timeouts[i].countdown--;
              timeouts[i].timeout_status = TO_COUNTING_DOWN;
              continue;
            }

            if(timeouts[i].countdown == 0)
            {
                timeouts[i].timeout_status = TO_OCCURED;
                timeouts[i].timeout_activated = FALSE;
            }
        }
    }
}


/*  Function    : start_timeout_ms
 *  Inputs      : -
 *  Return      : -
 *  Desc        : start a timeout
 */
void start_timeout_ms(u8 to_no, u32 to_val_ms)
{
//CLEAR_INTERRUPTS;
    timeouts[to_no].timeout_status      = TO_LOADED;
    timeouts[to_no].countdown           = to_val_ms;
    timeouts[to_no].timeout_activated   = TRUE;
//RESTORE_INTERRUPTS;
}


/*  Function    : check_timeout
 *  Inputs      : -
 *  Return      : status of TO
 *  Desc        : check timeout and clears the status to IDLE if OCCURED is returned
 */


u32 check_timeout(u8 to_no)
{
    u8 *status_ptr;

//CLEAR_INTERRUPTS;

    status_ptr = &timeouts[to_no].timeout_status;

    if(*status_ptr == TO_OCCURED)
    {
        *status_ptr = TO_IDLE;
        return TO_OCCURED;
    }

//RESTORE_INTERRUPTS;

    return *status_ptr;

}


/*  Function    : get_time_ms
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
u32 get_time_ms()
{
    return system_status.timer_tick;
}

/*  Function    : calc_time_diff_ms
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
u32 calc_time_diff_ms(u32 prev_time)
{
    return (system_status.timer_tick - prev_time);
}


