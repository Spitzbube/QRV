#
# Makefile for startup
#

include ../../../def.mk

CFLAGS += -nostdinc -I../../../include -I../include
LDFLAGS = -z max-page-size=4096

OBJECTS = entry.o \
          vectors.o \
          trampoline.o \
          spinlock.o \
          plic.o \
          trap.o \
          task.o \
          start.o \
          common_options.o \
          syspage_memory.o \
          _main.o \
          main.o

# Library
OBJECTS += lib/mem.o \
           lib/strtoul.o \
           lib/getopt.o \
           lib/kprintf.o \
           lib/typed_strings.o \
           lib/util.o

# Platform-dependent
OBJECTS += ../platform/qemu_virt/dbg_uart.o

kernel: $(OBJECTS) kernel.ld
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel $(OBJECTS)
	$(OBJDUMP) -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
