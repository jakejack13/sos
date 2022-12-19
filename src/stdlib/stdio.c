#include "stdlib/stdio.h"

#include "config.h"
#include "io/io.h"
#include "stdlib/stdstr.h"

/** The currently used standard iostream */
static struct iostream *iostream;

void stdio_init() {
    #ifdef USER
    iostream = glibc_iostream();
    #elif CONFIG_UART_IO
    iostream = uart_iostream();
    #endif
    (iostream->init)();
}

void prints(const char *s) {
    (iostream->prints)(s);
}

void printc(char c) {
    (iostream->printc)(c);
}

void gets(char *buffer, size_t length) {
    (iostream->gets)(buffer, length);
}

char getc() {
    return (iostream->getc)();
}
