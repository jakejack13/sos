#include "alloc/alloc.h"

/** The global allocator */
static struct allocator global_allocator;

#define POOL_SIZE 16 * 1024 * 1024

/** Pool node for metadata */
struct Node {
  char*   pool_element;
  bool    used;
};

/** Pool of metadata that maps to the pool array */
static struct Node metadata[POOL_SIZE];

/** The pool of memory that can be accessed by the global allocator */
static char pool[POOL_SIZE];

/** Initializes the global allocator */
static void global_init() {

}

/** Allocates a chunk of memory of the given size in global memory */
static void *global_malloc(size_t size) {
    return NULL;
}

/** Resizes a chunk of memory in global memory previously allocated by malloc */
static void *global_realloc(void *p, size_t size) {
    return NULL;
}

/** Frees a chunk of memory in global memory previous allocated by malloc */
static int global_free(void *p) {
    return -1;
}

struct allocator *global_alloc() {
    global_allocator.init = global_init;
    global_allocator.malloc = global_malloc;
    global_allocator.realloc = global_realloc;
    global_allocator.free = global_free;
    return &global_allocator;
}
