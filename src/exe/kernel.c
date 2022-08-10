#include "io/uart.h"

void main()
{
    uart_init();
    uart_writestring("Hello, world!\n");
    while (1);
}
