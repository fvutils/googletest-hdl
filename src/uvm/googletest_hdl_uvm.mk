
GOOGLETEST_HDL_UVM_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(GOOGLETEST_HDL_UVM_DIR)

GOOGLETEST_HDL_UVM_SRC = $(notdir $(wildcard $(GOOGLETEST_HDL_UVM_DIR)/*.cpp))


else # Rules

libgoogletest-hdl-uvm.o : $(GOOGLETEST_HDL_UVM_SRC:.cpp=.o)
	$(Q)$(LD) -r -o $@ $(GOOGLETEST_HDL_UVM_SRC:.cpp=.o)

endif
