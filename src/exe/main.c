#include "config.h"

#include "stdlib/stdio.h"
#include "stdlib/stdstr.h"
#include "io/framebuffer.h"


void main() {
    #if HELLO_WORLD
    fb_init();
    fb_draw_string(100,100,"Hello, world!", default_font);
    #else
    stdio_init();
    prints("Hello, world!\n");
    while (1) {
        printc(getc());
    }
    #endif
}
