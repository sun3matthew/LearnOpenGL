# Compiler and flags
CXX = clang++
CXXFLAGS = -I$(shell brew --prefix)/include
CXXFLAGS += -Iinclude
CXXFLAGS += -std=c++17
CXXFLAGS += -DGL_SILENCE_DEPRECATION


LDFLAGS = -L$(shell brew --prefix)/lib -lglfw -framework OpenGL

# Source directory
SRC_DIR = src

# Build directory
BUILD_DIR = builds

# Target names
TARGET_NAME = main
SRC = $(SRC_DIR)/$(TARGET_NAME).cpp
GLAD_SRC = $(SRC_DIR)/glad.c
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

# Default rule to build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(TARGET) $(SRC) $(GLAD_SRC) $(CXXFLAGS) $(LDFLAGS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
