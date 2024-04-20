CXX=g++
CXXFLAGS=-std=c++11 -Wall
OBJDIR=obj
BINDIR=bin

all: directories compiler

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

compiler: $(OBJDIR)/main.o $(OBJDIR)/Lexer.o $(OBJDIR)/Parser.o
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/compiler $(OBJDIR)/main.o $(OBJDIR)/Lexer.o $(OBJDIR)/Parser.o

$(OBJDIR)/main.o: main.cpp Parser.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/Lexer.o: Lexer.cpp Lexer.h
	$(CXX) $(CXXFLAGS) -c Lexer.cpp -o $(OBJDIR)/Lexer.o

$(OBJDIR)/Parser.o: Parser.cpp Parser.h Lexer.h
	$(CXX) $(CXXFLAGS) -c Parser.cpp -o $(OBJDIR)/Parser.o

clean:
	rm -rf $(OBJDIR) $(BINDIR)

