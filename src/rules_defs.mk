
GOOGLETEST_UVM_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/../googletest/googletest/include
CXXFLAGS += -I$(GOOGLETEST_UVM_DIR)/../googletest/googletest
CXXFLAGS += -DGTEST_HAS_PTHREAD=0

GOOGLETEST_UVM_OBJ = \
	gtest-all.o \
	googletest_uvm.o
	
GOOGLETEST_OBJ = \
	gtest-all.o 
	
	
SRC_DIRS += $(GOOGLETEST_UVM_DIR)
SRC_DIRS += $(GOOGLETEST_UVM_DIR)/../googletest/googletest/src

DPI_OBJS_LIBS += googletest_uvm_dpi.o

BUILD_COMPILE_TARGETS += print

else

print :
	echo "Hello"

googletest_uvm_dpi.o : $(GOOGLETEST_UVM_OBJ)
	$(LD) -r -o $@ $^
	
googletest.o : $(GOOGLETEST_OBJ)
	$(LD) -r -o $@ $^

endif

