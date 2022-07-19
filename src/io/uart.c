#include "io/uart.h"

#include "io/mmio.h"
#include "io/gpio.h"

enum aux_addresses {
    AUX_BASE        = PERIPHERAL_BASE + 0x215000,
    AUX_ENABLES     = AUX_BASE + 4,
    AUX_MU_IO_REG   = AUX_BASE + 64,
    AUX_MU_IER_REG  = AUX_BASE + 68,
    AUX_MU_IIR_REG  = AUX_BASE + 72,
    AUX_MU_LCR_REG  = AUX_BASE + 76,
    AUX_MU_MCR_REG  = AUX_BASE + 80,
    AUX_MU_LSR_REG  = AUX_BASE + 84,
    AUX_MU_CNTL_REG = AUX_BASE + 96,
    AUX_MU_BAUD_REG = AUX_BASE + 104,
};

enum uart_consts {
    AUX_UART_CLOCK  = 500000000,
    UART_MAX_QUEUE  = 16 * 1024,
};

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

void uart_init() {
    mmio_write(AUX_ENABLES, 1); //enable UART1
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_CNTL_REG, 0);
    mmio_write(AUX_MU_LCR_REG, 3); //8 bits
    mmio_write(AUX_MU_MCR_REG, 0);
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_IIR_REG, 0xC6); //disable interrupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
    gpio_use_as_alt5(14);
    gpio_use_as_alt5(15);
    mmio_write(AUX_MU_CNTL_REG, 3); //enable RX/TX
}

static unsigned int uart_iswritebyteready() { 
    return mmio_read(AUX_MU_LSR_REG) & 0x20; 
}

static unsigned int uart_isreadbyteready() {
    return mmio_read(AUX_MU_LSR_REG) & 0x10;
}

void uart_writebyte(unsigned char c) {
    while (!uart_iswritebyteready()); 
    mmio_write(AUX_MU_IO_REG, (unsigned int)c);
}

void uart_writestring(const char *buffer) {
    while (*buffer) {
       if (*buffer == '\n') uart_writebyte('\r');
       uart_writebyte(*buffer++);
    }
}

char uart_readbyte() {
    while (!uart_isreadbyteready());
    return (char) mmio_read(AUX_MU_IO_REG);
}

unsigned int uart_readstring(char *buffer, unsigned int size) {
    char c;
    for (unsigned int i = 0; i < size; i++) {
        c = uart_readbyte();
        if (c == '\n' || c == '\r') {
            buffer[i] = '\0';
            return i;
        } else buffer[i] = uart_readbyte();
    }
    return size;
}
