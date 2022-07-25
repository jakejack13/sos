#include "stdlib/stdalloc.h"

#include "alloc/alloc.h"
#include "config.h"

/** The currently used standard allocator */
static struct allocator *allocator;

void stdalloc_init() {
    #if CONFIG_STDALLOC_HEAP 
    allocator = heap_alloc();
    #endif 
}

void *malloc(size_t size) {
    return (allocator->malloc)(size);
}

void *realloc(void *p, size_t size) {
    return (allocator->realloc)(p,size);
}

int free(void *p) {
    return (allocator->free)(p);
}
