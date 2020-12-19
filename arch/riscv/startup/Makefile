#
# Makefile for startup
#

include ../../../def.mk

CFLAGS += -nostdinc -I../../../include -I../include
LDFLAGS = -z max-page-size=4096

OBJECTS = entry.o \
          trampoline.o \
          start.o \
          main.o

kernel: $(OBJECTS) kernel.ld
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel $(OBJECTS)
	$(OBJDUMP) -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
