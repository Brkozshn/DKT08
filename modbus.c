/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : modbus.c
* Author             : Onur Kayï¿½kcï¿½
* Version            : V1.0
* Date               : 24/02/2022
* Description        : modbus functions
********************************************************************************/



#include <msp430.h>


#include "main.h"
#include "timeout.h"
#include "bsp.h"
#include "ram.h"
#include "cnc.h"
#include "string.h"
#include "stdlib.h"
#include "telemetry.h"
#include "button.h"
#include "uart_A0.h"
#include "uart_A1.h"
#include "submain.h"
#include "display.h"
#include "modbus.h"
#include "DS1302.h"
#include "ATM90E32.h"
#include "fram.h"

u8 report_ix = 0;
u8 all_report_ix = 0;

u16 mb_message_ix;
u16 info_ix;
u8 sn_unlock_flag = FALSE;
u16 temp_device_SN_H = 0;

/*  Function    : modbus_generate_and_inc_tx_packet_no
 *  Inputs      : -
 *  Return      : tx packet no
 *  Desc        : -
 */
u8 modbus_generate_and_inc_tx_packet_no()
{
    return system_status.modbus_protocol_curr_tx_no++;
}


/*  Function    : generate_modbus_error_msg
 *  Inputs      : data, len
 *  Return      : TRUE/FALSE
 *  Desc        : Capsulate packet and send via uart
 */
u8 generate_modbus_error_msg(u8 func_no, u8 error_code)
{

    u16 crc_result;
    u8 crc_data_ptr[MODBUS_MAX_ORDER];


    modbus_out_error_msg.mb_address           = modbus_adress;
    modbus_out_error_msg.mb_func_no           = func_no + 128;
    modbus_out_error_msg.mb_error_code        = error_code;

    crc_data_ptr[0] = modbus_out_error_msg.mb_address ;
    crc_data_ptr[1] = modbus_out_error_msg.mb_func_no ;
    crc_data_ptr[3] = modbus_out_error_msg.mb_error_code ;


    crc_result = generate_modbus_crc(&crc_data_ptr[0], 3);
    u_16byte.data_u16 = crc_result;

    modbus_out_error_msg.mb_crc_low  = u_16byte.data_u8[0];
    modbus_out_error_msg.mb_crc_high = u_16byte.data_u8[1];

    return TRUE;
}



/*  Function    : generate_modbus_msg
 *  Inputs      : data, len
 *  Return      : TRUE/FALSE
 *  Desc        : Capsulate packet and send via uart
 */
u8 generate_modbus_msg(u8 func_no, u8 *data_ptr, u8 data_len)
{
    u8 i;
    u16 crc_result;
    u8 crc_data_ptr[MODBUS_MAX_ORDER];
   // u8 start_order_no_high, start_order_no_low=0;
    // Max len cntrl
    if(data_len > MODBUS_OUT_MSG_DATA_SIZE)
        return FALSE;

    // Tx Operation cntrl
    // ... ?

    modbus_out_msg.mb_address           = modbus_adress;
    modbus_out_msg.mb_func_no           = func_no;
    modbus_out_msg.mb_data_len          = data_len*2;
   // modbus_out_msg.mb_start_adr_high    = start_order_no_high;
   // modbus_out_msg.mb_start_adr_low     = start_order_no_low;

    crc_data_ptr[0] = modbus_out_msg.mb_address ;
    crc_data_ptr[1] = modbus_out_msg.mb_func_no ;
    crc_data_ptr[2] = modbus_out_msg.mb_data_len ;

    for(i = 0; i < modbus_out_msg.mb_data_len ; i++)
    {
        crc_data_ptr[i+3] = data_ptr[i];
        modbus_out_msg.mb_data[i] = data_ptr[i];
        __no_operation();
    }

  //  crc_result = generate_modbus_crc( &modbus_out_msg.mb_data[0], modbus_out_msg.mb_data_len);
    crc_result = generate_modbus_crc(&crc_data_ptr[0], modbus_out_msg.mb_data_len+3);
    u_16byte.data_u16 = crc_result;

    modbus_out_msg.mb_crc_low  = u_16byte.data_u8[0];
    modbus_out_msg.mb_crc_high = u_16byte.data_u8[1];

    return TRUE;
}

/*  Function    : generate_modbus_write_msg
 *  Inputs      : -
 *  Return      : TRUE/FALSE
 *  Desc        : Capsulate packet and send via uart
 */
u8 generate_modbus_write_msg()
{

    u16 crc_result;
    u8 crc_data_ptr[MODBUS_MAX_ORDER];





    modbus_out_write_msg.mb_address           = modbus_adress;
    modbus_out_write_msg.mb_func_no           = modbus_in_write_msg.mb_func_no;
    modbus_out_write_msg.mb_start_adr_high    = modbus_in_write_msg.mb_start_adr_high;
    modbus_out_write_msg.mb_start_adr_low     = modbus_in_write_msg.mb_start_adr_low;
    modbus_out_write_msg.mb_register_len_high = modbus_in_write_msg.mb_register_len_high;
    modbus_out_write_msg.mb_register_len_low  = modbus_in_write_msg.mb_register_len_low;


    crc_data_ptr[0] = modbus_out_write_msg.mb_address ;
    crc_data_ptr[1] = modbus_out_write_msg.mb_func_no ;
    crc_data_ptr[2] = modbus_out_write_msg.mb_start_adr_high ;
    crc_data_ptr[3] = modbus_out_write_msg.mb_start_adr_low ;
    crc_data_ptr[4] = modbus_out_write_msg.mb_register_len_high ;
    crc_data_ptr[5] = modbus_out_write_msg.mb_register_len_low ;



  //  crc_result = generate_modbus_crc( &modbus_out_msg.mb_data[0], modbus_out_msg.mb_data_len);
    crc_result = generate_modbus_crc(&crc_data_ptr[0], 6);
    u_16byte.data_u16 = crc_result;

    modbus_out_write_msg.mb_crc_low  = u_16byte.data_u8[0];
    modbus_out_write_msg.mb_crc_high = u_16byte.data_u8[1];

    return TRUE;
}



/*  Function    : generate_modbus_single_write_msg
 *  Inputs      : -
 *  Return      : TRUE/FALSE
 *  Desc        : Capsulate packet and send via uart
 */
u8 generate_modbus_single_write_msg()
{

    u16 crc_result;
    u8 crc_data_ptr[MODBUS_MAX_ORDER];

    modbus_out_write_msg.mb_address           = modbus_adress;
    modbus_out_write_msg.mb_func_no           = modbus_in_msg.mb_func_no;
    modbus_out_write_msg.mb_start_adr_high    = modbus_in_msg.mb_start_adr_high;
    modbus_out_write_msg.mb_start_adr_low     = modbus_in_msg.mb_start_adr_low;
    modbus_out_write_msg.mb_register_len_high = modbus_in_msg.mb_data_high;
    modbus_out_write_msg.mb_register_len_low  = modbus_in_msg.mb_data_low;


    crc_data_ptr[0] = modbus_out_write_msg.mb_address ;
    crc_data_ptr[1] = modbus_out_write_msg.mb_func_no ;
    crc_data_ptr[2] = modbus_out_write_msg.mb_start_adr_high ;
    crc_data_ptr[3] = modbus_out_write_msg.mb_start_adr_low ;
    crc_data_ptr[4] = modbus_out_write_msg.mb_register_len_high ;
    crc_data_ptr[5] = modbus_out_write_msg.mb_register_len_low ;



  //  crc_result = generate_modbus_crc( &modbus_out_msg.mb_data[0], modbus_out_msg.mb_data_len);
    crc_result = generate_modbus_crc(&crc_data_ptr[0], 6);
    u_16byte.data_u16 = crc_result;

    modbus_out_write_msg.mb_crc_low  = u_16byte.data_u8[0];
    modbus_out_write_msg.mb_crc_high = u_16byte.data_u8[1];

    return TRUE;
}



