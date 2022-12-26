/** Implementation of a generic map */
#ifndef _MAP_H_
#define _MAP_H_

#include "stdlib/stdtypes.h"

/** Structures for a generic map. */
struct entry {
    void *key;
    void *value;
};

struct map {
    struct entry *table;
    size_t used;
    size_t size;
};

/** Initializes a new hashmap. Returns `-1` if not allocated. */
int map_init(struct map *m, size_t size);

/** Frees the hashtable from memory. */
void map_free(struct map *m);

/** Adds the key/value pair to the hashtable. */
int map_put(struct map *m, void *key, void *value, size_t size);

/** Gets the value associated with the specified key. */
void *map_get(struct map *m, void *key, size_t size);

/** Checks if key exists in hashmap. */
bool map_contains(struct map *m, void *key, size_t size);

/** Hash function for strings. */
size_t fnv_1a(char *str);

#endif //_MAP_H_