#include "stdlib/stdalloc.h"
#include "stdlib/stdstr.h"

#include "alloc/heapalloc.h"
#include "alloc/pagealloc.h"

struct heap_state *current_heap;

void stdalloc_init() {
    page_init();
}

void *malloc(size_t size) {
    return heap_malloc(current_heap, size);
}

void *calloc(size_t _NumOfElements, size_t _SizeOfElements) { 
    void* buffer = malloc(_NumOfElements * _SizeOfElements);
    
    if (buffer == NULL) return NULL;

    memset(buffer, 0, _NumOfElements * _SizeOfElements);
    return buffer;
}

void *realloc(void *p, size_t size) {
    return heap_realloc(current_heap, p, size);
}

bool free(void *p) {
    return heap_free(current_heap, p);
}
