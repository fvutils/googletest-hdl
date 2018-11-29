
GOOGLETEST_HDL_MKFILES_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
GOOGLETEST_HDL_DIR := $(abspath $(GOOGLETEST_HDL_MKFILES_DIR)/..)

GOOGLETEST_HDL := $(GOOGLETEST_HDL_DIR)
export GOOGLETEST_HDL


ifneq (1,$(RULES))

# GOOGLETEST_MK_INCLUDES += $(GOOGLETEST_HDL_DIR)/src/uvm/googletest_hdl_uvm.mk
GOOGLETEST_MK_INCLUDES += $(GOOGLETEST_HDL_DIR)/src/googletest_hdl.mk

include $(GOOGLETEST_MK_INCLUDES)
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/googletest/googletest/include
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/googletest/googletest
CXXFLAGS += -DGTEST_HAS_PTHREAD=0

GOOGLETEST_UVM_OBJ = \
	gtest-all.o \
	googletest_uvm.o
	
GOOGLETEST_OBJ = \
	gtest-all.o 
	
	
SRC_DIRS += $(GOOGLETEST_UVM_DIR)/src
SRC_DIRS += $(GOOGLETEST_UVM_DIR)/googletest/googletest/src

# DPI_OBJS_LIBS += googletest_uvm_dpi.o

else

googletest_uvm_dpi.o : $(GOOGLETEST_UVM_OBJ)
	$(LD) -r -o $@ $^
	
googletest.o : $(GOOGLETEST_OBJ)
	$(LD) -r -o $@ $^

include $(GOOGLETEST_MK_INCLUDES)

endif

