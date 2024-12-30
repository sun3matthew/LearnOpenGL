# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LearnOpenGL VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find all source files in src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# Add executable target
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    /opt/homebrew/include
)

# Library directories
target_link_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/lib)

add_subdirectory(external/assimp)
target_include_directories(${PROJECT_NAME} PUBLIC external/assimp/include)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

# Link GLFW and OpenGL libraries (using keyword syntax)
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL)
endif()

# Compiler definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

# Copy resources directory to the build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources)
