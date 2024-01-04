#include "proc/loader.h"

#include "alloc/pagealloc.h"
#include "alloc/heapalloc.h"
#include "stdlib/stdstr.h"

/** The maximum number of processes that can run on the system */
#define MAX_PROCS 1024

/** The unique processes that are running on the system */
static struct process processes[MAX_PROCS];
/** The current number of running processes */
static unsigned int curr_num_proc = 0;

/** Returns the index of an empty process or -1 if not found */
static int find_empty_proc() {
    if (curr_num_proc == MAX_PROCS) return -1;
    for (int i = 1; i < MAX_PROCS; i++) {
        if (processes[i].pid == 0) return i;
    }
    return -1;
}

struct process *loader_spawn(struct program *p, int argc, char **argv) {
    int pid = find_empty_proc();
    if (pid == -1) return NULL;

    struct process *proc = &processes[pid];
    proc->pid = pid;
    proc->program = p;
    proc->stack_start = page_alloc() + PAGE_SIZE;
    proc->stack_size = PAGE_SIZE;
    proc->sp = proc->stack_start;
    proc->argc = argc;
    proc->argv = argv;
    memset(&proc->heap, 0, sizeof(struct heap_state));
    heap_init(&proc->heap);
    curr_num_proc++;

    return proc;
}

struct process *get_process(pid_t pid) {
    struct process *proc = &processes[pid];
    if (proc->pid == 0) return NULL;
    return proc;
}

void loader_free(struct process *p) {
    heap_done(&p->heap);
    page_free(p->stack_start - PAGE_SIZE);
    p->pid = 0;
    curr_num_proc--;
}