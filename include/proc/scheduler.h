/** Scheduler for all processes spawned by the operating system and user */

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "proc/process.h"

/** Initializes the scheduler */
void scheduler_init();

/** Spawns a process that is an instance of the given program and returns the pid of the process */
pid_t scheduler_spawn(struct program *p, int argc, char **argv);

/** Waits for the process with the given pid to finish running and returns the exit code of the process */
unsigned int scheduler_wait(pid_t pid);

#endif //_SCHEDULER_H_