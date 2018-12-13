
/*---------------------------------------------------------------------
 * Brady Knaeble 
 * ECE 422
 * October 31, 2018
 * Instructor: Peng Lei
 * 
 * Devices:
 * PIC24FJ256GA702-I/SP
 * RN42 BlueSmirf Bluetooth module
 * momentary switch to drive external interrupt 0
 * teraTerm was used to write to, and read from the UART buffers
 *-----------------------------------------------------------------------*/
/* Device header file */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__PIC24E__)
#include <p24Exxxx.h>
#elif defined (__PIC24F__)||defined (__PIC24FK__)
#include <p24Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>
#include <xc.h>
#include "uart.h"
#include "system.h"
#include "gpio.h"
#include "adc1.h"
#include "app.h"

bool sampleFlag = false;
APP_DATA appData;
double tempCon = 0;

int main() {

    system_init();
    uart_init();
    ADC1_init();


    while (1) {
        if (sampleFlag) {
            //initialize ADC on pin RB14 analog channel 6             

            appData.soilConversion = ADC1_getConversion(ADC1_SOIL_SENSOR);
            // convert 
            sprintf(U1TxBuffer, "soil: %i\n\r", (uint16_t) appData.soilConversion);
            uart_write_string(U1TxBuffer);

            
            
            appData.liteConversion = ADC1_getConversion(ADC1_PHOTORESISTOR);
            
            tempCon = (appData.liteConversion)/10.24;
            sprintf(U1TxBuffer, "lite: %.2f%\n\r", (double)tempCon);
            uart_write_string(U1TxBuffer);



            appData.tempConversion = ADC1_getConversion(ADC1_TEMPERATURE);
            // convert 
            tempCon = ((((appData.tempConversion) / 16.0)) * (1.8)) + 32.0;
            sprintf(U1TxBuffer, "temp: %.2f\n\r", (double)tempCon);
            uart_write_string(U1TxBuffer);

            sampleFlag = false;

        }
    }
    return 0;

}

/* Timer 1 ISR for heartbeat indicator */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    PORTBbits.RB3 = !(PORTBbits.RB3);
    IFS0bits.T1IF = 0;
    sampleFlag = true;
    TMR1 = 0x0000;
}

/* UART1 U1RX interrupt routine code */
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0; // clear U1RX flag 
    appData.U1RxByte = U1RXREG;
    uart_flag = 1;
}

