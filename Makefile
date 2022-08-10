CFILES = $(wildcard */*/*.c)
SFILES = $(wildcard */*/*.S)
COFILES = $(CFILES:.c=.co)
AOFILES = $(SFILES:.S=.ao)
LLVMPATH = /opt/homebrew/opt/llvm/bin
CLANGFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72+nosimd
CPPFLAGS = -Iinclude -I.

all: clean kernel8.img

*/*/%.ao: src/*/%.S
	$(LLVMPATH)/clang --target=aarch64-elf $(CLANGFLAGS) $(CPPFLAGS) -c $< -o $@

*/*/%.co: src/*/%.c
	$(LLVMPATH)/clang --target=aarch64-elf $(CLANGFLAGS) $(CPPFLAGS) -c $< -o $@

kernel8.img: $(COFILES) $(AOFILES)
	$(LLVMPATH)/ld.lld -m aarch64elf -nostdlib $(COFILES) $(AOFILES) -T link.ld -o kernel8.elf
	$(LLVMPATH)/llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm *.elf */*/*.co */*/*.ao *.img > /dev/null 2> /dev/null || true
