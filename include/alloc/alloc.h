#ifndef _ALLOC_H_
#define _ALLOC_H_

#include "stdlib/stdtypes.h"

/** The data structure used to define dynamic memory allocators */
struct allocator {
    /** The state of the allocator */
    void *state;
    /** Initializes the allocator */
    void (*init)(void);
    /** Allocates a chunk of memory of the given size */
    void *(*malloc)(size_t size);
    /** Resizes a chunk of memory previously allocated by malloc */
    void *(*realloc)(void *p, size_t size);
    /** Frees a chunk of memory previous allocated by malloc */
    int (*free)(void *p);
};

/** Returns a heap allocator */
struct allocator *heap_alloc();
/** Returns a global allocator */
struct allocator *global_alloc();

#endif //_ALLOC_H_