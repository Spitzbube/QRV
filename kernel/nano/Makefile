#
# Makefile for the nanokernel
#

include ../../def.mk

CFLAGS += -I../../include -I..

ARCHIVE = nanokernel.a
OBJECTS = nano_alloc.o \
          nano_connect.o \
          nano_conf.o \
          nano_message.o \
          nano_clock.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
