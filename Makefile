# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++20 -Wall

# Source files
SRCS := main.cpp main_logic.cpp menu_logic.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Header files
HEADERS := main_logic.hpp menu_logic.hpp

# Executable name
TARGET := fileUtility

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJS) $(TARGET)
