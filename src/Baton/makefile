# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17

# Source file
SRC := Main.cpp

# Object file directory
OBJDIR := obj

# Linker flags
LDFLAGS := -lstdc++fs -lm -lcurl

# Object file
OBJ := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

# Binary file directory
BINDIR := bin

# Binary file
BIN := $(BINDIR)/baton

# Default target
all: $(BIN)

# Rule to compile the source file into an objexct file
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link the object files into a binary file
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean target
clean:
	rm -f $(OBJDIR)/*.o $(BIN)
