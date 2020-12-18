#! /bin/sh

# Settings
CPUS=4

QEMU=qemu-system-riscv64

QEMUOPTS="-machine virt -bios none -kernel qrv32.elf -m 128M -smp $(CPUS) -nographic
          -drive file=fs.img,if=none,format=raw,id=x0
          -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0"

$QEMU $QEMUOPTS
