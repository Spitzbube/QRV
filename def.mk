#
# Common definition for all projects.
#

export ARCH = riscv
export VARIANT = 64
export ARCHVAR = $(ARCH)$(VARIANT)

CC = riscv64-linux-gnu-gcc
CFLAGS = -Wall -D__RISCV__ -D__QNXNTO__ -DVARIANT_smp -D__LITTLEENDIAN__ -D__PTR_BITS=64