u16 Convert_Write_Order_from_Address(u16 start_Adr)
{
    u16 order_num = 0;

    if((start_Adr >= MODBUS_PHASE_1_MEASUREMENT_WRITE_ORDER)&&(start_Adr < MODBUS_END_OF_ORDERS))
    {
        order_num = start_Adr - MODBUS_PHASE_1_MEASUREMENT_WRITE_ORDER + 5; //MODBUS_PHASE_1_MEASUREMENT_WRITE_ORDER = 5. sï¿½ra
    }
    else
    {
        switch(start_Adr)
          {
          case MODBUS_TEST_WRITE_ORDER:
              order_num = 0;
              break;

          case MODBUS_OWN_ADRESS_WRITE_ORDER:
              order_num = 1;
              break;

          case MODBUS_BAUDRATE_WRITE_ORDER:
              order_num = 2;
              break;

          case MODBUS_READ_LOCK_WRITE_ORDER:
              order_num = 3;
              break;

          case MODBUS_WRITE_LOCK_WRITE_ORDER:
              order_num = 4;
              break;

          case MODBUS_READ_KEY_WRITE_ORDER:
          case MODBUS_WRITE_KEY_WRITE_ORDER:
              order_num = start_Adr - MODBUS_READ_KEY_WRITE_ORDER + (MODBUS_END_OF_ORDERS - MODBUS_PHASE_1_MEASUREMENT_WRITE_ORDER + 1) + 5;
              break;

          }
    }

    return order_num;

}


u16 Convert_Order_from_Address(u16 start_Adr)
{
    u16 order_num = 0;

    if((start_Adr >= MODBUS_PHASE_1_MEASUREMENT_ORDER)&&(start_Adr < MODBUS_END_OF_ORDERS))
    {
        order_num = start_Adr - MODBUS_PHASE_1_MEASUREMENT_ORDER + 3; //MODBUS_PHASE_MEASUREMENTS_ORDER = 3. sï¿½ra
    }
    else
    {
        switch(start_Adr)
        {
        case MODBUS_TEST_ORDER:
            order_num = 0;
            break;

        case MODBUS_OWN_ADRESS_ORDER:
            order_num = 1;
            break;

        case MODBUS_BAUDRATE_ORDER:
            order_num = 2;
            break;

        case MODBUS_PGV_ORDER:
        case MODBUS_HWV_ORDER:
            order_num = start_Adr - MODBUS_PGV_ORDER + (MODBUS_END_OF_ORDERS - MODBUS_PHASE_1_MEASUREMENT_ORDER + 1) + 5;
            break;


        }
    }



    return order_num;
}


/*  Function    : process_modbus_multiple_read_msg
 *  Inputs      : data ptr, data len
 *  Return      : TRUE/FALSE
 *  Desc        :
 */
