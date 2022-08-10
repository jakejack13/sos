#ifndef _MMIO_H_
#define _MMIO_H_

#define PERIPHERAL_BASE 0xFE000000

void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

#endif // _MMIO_H_