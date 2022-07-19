#ifndef _STDSTR_H_
#define _STDSTR_H_

#include "stdlib/stdtypes.h"

void memcpy(void *dest, const void *src, size_t n);
void memset(void *str, char c, size_t n);
size_t strlen(const char *s);

#endif //_STDSTR_H_