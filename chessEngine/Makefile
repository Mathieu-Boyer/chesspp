# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23 -Iincludes -MMD -MP

# Directories
SRC_DIR := src
INC_DIR := includes
BUILD_DIR := build
TARGET := app

# Source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	@echo Linking $(TARGET)
	@$(CXX) $(OBJS) -o $@

# Compile source files into build/ directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files if they exist
-include $(DEPS)

# Clean target
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
