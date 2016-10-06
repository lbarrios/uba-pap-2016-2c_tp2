# Default vars
UNAME:=$(shell uname)

ifeq ($(UNAME),FreeBSD)
        MAKE=gmake
endif

ifeq ($(UNAME),Linux)
        MAKE=make
endif

ifeq ($(EXE),)
        EXE=$(notdir $(shell pwd))
endif

.PHONY: all clean tests
all: $(EXE)

$(EXE): | $(EXE).py
	ln -s $(EXE).py $(EXE)
	$(MAKE) tests

clean:
	rm -f $(EXE)

tests: $(EXE)
	@./run_tests.sh
