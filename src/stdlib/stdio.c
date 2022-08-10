#include "stdlib/stdio.h"

#include "io/uart.h"

void prints(const char *string) {
    #if UART_IO
    uart_writestring(string);
    #endif
}

void gets(char *buffer, unsigned int length) {
    #if UART_IO
    uart_readstring(buffer, length); 
    #endif
}
