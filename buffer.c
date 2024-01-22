/******************** (C) COPYRIGHT 2020 ORION EE ********************************
* File Name          : buffer.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 18/03/2020
* Description        : buffer.c
********************************************************************************/
#include <msp430.h>
#include "main.h"

#include "bsp.h"
#include "buffer.h"
#include "cnc.h"

#include "ram.h"

#include "telemetry.h"
#include "utilities.h"



/*  Function    : read_sample_from_adc_buffer
 *  Inputs      : -
 *  Return      : -
 *  Desc        : örneði buffer'dan çek Overflow korumasý yok, yalnýzca info log var.
 */
u8 read_sample_from_buffer(buffer_t *buff_ptr, u8 *sample_ptr)
{
    u8 read_index, write_index;

    CLEAR_INTERRUPTS;

    read_index  = buff_ptr->buffer_read_index;
    write_index = buff_ptr->buffer_write_index;

    // if buffer is emty, return
    if(read_index == write_index)
    {
        RESTORE_INTERRUPTS;
        return FALSE;
    }

    *sample_ptr = buff_ptr->buffer_chunk[read_index];

    // circular que
    read_index++;
    if(read_index == SAMPLE_BUFFER_LEN)
    {
        read_index = 0;
    }

    buff_ptr->buffer_read_index = read_index;

    RESTORE_INTERRUPTS;
    return TRUE;
}


/*  Function    : write_sample_to_buffer
 *  Inputs      : -
 *  Return      : -
 *  Desc        : örneði buffer'a yazar. Overflow korumasý yok, yalnýzca info log var. Interrupt içinde çalýþýr
 */
void write_sample_to_buffer(buffer_t *buffer_ptr, u8 sample)
{
    u8 write_index, next_index;
    u8 read_index;

    // Local initialization - abstraction
    write_index = buffer_ptr->buffer_write_index;
    read_index  = buffer_ptr->buffer_read_index;

    // check if que full
    next_index = write_index + 1;
    if(next_index == SAMPLE_BUFFER_LEN)
    {
        next_index = 0;
    }

    // err check
    if(next_index == read_index )
    {
        //system_status.uart_rx_buff_full_err++;
        return;
    }

    // sample
    buffer_ptr->buffer_chunk[write_index] = sample;

    //update global ptr
    buffer_ptr->buffer_write_index = next_index;

}

/*  Function    : write_u16_sample_to_buffer
 *  Inputs      : -
 *  Return      : -
 *  Desc        : örneði buffer'a yazar.
 */
void write_sample_to_adc_buffer(adc_buffer_t *buffer_ptr, u16 sample)
{
    u8 write_index, next_index;
//    u8 read_index;

    // Local initialization - abstraction
    write_index = buffer_ptr->buffer_write_index;
//    read_index  = buffer_ptr->buffer_read_index;

    // check if que full
    next_index = write_index + 1;
    if(next_index == ADC_SAMPLE_BUFFER_LEN)
    {
        next_index = 0;
    }



    // sample
    buffer_ptr->buffer_chunk[write_index] = sample;

    //update global ptr
    buffer_ptr->buffer_write_index = next_index;

}

