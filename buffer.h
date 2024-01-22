/******************** (C) COPYRIGHT 2019 ORION EE ********************************
* File Name          : buffer.h
* Author             : Sercan Tun�ay
* Version            : V1.0
* Date               : 30/10/2019
* Description        : Buffer library
********************************************************************************/

#ifndef BUFFER_H_
#define BUFFER_H_

#include "cnc.h"

typedef struct buffer_s
{
  u8 buffer_write_index;
  u8 buffer_read_index;
  u16 buffer_avg;
  u32 buffer_square_avg;
  u8 buffer_chunk[SAMPLE_BUFFER_LEN];
}buffer_t;

typedef struct adc_buffer_s
{
  u8 buffer_write_index;
  u8 buffer_read_index;
  u32 buffer_avg;
  u32 buffer_square_avg;
  u16 buffer_max_pk;
  u16 buffer_min_pk;
  u16 buffer_chunk[ADC_SAMPLE_BUFFER_LEN];
  u8 buffer_direction;
}adc_buffer_t;



extern void get_buff_avg(adc_buffer_t *buffer_ptr);
extern void get_buff_square_avg(adc_buffer_t *buffer_ptr);
extern void get_buffer_direction(adc_buffer_t *buffer_ptr);
extern void discard_buffer(buffer_t *buff_ptr);
extern u8 read_sample_from_buffer(buffer_t *buff_ptr, u8 *sample_ptr);
extern void write_sample_to_buffer(buffer_t *buffer_ptr, u8 sample);
extern void write_sample_to_adc_buffer(adc_buffer_t *buffer_ptr, u16 sample);

#endif /* BUFFER_H_ */
