#include "lib/map.h"

int map_init(struct map* m, uint64_t size) {
	m->table = calloc(size, sizeof(struct map));
	m->size = size;

	/** Ensure map was allocated. */
	if (m->table == NULL) return -1;
	else return 0;
}

void map_free(struct map* m) {
	free(m->table);
}

void map_put(struct map* m, void* key, void* value) {
	uint64_t idx = fnv_1a(key) % m->size;
	m->table[idx].key = key;
	m->table[idx].value = value;
	m->used++;
}

void* map_get(struct map* m, void* key) {
	return m->table[fnv_1a(key) % m->size].value;
}