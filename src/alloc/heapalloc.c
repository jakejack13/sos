#include "alloc/alloc.h"

static struct allocator heap_allocator;

/** The start of the heap as declared in the linker script */
extern char __heap_start;
/** The heap, in the form of a char array */
static char *heap = &__heap_start;
/** The size of the heap */
extern size_t __heap_size;

/** Initializes the heap allocator */
static void heap_init() {
    
}

/** Allocates a chunk of memory of the given size in heap memory */
static void *heap_malloc(size_t size) {
    return NULL;
}

/** Resizes a chunk of memory in heap memory previously allocated by malloc */
static void *heap_realloc(void *p, size_t size) {
    return NULL;
}

/** Frees a chunk of memory in heap memory previous allocated by malloc */
static int heap_free(void *p) {
    return -1;
}

struct allocator *heap_alloc() {
    heap_allocator.init = heap_init;
    heap_allocator.malloc = heap_malloc;
    heap_allocator.realloc = heap_realloc;
    heap_allocator.free = heap_free;
    return &heap_allocator;
}
