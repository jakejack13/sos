#include "alloc/alloc.h"

/** The global allocator */
static struct allocator global_allocator;

#define POOL_SIZE 16 * 1024 * 1024

/** Pool node for metadata */
struct Node {
  char*   pool_element;
  bool    used;
  bool    head;
  int     allocated;  // Should be -1 if node is not a head. 
};

/** Pool of metadata that maps to the pool array */
static struct Node metadata[POOL_SIZE];

/** The pool of memory that can be accessed by the global allocator */
static char pool[POOL_SIZE];

/** Initializes the global allocator */
static void global_init() {
    for(int i = 0; i < POOL_SIZE; i++) {
        metadata[i].pool_element = &pool[i];
        metadata[i].used = false;
        metadata[i].head = false;
        metadata[i].allocated = -1;
    }
}

/** Finds corresponding metadata to a given pool element */
static struct Node *find_element(void *p) {
    struct Node *element;
    for(int i = 0; i < POOL_SIZE; i++) {
        if(metadata[i].pool_element == p) {
            element = metadata+i;
            break;
        }
    }

    return element;
}

/** Flips a chunk of data's "used" state to the opposite */
static void switch_state(void *p, size_t size) {
    struct Node *element = find_element(p);

    // Set data to opposite state
    for(int i = 0; i < size; i++) {
        if(element[i].used) element[i].used = false;
        else element[i].used = true;
    }
}

/** Allocates a chunk of memory of the given size in global memory */
static void *global_malloc(size_t size) {

}

/** Resizes a chunk of memory in global memory previously allocated by malloc */
static void *global_realloc(void *p, size_t size) {
    return NULL;
}

/** Frees a chunk of memory in global memory previous allocated by malloc */
static int global_free(void *p) {
    if (!find_element(p)->head) return 0;

}

struct allocator *global_alloc() {
    global_allocator.init = global_init;
    global_allocator.malloc = global_malloc;
    global_allocator.realloc = global_realloc;
    global_allocator.free = global_free;
    return &global_allocator;
}
