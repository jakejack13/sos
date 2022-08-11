PROVIDE(__pages_size = 512 * 1024 * 1024);
SECTIONS
{
    . = 0x80000;     /* Kernel load address for AArch64 */
    PROVIDE(__stack_start = .); /* Stack grows down from kernel code */
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
    .pages (NOLOAD) : {
        . = ALIGN(16);
        PROVIDE(__pages_start = .);
        . = __pages_start + __pages_size;
        __pages_end = .;
    }
    _end = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;
