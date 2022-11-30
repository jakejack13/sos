/** Implementation of a generic list */
#ifndef _LIST_H_
#define _LIST_H_

#include "stdlib/stdtypes.h"

/** Data structure for a generic list */
struct list {
    /** The initial node of the list */
    struct node* next;
};

/** Initializes a new list */
void list_init(struct list *l);

/** Frees the list from memory */
void list_free(struct list *l);

/** Adds the given element to the list */
void list_add(struct list *l, void *elm);

/** Removes the given element from the list */
void list_remove(struct list *l, void *elm);

/** Removes all elements from the list */
void list_clear(struct list *l);

/** Returns true if the element is in the list, false otherwise */
bool list_contains(struct list *l, void *elm);

/** Returns the number of elements in the list */
size_t list_size(struct list *l);

/** Places the first size number of elements of the list into the given array */
void list_to_array(struct list *l, void **buffer, size_t size);

#endif //_LIST_H_