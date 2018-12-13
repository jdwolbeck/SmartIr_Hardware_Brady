#include <xc.h> 
#include "gpio.h"

void LED_enable( int );
void LED_off( int );
void LED_on( int );
void LED_toggle( int );
bool LED_status( int );


void LED_enable( int ledPin)
{   
    switch(ledPin)
    {
        case 5 :
            TRISBbits.TRISB5 = 0;
            break;
        case 6 :
            TRISBbits.TRISB6 = 0;
            break;
        default:
            break;
    }
    
}

void LED_toggle( int ledPin)
{   
    switch(ledPin)
    {
        case 5 :
            PORTBbits.RB5 ^= 1;
            break;
            
        case 6 :
            PORTBbits.RB6 ^= 1;
            break;
        default:
            break;
    }
    
}

bool LED_status( int ledPin)
{   
    bool status;
    switch(ledPin)
    {
        case 5 :
            status = PORTBbits.RB5 ?  true :  false ;
            return status;
            
        case 6 :
            status = PORTBbits.RB6 ?  true :  false ;
            return status;
            
        default:
            return false;
    }
    
}


