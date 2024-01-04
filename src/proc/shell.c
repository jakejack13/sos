#include "proc/shell.h"

#include "stdlib/stdtypes.h"
#include "stdlib/stdio.h"
#include "proc/process.h"
#include "proc/scheduler.h"

/** Runs the program with the arguments as specified in the given string and returns the exit code of the process */
static int shell_run(const char *str, size_t length) {
    return -1;
}

void shell_main() {
    prints("Loading programs\n");
    pid_t pid = scheduler_spawn(&helloworld_app, 0, NULL);
    scheduler_wait(pid);
    prints("Done\n");
}
