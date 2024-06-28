# Makefile for compiling main.cpp using g++

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall

# SFML libraries
LIBS := -lsfml-audio -lsfml-system -lreadline

# Directories
SRCDIR := src
BUILDDIR := build
TARGET := audio_player

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Default target
all: $(TARGET)

# Target: audio_player
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Rule for building object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean
