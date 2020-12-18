#
# Makefile for kernel
#

include ../def.mk

CFLAGS += -nostdinc -I../include -I../include/kernel -I../arch/$(ARCH)/include

OBJECTS = _main.o \
          init.o

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
