/** 
 * Library of functions for accessing standard io
 */

#ifndef _STDIO_H_
#define _STDIO_H_

#include "stdlib/stdtypes.h"

/** Initializes the standard io */
void stdio_init();
/** Prints the string to stdout */
void prints(const char *s);
/** Prints the character to stdout */
void printc(char c);
/** Gets a string from stdin, limited by the given length */
void gets(char *buffer, size_t length);
/** Gets a character from stdin */
char getc();

#endif //_STDIO_H_