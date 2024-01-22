
/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : modbus.h
* Author             : Onur Kay�kc�
* Version            : V1.0
* Date               : 24/02/2022
* Description        : modbus headers
********************************************************************************/


#ifndef MODBUS_H_
#define MODBUS_H_

#define MAX_BRS_NUMBER 36







extern void uart_send_modbus_frame();


extern void modbus_serial_no_function(u8 *data_ptr, u32 data_len);

#define MODBUS_ADDRESS           0x01

#define MODBUS_HEADER_1          0xA0
#define MODBUS_HEADER_2          0xEE

#define MODBUS_IN_MSG_DATA_SIZE  32*2//64//32//128
#define MODBUS_OUT_MSG_DATA_SIZE 128*2//64//32//128

#define MODBUS_IN_MSG_BUF_LEN  36

#define MODBUS_DATA_FUNC_NO_INDEX    0
#define MODBUS_DATA_DATA_INDEX       1

#define MODBUS_TIMEOUT_MS            1000

#define MODBUS_RESPONSE_DELAY 100 // ms


#define MODBUS_MAX_ORDER  128*2
#define MODBUS_MIN_ORDER  0

#define MODBUS_MAX_SINGLE_WRITE_ORDER  15600*2
#define MODBUS_MIN_SINGLE_WRITE_ORDER  -2560

#define MODBUS_MAX_MULTIPLE_WRITE_ORDER  32*2
#define MODBUS_MIN_MULTIPLE_WRITE_ORDER  0

#define MODBUS_DATA_FACTOR 100
/* ORDERS CODES */

#define MODBUS_REPLY_ORDER  20



enum
{
    MODBUS_TEST_ORDER               =   0,

    MODBUS_PHASE_1_MEASUREMENT_ORDER = 100,
    MODBUS_PHASE_2_MEASUREMENT_ORDER,
    MODBUS_PHASE_3_MEASUREMENT_ORDER,
    MODBUS_EARTH_MEASUREMENT_ORDER,
    MODBUS_PHASE_1_FAULT_ORDER,
    MODBUS_PHASE_2_FAULT_ORDER,
    MODBUS_PHASE_3_FAULT_ORDER,
    MODBUS_EARTH_FAULT_ORDER,
    MODBUS_EXTERNAL_ORDER,

    MODBUS_FAULT_REPORT_COUNT_ORDER = 110,
    MODBUS_DELETE_REPORT_ORDER,
    MODBUS_DELETE_ALL_ORDER,
    MODBUS_FAULT_REPORT_LIST_ORDER = 115,
    MODBUS_FAULT_L1_CURR_ORDER,
    MODBUS_FAULT_L2_CURR_ORDER,
    MODBUS_FAULT_L3_CURR_ORDER,
    MODBUS_FAULT_E_CURR_ORDER,

    MODBUS_FAULT_L1_FAULT_ORDER = 120,
    MODBUS_FAULT_L2_FAULT_ORDER,
    MODBUS_FAULT_L3_FAULT_ORDER,
    MODBUS_FAULT_E_FAULT_ORDER,
    MODBUS_FAULT_YEAR_ORDER,
    MODBUS_FAULT_MONTH_ORDER,
    MODBUS_FAULT_DAY_ORDER,
    MODBUS_FAULT_HOUR_ORDER,
    MODBUS_FAULT_MINUTE_ORDER,
    MODBUS_FAULT_SECOND_ORDER,

    MODBUS_PHASE_CURRENT_ORDER = 130,
    MODBUS_PHASE_DETECTION_TIME_ORDER,
    MODBUS_EARTH_CURRENT_ORDER,
    MODBUS_EARTH_DETECTION_TIME_ORDER,
    MODBUS_AUTO_RESET_TIME_ORDER,
    MODBUS_AFTER_DRESET_IN_TIME_ORDER,
    MODBUS_RELAY1_SETTING_ORDER,
    MODBUS_RELAY2_SETTING_ORDER,
    MODBUS_PHASE_FREQUENCY_ORDER,
    MODBUS_PASSWORD_ORDER,

