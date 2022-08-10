#include "config.h"

#include "stdlib/stdio.h"
#include "stdlib/stdstr.h"


void main() {
    stdio_init();
    prints("Hello, world!\n");
    while (1) {
        printc(getc());
    }
}
