/** Definitions of processes and programs */

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "stdlib/stdtypes.h"
#include "alloc/heapalloc.h"

/** Definition of a program, which are the text and data sections of an executable */
struct program {
    /** The name of the program */
    const char *name;
    /** The entrypoint into the program */
    int (*main)(int argc, char **argv);
    /** The start of the data section */
    void *data;
    /** The size of the data section */
    size_t data_size;
};

/** Definition of a process, which is an instance of a program with a stack and heap */
struct process {
    /** The ID of the process */
    int pid;
    /** The program that spawned this process */
    struct program *program;
    /** The start of the stack for this process */
    void *stack_start;
    /** The size of the stack for this process */
    size_t stack_size;
    /** The heap for this process */
    struct heap_state heap;
};

/** Initializes the programs available on the system */
void program_init();

/** The hello world program */
extern struct program helloworld_app;

#endif //_PROCESS_H_