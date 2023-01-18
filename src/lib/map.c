#include "lib/map.h"

size_t fnv_1a(char *ptr, size_t size) {
    size_t hash = 0x811C9DC5;

    for (;size--;) {
        hash ^= ptr[size];
        hash *= 0x01000193;
    }

    return hash;
}

int map_init(struct map *m, size_t size) {
	m->table = calloc(size, sizeof(struct entry));
	m->size = size;

	/** Ensure map was allocated. */
	if (m->table == NULL) return -1;
	else return 0;
}

void map_free(struct map *m) {
	free(m->table);
}

int map_put(struct map *m, void *key, void *value, size_t size) {
	size_t idx = fnv_1a(key, size) % m->size;
	size_t start = idx;

	
	while (m->table[idx].key != NULL) {
		idx = (++idx) % m->size;
		if (idx == start) return -1;
		if (memcmp(key, m->table[idx].key, size) == 0) break;
	}

	m->table[idx].key = key;
	m->table[idx].value = value;
	m->used++;

	return 0;
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
