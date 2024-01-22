/*
 * telemetry.h
 *
 *  Created on: 11 May 2022
 *      Author: onur.kayikci
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

enum
{
    UART_2400,
    UART_4800,
    UART_9600,
    UART_19200,
    UART_38400,
    UART_57600,
    // UART_115200,

    NUM_OF_BAUDRATE
};



#define UCA0_BAUDRATE       UART_9600
#define UCA1_BAUDRATE       UART_9600

#if MCLK_FREQ_MHZ == 8

#define UCBRS_2400          0x2500
#define UCBRS_4800          0xD600
#define UCBRS_9600          0x4900
#define UCBRS_19200         0xB600
#define UCBRS_38400         0x8400
#define UCBRS_57600         0xF700
#define UCBRS_115200        0x5500

#define UCBR0_2400          208
#define UCBR0_4800          104
#define UCBR0_9600          52
#define UCBR0_19200         26
#define UCBR0_38400         13
#define UCBR0_57600         8
#define UCBR0_115200        4

#define UCBR1_2400          0

#define UCBRF_2400          0x50
#define UCBRF_4800          0x20
#define UCBRF_9600          0x10
#define UCBRF_19200         0x00
#define UCBRF_38400         0x00
#define UCBRF_57600         0xA0
#define UCBRF_115200        0x50

#elif MCLK_FREQ_MHZ == 16

#define UCBRS_2400          0xD600
#define UCBRS_4800          0x2500
#define UCBRS_9600          0xD600
#define UCBRS_19200         0x4900
#define UCBRS_38400         0xB600
#define UCBRS_57600         0xDD00
// #define UCBRS_115200        0xF700

#define UCBR0_2400          160     //416
#define UCBR0_4800          208
#define UCBR0_9600          104
#define UCBR0_19200         52
#define UCBR0_38400         26
#define UCBR0_57600         17
// #define UCBR0_115200        8

#define UCBR1_2400          1

#define UCBRF_2400          0xA0
#define UCBRF_4800          0x50
#define UCBRF_9600          0x20
#define UCBRF_19200         0x10
#define UCBRF_38400         0x00
#define UCBRF_57600         0x50
// #define UCBRF_115200        0xA0

#endif



#endif /* TELEMETRY_H_ */
