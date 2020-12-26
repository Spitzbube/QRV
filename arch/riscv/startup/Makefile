#
# Makefile for startup
#

include ../../../def.mk

CFLAGS += -g -nostdinc -I../include -I../../../include
LDFLAGS = -z max-page-size=4096

OBJECTS = head.o \
          _main.o \
          board.o \
          boot_args.o \
          vectors.o \
          trampoline.o \
          spinlock.o \
          plic.o \
          trap.o \
          task.o \
          common_options.o \
          syspage_memory.o \
          cpu_syspage_memory.o \
          private.o \
          print_syspage.o \
          hwi.o \
          ram.o \
          addr_space.o \
          smp.o \
          mmu.o \
          debug.o \
          main.o

# xv6 objects
#OBJECTS += start.o $(PLAT)/dbg_uart.o

# Library
OBJECTS += lib/mem.o \
           lib/strtoul.o \
           lib/getopt.o \
           lib/kprintf.o \
           lib/typed_strings.o \
           lib/util.o

# Platform-dependent
PLAT = ../platform/qemu_virt
OBJECTS +=  $(PLAT)/mem.o

kernel: $(OBJECTS) qrv_kernel.ld
	$(LD) $(LDFLAGS) -T qrv_kernel.ld -o kernel $(OBJECTS)
	$(OBJDUMP) -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS) kernel kernel.asm kernel.sym
