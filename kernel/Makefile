#
# Makefile for kernel
#

include ../def.mk

CC = riscv64-linux-gnu-gcc
CFLAGS = -Wall -DVARIANT_smp

OBJECTS = _main.o \
          init.o

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
