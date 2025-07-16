# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++23 -Iincludes -MMD -MP

SRC_DIR := src
INC_DIR := includes
BUILD_DIR := build
TARGET := app

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking $(TARGET)
	@$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
