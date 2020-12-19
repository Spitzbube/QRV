#
# Common definition for all projects.
#

export ARCH = riscv
export VARIANT = 64
export ARCHVAR = $(ARCH)$(VARIANT)

CC = riscv64-linux-gnu-gcc
CFLAGS = -Wall -D__RISCV__ -D__QNXNTO__ -DVARIANT_smp -D__LITTLEENDIAN__ -fno-builtin \
         -D__INT_BITS__==32 -D__LONG_BITS__==64 -D__PTR_BITS=64 \
         -D_FILE_OFFSET_BITS=64 -D_PADDR_BITS=64
