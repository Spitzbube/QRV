#
# QRV userland makefile configuration.
#

ifndef QRV_PROJ_ROOT
$(error QRV_PROJ_ROOT is not defined
endif

MKFILES_ROOT := $(QRV_PROJ_ROOT)/build

BUILDENV := gcc

SH_HOST := /bin/sh
CP_HOST := cp
LN_HOST := ln -sf
RM_HOST := rm -f
TOUCH_HOST := touch
PWD_HOST = pwd

PWD := $(shell $(PWD_HOST))

ECHO_HOST := echo
DATE_HOST := /bin/date +%Y/%m/%d-%T-%Z
USER_HOST := $(firstword $(filter /%, $(shell which -a id))) -un
HOST_HOST := /bin/hostname

# Extras
BISON_HOST := bison
FLEX_HOST  := flex

#
# CL_*  Compile and link
# CC_*  Compile C/C++ source to an object file
# AS_*  Assemble something to an object file
# AR_*  Generate an object file library (archive)
# LR_*  Link a list of objects/libraries to a relocatable object file
# LD_*  Link a list of objects/libraries to a executable/shared object
# UM_*  Add a usage message to an executable
#

#
# Host system
#
CL_HOST = gcc
CC_HOST = gcc -c
AS_HOST = gcc -c
AR_HOST = ar -r
LD_HOST = gcc

dash:=-
comma:=,
gcc_ver_suffix=$(if $(GCC_VERSION),$(dash)$(GCC_VERSION))
gcc_ver_string=$(if $(GCC_VERSION),$(GCC_VERSION)$(comma))

#
# RISC-V target
#
CROSS := riscv64-linux-gnu-
CC := $(CROSS)gcc
AS := $(CROSS)gcc
AR := $(CROSS)ar
LR := $(CROSS)gcc
LD := $(CROSS)gcc
#UM_qrv_riscv_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC := $(CROSS)objcopy

CCOPTS := -nostdinc -fno-builtin -nostdlib -DQRV
# TODO: remove when the porting is finished
CCOPTS += -D__QNX__ -D__QNXNTO__

LDOPTS = -nostdlib

ifndef QCONF_OVERRIDE

CWD := $(shell $(PWD_HOST))
roots:=$(filter $(ROOT_DIR) cvs src qssl, $(subst /, ,$(CWD)))
ifneq ($(roots),)
root:=$(word $(words $(roots)), $(roots))
src_root := $(patsubst %/,%,$(subst !,/,$(dir $(subst !$(root)!,!$(root)/, $(subst /,!, $(CWD))))))
QCONF_OVERRIDE=$(src_root)/qconf-override.mk
endif
endif

ifneq ($(QCONF_OVERRIDE),)
-include $(QCONF_OVERRIDE)
endif
