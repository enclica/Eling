CXX=g++
CXXFLAGS=-std=c++11 -Wall
OBJDIR=obj
BINDIR=bin
SRCDIR=SRC_compiler

COLOR_RED=\033[0;31m
COLOR_GREEN=\033[0;32m
COLOR_NC=\033[0m

SRCFILES := $(shell find $(SRCDIR) -name '*.cpp')
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))

all: directories compiler

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

compiler: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/compiler $(OBJFILES)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

	@echo "$(COLOR_GREEN)Compiler is up to date$(COLOR_NC)"

clean:
	rm -rf $(OBJDIR) $(BINDIR)

cleansmall:
	rm -rf $(OBJDIR)
	rm $(BINDIR)/eling
