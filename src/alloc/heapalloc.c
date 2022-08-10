#include "alloc/alloc.h"

static struct allocator heap_struct;

/** The start of the heap as declared in the linker script */
extern char _heap_start;

/** The heap, in the form of a char array */
static char *heap = &_heap_start;
/** The size of the heap */
static size_t heap_size;

static void heap_init() {
    
}

static void *heap_malloc(size_t size) {
    return NULL;
}

static void *heap_realloc(void *p, size_t size) {
    return NULL;
}

static int heap_free(void *p) {
    return -1;
}

struct allocator *heap_alloc() {
    heap_struct.init = heap_init;
    heap_struct.malloc = heap_malloc;
    heap_struct.realloc = heap_realloc;
    heap_struct.free = heap_free;
    return &heap_struct;
}
