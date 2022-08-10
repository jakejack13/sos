/** 
 * Interface to io streams
 */

#ifndef _IO_H_
#define _IO_H_

/** The data structure used to print to in and get from out */
struct iostream {
    /** The state of the io stream */
    void *state;
    /** Initializes the io stream */
    void (*init)(void);
    /** Prints the string to out */
    void (*prints)(const char *s);
    /** Prints the character to out */
    void (*printc)(char c);
    /** Gets a string from in, limited by the given length */
    void (*gets)(char *buffer, unsigned int length);
    /** Gets a character from in */
    char (*getc)(void);
};

/** Returns a UART io stream */
struct iostream *uart_iostream();

#endif