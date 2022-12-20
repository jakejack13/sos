#include "config.h"

#include "stdlib/stdio.h"
#include "stdlib/stdstr.h"
#include "io/framebuffer.h"
#include "proc/scheduler.h"
#include "stdlib/stdalloc.h"
#include "proc/shell.h"

/** Initializes all necessary modules */
void init() {
    stdalloc_init();
    program_init();
    stdio_init();
    scheduler_init();
}

int main() {
    init();
#if SHELL
    shell_main();
#elif HELLO_WORLD
    fb_init();
    fb_paint_screen(BLACK);
    fb_draw_string(100,100,"Hello, world!", default_font);
#else
    prints("Hello, world!\n");
    while (1) {
        printc(getc());
    }
#endif
}
