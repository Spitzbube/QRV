#
# Common definition for all projects.
#

export ARCH = riscv
export VARIANT = 64
export ARCHVAR = $(ARCH)$(VARIANT)

# Tools
TOOLPREFIX = riscv64-linux-gnu-
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump

# Flags
CFLAGS = -Wall -D__RISCV__ -D__QNXNTO__ -DVARIANT_smp -D__LITTLEENDIAN__ \
         -D_FILE_OFFSET_BITS=64 -D_PADDR_BITS=64
CFLAGS += -MD -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -fno-pie -no-pie -fno-builtin
