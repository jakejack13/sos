#include "stdlib/stdio.h"

#include "config.h"
#include "io/uart.h"
#include "stdlib/stdstr.h"

void stdio_init() {
    #if UART_IO
    uart_init();
    #endif
}

void prints(const char *string) {
    #if UART_IO
    uart_writestring(string);
    #endif
}

void printc(char c) {
    #if UART_IO
    uart_writebyte((unsigned char) c);
    #endif
}

void gets(char *buffer, unsigned int length) {
    #if UART_IO
    uart_readstring(buffer, length); 
    #endif
}

char getc() {
    #if UART_IO
    return (char) uart_readbyte();
    #endif
}