    MODBUS_DATE_YEAR_ORDER = 140,
    MODBUS_DATE_MONTH_ORDER,
    MODBUS_DATE_DAY_ORDER,
    MODBUS_CLOCK_HOUR_ORDER,
    MODBUS_CLOCK_MINUTE_ORDER,
    MODBUS_CLOCK_SECOND_ORDER,
    MODBUS_LANGUAGE_ORDER,
    MODBUS_OWN_ADRESS_ORDER, // cihaz adresi
    MODBUS_BAUDRATE_ORDER, // baudrate

    MODBUS_LED_TEST_ORDER = 150,
    MODBUS_RELAY_TEST_ORDER,
    MODBUS_LAMP_TEST_ORDER,
    MODBUS_L1_FAULT_TEST_ORDER,
    MODBUS_L2_FAULT_TEST_ORDER,
    MODBUS_L3_FAULT_TEST_ORDER,
    MODBUS_E_FAULT_TEST_ORDER,
    MODBUS_SOFTWARE_VERSION_ORDER,
    MODBUS_SERIAL_NO_HIGH_ORDER,
    MODBUS_SERIAL_NO_LOW_ORDER,
    
    MODBUS_REPORT_NO_1 = 160,			
    MODBUS_REPORT_NO_2 = MODBUS_REPORT_NO_1 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_3 = MODBUS_REPORT_NO_2 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_4 = MODBUS_REPORT_NO_3 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_5 = MODBUS_REPORT_NO_4 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_6 = MODBUS_REPORT_NO_5 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_7 = MODBUS_REPORT_NO_6 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_8 = MODBUS_REPORT_NO_7 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_9 = MODBUS_REPORT_NO_8 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_10 = MODBUS_REPORT_NO_9 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_11 = MODBUS_REPORT_NO_10 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_12 = MODBUS_REPORT_NO_11 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_13 = MODBUS_REPORT_NO_12 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_14 = MODBUS_REPORT_NO_13 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_15 = MODBUS_REPORT_NO_14 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_16 = MODBUS_REPORT_NO_15 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_17 = MODBUS_REPORT_NO_16 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_18 = MODBUS_REPORT_NO_17 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_19 = MODBUS_REPORT_NO_18 + REPORT_ELEMENT_SIZE,
    MODBUS_REPORT_NO_20 = MODBUS_REPORT_NO_19 + REPORT_ELEMENT_SIZE,
// MODBUS_REPORT_NO_1 + 20*15
    MODBUS_END_OF_ORDERS = MODBUS_REPORT_NO_20+15,  // AKTIF BIR ADRES DEGILDIR
// 460

    MODBUS_PGV_ORDER          =   12288, // Yazilim Versiyonu
    MODBUS_HWV_ORDER          =   12289, // Donanım Versiyonu

    MODBUS_NUM_OF_ORDERS
};

enum
{
    MODBUS_TEST_WRITE_ORDER         =   0,







    MODBUS_READ_LOCK_WRITE_ORDER    =   57,
    MODBUS_WRITE_LOCK_WRITE_ORDER   =   58,



    MODBUS_PHASE_1_MEASUREMENT_WRITE_ORDER = 100,
    MODBUS_PHASE_2_MEASUREMENT_WRITE_ORDER,
    MODBUS_PHASE_3_MEASUREMENT_WRITE_ORDER,
    MODBUS_EARTH_MEASUREMENT_WRITE_ORDER,
    MODBUS_PHASE_1_FAULT_WRITE_ORDER,
    MODBUS_PHASE_2_FAULT_WRITE_ORDER,
    MODBUS_PHASE_3_FAULT_WRITE_ORDER,
    MODBUS_EARTH_FAULT_WRITE_ORDER,
    MODBUS_EXTERNAL_WRITE_ORDER,
    MODBUS_FAULT_RESET_WRITE_ORDER,

    MODBUS_FAULT_REPORT_COUNT_WRITE_ORDER = 110,
    MODBUS_DELETE_REPORT_WRITE_ORDER,
    MODBUS_DELETE_ALL_WRITE_ORDER,

