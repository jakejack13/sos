#include "alloc/alloc.h"

/** The global allocator */
static struct allocator global_allocator;

#define POOL_SIZE 16 * 1024 * 1024

/** Pool node for metadata */
struct Node {
  char*   pool_element;
  int     allocated;  // Should be -1 if node is not a head. 
  int     index;
  bool    used;
  bool    head;
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
        metadata[i].index = i;
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
static void switch_state(struct Node *element, size_t size) {
    // Set data to opposite state
    for(int i = 0; i < size; i++) {
        if((element+i)->used) (element+i)->used = false;
        else (element+i)->used = true;
    }
}

/** Finds a chunk in the pool that satisfies the size requirement. Returns the head of the chunk */
static struct Node *find_space(size_t size) {
    int index = 0;
    bool fits = true;
    while(index < POOL_SIZE) {
        for(int i = 0; i < size; i++) {
            if((metadata+i)->used) {
                fits = false;
                index += (i + (metadata+i)->allocated); // Skip the allocated block to save traversal time :rofl:
                break;
            }
        }

        if(fits) return (metadata+index);
    }
    return NULL;
}

/** Allocates a chunk of memory of the given size in global memory */
static void *global_malloc(size_t size) {
    struct Node *head = find_space(size);
    head->allocated = size;
    head->head = true;
    switch_state(head, size);
    for(int i = 0; i < size; i++) {
        (head+i)->pool_element = &pool[(head+i)->index]; // Link metadata node to pool element
    }
    return head->pool_element;
}

/** Resizes a chunk of memory in global memory previously allocated by malloc */
static void *global_realloc(void *p, size_t size) {
    if(!global_free(p)) return NULL;
    struct Node *head = find_space(size);
    switch_state(head, size);
    for(int i = 0; i < size; i++) {
        (head+i)-> pool_element = p+i;
    }
    
    return head;
}

/** Frees a chunk of memory in global memory previous allocated by malloc */
static int global_free(void *p) {
    struct Node* element = find_element(p);
    if (!element->head) return 0;
    else {
        element->head = false;
        switch_state(element, element->allocated);
        return 1;
    }
}

struct allocator *global_alloc() {
    global_allocator.init = global_init;
    global_allocator.malloc = global_malloc;
    global_allocator.realloc = global_realloc;
    global_allocator.free = global_free;
    return &global_allocator;
}
