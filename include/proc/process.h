/** Definitions of processes and programs */

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "stdlib/stdtypes.h"
#include "alloc/heapalloc.h"

typedef unsigned int pid_t;

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
    pid_t pid;
    /** The program that spawned this process */
    struct program *program;
    /** The number of command line arguments into the program */
    int argc;
    /** The command line arguments into the program */
    char **argv;
    /** The start of the stack for this process */
    void *stack_start;
    /** The size of the stack for this process */
    size_t stack_size;
    /** The stack pointer */
    void *sp;
    /** The heap for this process */
    struct heap_state heap;
    /** The pid of the process this process is waiting for, if any*/
    pid_t waiting;
};

/** Initializes the programs available on the system */
void program_init();

/** Searches for and returns the program with the given name */
struct program *program_search(const char *name, size_t length);

/** The hello world program */
extern struct program helloworld_app;

#endif //_PROCESS_H_