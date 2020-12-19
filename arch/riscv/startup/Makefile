#
# Makefile for startup
#

include ../../../def.mk

CFLAGS += -nostdinc -I../../../include -I../include

OBJECTS = entry.o \
          start.o \
          main.o

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)