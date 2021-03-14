#
# Makefile for the nanokernel
#

include ../../def.mk

CFLAGS += -I../../include

ARCHIVE = sysmgr.a
OBJECTS = externs.o \
          sysmgr_init.o \
          main.o \
          message.o \
          proc_loader.o \
          proc_read.o \
          proc_termer.o \
          bootimage_init.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
