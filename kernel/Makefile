#
# Makefile for kernel
#

include ../def.mk

CFLAGS += -I../include

ARCHIVE = kernel.a

TESTING = 1

OBJECTS += init.o \
           kmain.o \
           ker_call_table.o \
           ker_ring0.o \
           ker_channel.o \
           ker_connect.o \
           kexterns.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
