#include "alloc/pagealloc.h"

extern char __pages_start; // linker symbol
extern char __pages_size; // linker symbol

/** The pointer to the start of the pages section of memory where all pages are allocated from */
static const char *pages = &__pages_start;
/** The length of the pages section of memory */
static const unsigned long pages_size = (unsigned long) &__pages_size;