    MODBUS_FAULT_REPORT_LIST_WRITE_ORDER = 115,
    // MODBUS_FAULT_L1_CURR_ORDER,
    // MODBUS_FAULT_L2_CURR_ORDER,
    // MODBUS_FAULT_L3_CURR_ORDER,
    // MODBUS_FAULT_E_CURR_ORDER,

    // MODBUS_FAULT_L1_FAULT_ORDER = 120,
    // MODBUS_FAULT_L2_FAULT_ORDER,
    // MODBUS_FAULT_L3_FAULT_ORDER,
    // MODBUS_FAULT_E_FAULT_ORDER,
    // MODBUS_FAULT_DAY_ORDER,
    // MODBUS_FAULT_MONTH_ORDER,
    // MODBUS_FAULT_YEAR_ORDER,
    // MODBUS_FAULT_HOUR_ORDER,
    // MODBUS_FAULT_MINUTE_ORDER,
    // MODBUS_FAULT_SECOND_ORDER,

    MODBUS_PHASE_CURRENT_WRITE_ORDER = 130,
    MODBUS_PHASE_DETECTION_TIME_WRITE_ORDER,
    MODBUS_EARTH_CURRENT_WRITE_ORDER,
    MODBUS_EARTH_DETECTION_TIME_WRITE_ORDER,
    MODBUS_AUTO_RESET_TIME_WRITE_ORDER,
    MODBUS_AFTER_DRESET_IN_TIME_WRITE_ORDER,
    MODBUS_RELAY1_SETTING_WRITE_ORDER,
    MODBUS_RELAY2_SETTING_WRITE_ORDER,
    MODBUS_PHASE_FREQUENCY_WRITE_ORDER,
    MODBUS_PASSWORD_WRITE_ORDER,

    MODBUS_DATE_YEAR_WRITE_ORDER = 140,
    MODBUS_DATE_MONTH_WRITE_ORDER,
    MODBUS_DATE_DAY_WRITE_ORDER,
    MODBUS_CLOCK_HOUR_WRITE_ORDER,
    MODBUS_CLOCK_MINUTE_WRITE_ORDER,
    MODBUS_CLOCK_SECOND_WRITE_ORDER,
    MODBUS_LANGUAGE_WRITE_ORDER,
    MODBUS_OWN_ADRESS_WRITE_ORDER, // cihaz adresi
    MODBUS_BAUDRATE_WRITE_ORDER, // baudrate
    MODBUS_FACTORY_RESET_WRITE_ORDER = 149,

    MODBUS_LED_TEST_WRITE_ORDER = 150,
    MODBUS_RELAY_TEST_WRITE_ORDER,
    MODBUS_LAMP_TEST_WRITE_ORDER,
    MODBUS_L1_FAULT_TEST_WRITE_ORDER,
    MODBUS_L2_FAULT_TEST_WRITE_ORDER,
    MODBUS_L3_FAULT_TEST_WRITE_ORDER,
    MODBUS_E_FAULT_TEST_WRITE_ORDER,
    
    // MODBUS_REPORT_NO_1 = 160,			
    // MODBUS_REPORT_NO_2 = MODBUS_REPORT_NO_1 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_3 = MODBUS_REPORT_NO_2 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_4 = MODBUS_REPORT_NO_3 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_5 = MODBUS_REPORT_NO_4 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_6 = MODBUS_REPORT_NO_5 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_7 = MODBUS_REPORT_NO_6 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_8 = MODBUS_REPORT_NO_7 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_9 = MODBUS_REPORT_NO_8 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_10 = MODBUS_REPORT_NO_9 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_11 = MODBUS_REPORT_NO_10 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_12 = MODBUS_REPORT_NO_11 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_13 = MODBUS_REPORT_NO_12 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_14 = MODBUS_REPORT_NO_13 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_15 = MODBUS_REPORT_NO_14 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_16 = MODBUS_REPORT_NO_15 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_17 = MODBUS_REPORT_NO_16 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_18 = MODBUS_REPORT_NO_17 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_19 = MODBUS_REPORT_NO_18 + REPORT_ELEMENT_SIZE,
    // MODBUS_REPORT_NO_20 = MODBUS_REPORT_NO_19 + REPORT_ELEMENT_SIZE,
// MODBUS_REPORT_NO_1 + 20*15
    // MODBUS_END_OF_ORDERS = MODBUS_REPORT_NO_20+15,
// 460
//    MODBUS_READ_KEY_WRITE_ORDER       =   4096,
//    MODBUS_WRITE_KEY_WRITE_ORDER      =   4097,
    MODBUS_READ_KEY_WRITE_ORDER       =   4096,
    MODBUS_WRITE_KEY_WRITE_ORDER      =   4097,

