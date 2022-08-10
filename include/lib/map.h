/** Implementation of a generic map */
#ifndef _MAP_H_
#define _MAP_H_

#include "stdlib/stdtypes.h"

/** Data structure for a generic map */
struct map {
    //TODO
};

/** Initializes a new hashtable */
void map_init(struct map *m);

/** Frees the hashtable from memory */
void map_free(struct map *m);

/** Adds the key/value pair to the hashtable */
void map_put(struct map *m, void *key, void *value);

/** Gets the value associated with the specified key */
void *map_get(struct map *m, void *key);

/** Returns true if the hashtable contains the key, false otherwise */
bool map_contains(struct map *m, void *key);

#endif //_MAP_H_