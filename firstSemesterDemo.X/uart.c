#include<xc.h>
#include "uart.h"
#include <stdbool.h>


#define MAX 20
    
unsigned int uart_flag = 0;

char U1RxByte = '1';
char U1RxBuffer[MAX];
char U1TxBuffer[MAX];

    
bool uart_init(void){
       
/************************************************************
 * Setup the UART 1 pins 
 ************************************************************/
         
    // set pin direction 
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB7 = 0;
    
    // set pins to digital
    ANSBbits.ANSB2 = 0;
    ANSBbits.ANSB7 = 0;

    
/************************************************************
 * Configure UART 1 SFR's 
 ************************************************************/    
    
    // disable UART
    U1MODE = 0x0000;

    // Baudrate = 9600;    clock 4MHz; U1BRG 103
    // Baudrate = 115200;  clock 4MHz; U1BRG 8
    U1MODE= 0x0000;
    U1MODEbits.BRGH = 1;
    U1STA = 0x0000;
    U1BRG = 103;
    IPC2bits.U1RXIP = 1;
    IEC0bits.U1RXIE = 1;         // Enable UART RX interrupt
    IFS0bits.U1RXIF = 0;        // clear flag  
    U1MODEbits.UARTEN = 1;       // Enable UART and wait to enable the TX
    U1STAbits.UTXEN = 1;         // enable Transmission
    return true;

}


void uart_write_byte(char ch )
{
    U1TXREG  = ch;
}

void uart_write_string(char buf[])
{
    int i = 0;
    while(buf[i] != '\0')
    {
        
        while(U1STAbits.UTXBF == 0)
        {
            uart_write_byte( buf[i] );
            i++;
        }
    }
}



