/** Implementation of a generic hashtable */
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "stdlib/stdtypes.h"

/** Data structure for a generic hashtable */
struct hashtable {
    //TODO
};

/** Initializes a new hashtable */
void hashtable_init(struct hashtable *h);

/** Frees the hashtable from memory */
void hashtable_free(struct hashtable *h);

/** Adds the key/value pair to the hashtable */
void hashtable_put(struct hashtable *h, void *key, void *value);

/** Gets the value associated with the specified key */
void *hashtable_get(struct hashtable *h, void *key);

/** Returns true if the hashtable contains the key, false otherwise */
bool hashtable_contains(struct hashtable *h, void *key);

#endif //_HASHTABLE_H_