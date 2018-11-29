
GOOGLETEST_HDL_VL_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(GOOGLETEST_HDL_VL_DIR)
GOOGLETEST_HDL_VL_SRC = $(notdir $(wildcard $(GOOGLETEST_HDL_VL_DIR)/*.cpp))

GOOGLETEST_HDL_LIBS := libgoogletest_hdl_vl.o

else # Rules

libgoogletest-hdl-vl.o : $(GOOGLETEST_HDL_VL_SRC:.cpp=.o)
	$(Q)$(LD) -r -o $@ $(GOOGLETEST_HDL_VL_SRC:.cpp=.o)

endif