    MODBUS_SN_UNLOCK_WRITE_ORDER = 7890,
    MODBUS_SERIAL_NO_HIGH_WRITE_ORDER,
    MODBUS_SERIAL_NO_LOW_WRITE_ORDER,

    MODBUS_NUM_OF_WRITE_ORDERS
};



/* FUNCTIONS CODES */
enum
{
    MODBUS_READ_FUNC            =   3,          /* 3 */

    MODBUS_SINGLE_WRITE_FUNC    =   6,          /* 6 */

    MODBUS_MULT_WRITE_FUNC      =   16,         /* 16 */

    MODBUS_SEND_ERROR_FUNC      =   128,

    MODBUS_NUM_OF_FUNCTIONS

};

/* ERRORS CODES */
enum
{
    MODBUS_FUNCTION_ERROR       =   1,          /* 1 */

    MODBUS_ADDRESS_ERROR        =   2,          /* 2 */

    MODBUS_DATA_QUANTITY_ERROR           =   3,          /* 4 */

    MODBUS_EXECUTE_FUNC_ERROR   =   4,          /* 4 */

    MODBUS_CRC_ERROR   =   15,          /* 4 */

    MODBUS_NUM_OF_ERRORS

};


/* function Message Structures */
/* ORTEQ_REPLY_FUNC - 1 */
struct modbus_reply_msg_s
{
    u8 status;
    u8 reply_func_no;
};


enum
{
    MODBUS_WAITING_ADDRESS = 0,
    MODBUS_WAITING_FUNC_NO,
    MODBUS_WAITING_START_ADRESS_HIGH,
    MODBUS_WAITING_START_ADRESS_LOW,
    MODBUS_WAITING_DATA_HIGH,
    MODBUS_WAITING_DATA_LOW,
    MODBUS_WAITING_CRC_LOW,
    MODBUS_WAITING_CRC_HIGH,

    //WRITE komutuna ait extra stateler
    MODBUS_WAITING_REGISTER_ADRESS_HIGH,
    MODBUS_WAITING_REGISTER_ADRESS_LOW,
    MODBUS_WAITING_DATA_LEN,
    MODBUS_WAITING_DATAS,
    MODBUS_WAITING_WRITE_CRC_LOW,
    MODBUS_WAITING_WRITE_CRC_HIGH,


    MODBUS_TOTAL_RX_DATA
};

enum
{
    MODBUS_TX_ADDRESS = 0,
    MODBUS_TX_FUNC_NO,
    MODBUS_TX_DATA_LEN,
    MODBUS_TX_DATAS,
    MODBUS_TX_CRC_LOW,
    MODBUS_TX_CRC_HIGH,
    MODBUS_TX_END,

    //WRITE TX STATES
    MODBUS_TX_WRITE_START_ADRESS_HIGH,
    MODBUS_TX_WRITE_START_ADRESS_LOW,
    MODBUS_TX_WRITE_REGISTER_ADRESS_HIGH,
    MODBUS_TX_WRITE_REGISTER_ADRESS_LOW,
    MODBUS_TX_WRITE_CRC_LOW,
    MODBUS_TX_WRITE_CRC_HIGH,


    MODBUS_TOTAL_TX_DATA
};


