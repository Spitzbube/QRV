#! /bin/bash

# Number of CPUs to emulate
CPUS=4
# Set this to 'none' to run without BIOS
BIOS=bios/fw.bin

QEMU=qemu-system-riscv64

QEMUOPTS="-machine virt -bios $BIOS -kernel arch/riscv/startup/kernel -m 256M -smp $CPUS -nographic
          -drive file=fs.img,if=none,format=raw,id=x0
          -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0"

# Add the following to enable remote gdb ("target extended-remote :1234")
#QEMUOPTS+=" -s -S"

touch fs.img
$QEMU $QEMUOPTS
