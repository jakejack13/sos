/**
 * Universal Asynchronous Receiver/Transmitter
 */

#ifndef _UART_H_
#define _UART_H_

void uart_init();
void uart_writebyte(unsigned char c);
void uart_writestring(const char *buffer);
unsigned char uart_readbyte();
unsigned int uart_readstring(char *buffer, unsigned int size);

#endif //_UART_H_