void process_modbus_multiple_read_msg(modbus_in_msg_t *msg_ptr)
{

    u16 order_no;
    u16 cnter;

   // int data;
    u16 data_u16;

    u8 data_ptr[MODBUS_MAX_ORDER];

    u_16byte.data_u8[0]=msg_ptr->mb_start_adr_low;
    u_16byte.data_u8[1]=msg_ptr->mb_start_adr_high;

    u16 start_adr = u_16byte.data_u16;//(((msg_ptr->mb_start_adr_high)<<8)&(msg_ptr->mb_start_adr_low));

    u_16byte.data_u8[0]=msg_ptr->mb_data_low;
    u_16byte.data_u8[1]=msg_ptr->mb_data_high;

    u16 data_len = u_16byte.data_u16;//(((msg_ptr->mb_data_high)<<8)&(msg_ptr->mb_data_low));

    time_ds_t temp_time_data;

    order_no = start_adr;

    __no_operation();


    if(order_no + data_len > MODBUS_MAX_ORDER)
    {
        __no_operation();
        //buraya arizalï¿½ istek gï¿½nderildi fonksiyonu yazï¿½lacak
    }

    __no_operation();

    if(order_no >= MODBUS_NUM_OF_ORDERS)
    {
        __no_operation();
        system_status.modbus_protocol_order_no_err++;
        return;
        //buraya arizalï¿½ istek gï¿½nderildi fonksiyonu yazï¿½lacak
    }


    order_no = Convert_Order_from_Address(start_adr);

//    temp_time_data = read_time();


    for(cnter = 0; cnter < data_len; cnter++ )
    {

        if(MODBUS_REPORT_NO_1 <= (cnter + start_adr) && (cnter + start_adr) < MODBUS_END_OF_ORDERS){
            mb_message_ix = cnter + start_adr - MODBUS_REPORT_NO_1;
            all_report_ix = mb_message_ix / 15;
            info_ix = mb_message_ix % 15;
            __no_operation();
            
            switch (info_ix)
            {
            case FAULT_REPORT_NO:
                data_u16 = all_report_ix + 1;
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L1_CURR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L2_CURR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L3_CURR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_E_CURR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L1_FAULT:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L2_FAULT:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_L3_FAULT:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_E_FAULT:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_DAY:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_MONTH:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_YEAR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_HOUR:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_MINUTE:
                u_16byte.data_u16 = data_u16;
            break;
            case FAULT_SECOND:
                u_16byte.data_u16 = data_u16;
            break;
            }
            __no_operation();
        }
        else
        {

            switch(cnter + start_adr)
            {
            case MODBUS_TEST_ORDER:
                data_u16 = 0;
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_OWN_ADRESS_ORDER:
                data_u16 = modbus_adress;
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_BAUDRATE_ORDER:
                switch (baudrate_A0)
                {
                case UART_2400:
                    data_u16 = 2400;
                    break;
                case UART_4800:
                    data_u16 = 4800;
                    break;
                case UART_9600:
                    data_u16 = 9600;
                    break;
                case UART_19200:
                    data_u16 = 19200;
                    break;
                case UART_38400:
                    data_u16 = 38400;
                    break;
                case UART_57600:
                    data_u16 = 57600;
                    break;
                default:
                    data_u16 = 0;
                    break;
                }
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_PHASE_1_MEASUREMENT_ORDER:
//                data_u16 = (u16)(line_currents[I1]);

                data_u16 = (u16)(0);
                u8 i = 0;

                channel_flag[I1_Trip] = 1;
                channel_flag[I2_Alarm] = 1;
                channel_flag[I4_Alarm] = 1;

                // Kanal mod konfigurasyonu  trip mi alarm mý  her kanal için 2 bit

                for(i = 0; i < NUM_OF_CHANNEL; i++)
                {
                    data_u16 |= (u16)(channel_flag[i] & 0x01) << i;
                    __no_operation();
                }


                //data_u16 = (u16)(565);
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_PHASE_2_MEASUREMENT_ORDER:
                //data_u16 = (u16)(line_currents[I2]);

                // Kanallarýn anlýk durumu hangi bit 1 ise sinyal var mý yok mu (active passive)
                data_u16 = (u16)(0);
                for(i = 0; i < NUM_OF_CASE; i++)
                {
                    data_u16 |= (u16)(caseFlag[i] & 0x01) << i;
                    __no_operation();
                }

                //data_u16 = (u16)(caseFlag[Channel1]);
                u_16byte.data_u16 = ~data_u16;
                __no_operation();
                break;

            case MODBUS_PHASE_3_MEASUREMENT_ORDER:


                // Sinyallerin gitme durumu hangi bit 1 ise sinyal gitmiþtir.
                data_u16 = (u16)(0);
                for(i = 0; i < NUM_OF_CASE; i++)
                {

                    if(caseFlag[i] == SIGNAL_DISAPPEARED)
                    {
                        data_u16 |= (u16)(caseFlag[i] & 0x01) << i;
                        __no_operation();
                    }
                }

//                data_u16 = (u16)(line_currents[I3]);
                //data_u16 = (u16)(channel_flag[I4_Trip]);
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_EARTH_MEASUREMENT_ORDER:
//                data_u16 = (u16)(line_currents[IE]);
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_PHASE_1_FAULT_ORDER:

                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_PHASE_2_FAULT_ORDER:

                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_PHASE_3_FAULT_ORDER:

                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_EARTH_FAULT_ORDER:

                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_EXTERNAL_ORDER:
                data_u16 = !system_status.system_battery_active_flag;
                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_FAULT_REPORT_COUNT_ORDER:
                u_16byte.data_u16 = data_u16;
                __no_operation();
                break;

            case MODBUS_FAULT_REPORT_LIST_ORDER:

                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L1_CURR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L2_CURR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L3_CURR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_E_CURR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L1_FAULT_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L2_FAULT_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_L3_FAULT_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_E_FAULT_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_DAY_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_MONTH_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_YEAR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_HOUR_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_MINUTE_ORDER:
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_FAULT_SECOND_ORDER:
                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_PHASE_CURRENT_ORDER:
            case MODBUS_PHASE_DETECTION_TIME_ORDER:
            case MODBUS_EARTH_CURRENT_ORDER:
            case MODBUS_EARTH_DETECTION_TIME_ORDER:
            case MODBUS_AUTO_RESET_TIME_ORDER:
            case MODBUS_AFTER_DRESET_IN_TIME_ORDER:
            case MODBUS_RELAY1_SETTING_ORDER:
            case MODBUS_RELAY2_SETTING_ORDER:
            case MODBUS_PHASE_FREQUENCY_ORDER:
                u_16byte.data_u16 = data_u16;
                __no_operation();
                
                break;

            case MODBUS_PASSWORD_ORDER:
                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_DATE_DAY_ORDER:
                data_u16 = temp_time_data.date;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_DATE_MONTH_ORDER:
                data_u16 = temp_time_data.month;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_DATE_YEAR_ORDER:
                data_u16 = temp_time_data.year;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_CLOCK_HOUR_ORDER:
                data_u16 = temp_time_data.hour;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_CLOCK_MINUTE_ORDER:
                data_u16 = temp_time_data.min;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_CLOCK_SECOND_ORDER:
                data_u16 = temp_time_data.sec;
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;

            case MODBUS_LANGUAGE_ORDER:
//                data_u16 = config_menu_variables[LANGUAGE];
                u_16byte.data_u16 = data_u16;
                __no_operation();

                break;
            case MODBUS_SOFTWARE_VERSION_ORDER:
                data_u16 = SOFTWARE_VERSION;
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_SERIAL_NO_HIGH_ORDER:
//                data_u16 = device_SN_H;
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_SERIAL_NO_LOW_ORDER:
//                data_u16 = device_SN_L;
                u_16byte.data_u16 = data_u16;
                break;
            case MODBUS_PGV_ORDER:
                data_u16 = SOFTWARE_VERSION;
                u_16byte.data_u16 = data_u16;
                break;

            case MODBUS_HWV_ORDER:
                data_u16 = HARDWARE_VERSION;
                u_16byte.data_u16 = data_u16;
                break;
            
            default:
                data_u16 = 0;
                u_16byte.data_u16 = data_u16;
                
                break;
            }
        }

        data_ptr[2*(cnter)+0] = u_16byte.data_u8[1];
        data_ptr[2*(cnter)+1] = u_16byte.data_u8[0];
        __no_operation();

    }



    __no_operation();




    generate_modbus_msg(modbus_in_msg.mb_func_no, &data_ptr[0], data_len );

    // Send it
    uart_send_modbus_frame();
}



/*  Function    : process_modbus_multiple_write_msg
 *  Inputs      : data ptr, data len
 *  Return      : TRUE/FALSE
 *  Desc        :
 */
