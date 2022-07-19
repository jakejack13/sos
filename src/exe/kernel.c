#include "stdlib/stdio.h"
#include "stdlib/stdstr.h"

#define BUFFER_SIZE 16 * 1024

void main() {
    char buffer[BUFFER_SIZE];
    stdio_init();
    prints("Hello, world!\n");
    while (1) {
        memset(buffer, (char) 0, BUFFER_SIZE);
        gets(buffer, BUFFER_SIZE);
        prints(buffer);
    }
}
