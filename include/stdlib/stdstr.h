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
/** Compares the first n bytes of memory area str1 and memory area str2.
 * If result < 0 then str1 < str2.
 * If result > 0 then str1 > str2.
 * If result = 0 then str1 == str2.
 */
int memcmp(const void *str1, const void *str2, size_t n);
/** Returns the length of a null-pointer string */
size_t strlen(const char *s);

#endif //_STDSTR_H_