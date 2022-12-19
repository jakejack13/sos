#ifdef USER
    .global _ctx_start, _ctx_switch
#else
    .section .text
    .global ctx_start, ctx_switch
#endif

#ifdef USER
_ctx_start:
#else
ctx_start:
#endif
#if defined(__x86_64__)
    /* old_sp = x0, new_sp = x1 */

    addi sp,sp,-64
    sw s0,4(sp)       /* Save callee-saved registers */
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    sw s5,24(sp)
    sw s6,28(sp)
    sw s7,32(sp)
    sw s8,36(sp)
    sw s9,40(sp)
    sw s10,44(sp)
    sw s11,48(sp)
    sw ra,52(sp)      /* Save return address */
    sw sp,0(a0)       /* Save the current stack pointer */
    mv sp,a1          /* Switch the stack */
    call ctx_entry    /* Call ctx_entry() */
#elif defined(__aarch64__)
    /* old_sp = x0, new_sp = x1 */

    /* Save the current context */
    mrs x0, sp_el0       // x1 = current stack pointer
    stp x29, x30, [x0]    // save x29 and x30 (frame pointer and link register)
    stp x19, x20, [x0, #16] // save x19 and x20
    stp x21, x22, [x0, #32] // save x21 and x22
    stp x23, x24, [x0, #48] // save x23 and x24
    stp x25, x26, [x0, #64] // save x25 and x26
    stp x27, x28, [x0, #80] // save x27 and x28
    
    #ifdef USER
    bl _ctx_entry
    #else
    bl ctx_entry
    #endif
#else
    #error Unsupported architecture
#endif

#ifdef USER
_ctx_switch:
#else
ctx_switch:
#endif
#if defined(__x86_64__)
    /* old_sp = a0, new_sp = a1 */
    
    addi sp,sp,-64
    sw s0,4(sp)       /* Save callee-saved registers */
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    sw s5,24(sp)
    sw s6,28(sp)
    sw s7,32(sp)
    sw s8,36(sp)
    sw s9,40(sp)
    sw s10,44(sp)
    sw s11,48(sp)
    sw ra,52(sp)      /* Save return address */
    sw sp,0(a0)       /* Save the current stack pointer */
    mv sp,a1          /* Switch the stack */
    lw s0,4(sp)       /* Restore callee-saved registers */
    lw s1,8(sp)
    lw s2,12(sp)
    lw s3,16(sp)
    lw s4,20(sp)
    lw s5,24(sp)
    lw s6,28(sp)
    lw s7,32(sp)
    lw s8,36(sp)
    lw s9,40(sp)
    lw s10,44(sp)
    lw s11,48(sp)
    lw ra,52(sp)      /* Restore return address */
    addi sp,sp,64
    ret
#elif defined(__aarch64__)
    /* old_sp = x0, new_sp = x1 */

    /* Save the current context */
    mrs x0, sp_el0       // x0 = current stack pointer
    stp x29, x30, [x0]    // save x29 and x30 (frame pointer and link register)
    stp x19, x20, [x0, #16] // save x19 and x20
    stp x21, x22, [x0, #32] // save x21 and x22
    stp x23, x24, [x0, #48] // save x23 and x24
    stp x25, x26, [x0, #64] // save x25 and x26
    stp x27, x28, [x0, #80] // save x27 and x28

    /* Switch to the new context */
    ldp x19, x20, [x1, #16] // save x19 and x20
    ldp x21, x22, [x1, #32] // save x21 and x22
    ldp x23, x24, [x1, #48] // save x23 and x24
    ldp x25, x26, [x1, #64] // save x25 and x26
    ldp x27, x28, [x1, #80] // save x27 and x28
    msr sp_el0, x1       // switch to the new stack
    ldp x29, x30, [x1]    // load x29 and x30 (frame pointer and link register)

    /* Resume execution at the saved return address */
    ret
#else
    #error Unsupported architecture
#endif