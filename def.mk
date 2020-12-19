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
CFLAGS += -mcmodel=medany -mno-relax
CFLAGS += -ffreestanding -fno-common -nostdlib
CFLAGS += -fno-pie -no-pie -fno-builtin
