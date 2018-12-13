
#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

void LED_enable(int);
void LED_off( int );
void LED_on( int );
void LED_toggle( int );
bool LED_status( int );

#endif // GPIO_H