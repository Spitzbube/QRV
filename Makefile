#
# Top-level Makefile
#

RAMDISK := ramdisk.cpio

.PHONY: all ramdisk clean

all: kernel startup ramdisk

startup:
	make -C arch/riscv/startup

kernel:
	make -C kernel

clean:
	make -C arch/riscv/startup clean
	make -C kernel clean
	rm -rf ramdisk $(RAMDISK)

qemu: arch/riscv/startup/kernel
	./emu.sh

ramdisk: $(RAMDISK)

$(RAMDISK):
	@echo "Creating RAM-disk hierarchy..."
	@mkdir -p ramdisk
	@(cd ramdisk && mkdir -p boot bin sbin etc tmp root)
	echo "Copying binaries..."
	@cp -v largefile ramdisk/boot/
	@echo "Creating CPIO archive $(RAMDISK)..."
	@(cd ramdisk && find . | cpio -H newc -o > ../$(RAMDISK))