void process_modbus_multiple_write_msg(modbus_in_write_msg_t *msg_ptr)
{


    u16 order_no;
    u16 cnter;

//    u8 data_ptr[MODBUS_MAX_ORDER];

    u_16byte.data_u8[0]=msg_ptr->mb_start_adr_low;
    u_16byte.data_u8[1]=msg_ptr->mb_start_adr_high;

    u16 start_adr = u_16byte.data_u16;//(((msg_ptr->mb_start_adr_high)<<8)&(msg_ptr->mb_start_adr_low));

    u_16byte.data_u8[0]=msg_ptr->mb_register_len_low;
    u_16byte.data_u8[1]=msg_ptr->mb_register_len_high;

 //   u16 register_len = u_16byte.data_u16;//(((msg_ptr->mb_data_high)<<8)&(msg_ptr->mb_data_low));

    u8 data_len = (msg_ptr->mb_data_len)>>1;

    int data;

    int temp_data;

    time_ds_t temp_time_data;

    order_no = start_adr;


    __no_operation();


    order_no = Convert_Write_Order_from_Address(start_adr);

//    temp_time_data = read_time();
    system_status.temp_system_second = temp_time_data.sec;
    system_status.temp_system_minute = temp_time_data.min;
    system_status.temp_system_hour = temp_time_data.hour;
    system_status.temp_system_day = temp_time_data.date;
    system_status.temp_system_month = temp_time_data.month;
    system_status.temp_system_year = temp_time_data.year;

    for(cnter = 0; cnter < data_len; cnter++ )
    {
        u_16byte.data_s8[1]=msg_ptr->mb_data[2*cnter];
        u_16byte.data_s8[0]=msg_ptr->mb_data[2*cnter+1];

        data = u_16byte.data_int16;
        order_no = start_adr+cnter;
        __no_operation();

//          SYSCFG0 = FRWPPW | FRWPOA0 | DFWP | PFWP;// Configure 1024 bytes for FRAM write

          switch(order_no)
            {
            case MODBUS_TEST_WRITE_ORDER:

                __no_operation();

                break;

            case MODBUS_OWN_ADRESS_WRITE_ORDER:
                modbus_adress = data;
                __no_operation();

                break;

            case MODBUS_BAUDRATE_WRITE_ORDER:
                if(data < NUM_OF_BAUDRATE)
                {
                    baudrate_A0 = data;
                    baudrate_A1 = data;
                    UART_A1_init();
                }
                __no_operation();

                break;

            case MODBUS_FAULT_RESET_WRITE_ORDER:
                if(data == RESET_FUNC_NUM)
                {
//                    resetFunc();
                }

                __no_operation();

                break;

            case MODBUS_DELETE_REPORT_WRITE_ORDER:

                break;

            case MODBUS_DELETE_ALL_WRITE_ORDER:
                
                
                break;

            case MODBUS_FAULT_REPORT_LIST_WRITE_ORDER:

                break;

            case MODBUS_PHASE_CURRENT_WRITE_ORDER:
            case MODBUS_PHASE_DETECTION_TIME_WRITE_ORDER:
            case MODBUS_EARTH_CURRENT_WRITE_ORDER:
            case MODBUS_EARTH_DETECTION_TIME_WRITE_ORDER:
            case MODBUS_AUTO_RESET_TIME_WRITE_ORDER:
            case MODBUS_AFTER_DRESET_IN_TIME_WRITE_ORDER:
            case MODBUS_RELAY1_SETTING_WRITE_ORDER:
            case MODBUS_RELAY2_SETTING_WRITE_ORDER:
            case MODBUS_PHASE_FREQUENCY_WRITE_ORDER:
            


                __no_operation();

//                switch (start_adr - MODBUS_PHASE_CURRENT_WRITE_ORDER)
//                {
//                case PHASE_CURRENT:
//
//                    break;
//
//                case PHASE_DETECTION_TIME:
//
//                    break;
//
//                case EARTH_CURRENT:
//
//                    break;
//
//                case EARTH_DETECTION_TIME:
//
//                    break;
//
//                case AUTO_RESET_TIME:
//
//                    break;
//
//                case DIGITAL_RESET_TIME:
//
//                    break;
//
//                case RELAY1_SETTING:
//
//                    break;
//
//                case RELAY2_SETTING:
//
//                    break;
//
//                case PHASE_FREQ:
//
//                    break;
//                }

                break;
            case MODBUS_PASSWORD_WRITE_ORDER:
                break;

            case MODBUS_DATE_DAY_WRITE_ORDER:
                if(data<=31 && data >=1)
                {
                    system_status.temp_system_day = data;
                    checkDayValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_DATE_MONTH_WRITE_ORDER:
                if(data<=12 && data >=1)
                {
                    system_status.temp_system_month = data;
                    checkMonthValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_DATE_YEAR_WRITE_ORDER:
                if(data<=99 && data >= 23)
                {
                    system_status.temp_system_year = data;
                    checkMonthValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }   

                __no_operation();

                break;

            case MODBUS_CLOCK_HOUR_WRITE_ORDER:
                if(data <=23)
                {
                    system_status.temp_system_hour = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;
            case MODBUS_CLOCK_MINUTE_WRITE_ORDER:
                if(data <= 59)
                {
                    system_status.temp_system_minute = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;
            case MODBUS_CLOCK_SECOND_WRITE_ORDER:
                if(data <= 59)
                {
                    system_status.temp_system_second = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_LANGUAGE_WRITE_ORDER:

                break;

            case MODBUS_FACTORY_RESET_WRITE_ORDER:

                break;

            case MODBUS_LED_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(LED_TEST);
                }

                __no_operation();

                break;

            case MODBUS_RELAY_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(RELAY_TEST);
                }

                __no_operation();

                break;

            case MODBUS_LAMP_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(LAMP_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L1_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L1_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L2_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L2_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L3_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L3_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_E_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(E_FAULT_TEST);
                }

                __no_operation();

                break;
            case MODBUS_SN_UNLOCK_WRITE_ORDER:
                if(data == 13579)
                {
                    sn_unlock_flag = TRUE;
                    __no_operation();
                }
                break;
            case MODBUS_SERIAL_NO_HIGH_WRITE_ORDER:
                if(sn_unlock_flag == TRUE){
                    temp_device_SN_H = data;
                    __no_operation();
                }
                break;
            case MODBUS_SERIAL_NO_LOW_WRITE_ORDER:
                if(sn_unlock_flag == TRUE){
//                    device_SN_H = temp_device_SN_H;
//                    device_SN_L = data;
                    sn_unlock_flag = FALSE;
                    __no_operation();
                }
                break;
            }



          __no_operation();

//          SYSCFG0 = FRWPPW | DFWP | PFWP;     // Program FRAM write protected (not writable)


        __no_operation();
    }

    generate_modbus_write_msg();

    // Send it
    uart_send_modbus_frame();
}


/*  Function    : process_modbus_single_write_msg
 *  Inputs      : data ptr, data len
 *  Return      : TRUE/FALSE
 *  Desc        :
 */
void process_modbus_single_write_msg(modbus_in_msg_t *msg_ptr)
{


    u16 order_no;
    int data;
    u32 temp_data;

    time_ds_t temp_time_data;
    //u16 data_u16;
    //u8 cnter;

    //u8 data_ptr[MODBUS_MAX_ORDER];

    u_16byte.data_u8[0]=msg_ptr->mb_start_adr_low;
    u_16byte.data_u8[1]=msg_ptr->mb_start_adr_high;

    u16 start_adr = u_16byte.data_u16;//(((msg_ptr->mb_start_adr_high)<<8)&(msg_ptr->mb_start_adr_low));

    u_16byte.data_u8[0]=msg_ptr->mb_data_low;
    u_16byte.data_u8[1]=msg_ptr->mb_data_high;

    //u16 data_write = u_16byte.data_u16;//(((msg_ptr->mb_data_high)<<8)&(msg_ptr->mb_data_low));
    data = u_16byte.data_int16;;



    order_no = start_adr;

    if(MODBUS_DATE_DAY_WRITE_ORDER <= start_adr && start_adr <= MODBUS_CLOCK_SECOND_WRITE_ORDER)
    {
//        temp_time_data = read_time();
        system_status.temp_system_second = temp_time_data.sec;
        system_status.temp_system_minute = temp_time_data.min;
        system_status.temp_system_hour = temp_time_data.hour;
        system_status.temp_system_day = temp_time_data.date;
        system_status.temp_system_month = temp_time_data.month;
        system_status.temp_system_year = temp_time_data.year;
    }

    __no_operation();



    order_no = Convert_Write_Order_from_Address(start_adr);



//    SYSCFG0 = FRWPPW | FRWPOA0 | DFWP | PFWP;// Configure 1024 bytes for FRAM write

    switch(start_adr)
      {
            case MODBUS_TEST_WRITE_ORDER:

                __no_operation();

                break;

            case MODBUS_OWN_ADRESS_WRITE_ORDER:
                modbus_adress = data;
                __no_operation();

                break;

            case MODBUS_BAUDRATE_WRITE_ORDER:
                if(data < NUM_OF_BAUDRATE)
                {
                    baudrate_A0 = data;
                    baudrate_A1 = data;
                    UART_A1_init();
                }
                __no_operation();

                break;

            case MODBUS_FAULT_RESET_WRITE_ORDER:
                if(data == RESET_FUNC_NUM)
                {
//                    resetFunc();
                }

                __no_operation();

                break;

            case MODBUS_DELETE_REPORT_WRITE_ORDER:

                break;

            case MODBUS_DELETE_ALL_WRITE_ORDER:
                
                
                break;

            case MODBUS_FAULT_REPORT_LIST_WRITE_ORDER:
                break;

            case MODBUS_PHASE_CURRENT_WRITE_ORDER:
            case MODBUS_PHASE_DETECTION_TIME_WRITE_ORDER:
            case MODBUS_EARTH_CURRENT_WRITE_ORDER:
            case MODBUS_EARTH_DETECTION_TIME_WRITE_ORDER:
            case MODBUS_AUTO_RESET_TIME_WRITE_ORDER:
            case MODBUS_AFTER_DRESET_IN_TIME_WRITE_ORDER:
            case MODBUS_RELAY1_SETTING_WRITE_ORDER:
            case MODBUS_RELAY2_SETTING_WRITE_ORDER:
            case MODBUS_PHASE_FREQUENCY_WRITE_ORDER:
            

                __no_operation();


                break;
            case MODBUS_PASSWORD_WRITE_ORDER:

                break;

            case MODBUS_DATE_DAY_WRITE_ORDER:
                if(data<=31 && data >=1)
                {
                    system_status.temp_system_day = data;
                    checkDayValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_DATE_MONTH_WRITE_ORDER:
                if(data<=12 && data >=1)
                {
                    system_status.temp_system_month = data;
                    checkMonthValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_DATE_YEAR_WRITE_ORDER:
                if(data<=99 && data >= 23)
                {
                    system_status.temp_system_year = data;
                    checkMonthValidation();
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }   

                __no_operation();

                break;

            case MODBUS_CLOCK_HOUR_WRITE_ORDER:
                if(data <=23)
                {
                    system_status.temp_system_hour = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;
            case MODBUS_CLOCK_MINUTE_WRITE_ORDER:
                if(data <= 59)
                {
                    system_status.temp_system_minute = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;
            case MODBUS_CLOCK_SECOND_WRITE_ORDER:
                if(data <= 59)
                {
                    system_status.temp_system_second = data;
                    set_RTC(system_status.temp_system_day, system_status.temp_system_month, system_status.temp_system_year, system_status.temp_system_hour, system_status.temp_system_minute, system_status.temp_system_second);
                }

                __no_operation();

                break;

            case MODBUS_LANGUAGE_WRITE_ORDER:

                break;

            case MODBUS_FACTORY_RESET_WRITE_ORDER:
                if(data == TRUE)
                {
                    baudrate_A1 = UCA1_BAUDRATE;
                    UART_A1_init();
                }
                
                break;
            case MODBUS_LED_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(LED_TEST);
                }

                __no_operation();

                break;

            case MODBUS_RELAY_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(RELAY_TEST);
                }

                __no_operation();

                break;

            case MODBUS_LAMP_TEST_WRITE_ORDER:
                if(data == TRUE)
                {
//                    chooseTest(LAMP_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L1_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L1_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L2_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L2_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_L3_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(L3_FAULT_TEST);
                }

                __no_operation();

                break;

            case MODBUS_E_FAULT_TEST_WRITE_ORDER:

                if(data == TRUE)
                {
//                    chooseTest(E_FAULT_TEST);
                }

                __no_operation();

                break;

      }


    __no_operation();

//    SYSCFG0 = FRWPPW | DFWP | PFWP;     // Program FRAM write protected (not writable)

    if(order_no  == MODBUS_BAUDRATE_ORDER)
    {
//        UART_A0_init();
        UART_A1_init();
        PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode
    }


        __no_operation();

    generate_modbus_single_write_msg();

    // Send it
    uart_send_modbus_frame();

}



/*  Function    : generate_crc
 *  Inputs      :
 *  Return      : crc val
 *  Desc        :
 */
u16 generate_modbus_crc(u8 *data_ptr, u32 len)
{
   u16 crc16 = 0xFFFF;
   u8 i = 0;
   u8 bit_of_data= 0;

   u8 *buf ;

   buf = data_ptr;

   for( i = 0; i < len; i++ )
       {
       crc16 ^= buf[i];

           for( bit_of_data = 0; bit_of_data < 8; bit_of_data++ )
           {
               if( crc16 & 0x0001 )
               {
                   crc16 >>= 1;
                   crc16 ^= 0xA001;
               }
               else
               {
                   crc16 >>= 1;
               }
           }
       }

       return crc16;

}


/*  Function    : check_modbus_msg_crc
 *  Inputs      : in msg ptr
 *  Return      : TRUE/FALSE
 *  Desc        : Packet data validation
 */
u8 check_modbus_msg_crc(modbus_in_msg_t *msg_ptr)
{
    u16 crc_16;
    u8 crc16_low;
    u8 crc16_high;
  //  u8 i;
    u8 buf [] = {msg_ptr->mb_address,
                 msg_ptr->mb_func_no,
                 msg_ptr->mb_start_adr_high,
                 msg_ptr->mb_start_adr_low,
                 msg_ptr->mb_data_high,
                 msg_ptr->mb_data_low,
                };

    crc_16 = generate_modbus_crc(buf , (sizeof buf/sizeof *buf));

    crc16_low = (crc_16&0xFF);
    crc16_high = ((crc_16>>8)&0xFF);


    if ((crc16_low != msg_ptr->mb_crc_low)||( crc16_high != msg_ptr->mb_crc_high))
        return FALSE;




    return TRUE;
}


/*  Function    : check_modbus_multiple_write_msg_crc
 *  Inputs      : in msg ptr
 *  Return      : TRUE/FALSE
 *  Desc        : Packet data validation
 */
u8 check_modbus_multiple_write_msg_crc(modbus_in_write_msg_t *msg_ptr)
{
    u16 crc_16;
    u8 crc16_low;
    u8 crc16_high;
    u8 i;
    u8 dta_ptr[MODBUS_IN_MSG_DATA_SIZE + 7];
   /* u8 buf [] = {msg_ptr->mb_address,
                 msg_ptr->mb_func_no,
                 msg_ptr->mb_start_adr_high,
                 msg_ptr->mb_start_adr_low,
                 msg_ptr->mb_register_len_high,
                 msg_ptr->mb_register_len_low,
                 msg_ptr->mb_data_len,
                 msg_ptr->mb_data[msg_ptr->mb_data_len]


                };*/

    dta_ptr[0] = msg_ptr->mb_address;
    dta_ptr[1] = msg_ptr->mb_func_no;
    dta_ptr[2] = msg_ptr->mb_start_adr_high;
    dta_ptr[3] = msg_ptr->mb_start_adr_low;
    dta_ptr[4] = msg_ptr->mb_register_len_high;
    dta_ptr[5] = msg_ptr->mb_register_len_low;
    dta_ptr[6] = msg_ptr->mb_data_len;



    for(i = 0; i < (msg_ptr->mb_data_len) + 7; i++)
    {
        dta_ptr[i+7] = msg_ptr->mb_data[i];

        if(i == 10)
        {
            __no_operation();                         // For debugger
        }
    }

    crc_16 = generate_modbus_crc(&dta_ptr[0] ,(msg_ptr->mb_data_len) + 7 );

    crc16_low = (crc_16&0xFF);
    crc16_high = ((crc_16>>8)&0xFF);


    if ((crc16_low != msg_ptr->mb_crc_low)||( crc16_high != msg_ptr->mb_crc_high))
        return FALSE;


    return TRUE;
}


/*  Function    : send_modbus_msg
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
u8 send_modbus_reply_msg(u8 status, u8 reply_func_no)
{
    struct modbus_reply_msg_s modbus_reply_msg;

    if(is_uart_tx_busy_A0() == TRUE)
        return FALSE;

    /* Fill data */
    modbus_reply_msg.status        = status;
    modbus_reply_msg.reply_func_no = reply_func_no;

    // generate packet
    generate_modbus_msg(MODBUS_REPLY_ORDER, (u8 *)&modbus_reply_msg, sizeof(struct modbus_reply_msg_s) );

    // Send it
    uart_send_modbus_frame();

    return TRUE;
}

/*  Function    : is_modbus_session_started
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
u8 is_modbus_session_started()
{
    if(system_status.modbus_protocol_state > MODBUS_WAITING_ADDRESS)
        return TRUE;

    return FALSE;
}

/*  Function    : process_uart_in_buffer
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
void processModbus()
{
    u8 data;
    u8 result;
    u16 data_start_address;
 //   u16 data_quantity;
    int data_quantity_int;

    while(TRUE)
    {
        /* Timeout Control */
        if(is_modbus_session_started() == TRUE)
        {
            if(calc_time_diff_ms(system_status.modbus_session_start_time) >= system_status.modbus_session_timeout_ms)
            {
                system_status.modbus_protocol_state = MODBUS_WAITING_ADDRESS;
            }
        }
        /* Read sample frmb buffer */
        result = read_sample_from_buffer(&uart_rx_buffer, &data);
        if(result == FALSE)
            break;

        __no_operation();
        switch (system_status.modbus_protocol_state)
        {
            case MODBUS_WAITING_ADDRESS :

                /* Reset cmbm */
                system_status.modbus_protocol_curr_rx_cnt = 0;
                __no_operation();
                if( data == modbus_adress)
                {
                    modbus_in_msg.mb_address = data;
                    modbus_in_write_msg.mb_address = data;
                    system_status.modbus_session_start_time   = get_time_ms();
                    system_status.modbus_protocol_state       = MODBUS_WAITING_FUNC_NO;
                    __no_operation();
                }

                else
                {
                    __no_operation();
                }

            break;

            case MODBUS_WAITING_FUNC_NO :

                __no_operation(); //for debugger
                if(( data == MODBUS_READ_FUNC)||
                   ( data == MODBUS_SINGLE_WRITE_FUNC)||
                   ( data == MODBUS_MULT_WRITE_FUNC))
                {

                    modbus_in_msg.mb_func_no = data;
                    modbus_in_write_msg.mb_func_no = data;
                    system_status.modbus_protocol_state = MODBUS_WAITING_START_ADRESS_HIGH;

                }

                else
                {

                    system_status.modbus_protocol_func_no_err++;
                    process_modbus_error_msg(MODBUS_FUNCTION_ERROR);
                    system_status.modbus_protocol_state       = MODBUS_WAITING_ADDRESS;
                }


            break;

            case MODBUS_WAITING_START_ADRESS_HIGH :



                modbus_in_msg.mb_start_adr_high = data;
                modbus_in_write_msg.mb_start_adr_high = data;

                system_status.modbus_protocol_state = MODBUS_WAITING_START_ADRESS_LOW;

            break;

            case MODBUS_WAITING_START_ADRESS_LOW :

                modbus_in_msg.mb_start_adr_low             = data;
                modbus_in_write_msg.mb_start_adr_low             = data;


                u_16byte.data_u8[0] = modbus_in_msg.mb_start_adr_low;
                u_16byte.data_u8[1] = modbus_in_msg.mb_start_adr_high;

                data_start_address = u_16byte.data_u16;
                //Check Address

                if(does_have_this_address(data_start_address) == TRUE)
                {
                    switch(modbus_in_msg.mb_func_no)
                    {
                    case MODBUS_READ_FUNC:
                    case MODBUS_SINGLE_WRITE_FUNC:

                        system_status.modbus_protocol_state  = MODBUS_WAITING_DATA_HIGH;
                        break;

                    case MODBUS_MULT_WRITE_FUNC:
                        system_status.modbus_protocol_state  = MODBUS_WAITING_REGISTER_ADRESS_HIGH;
                        break;
                    }

                }
                else
                {
                    process_modbus_error_msg(MODBUS_ADDRESS_ERROR);
                    system_status.modbus_protocol_state       = MODBUS_WAITING_ADDRESS;
                }

            break;

            case MODBUS_WAITING_DATA_HIGH :

                modbus_in_msg.mb_data_high             = data;
                system_status.modbus_protocol_state  = MODBUS_WAITING_DATA_LOW;


            break;

            case MODBUS_WAITING_DATA_LOW :
                    /* record Sample*/

                    modbus_in_msg.mb_data_low = data;

                    u_16byte.data_u8[0] = modbus_in_msg.mb_start_adr_low;
                    u_16byte.data_u8[1] = modbus_in_msg.mb_start_adr_high;

                    data_start_address = u_16byte.data_u16;

                 //   u_16byte.data_u8[0] = modbus_in_msg.mb_data_low;
                  //  u_16byte.data_u8[1] = modbus_in_msg.mb_data_high;

                 //   data_quantity = u_16byte.data_u16;

                    u_16byte.data_u8[0] = modbus_in_msg.mb_data_low;
                    u_16byte.data_u8[1] = modbus_in_msg.mb_data_high;

                    __no_operation(); //for debugger
                    data_quantity_int = u_16byte.data_int16;
                    data_quantity_int = data_quantity_int+0;
                    __no_operation(); //for debugger
                    //Check Address

                    if(is_data_number_in_range(data_quantity_int,modbus_in_msg.mb_func_no ) == FALSE)
                    {

                        process_modbus_error_msg(MODBUS_DATA_QUANTITY_ERROR);
                        system_status.modbus_protocol_state       = MODBUS_WAITING_ADDRESS;


                    }
                    else if(is_request_data_legal(data_quantity_int, data_start_address, modbus_in_msg.mb_func_no ) == FALSE)
                    {
                        process_modbus_error_msg(MODBUS_ADDRESS_ERROR);
                        system_status.modbus_protocol_state       = MODBUS_WAITING_ADDRESS;

                    }
                    else
                    {
                        system_status.modbus_protocol_state  = MODBUS_WAITING_CRC_LOW;
                    }

            break;

            case MODBUS_WAITING_CRC_LOW :

                modbus_in_msg.mb_crc_low = data;



                system_status.modbus_protocol_state  = MODBUS_WAITING_CRC_HIGH;

            break;

            case MODBUS_WAITING_CRC_HIGH :

                modbus_in_msg.mb_crc_high = data;


                result = check_modbus_msg_crc(&modbus_in_msg);

                if(result == FALSE)
                {
                    system_status.modbus_protocol_state  = MODBUS_WAITING_ADDRESS;
                    system_status.modbus_protocol_crc_err++;
                    break;
                }

                /* Half duplex Wireless Response Delay */
          //      delay_ms(MODBUS_RESPONSE_DELAY);



                switch(modbus_in_msg.mb_func_no)
                {
                case MODBUS_READ_FUNC:
                    process_modbus_multiple_read_msg(&modbus_in_msg);
                    break;
                case MODBUS_SINGLE_WRITE_FUNC:
                    process_modbus_single_write_msg(&modbus_in_msg);
                    break;
                case MODBUS_MULT_WRITE_FUNC:
                    process_modbus_multiple_write_msg(&modbus_in_write_msg);
                    break;

                }

                system_status.modbus_protocol_rx_msg_cnt++;
                system_status.modbus_protocol_state  = MODBUS_WAITING_ADDRESS;

            break;


                case MODBUS_WAITING_REGISTER_ADRESS_HIGH :

                    modbus_in_write_msg.mb_register_len_high             = data;
                    system_status.modbus_protocol_state  = MODBUS_WAITING_REGISTER_ADRESS_LOW;


                break;

                case MODBUS_WAITING_REGISTER_ADRESS_LOW :

                    modbus_in_write_msg.mb_register_len_low             = data;
                    system_status.modbus_protocol_state  = MODBUS_WAITING_DATA_LEN;


                break;

                case MODBUS_WAITING_DATA_LEN :

                    modbus_in_write_msg.mb_data_len             = data;
                    system_status.modbus_rx_write_index = 0;
                    system_status.modbus_protocol_state  = MODBUS_WAITING_DATAS;


                break;

                case MODBUS_WAITING_DATAS :

                    modbus_in_write_msg.mb_data[system_status.modbus_rx_write_index++]   = data;


                    if(system_status.modbus_rx_write_index == modbus_in_write_msg.mb_data_len)
                    {
                        system_status.modbus_protocol_state  = MODBUS_WAITING_WRITE_CRC_LOW;
                    }


                break;

                case MODBUS_WAITING_WRITE_CRC_LOW :

                    modbus_in_write_msg.mb_crc_low = data;

                    system_status.modbus_protocol_state  = MODBUS_WAITING_WRITE_CRC_HIGH;

                break;


                case MODBUS_WAITING_WRITE_CRC_HIGH :

                    modbus_in_write_msg.mb_crc_high = data;

                    system_status.modbus_protocol_state  = MODBUS_WAITING_ADDRESS;

                    result = check_modbus_multiple_write_msg_crc(&modbus_in_write_msg);

                    if(result == FALSE)
                    {
                        system_status.modbus_protocol_state  = MODBUS_WAITING_ADDRESS;
                        system_status.modbus_protocol_crc_err++;
                    //    break;
                    }

                    /* Half duplex Wireless Response Delay */
              //      delay_ms(MODBUS_RESPONSE_DELAY);



                    switch(modbus_in_write_msg.mb_func_no)
                    {
                    case MODBUS_READ_FUNC:
               //         process_modbus_multiple_read_msg(&modbus_in_msg);
                        break;
                    case MODBUS_SINGLE_WRITE_FUNC:
               //         process_modbus_single_write_msg(&modbus_in_msg);
                        break;
                    case MODBUS_MULT_WRITE_FUNC:
                        process_modbus_multiple_write_msg(&modbus_in_write_msg);
                        break;

                    }

                    system_status.modbus_protocol_rx_msg_cnt++;
                    system_status.modbus_protocol_state  = MODBUS_WAITING_ADDRESS;


                break;





        }
    }
}



// Must be called while uart is not busy
void uart_send_modbus_frame()
{


    CLEAR_INTERRUPTS;

    if(is_uart_tx_busy_A0() == TRUE)
    {
        system_status.uart_tx_busy_err++;
        return ;
    }


    system_status.uart_tx_busy_A0   = TRUE;
    system_status.modbus_tx_index  = 0;
    system_status.modbus_tx_flag = MODBUS_NUM_OF_FUNCTIONS;
    system_status.modbus_tx_state  = MODBUS_TX_FUNC_NO;

    UCA1IE |= UCTXIE;                        // Enable USCI_A1 TX interrupt
    UCA1TXBUF = modbus_in_msg.mb_address;   // Tx first char, start transmission

    RESTORE_INTERRUPTS;
}

// Must be called while uart is not busy
void uart_send_modbus_error_frame()
{


    CLEAR_INTERRUPTS;

    if(is_uart_tx_busy_A0() == TRUE)
    {
        system_status.uart_tx_busy_err++;
        return ;
    }


    system_status.uart_tx_busy_A0   = TRUE;

    system_status.modbus_tx_flag = MODBUS_SEND_ERROR_FUNC;
    system_status.modbus_tx_error_state  = MODBUS_TX_ERROR_FUNC_NO;

    UCA1IE |= UCTXIE;                        // Enable USCI_A1 TX interrupt
    UCA1TXBUF = modbus_out_error_msg.mb_address;   // Tx first char, start transmission

    RESTORE_INTERRUPTS;
}



/*  Function    : modbus_tx_multiple_datas_int_handler
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
void modbus_tx_multiple_datas_int_handler()
{

    u8 modbus_tx_state;

    modbus_tx_state = system_status.modbus_tx_state;

   // delay_ms(DENEME_TEST);
//for(timer_cnt = 1000; timer_cnt >0;timer_cnt--)
    __no_operation();


    switch(modbus_tx_state)
    {
        case MODBUS_TX_ADDRESS :
            system_status.modbus_tx_state = MODBUS_TX_FUNC_NO;
          //  UCA1TXBUF = modbus_out_msg.mb_address;  // Header1 is send from start caondidition in sw
            //system_status.modbus_tx_state = MODBUS_TX_FUNC_NO;
        break;

        case MODBUS_TX_FUNC_NO :

            UCA1TXBUF = modbus_in_msg.mb_func_no;
            switch(modbus_in_msg.mb_func_no)
            {
            case MODBUS_READ_FUNC:
                system_status.modbus_tx_state = MODBUS_TX_DATA_LEN;
                break;

            case MODBUS_SINGLE_WRITE_FUNC:
            case MODBUS_MULT_WRITE_FUNC:
                system_status.modbus_tx_state = MODBUS_TX_WRITE_START_ADRESS_HIGH;
                break;

            }

        break;


        case MODBUS_TX_DATA_LEN :
            UCA1TXBUF = modbus_out_msg.mb_data_len;

            if(modbus_out_msg.mb_data_len == 0)
            {
                system_status.modbus_tx_state = MODBUS_TX_CRC_LOW;
            }
            else
                system_status.modbus_tx_state = MODBUS_TX_DATAS;

        break;

        case MODBUS_TX_DATAS :

            __no_operation();
            UCA1TXBUF = modbus_out_msg.mb_data[system_status.modbus_tx_index++];
            __no_operation();
            if(system_status.modbus_tx_index == modbus_out_msg.mb_data_len)
            {
                __no_operation();
                system_status.modbus_tx_state = MODBUS_TX_CRC_LOW;
            }
           // UCA1TXBUF = modbus_out_msg.mb_data[system_status.modbus_tx_index++];
        break;

        case MODBUS_TX_CRC_LOW :
            UCA1TXBUF = modbus_out_msg.mb_crc_low;
            system_status.modbus_tx_state = MODBUS_TX_CRC_HIGH;
            //UCA1TXBUF = modbus_out_msg.mb_crc_low;
        break;

        case MODBUS_TX_CRC_HIGH :
            UCA1TXBUF = modbus_out_msg.mb_crc_high;


            system_status.modbus_tx_state = MODBUS_TX_END;
           // UCA1TXBUF = modbus_out_msg.mb_crc_high;
        break;

        case MODBUS_TX_END :

            system_status.uart_tx_busy_A0 = FALSE;
            UCA1IE &= ~UCTXIE;
            system_status.modbus_tx_flag = MODBUS_NUM_OF_FUNCTIONS;
            system_status.modbus_protocol_tx_msg_cnt++;
            system_status.modbus_tx_state = MODBUS_TX_FUNC_NO;
        break;


        //WRITE STATES
        case MODBUS_TX_WRITE_START_ADRESS_HIGH :
            UCA1TXBUF = modbus_out_write_msg.mb_start_adr_high;
            system_status.modbus_tx_state = MODBUS_TX_WRITE_START_ADRESS_LOW;
        break;


        case MODBUS_TX_WRITE_START_ADRESS_LOW :
            UCA1TXBUF = modbus_out_write_msg.mb_start_adr_low;
            system_status.modbus_tx_state = MODBUS_TX_WRITE_REGISTER_ADRESS_HIGH;
        break;

        case MODBUS_TX_WRITE_REGISTER_ADRESS_HIGH :
            UCA1TXBUF = modbus_out_write_msg.mb_register_len_high;
            system_status.modbus_tx_state = MODBUS_TX_WRITE_REGISTER_ADRESS_LOW;
        break;


        case MODBUS_TX_WRITE_REGISTER_ADRESS_LOW :
            UCA1TXBUF = modbus_out_write_msg.mb_register_len_low;
            system_status.modbus_tx_state = MODBUS_TX_WRITE_CRC_LOW;
        break;


        case MODBUS_TX_WRITE_CRC_LOW :
            UCA1TXBUF = modbus_out_write_msg.mb_crc_low;
            system_status.modbus_tx_state = MODBUS_TX_WRITE_CRC_HIGH;
        break;


        case MODBUS_TX_WRITE_CRC_HIGH :
            UCA1TXBUF = modbus_out_write_msg.mb_crc_high;
            system_status.modbus_tx_state = MODBUS_TX_END;
        break;


    }


}



/*  Function    : modbus_tx_error_int_handler
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
void modbus_tx_error_int_handler()
{

    u8 modbus_tx_error_state;

    modbus_tx_error_state = system_status.modbus_tx_error_state;


    __no_operation();


    switch(modbus_tx_error_state)
    {
        case MODBUS_TX_ERROR_ADDRESS :
            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_FUNC_NO;

        break;

        case MODBUS_TX_ERROR_FUNC_NO :

            UCA1TXBUF = modbus_out_error_msg.mb_func_no;
            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_CODE;
        break;


        case MODBUS_TX_ERROR_CODE :
            UCA1TXBUF = modbus_out_error_msg.mb_error_code;

            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_CRC_LOW;

        break;



        case MODBUS_TX_ERROR_CRC_LOW :
            UCA1TXBUF = modbus_out_error_msg.mb_crc_low;
            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_CRC_HIGH;
            //UCA1TXBUF = modbus_out_msg.mb_crc_low;
        break;

        case MODBUS_TX_ERROR_CRC_HIGH :
            UCA1TXBUF = modbus_out_error_msg.mb_crc_high;
            system_status.uart_tx_busy_A0 = FALSE;

            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_END;

        break;

        case MODBUS_TX_ERROR_END :

            system_status.uart_tx_busy_A0 = FALSE;
            UCA1IE &= ~UCTXIE;
            system_status.modbus_tx_flag = MODBUS_NUM_OF_FUNCTIONS;
            system_status.modbus_protocol_tx_msg_cnt++;
            system_status.modbus_tx_error_state = MODBUS_TX_ERROR_FUNC_NO;
        break;

    }


}





u8 does_have_this_address(u16 start_Adr)
{

    if(MODBUS_PHASE_1_MEASUREMENT_ORDER <= start_Adr && start_Adr < MODBUS_END_OF_ORDERS){
        return TRUE;
    }

    switch(start_Adr)
    {

    case MODBUS_TEST_ORDER                  :

    // case MODBUS_READ_KEY_WRITE_ORDER        :
    // case MODBUS_WRITE_KEY_WRITE_ORDER       :

    case MODBUS_SN_UNLOCK_WRITE_ORDER       :
    case MODBUS_SERIAL_NO_HIGH_WRITE_ORDER  :
    case MODBUS_SERIAL_NO_LOW_WRITE_ORDER:

    // case MODBUS_PGV_ORDER                   :   // Yazï¿½lï¿½m versiyonu
    // case MODBUS_HWV_ORDER                   :

        __no_operation();                               // For debugger

        return TRUE;//order_no = MODBUS_TEST_ORDER;

        default:

        //ariza mesajï¿½ gï¿½nderilecek
        __no_operation();                         // For debugger
        return FALSE;

    }
}



u8 is_data_number_in_range(int data_quantity, u8 func_no)
{

    switch(func_no)
    {
    case MODBUS_READ_FUNC:


        if((data_quantity < MODBUS_MAX_ORDER)&&(data_quantity >= MODBUS_MIN_ORDER))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }




    case MODBUS_SINGLE_WRITE_FUNC:

        if((data_quantity < MODBUS_MAX_SINGLE_WRITE_ORDER)&&(data_quantity >= MODBUS_MIN_SINGLE_WRITE_ORDER))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }



    case MODBUS_MULT_WRITE_FUNC:


        if((data_quantity < MODBUS_MAX_MULTIPLE_WRITE_ORDER)&&(data_quantity >= MODBUS_MIN_MULTIPLE_WRITE_ORDER))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }





    }

    return FALSE;

}



u8 is_request_data_legal(int data_quantity, u16 data_start_address, u8 func_no)
{

    switch(func_no)
    {
    case MODBUS_READ_FUNC:


        // if((data_quantity + data_start_address < MODBUS_NUM_OF_ORDERS))
        if(does_have_this_address(data_quantity + data_start_address - 1))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }






    case MODBUS_SINGLE_WRITE_FUNC:

        if(does_have_this_address(data_start_address))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }



    case MODBUS_MULT_WRITE_FUNC:


        if(does_have_this_address(data_quantity + data_start_address - 1))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }





    }

    return FALSE;



}


void process_modbus_error_msg(u8 error_code)
{


    generate_modbus_error_msg(modbus_in_msg.mb_func_no, error_code );

    // Send it
    uart_send_modbus_error_frame();


}






