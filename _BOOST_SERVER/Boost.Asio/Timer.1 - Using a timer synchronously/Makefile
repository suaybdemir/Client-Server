# Define variables
CXX := g++
CXXFLAGS := -I /usr/local/include
TARGET := main
SRC := main.cpp

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up the build
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
