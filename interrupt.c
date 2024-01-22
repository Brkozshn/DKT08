/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : interrupt.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 16/05/2022
* Description        : All interrupt functions will be here
********************************************************************************/
#include "msp430.h"
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "bsp.h"
#include "timeout.h"
#include "ram.h"
#include "submain.h"
#include "DS1302.h"
#include "lcd.h"


u8 ms20_cntr = 0;    //19 clock equals to 2 ms at 9009Hz

/*  Function    : uart_rx_int_handler
 *  Inputs      : -
 *  Return      : -
 *  Desc        :
 */
void uart_rx_int_handler()
{
    volatile u8 c;
//    while (!(IFG2&UCA1TXIFG));                // USCI_A1 TX buffer ready?
//        UCA1TXBUF = UCA1RXBUF;                    // TX -> RXed character

    c = UCA1RXBUF;


if(c==0x01)
{
    __no_operation(); //for debugger
}

if(c==51)
{
 __no_operation(); //for debugger


}


    write_sample_to_buffer(&uart_rx_buffer, c);
}

//******************************************************************************
// UART Interrupt ***********************************************************
//******************************************************************************

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
    //  while(!(UCA1IFG&UCTXIFG));
      UCA1IFG &=~ UCRXIFG;            // Clear interrupt
   //   UCA1TXBUF = UCA1RXBUF;
    //  UCA1TXBUF = UCA1RXBUF;
      uart_rx_int_handler();
      __no_operation();
      break;
    case USCI_UART_UCTXIFG:
       // uart_tx_int_handler();
        __no_operation();
        switch(system_status.modbus_tx_flag)
        {
        case MODBUS_SEND_ERROR_FUNC:

            modbus_tx_error_int_handler();
            __no_operation();
            break;
        default:

            modbus_tx_multiple_datas_int_handler();
            __no_operation();
            break;
        }
        break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
  }
}
// #if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
// #pragma vector=USCI_A0_VECTOR
// __interrupt void USCI_A0_ISR(void)
// #elif defined(__GNUC__)
// void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
// #else
// #error Compiler not supported!
// #endif
// {
//   switch(__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
//   {
//     case USCI_NONE: break;
//     case USCI_UART_UCRXIFG:
//     //  while(!(UCA0IFG&UCTXIFG));
//       UCA0IFG &=~ UCRXIFG;            // Clear interrupt
//    //   UCA0TXBUF = UCA0RXBUF;
//     //  UCA1TXBUF = UCA0RXBUF;
//       uart_rx_int_handler();
//       __no_operation();
//       break;
//     case USCI_UART_UCTXIFG:
//        // uart_tx_int_handler();
//         __no_operation();
//         switch(system_status.modbus_tx_flag)
//         {
//         case MODBUS_SEND_ERROR_FUNC:

//             modbus_tx_error_int_handler();
//             __no_operation();
//             break;
//         default:

//             modbus_tx_multiple_datas_int_handler();
//             __no_operation();
//             break;
//         }
//         break;
//     case USCI_UART_UCSTTIFG: break;
//     case USCI_UART_UCTXCPTIFG: break;
//   }
// }


// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    CLEAR_INTERRUPTS;
    ms20_cntr++;

    if(ms20_cntr > (TIMER_FREQ/1000)-1){
        ms20_cntr = 0;
        process_timeouts(1);
        system_status.timer_tick++;

        if(system_status.timer_tick >= 200000000)
        {
            system_status.timer_tick = 0;
        }
    }
    RESTORE_INTERRUPTS;
}


//// Timer0 B0 interrupt service routine
//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=TIMER0_B0_VECTOR
//__interrupt void TIMER0_B0_ISR(void)
//#elif defined(__GNUC__)
//void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) TIMER0_B0_ISR (void)
//#else
//#error Compiler not supported!
//#endif
//{
//    P2OUT |= BIT7;
//    start_conversion_adc();
//    __no_operation();                               // Only for debugger
//    P2OUT &= ~BIT7;
//
//}






//// ADC interrupt service routine
//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=ADC_VECTOR
//__interrupt void ADC_ISR(void)
//#elif defined(__GNUC__)
//void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
//#else
//#error Compiler not supported!
//#endif
//{
//    P2OUT |= BIT4;
//    __no_operation();
//    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
//    {
//        case ADCIV_NONE:
//            break;
//        case ADCIV_ADCOVIFG:
//            break;
//        case ADCIV_ADCTOVIFG:
//            break;
//        case ADCIV_ADCHIIFG:
//            break;
//        case ADCIV_ADCLOIFG:
//            break;
//        case ADCIV_ADCINIFG:
//            break;
//        case ADCIV_ADCIFG:
//
//            temp_values[adc_ind] = ADCMEM0;
//            write_sample_to_adc_buffer(&adc_buffer[adc_ind], temp_values[adc_ind]);
//
//            __no_operation();                               // Only for debugger
//            if(adc_ind >= NUM_OF_ADC-1)
//              {
//                system_status.adc_flag = TRUE;
//
//                syc_adc++;
//                if(syc_adc>= 21234567)
//                {
//                    adc_ind = 0;
//                    __no_operation();
//                }
//
//                __no_operation();                               // Only for debugger
//                adc_ind = 0;
//              }
//              else
//              {
//                  adc_ind++;
//                  __no_operation();
//              }
//
//            __no_operation(); // For debugger
//            ADCIFG=0;
//
//            //ADCCTL0 |= ADCENC | ADCSC; // Sampling and conversion start
//            ADCCTL0 &= ~ADCENC;                                      // Enable ADC
////            TB0CCTL1 |= TBCLR;                                   // Clear TAR to start the ADC sample-and-conversion
////
//            break;
//        default:
//            break;
//    }
//
//
//    if(ms20_cntr > (TIMER_FREQ/1000)-1){
//        ms20_cntr = 0;
//        process_timeouts(1);
//    }
//
//    P2OUT &= ~BIT4;
//}



