CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -O3

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# CORE LIBRARY OBJECTS
CORE_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CORE_SRCS))

# TEST EXECUTABLES
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXES = $(patsubst $(TEST_DIR)/%.cpp, %, $(TEST_SRCS))

# Build all test executables
all: $(TEST_EXES)

# LINKING RULES
%: $(BUILD_DIR)/%.o $(CORE_OBJS)
	$(CXX) $(CXXFLAGS) $< $(CORE_OBJS) -o $@

# COMPILATION RULES
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test/%.cpp -> build/%.o
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TEST_EXES)

.PHONY: all clean