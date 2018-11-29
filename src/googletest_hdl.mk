
GOOGLETEST_HDL_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/../googletest/googletest/include
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/../googletest/googletest
CXXFLAGS += -DGTEST_HAS_PTHREAD=0

SRC_DIRS += $(GOOGLETEST_HDL_SRC_DIR)

GOOGLETEST_HDL_SRC = $(notdir $(wildcard $(GOOGLETEST_HDL_SRC_DIR)/*.cpp))

GOOGLETEST_UVM_OBJ = \
	gtest-all.o \
	googletest_uvm.o
	
GOOGLETEST_OBJ = \
	gtest-all.o 
	
	
SRC_DIRS += $(GOOGLETEST_UVM_DIR)
SRC_DIRS += $(GOOGLETEST_UVM_DIR)/../googletest/googletest/src

else

libgoogletest-hdl.o : $(GOOGLETEST_HDL_SRC:.cpp=.o)
	$(LD) -r -o $@ $^
	
endif

