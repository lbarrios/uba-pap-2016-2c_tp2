# Default vars
UNAME:=$(shell uname)

ifeq ($(UNAME),FreeBSD)
	CXX=g++48
	MAKE=gmake
endif

ifeq ($(UNAME),Linux)
	ifeq ($(CXX),)
		CXX=g++
	endif
	MAKE=make
endif

ifeq ($(MAKE),)
	MAKE=make
endif

ifeq ($(CXX),)
	CXX=g++
endif

C11_FLAG=c++11
C14_FLAG=c++14

ifeq ($(CXX),g++-4.6)
	C11_FLAG=c++0x
	C14_FLAG=c++0x
endif

ifeq ($(CXX),g++-4.7)
	C11_FLAG=c++0x
	C14_FLAG=c++0x
endif

ifeq ($(CXX),g++-4.8)
	C11_FLAG=c++0x
	C14_FLAG=c++0x
endif
ifeq ($(CXX),g++48)
	C11_FLAG=c++0x
	C14_FLAG=c++0x
endif

#CXX=g++ # setear CXX manualmente con "setenv CXX ..."
#-Wall: All Warnings
#-pedantic: pedantic warnings
#-std=...: set C standard to:...
#-O0: without optimizations
#-g: for debugging
CFLAGS=-Wall -pedantic -std=$(C14_FLAG) -O0

ifeq ($(EXE),)
	EXE=$(notdir $(shell pwd))
endif

# Default targets
.PHONY: all clean tests
all: $(EXE)

$(EXE): $(EXE).cpp
	$(CXX) $(CFLAGS) -o $(EXE) $(EXE).cpp
	$(MAKE) tests

clean:
	rm -f $(EXE)

tests: $(EXE)
	@./run_tests.sh
