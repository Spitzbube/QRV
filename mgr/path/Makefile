#
# Makefile for the nanokernel
#

include ../../def.mk

CFLAGS += -I../../include

ARCHIVE = pathmgr.a
OBJECTS = devnull.o \
          devmem.o \
          pathmgr_init.o \
          pathmgr_link.o \
          pathmgr_object.o \
          pathmgr_node.o \
          pathmgr_resolve.o \
          pathmgr_open.o

all: $(ARCHIVE)($(OBJECTS))

clean:
	rm -f $(ARCHIVE) $(OBJECTS)
