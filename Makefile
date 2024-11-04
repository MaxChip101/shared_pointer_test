# Compiler
CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++

# Directories
SRC_DIR = src
SRC_DIR2 = src2
BUILD_DEBUG_DIR = build/debug
BUILD_LINUX_DIR = build/linux
BUILD_LINUX2_DIR = build/linux2

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES2 = $(wildcard $(SRC_DIR2)/*.cpp)


# Executable names
EXEC_LINUX = test

# Flags
CXXFLAGS = -Wall -std=c++17

# Debug Flags
DEBUGFLAGS = -fsanitize=address

# Default rule
all: linux

# Linux build
linux: $(BUILD_LINUX_DIR)/$(EXEC_LINUX)

$(BUILD_LINUX_DIR)/$(EXEC_LINUX): $(SOURCES)
	@mkdir -p $(BUILD_LINUX_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

linux2: $(BUILD_LINUX2_DIR)/$(EXEC_LINUX)

$(BUILD_LINUX2_DIR)/$(EXEC_LINUX): $(SOURCES2)
	@mkdir -p $(BUILD_LINUX2_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES2) -o $@

# Debug build
debug: $(BUILD_DEBUG_DIR)/$(EXEC_LINUX)

$(BUILD_DEBUG_DIR)/$(EXEC_LINUX): $(SOURCES)
	@mkdir -p $(BUILD_DEBUG_DIR)
	$(CXX) $(DEBUGFLAGS) $(CXXFLAGS) $(SOURCES) -o $@

# Clean up the build directories
clean:
	rm -rf $(BUILD_LINUX_DIR)/$(EXEC_LINUX) $(BUILD_LINUX2_DIR)/$(EXEC_WINDOWS)

# Make sure nothing else runs if the Makefile targets are up-to-date
.PHONY: all clean linux linux2 debug
