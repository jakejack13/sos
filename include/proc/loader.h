#ifndef _LOADER_H_
#define _LOADER_H_

#include "proc/process.h"

/** Creates a process from the program and loads all necessary memory sections */
struct process *loader_spawn(struct program *p);

/** Frees the memory sections back to the kernel and frees the process from memory */
void loader_free(struct process *p);

#endif