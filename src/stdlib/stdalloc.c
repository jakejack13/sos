#include "stdlib/stdalloc.h"

#include "alloc/heapalloc.h"
#include "alloc/pagealloc.h"

struct heap_state *current_heap;

void stdalloc_init() {
    page_init();
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
