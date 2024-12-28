# Set the build directory
BUILD_DIR = build

# Default target to configure and build
all: configure build

# Configure the project (this will invoke CMake)
configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# Build the project (invokes make)
build: configure
	cd $(BUILD_DIR) && make

# Run the built project
run: build
	cd $(BUILD_DIR) && ./LearnOpenGL

# Clean the build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all configure build run clean
