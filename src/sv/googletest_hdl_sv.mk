
GOOGLETEST_HDL_SV_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(GOOGLETEST_HDL_SV_DIR)

GOOGLETEST_HDL_SV_SRC = $(notdir $(wildcard $(GOOGLETEST_HDL_SV_DIR)/*.cpp))


else # Rules

libgoogletest-hdl-sv.o : $(GOOGLETEST_HDL_SV_SRC:.cpp=.o)
	$(Q)$(LD) -r -o $@ $(GOOGLETEST_HDL_SV_SRC:.cpp=.o)

endif
