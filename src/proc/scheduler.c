#include "proc/scheduler.h"

#include "lib/queue.h"
#include "proc/loader.h"
#include "stdlib/stdalloc.h"

/** The kernel process */
static struct process kernel;
/** The FIFO queue of runnable processes */
static struct queue runnable;
/** The set of processes currently waiting on another process to finish */
static struct queue waiting;
/** The process that is currently running */
static struct process *current;

void scheduler_init() {
    queue_init(&runnable);
    queue_init(&current);
    stdalloc_init();
    program_init();
    kernel.pid = 0;
    kernel.heap = current_heap;
    current = &kernel;
}

pid_t scheduler_spawn(struct program *p) {
    struct process *proc = loader_spawn(p);
    queue_enqueue(&runnable, current);
    current = proc;
    ctx_switch();
    return proc->pid;
}

unsigned int scheduler_wait(pid_t pid) {
    struct process *next = queue_dequeue(&runnable);
    if (next == NULL) return -1;
    current->waiting = pid;
    queue_enqueue(&waiting, current);
    current = next;
    ctx_switch();
    unsigned int result = current->waiting;
    current->waiting = 0;
    return result;
}
