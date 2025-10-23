# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# --- Project Structure ---
# Name of the final executable program
TARGET_NAME = simulator
# Directory for all build artifacts (.o files and the executable)
BUILD_DIR = build

# --- Auto-generated Variables ---
# List ALL your .cpp source files here
SRCS = menu.cpp logic_gate_array.cpp circuit.cpp matrix.cpp vector.cpp graph_plotter.cpp
# Prepend the build directory to the object file names
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
# Prepend the build directory to the final target name
TARGET = $(BUILD_DIR)/$(TARGET_NAME)


# --- Rules ---

# The default command when you just type "make"
# This is the first rule, so it's the default goal.
all: $(TARGET)

# Rule to link all the object files into the final executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pattern rule to compile a .cpp file from the root directory into an
# object file inside the build directory.
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D) # Create the build directory if it doesn't exist
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up all generated files by removing the entire build directory
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR)

# Phony targets are not real files
.PHONY: all clean