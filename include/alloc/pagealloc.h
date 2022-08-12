/** Memory allocation part of the pager that allocates pages from a defined space in memory */

#ifndef _PAGEALLOC_H_
#define _PAGEALLOC_H_

#include "stdlib/stdtypes.h"

/** The size of pages in the system */
#define PAGE_SIZE 4 * 1024

/** Initializes the paging system */
void page_init();

/** Allocates a page of memory */
void *page_alloc();

/** Frees a previously allocated page */
bool page_free(void *p);

#endif //_PAGEALLOC_H_