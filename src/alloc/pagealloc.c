#include "alloc/pagealloc.h"

#include "config.h"

extern char __pagespace_start; // linker symbol
extern char __pagespace_size; // linker symbol

/** The pointer to the start of the page space, the pages section of memory where all pages are allocated from */
static char *pagespace;
/** The length of the page space */
static unsigned long ps_size;

#ifdef USER
#include <stdlib.h>
#endif

void page_init() {
    #ifdef USER
    ps_size = USER_PAGESPACE_SIZE;
    pagespace = malloc(USER_PAGESPACE_SIZE);
    #else
    pagespace = &__pagespace_start;
    ps_size = (unsigned long) &__pagespace_size;
    #endif
}

void *page_alloc() {
    return NULL;
}

bool page_free(void *p) {
    return false;
}
