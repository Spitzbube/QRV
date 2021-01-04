#
# Makefile for kernel
#

include ../def.mk

CFLAGS += -I../include

ARCHIVE = kernel.a

TESTING = 1

ifdef TESTING
OBJECTS += ktest.o \
           miniproc_start.o
else
# Add objects here
OBJECTS += init.o
endif

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