enum
{
    MODBUS_TX_ERROR_ADDRESS = 0,
    MODBUS_TX_ERROR_FUNC_NO,
    MODBUS_TX_ERROR_CODE,
    MODBUS_TX_ERROR_CRC_LOW,
    MODBUS_TX_ERROR_CRC_HIGH,
    MODBUS_TX_ERROR_END,


    MODBUS_TOTAL_TX_ERROR_DATA
};

enum
{
    FAULT_REPORT_NO = 0,
    FAULT_L1_CURR,
    FAULT_L2_CURR,
    FAULT_L3_CURR,
    FAULT_E_CURR,
    FAULT_L1_FAULT,
    FAULT_L2_FAULT,
    FAULT_L3_FAULT,
    FAULT_E_FAULT,
    FAULT_YEAR,
    FAULT_MONTH,
    FAULT_DAY,
    FAULT_HOUR,
    FAULT_MINUTE,
    FAULT_SECOND,
};


typedef struct modbus_in_msg_s
{
    u8 mb_address;
    u8 mb_func_no;
    u8 mb_start_adr_high;
    u8 mb_start_adr_low;
    u8 mb_data_high;
    u8 mb_data_low;
    u8 mb_crc_low;
    u8 mb_crc_high;

}modbus_in_msg_t;

typedef struct modbus_out_msg_s
{

    u8 mb_address;
    u8 mb_func_no;

    u8 mb_data_len;// max -> ORTEQ_OUT_MSG_DATA_SIZE

    u8 mb_data[MODBUS_OUT_MSG_DATA_SIZE];
    u8 mb_crc_low;
    u8 mb_crc_high;
}modbus_out_msg_t;


typedef struct modbus_in_write_msg_s
{

    u8 mb_address;
    u8 mb_func_no;
    u8 mb_start_adr_high;
    u8 mb_start_adr_low;
    u8 mb_register_len_high;
    u8 mb_register_len_low;
    u8 mb_data_len;// = 2* register_len

    u8 mb_data[MODBUS_IN_MSG_DATA_SIZE];
    u8 mb_crc_low;
    u8 mb_crc_high;
}modbus_in_write_msg_t;




typedef struct modbus_out_write_msg_s
{

    u8 mb_address;
    u8 mb_func_no;
    u8 mb_start_adr_high;
    u8 mb_start_adr_low;
    u8 mb_register_len_high;
    u8 mb_register_len_low;
    u8 mb_crc_low;
    u8 mb_crc_high;
}modbus_out_write_msg_t;



typedef struct modbus_out_error_msg_s
{

    u8 mb_address;
    u8 mb_func_no;
    u8 mb_error_code;
    u8 mb_crc_low;
    u8 mb_crc_high;

}modbus_out_error_msg_t;


typedef struct modbus_protocol_s
{
    u8 mp_msg_header_err;
    u8 mp_msg_no_err;
    u8 mp_in_msg_len_err;

    u8 mp_in_msg_no;
    u8 mp_out_msg_no;

}modbus_protocol_t;

extern u8 generate_modbus_msg(u8 func_no, u8 *data_ptr, u8 data_len);
extern u8 generate_modbus_write_msg();
extern u8 generate_modbus_error_msg(u8 func_no, u8 error_code);

extern u8 send_modbus_reply_msg(u8 status, u8 reply_func_no);

extern u16 generate_modbus_crc(u8 *data_ptr, u32 len);

extern void processModbus();
extern void process_modbus_multiple_read_msg(modbus_in_msg_t *msg_ptr);
extern void process_modbus_single_write_msg(modbus_in_msg_t *msg_ptr);
extern void process_modbus_multiple_write_msg(modbus_in_write_msg_t *msg_ptr);


extern void uart_send_modbus_frame();

extern void modbus_tx_multiple_datas_int_handler();
extern void modbus_tx_error_int_handler();

extern u8 does_have_this_address(u16 start_Adr);
extern u8 is_data_number_in_range(int data_quantity, u8 func_no);
extern u8 is_request_data_legal(int data_quantity, u16 data_start_address, u8 func_no);

extern void process_modbus_error_msg(u8 error_code);

#endif /* MODBUS_H_ */
