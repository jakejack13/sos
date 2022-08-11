#ifndef _HEAPALLOC_H_
#define _HEAPALLOC_H_

#include "stdlib/stdtypes.h"

struct heap_state {
    void *page;
    size_t size;
    //TODO
};

/** Asks the kernel for a page for allocation and initializes the allocator */
void heap_init(struct heap_state *state);

/** Frees the page used for allocation */
void heap_done(struct heap_state *state);

/** Allocates a chunk of memory of the given size on the heap */
void *heap_malloc(struct heap_state *state, size_t size);

/** Resizes a chunk of memory previously allocated by malloc */
void *heap_realloc(struct heap_state *state, void *p, size_t size);

/** Frees a chunk of memory previously allocated by malloc */
bool heap_free(struct heap_state *state, void *p);
#endif