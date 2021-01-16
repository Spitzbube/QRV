#
# Makefile for the nanokernel
#

include ../../def.mk

CFLAGS += -I../../include

ARCHIVE = sysmgr.a
OBJECTS = externs.o \
          main.o \
          message.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
