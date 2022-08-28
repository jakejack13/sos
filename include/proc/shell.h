/** A simple shell that allows user to run apps with arguments */

#ifndef _SHELL_H_
#define _SHELL_H_

#include "stdlib/stdtypes.h"

/** Runs the program with the arguments as specified in the given string and returns the exit code of the process */
int shell_run(const char *str, size_t length);

/** The main loop for the shell */
void shell_main();

#endif //_SHELL_H_