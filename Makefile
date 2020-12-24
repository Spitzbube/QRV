all:
	make -C arch/riscv/startup

clean:
	make -C arch/riscv/startup clean
	make -C kernel clean

qemu: arch/riscv/startup/kernel
	./emu.sh
