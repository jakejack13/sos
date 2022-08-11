#include "stdlib/stdalloc.h"

#include "alloc/heapalloc.h"

/** The currently used standard allocator */
static struct heap_state kernel_heap;

struct heap_state *current_heap;

void stdalloc_init() {
    current_heap = &kernel_heap;
    heap_init(current_heap);
}

void *malloc(size_t size) {
    return heap_malloc(current_heap, size);
}

void *realloc(void *p, size_t size) {
    return heap_realloc(current_heap, p, size);
}

bool free(void *p) {
    return heap_free(current_heap, p);
}
