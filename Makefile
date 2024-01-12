# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Source file
SOURCE = main.cpp

# Output executable
OUTPUT = my_program.exe

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	del $(OUTPUT)
