# Makefile for Horizon Parser

CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include
LEX = flex
YACC = bison
LDFLAGS = -L/opt/homebrew/lib -lhpdf

SRCDIR = src
TESTDIR = tests

# Source files
PARSER_Y = $(SRCDIR)/parser.y
SCANNER_L = $(SRCDIR)/scanner.l
AST_CPP = $(SRCDIR)/ast.cpp
MAIN_CPP = $(SRCDIR)/main.cpp
PDF_RENDERER_CPP = $(SRCDIR)/pdf_renderer.cpp

# Generated files
PARSER_TAB_CC = $(SRCDIR)/parser.tab.cc
PARSER_TAB_HH = $(SRCDIR)/parser.tab.hh
LEX_YY_CC = $(SRCDIR)/lex.yy.cc

# Object files
OBJS = $(SRCDIR)/ast.o $(SRCDIR)/parser.tab.o $(SRCDIR)/lex.yy.o $(SRCDIR)/main.o $(SRCDIR)/pdf_renderer.o

# Executable
TARGET = horizon

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SRCDIR)/parser.tab.cc $(SRCDIR)/parser.tab.hh: $(PARSER_Y)
	cd $(SRCDIR) && $(YACC) -d parser.y

$(SRCDIR)/lex.yy.cc: $(SCANNER_L) $(SRCDIR)/parser.tab.hh
	cd $(SRCDIR) && $(LEX) scanner.l

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRCDIR)/lex.yy.o: $(SRCDIR)/lex.yy.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRCDIR)/*.o $(SRCDIR)/parser.tab.* $(SRCDIR)/lex.yy.cc $(SRCDIR)/location.hh $(SRCDIR)/position.hh $(SRCDIR)/stack.hh $(TARGET)

