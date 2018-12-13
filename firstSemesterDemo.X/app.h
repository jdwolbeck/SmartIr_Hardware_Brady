#include "adc1.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct // temporarily moved from adc1.c
{
    uint16_t tempConversion; 
    uint16_t liteConversion; 
    uint16_t soilConversion; 
    uint8_t U1RxByte;
    
} APP_DATA;

extern APP_DATA appData;



