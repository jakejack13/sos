/** 
 * Library of functions for memory manipulation 
 */

#ifndef _STDSTR_H_
#define _STDSTR_H_

#include "stdlib/stdtypes.h"

/** Copies `n` characters from `src` to `dest` */
void memcpy(void *dest, const void *src, size_t n);
/** Writes `n` of character `c` to `str` */
void memset(void *str, char c, size_t n);
/** Returns the length of a null-pointer string */
size_t strlen(const char *s);

#endif //_STDSTR_H_