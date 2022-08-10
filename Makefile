CFILES = $(wildcard */*/*.c)
SFILES = $(wildcard */*/*.S)
COFILES = $(CFILES:.c=.co)
AOFILES = $(SFILES:.S=.ao)
LLVMPATH = /opt/homebrew/opt/llvm/bin
CLANGFLAGS = --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72+nosimd
CPPFLAGS = -Iinclude
LDFLAGS = -m aarch64elf -nostdlib -T link.ld --strip-all

all: clean kernel8.img

*/*/%.ao: src/*/%.S include/*/*.h
	$(LLVMPATH)/clang $(CLANGFLAGS) $(CPPFLAGS) -c $< -o $@

*/*/%.co: src/*/%.c include/*/*.h
	$(LLVMPATH)/clang $(CLANGFLAGS) $(CPPFLAGS) -c $< -o $@

kernel8.img: $(COFILES) $(AOFILES)
	$(LLVMPATH)/ld.lld $(LDFLAGS) $(COFILES) $(AOFILES) -o kernel8.elf
	$(LLVMPATH)/llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm *.elf */*/*.co */*/*.ao *.img > /dev/null 2> /dev/null || true
