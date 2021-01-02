#
# Makefile for kernel
#

include ../def.mk

CFLAGS += -I../include

ARCHIVE = kernel.a
OBJECTS = _main.o \
          init.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
