/** Functions used for switching context processes, most notably stack switches
 * Special thanks to Yunhao Zhang, Cornell University for the code
*/

#ifndef _CONTEXT_H_
#define _CONTEXT_H_

/** Saves the registers of the current process on its
 * stack and then the stack pointer in *old_sp.  It then sets the stack
 * pointer to new_sp and restores the registers previously saved. */
extern void ctx_switch(void **old_sp, void *new_sp);

/** Saves the registers of the current process on its
 * stack and then the stack pointer in *old_sp.  It then sets the stack
 * pointer to new_sp and calls ctx_entry */
extern void ctx_start(void **old_sp, void *new_sp);

/** Begins running a new process */
void ctx_entry();

#endif //_CONTEXT_H_