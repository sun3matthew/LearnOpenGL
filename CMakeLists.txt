# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LearnOpenGL VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include /opt/homebrew/include)

# Library directories
link_directories(/opt/homebrew/lib)

# Find all source files in src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# Add executable target
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} glfw "-framework OpenGL")

# Compiler definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
