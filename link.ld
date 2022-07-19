SECTIONS
{
    . = 0x10; /* Start heap at very top, ignoring NULL pointer */
    . = ALIGN(16);
    PROVIDE(_heap_start = .);
    . = 0x80000;     /* Kernel load address for AArch64 */
    PROVIDE(_stack_start = .); /* Stack grows down from kernel code */
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }
    _end = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;
