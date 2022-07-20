/** 
 * Library of functions for dynamically allocating memory 
 */

#ifndef _STDMEM_H_
#define _STDMEM_H_

#include "stdlib/stdtypes.h"

/** Initializes the standard allocator */
void stdalloc_init();
/** Allocates a chunk of memory of the given size */
void *malloc(size_t size);
/** Resizes a chunk of memory previously allocated by malloc */
void *realloc(void *p, size_t size);
/** Frees a chunk of memory previous allocated by malloc */
int free(void *p);

#endif //_STDMEM_H_