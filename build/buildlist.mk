#
# If the [EXCLUDE_]OSLIST or [EXCLUDE_]CPULIST macros aren't set, figure out
# what target systems we can actually build based on the name of the
# host system.
#
# Used by the recurse.mk makefile.
#

# cd to "/" first so we don't get caught when building our uname utility.
ifndef HOST_SYSTEM
ifdef SYSNAME
HOST_SYSTEM   := $(SYSNAME)
else
HOST_SYSTEM   := $(uname -s)
HOST_REVISION := $(uname -r)
endif
endif

DEFCPULIST := riscv
DEFOSLIST  := linux

ifeq ($(CPULIST)$(EXCLUDE_CPULIST),)
CPULIST=$(DEFCPULIST)
EXCLUDE_CPULIST=$(DEFEXCLUDE_CPULIST)
endif

ifeq ($(OSLIST)$(EXCLUDE_OSLIST),)
OSLIST=$(DEFOSLIST)
EXCLUDE_OSLIST=$(DEFEXCLUDE_OSLIST)
endif
