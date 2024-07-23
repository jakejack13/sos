#include "lib/map.h"
#include "stdlib/stdhash.h"
#include "stdlib/stdalloc.h"

/** Structures for a generic map. */
struct entry {
    /** The key associated with the entry. */
    void *key;
    /** The value associated with the entry. */
    void *value;
};

void map_init(struct map *m) {
	/** Default 1MB of data. */
	size_t size = 1024 * 1024;

	m->table = calloc(size, sizeof(struct entry));
	m->used = 0;
	m->size = size;
}

void map_resize(struct map *m, double resize_factor) {
	m->size *= resize_factor;
	m->table = realloc(m->table, m->size * sizeof(struct entry));
}

void map_free(struct map *m) {
	free(m->table);
}

void map_put(struct map *m, void *key, void *value, size_t size) {
	if (m->used * 2 >= m->size) {
		map_resize(m, 2);
	}

	size_t idx = fnv_1a(key, size) % m->size;
	size_t start = idx;
	
	while (m->table[idx].key != NULL) {
		idx = (++idx) % m->size;
		if (memcmp(key, m->table[idx].key, size) == 0) break;
	}

	m->table[idx].key = key;
	m->table[idx].value = value;
	m->used++;
}

void *map_get(struct map *m, void *key, size_t size) {
	size_t idx = fnv_1a(key, size) % m->size;

	if (m->table[idx].key == NULL) return NULL;
	while (m->table[idx].key != NULL) {
		if (memcmp(key, m->table[idx].key, size) == 0) return m->table[idx].value;
		idx = (++idx) % m->size;
	}

	return NULL;
}

bool map_contains(struct map *m, void *k, size_t size) {
	return map_get(m, k, size) != NULL;
}
