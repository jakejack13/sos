#include "alloc/pagealloc.h"

extern char __pagespace_start; // linker symbol
extern char __pagespace_size; // linker symbol

/** The pointer to the start of the page space, the pages section of memory where all pages are allocated from */
static const char *pagespace = &__pagespace_start;
/** The length of the page space */
static const unsigned long ps_size = (unsigned long) &__pagespace_size;

void page_init() { }

void *page_alloc() {
    return NULL;
}

bool page_free(void *p) {
    return false;
}
