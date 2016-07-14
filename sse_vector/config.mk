# Author : Pawel Gniewek (UC Berkeley)
# Email  : pawel.gniewek@berkeley.edu
# License: BSD

# C++ compiler
CXX      := g++

# Flags for the C++ compiler
# -g --Enable debugging
# -Wall --Turn on all warnings
# -D_USE_FIXED_PROTOTYPES_
# --Force the compiler to use the correct headers
# -ansi: In C++ mode, it is equivalent to -std=c++98
# "-O3" - optimization level
# -march=native - optimize for the particular architecture
DBGFLAGS := -DDEBUG -g -DPTR
DBGFLAGS := -DDEBUG -g

# Relative include and library paths for compilation of the examples
INCLUDE  := -I/usr/local/include -I$(CURDIR)/include
LIB      := -L/usr/lib -L/usr/local/lib
DFLAGS   :=

CXXFLAGS := -lm -Wall -O3 -msse3 -msse4 -std=gnu++0x $(INCLUDE) $(DBGFLAGS)
LDFLAGS  := $(LIB)
LDLIBS   :=


# Local dirs
SRC      := ./src
BIN      := ./bin

# Installation directory
PREFIX   := /usr/local
