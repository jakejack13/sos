/** Scheduler for all processes spawned by the operating system and user */

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "proc/process.h"

/** Spawns a process that is an instance of the given program and returns the pid of the process */
unsigned int scheduler_spawn(struct program *p);

/** Waits for the process with the given pid to finish running and returns the exit code of the process */
int scheduler_wait(unsigned int pid);

#endif //_SCHEDULER_H_