#
# Makefile for kernel
#

include ../def.mk

CFLAGS += -nostdinc -I../include -I../include/kernel -I../arch/$(ARCH)/include

ARCHIVE = kernel.a
OBJECTS = _main.o \
          init.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
