#****************************************************************************
#* ivpm.mk
#****************************************************************************
SCRIPTS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(SCRIPTS_DIR)/..)

include $(PACKAGES_DIR)/packages.mk
include $(ROOT_DIR)/etc/ivpm.info

PROJECT := $(name)

RULES := 1

ifeq (true,$(PHASE2))
build : $(BUILD_DEPS)
else
build : $($(PROJECT)_deps)
	$(Q)echo PROJECT=$(PROJECT) DEPS=$($(PROJECT)_deps) PROJECT_DEPS=$(PROJECT)_deps
	$(Q)$(MAKE) -f $(SCRIPTS_DIR)/ivpm.mk PHASE2=true VERBOSE=$(VERBOSE) build
endif

clean :

release :

include $(PACKAGES_DIR)/packages.mk

