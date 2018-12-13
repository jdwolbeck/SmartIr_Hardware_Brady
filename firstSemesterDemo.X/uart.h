#include <xc.h>
#include <stdbool.h>
#define MAX 20
    
extern unsigned int uart_flag;
extern char U1RxByte;
extern char U1RxBuffer[MAX];
extern char U1TxBuffer[MAX];

bool uart_init(void);
void uart_write_byte(char);
void uart_write_string(char[]);

