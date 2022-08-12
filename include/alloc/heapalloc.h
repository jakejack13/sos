/** Dynamic memory allocator that allocates memory from various heap pages */

#ifndef _HEAPALLOC_H_
#define _HEAPALLOC_H_

#include "stdlib/stdtypes.h"

/** Represents a node of metadata that maps to the corresponding element in the heap struct's memory page */
struct Node {
    /** The pointer to the corresponding element in the heap's memory page */
    char *page_element;
    /** The amount of space allocated for the appropriate chunk. Should only be used by head nodes. Default value is -1 if not a head */
    int allocated;
    /** The index of the corresponding element in the pool array */
    int index;
    /** Determines whether the current node is currently allocated or not */
    bool used;
    /** Determines whether the current node is the first element of a chunk of allocated memory */
    bool head;
};

/** The heap for the process currently executing */
extern struct heap_state *current_heap;

/** Represents the state of a heap */
struct heap_state {
    /** The pointer to memory returned by the pager */
    void *page;
    /** The size of memory allocated */
    size_t size;
    /** The pool of metadata nodes that maps to the memory allocated by the pager */
    struct Node metadata[];
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

#endif //_HEAPALLOC_H_