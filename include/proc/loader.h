/** The loader of memory segments for processes in the system */

#ifndef _LOADER_H_
#define _LOADER_H_

#include "proc/process.h"

/** Creates a process from the program and loads all necessary memory sections
 * using the given command line arguments
*/
struct process *loader_spawn(struct program *p, int argc, char **argv);

/** Returns the process that has the given pid */
struct process *get_process(pid_t pid);

/** Frees the memory sections back to the kernel and frees the process from memory */
void loader_free(struct process *p);

#endif //_LOADER_H_