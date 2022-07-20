/**
 * Memory Mapped Input/Output
 */

#ifndef _MMIO_H_
#define _MMIO_H_

/** The base of the memory addresses for peripherals */
#define PERIPHERAL_BASE 0xFE000000

/** Writes a value to the MMIO register at the memory address */
void mmio_write(long reg, unsigned int val);
/** Read a value from the MMIO register at the memory address */
unsigned int mmio_read(long reg);

#endif // _MMIO_H_