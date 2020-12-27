#
# Makefile rules
#

ifndef VARIANT_TAG
include $(MKFILES_ROOT)/qmacros.mk
endif

_native_path=$(1)
_vpath_normalize=$(1)

vpath %.h   $(call _vpath_normalize,$(INCVPATH))
ifeq ($(filter a,$(VARIANTS)),)
vpath %.lib $(call _vpath_normalize,$(LIBVPATH))
vpath %.a   $(call _vpath_normalize,$(LIBVPATH))
vpath %.so  $(call _vpath_normalize,$(LIBVPATH))
endif

ifeq ($(filter -g, $(CCFLAGS) $(FLAGS) $(CCVFLAGS)),)
ifeq ($(origin NDEBUG),undefined)
NDEBUG = -DNDEBUG
endif
endif
CCFLAGS += $(NDEBUG)

vpath %.S $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

# Rule to assemble an object
%.o: %.S $(EXTRA_ASDEPS)
	$(COMPILE_S_o)

# Rule to get pre-processed output from an assembly file
%.i: %.S
	$(COMPILE_S_i)

vpath %.c $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

# Rule to compile a C file
%.o: %.c $(EXTRA_CCDEPS)
	$(COMPILE_c_o)

# Rule to get pre-processed output from a C file
%.i: %.c
	$(COMPILE_c_i)

ifdef DEFFILE
$(DEFFILE): %.def: %.c
	$(COMPILE_c_o)
	$(MKASMOFF_HOST) $(if $(ASMOFF_FORMAT_$(CPU)),-f $(ASMOFF_FORMAT_$(CPU))) $(basename $(<F)).o $@
	$(RM_HOST) $(basename $(<F)).o
endif
