# Default vars
UNAME:=$(shell uname)
ifeq ($(UNAME),FreeBSD)
	CC=g++6
	MAKE=gmake
endif
ifeq ($(MAKE),)
	MAKE=make
endif

all: ej1 ej2 ej3 ej4
tests: tests-ej1 tests-ej2 tests-ej3 tests-ej4
clean: clean-ej1 clean-ej2 clean-ej3 clean-ej4

ej1:
	@$(MAKE) -C ej1
ej2:
	@$(MAKE) -C ej2
ej3:
	@$(MAKE) -C ej3
ej4:
	@$(MAKE) -C ej4

clean-ej1:
	@$(MAKE) -C ej1 clean
clean-ej2:
	@$(MAKE) -C ej2 clean
clean-ej3:
	@$(MAKE) -C ej3 clean
clean-ej4:
	@$(MAKE) -C ej4 clean

tests-ej1:
	@$(MAKE) -C ej1 tests
tests-ej2:
	@$(MAKE) -C ej2 tests
tests-ej3:
	@$(MAKE) -C ej3 tests
tests-ej4:
	@$(MAKE) -C ej4 tests

.PHONY: ej1 ej2 ej3 ej4 all clean clean-ej1 clean-ej2 clean-ej3 clean-ej4 tests tests-ej1 tests-ej2 tests-ej3 tests-ej4
