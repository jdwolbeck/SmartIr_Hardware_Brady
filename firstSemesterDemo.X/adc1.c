

#include <xc.h>
#include "app.h"
#include "adc1.h"
#include <stdbool.h>


/**********************************************************
 * 
 * ADC Driver functions
 * 
*************************************************************/


/****************************************************************
 * 
 * ADC1_Initialize must be call before all other ADC functions
 *  
 ***************************************************************/
void ADC1_init(void)
{
    
        AD1CON2bits.PVCFG = 0x0 ;
        AD1CON3bits.ADCS = 0xFF ;
        AD1CON1bits.SSRC = 0x0 ;
        AD1CON3bits.SAMC = 0b10000 ;
        AD1CON1bits.FORM = 0b00 ;
        AD1CON2bits.SMPI = 0x0 ;
        AD1CON1bits.ADON = 1 ;
   
}

void ADC1_start(void)
{
  
   int i = 0;
   int delay = 1000;
   AD1CON1bits.SAMP = 1;
   
   for(i = 0; i <delay; i++ ){}
   
}

void ADC1_stop( void )
{
   AD1CON1bits.SAMP = 0;
}


bool ADC1_conversionComplete( void )
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}


void ADC1_channelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}

uint16_t ADC1_getConversion( ADC1_CHANNEL channel )
{

    ADC1_channelSelect(channel);
    
    ADC1_start();
    
    ADC1_stop();
    
    while (!ADC1_conversionComplete()){}
    
    return ADC1BUF0;
}


void ADC1_Tasks ( void )
{
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}


/**
  End of File
*/
