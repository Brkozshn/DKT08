/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : uart_A1.c
* Author             : Onur Kay�kc�
* Version            : V1.0
* Date               : 24/02/2022
* Description        : uart A1 functions
********************************************************************************/


#include <msp430.h>
#include "main.h"
#include "timeout.h"
#include "bsp.h"
#include "ram.h"
#include "cnc.h"
#include "uart_A1.h"
#include "telemetry.h"

void UART_A1_init()
{

    //UCA1RXD -> P2.5 & UCA1TXD -> P2.6
    UART1_SEL_0 |=  (UART1_RX_PIN | UART1_TX_PIN);                    // set 2-UART pin as second function
    UART1_SEL_1 &= ~(UART1_RX_PIN | UART1_TX_PIN);                    // set 2-UART pin as second function

     // Configure UART
    UCA1CTLW0 |= UCSWRST;
    UCA1CTLW0 |= UCSSEL__SMCLK;
    switch(baudrate_A1)
    {

    case UART_2400:
        // BAUDRATE:2400//
        // Baud Rate calculation
        // N/16= 8000000/(16*2400) = 208.333
        // Fractional portion = 0.333
        // Family User's Guide Table 22-4: UCBRSx = 0x25
        // UCBRFx = int ( (208.333-208)*16) = int (5,328) = 5
        // UCBRSx =N - INT(N)=> N= 8000000/2400 =3333.3333  --- N - INT(N) = 0.3333 UCBRSx =0x25

        UCA1BR0 = UCBR0_2400;                             // 8000000/16/2400
        UCA1BR1 = UCBR1_2400;
        // UCBRS0 = 0x25;

        UCA1MCTLW = UCBRS_2400 | UCOS16_1 | UCBRF_2400 ;
       break;

   case UART_4800:
       // BAUDRATE:4800//
       // Baud Rate calculation
       // N/16= 8000000/(16*4800) = 104.167
       // Fractional portion = 0.167
       // Family User's Guide Table 22-4: UCBRSx = 0x25
       // UCBRFx = int ( (104.166-104)*16) = int (2,667) = 2
       // UCBRSx =N - INT(N)=> N= 8000000/4800 =1666.667  --- N - INT(N) = 0.6667 UCBRSx =0xD6

       UCA1BR0 = UCBR0_4800;
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_4800 | UCOS16_1 | UCBRF_4800 ;
       break;

   case UART_9600:
       // BAUDRATE:9600//
       // Baud Rate calculation
       // N/16= 8000000/(16*9600) = 52.083
       // Fractional portion = 0.083
       // Family User's Guide Table 22-4: UCBRSx = 0x25
       // UCBRFx = int ( (52.083-52)*16) = int (1,33) = 1
       // UCBRSx =N - INT(N)=> N= 8000000/9600 =833,3333  --- N - INT(N) = 0,3333 UCBRSx =0x25

       UCA1BR0 = UCBR0_9600;                             // 8000000/16/9600
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_9600 | UCOS16_1 | UCBRF_9600 ;

       break;

   case UART_19200:
       // BAUDRATE:19200//
       // Baud Rate calculation
       // N/16= 8000000/(16*19200) = 26.04166
       // Fractional portion = 0.04166
       // Family User's Guide Table 22-4: UCBRSx = 0xD6
       // UCBRFx = int ( (26.04166-26)*16) = int (0,6667) = 0
       // UCBRSx =N - INT(N)=> N= 8000000/19200 =416.6667  --- N - INT(N) = 0,6667 UCBRSx =0xD6

       UCA1BR0 = UCBR0_19200;
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_19200 | UCOS16_1 | UCBRF_19200 ;
       break;

   case UART_38400:
       // BAUDRATE:38400//
       // Baud Rate calculation
       // N/16= 8000000/(16*38400) = 13.02083
       // Fractional portion = 0.02083
       // Family User's Guide Table 22-4: UCBRSx = 0x25
       // UCBRFx = int ( (13.02083-13)*16) = int (0,3334) = 0
       // UCBRSx =N - INT(N)=> N= 8000000/38400 =208.3334  --- N - INT(N) = 0,3334 UCBRSx =0x25

       UCA1BR0 = UCBR0_38400;
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_38400 | UCOS16_1 | UCBRF_38400 ;
       break;

   case UART_57600:
       // BAUDRATE:57600//
       // Baud Rate calculation
       // N/16= 8000000/(16*57600) = 8.68055
       // Fractional portion = 0.68055
       // Family User's Guide Table 22-4: UCBRSx = 0xF7
       // UCBRFx = int ( (8.68055-8)*16) = int (10,8889) = 10
       // UCBRSx =N - INT(N)=> N= 8000000/57600 =138,8888  --- N - INT(N) = 0,8889 UCBRSx =0xF7

       UCA1BR0 = UCBR0_57600;
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_57600 | UCOS16_1 | UCBRF_57600 ;
       break;

//    case UART_115200:
//        // BAUDRATE:115200//
//        // Baud Rate calculation
//        // if N>16-> N/16= 8000000/(16*115200) = 4.340
//        // Fractional portion = 0.340
//        // Family User's Guide Table 22-4: UCBRSx = 55
//        // UCBRFx = int ( (4,340-4)*16) = int (5,44) = 5
//        // UCBRSx =N - INT(N)=> N= 8000000/115200 =69,444  --- N - INT(N) = 0,444 then UCBRSx =0x55

//        UCA1BR0 = UCBR0_115200;                             // 8000000/16/9600
//        UCA1BR1 = 0x00;


//        UCA1MCTLW = UCBRS_115200 | UCOS16_1 | UCBRF_115200 ;


//        break;
   default:
       __no_operation();
       UCA1BR0 = UCBR0_9600;                             // 8000000/16/9600
       UCA1BR1 = 0x00;
       // UCBRS0 = 0x25;

       UCA1MCTLW = UCBRS_9600 | UCOS16_1 | UCBRF_9600 ;

//       SYSCFG0 = FRWPPW | FRWPOA0 | DFWP | PFWP;// Configure 1024 bytes for FRAM write
//       baudrate_A1 = 2;
//       SYSCFG0 = FRWPPW | DFWP | PFWP;     // Program FRAM write protected (not writable)

   break;

   }

       UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
       UCA1IE |= UCRXIE;                        // Enable USCI_A0 RX interruptw

}


u8 is_uart_tx_busy_A1()
{
    return system_status.uart_tx_busy_A1;
}

void uart_send_byte_A1(u8 byte)
{
    while(!(UCA1IFG&UCTXIFG));               // USCI_A1 TX buffer ready?
        UCA1TXBUF = byte;                          // TX  character

}



