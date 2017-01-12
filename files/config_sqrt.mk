# Author : Pawel Gniewek (UC Berkeley)
# Email  : pawel.gniewek@berkeley.edu
# License: BSD

# C++ compiler
CXX      := g++

DBGFLAGS :=

# Relative include and library paths for compilation of the examples
INCLUDE  := -I/usr/local/include
LIB      := -L/usr/lib -L/usr/local/lib
DFLAGS   :=

CXXFLAGS := -lm -Wall -O3 -std=gnu++0x $(INCLUDE) $(DBGFLAGS)
LDFLAGS  := $(LIB)
LDLIBS   :=

# Local dirs
SRC      := ./src
BIN      := ./bin
