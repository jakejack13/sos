#include "lib/map.h"

uint64_t fnv_1a(char *str) {
    size_t len = strlen(str);
    uint64_t hash = 0xCBF29CE484222325;

    for (size_t i = len; i--;) {
        hash ^= str[i];
        hash *= 0x00000100000001B3;
    }

    return hash;
}

int map_init(struct map *m, uint64_t size) {
	m->table = calloc(size, sizeof(struct map));
	m->size = size;

	/** Ensure map was allocated. */
	if (m->table == NULL) return -1;
	else return 0;
}

void map_free(struct map *m) {
	free(m->table);
}

int map_put(struct map *m, void *k, void *value, uint64_t size) {
	char *key = k;
	uint64_t idx = fnv_1a(key) % m->size;

	if (m->table[idx].key != NULL) {
		if (m->used == m->size) return -1;

		while (1) {
			idx = (idx + 1) % m->size;
			if (m->table[idx].key == NULL || memcmp(key, m->table[idx].key, size) == 0) break;
		}
	}

	m->table[idx].key = key;
	m->table[idx].value = value;
	m->used++;

	return 0;
}

void *map_get(struct map *m, void *k, uint64_t size) {
	char *key = k;
	uint64_t idx = fnv_1a(key) % m->size;

	if (m->table[idx].key == NULL) return NULL;
	while (1) {
		if (m->table[idx].key == NULL) return NULL;
		if (memcmp(key, m->table[idx].key, size) == 0) return m->table[idx].value;
		idx = (idx + 1) % m->size;
	}
}

bool map_contains(struct map *m, void *k, uint64_t size) {
	return map_get(m, k, size) != NULL;
}