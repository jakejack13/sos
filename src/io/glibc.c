#include "io/io.h"

#ifdef USER
#include <stdio.h>

static struct iostream glibc_io;

static void glibc_init() {
    
}

static char glibc_getc() {
    return getchar();
}

static void glibc_gets(char *buffer, size_t length) {
    fgets(buffer, (int) length, stdin);
}

static void glibc_printc(char c) {
    printf("%c", c);
}

static void glibc_prints(const char *s) {
    printf("%s", s);
}

struct iostream *glibc_iostream() {
    glibc_io.init = glibc_init;
    glibc_io.getc = glibc_getc;
    glibc_io.gets = glibc_gets;
    glibc_io.printc = glibc_printc;
    glibc_io.prints = glibc_prints;
    return &glibc_io;
}

#endif