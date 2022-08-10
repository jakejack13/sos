#include "stdlib/stdstr.h"

void memcpy(void *dest, const void *src, size_t n) {
    char *cdest = (char *) dest;
    char *csrc = (char *) src;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

void memset(void *str, char c, size_t n) {
    char *cstr = (char *) str;
    for (size_t i = 0; i < n; i++) {
        cstr[i] = c;
    }
}

size_t strlen(const char *s) {
    size_t length = 0;
    while (*s != 0) {
        length++;
        s++;
    }
    return length;
}
