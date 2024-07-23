/** Implementation of a generic map */
#ifndef _MAP_H_
#define _MAP_H_

#include "stdlib/stdtypes.h"

struct map {
    /** Table which holds all entries. */
    struct entry *table;
    /** Amount of space used. */
    size_t used;
    /** Maximum space to allocate for entries */
    size_t size;
};

/** Initializes a new hashmap. Returns `-1` if not allocated. */
void map_init(struct map *m);
/** Resizes the hashmap. */
void map_resize(struct map *m, double resize_factor);
/** Frees the hashtable from memory. */
void map_free(struct map *m);

/** Adds the key/value pair to the hashtable. */
void map_put(struct map *m, void *key, void *value, size_t size);
/** Gets the value associated with the specified key. */
void *map_get(struct map *m, void *key, size_t size);
/** Checks if key exists in hashmap. */
bool map_contains(struct map *m, void *key, size_t size);

#endif //_MAP_H_
