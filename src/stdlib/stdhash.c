#include <stdlib/stdtypes.h>

size_t fnv_1a(char *ptr, size_t size) {
    size_t hash = 0x811C9DC5;

    for (;size--;) {
        hash ^= ptr[size];
        hash *= 0x01000193;
    }

    return hash;
}