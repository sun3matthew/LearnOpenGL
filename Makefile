# Set the build directory
BUILD_DIR = build

# Default build type (Release or Debug)
BUILD_TYPE ?= Release

# Default target to configure and build
all: configure build

# Configure the project (this will invoke CMake with the build type)
configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

# Build the project (invokes make)
build: configure
	cd $(BUILD_DIR) && make

# Run the built project
run: build
	cd $(BUILD_DIR) && ./LearnOpenGL

# Clean the build files
clean:
	rm -rf $(BUILD_DIR)

# Build a Release version
release:
	$(MAKE) BUILD_TYPE=Release

# Build a Debug version
debug:
	$(MAKE) BUILD_TYPE=Debug

.PHONY: all configure build run clean release debug
