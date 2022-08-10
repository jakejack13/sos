/**
 * Universal Asynchronous Receiver/Transmitter
 */

#ifndef _UART_H_
#define _UART_H_

/** Initializes the UART subsystem */
void uart_init();
/** Transmits a byte over UART */
void uart_writebyte(char c);
/** Transmits a null terminated string over UART */
void uart_writestring(const char *buffer);
/** Receives a byte over UART */
char uart_readbyte();
/** Receives a null terminated string over UART bound by the given size */
void uart_readstring(char *buffer, unsigned int size);

#endif //_UART_H_
