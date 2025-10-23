# Compiler and compiler flags
CXX = g++
# ADD -Iinclude TO THIS LINE
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# Name of the final executable program
TARGET = simulator

# List ALL your .cpp source files here
# NOTE: Your screenshot shows 'logic_gate_array.cpp' in the root,
# but if you have other .cpp files in a 'src' folder, you would list them here.
SRCS = menu.cpp logic_gate_array.cpp circuit.cpp matrix.cpp vector.cpp graph_plotter.cpp

# Generate the corresponding object file names (.o files)
OBJS = $(SRCS:.cpp=.o)

# The default command when you just type "make"
all: $(TARGET)

# Rule to link all the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# A pattern rule that tells make how to build a .o file from a .cpp file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# A rule to clean up all the compiled files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean