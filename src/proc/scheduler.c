#include "proc/scheduler.h"
#include "proc/context.h"

#include "lib/queue.h"
#include "proc/loader.h"
#include "stdlib/stdalloc.h"
#include "alloc/heapalloc.h"
#include "stdlib/stdstr.h"

/** The kernel process */
static struct process kernel_proc;
/** The FIFO queue of runnable processes */
static struct queue runnable;
/** The set of processes currently waiting on another process to finish */
static struct queue waiting;
/** The set of processes that have already terminated */
static struct queue terminated;
/** The process that is currently running */
static struct process *current;

void scheduler_init() {
    queue_init(&runnable);
    queue_init(&waiting);
    queue_init(&terminated);
    kernel_proc.pid = 0;
    memset(&kernel_proc.heap, 0, sizeof(struct heap_state));
    heap_init(&kernel_proc.heap);
    current_heap = &kernel_proc.heap;
    current = &kernel_proc;
}

/** Cleans up memory of the terminated processes */
static void clean_terminated() {
    while (!queue_empty(&terminated)) {
        struct process *proc = queue_dequeue(&terminated);
        loader_free(proc);
    }
}

/** Ends a process and generates an exit code */
static void process_exit(int code) {
    queue_enqueue(&terminated, current);
    size_t num_waiting = queue_size(&waiting);
    for (int i = 0; i < num_waiting; i++) {
        struct process *proc = queue_dequeue(&waiting);
        if (proc->waiting == current->pid) {
            proc->waiting = code;
            queue_enqueue(&runnable, proc);
        } else {
            queue_enqueue(&waiting, proc);
        }
    }
    struct process *previous = current;
    struct process *next = queue_dequeue(&runnable);
    current = next;
    current_heap = &current->heap;
    ctx_switch(&previous->sp, next->sp);
}

void ctx_entry() {
    clean_terminated();
    int code = (current->program->main)(current->argc, current->argv);
    process_exit(code);
}

pid_t scheduler_spawn(struct program *p, int argv, char **argc) {
    struct process *proc = loader_spawn(p, argv, argc);
    queue_enqueue(&runnable, current);
    current = proc;
    current_heap = &current->heap;
    ctx_start(&current->sp,proc->sp);
    return proc->pid;
}

unsigned int scheduler_wait(pid_t pid) {
    struct process *temp = current;
    struct process *next = queue_dequeue(&runnable);
    if (next == NULL) return -1;
    current->waiting = pid;
    queue_enqueue(&waiting, current);
    current = next;
    current_heap = &current->heap;
    ctx_switch(&temp->sp,current->sp);
    unsigned int result = current->waiting;
    current->waiting = 0;
    return result;
}
