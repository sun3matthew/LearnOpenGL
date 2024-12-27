#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

// #define GL_SILENCE_DEPRECATION

// Callback functions
void errorCallback(int error, const char* description)
{
    fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void frameBufferResizeCallback(GLFWwindow* window, int width, int height){
   glViewport(0, 0, width, height);
}

// Utility function to read shader files
char* readShaderFile(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open shader file: %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';

    fclose(file);
    return content;
}

int main(void)
{
    GLFWwindow* window;

    // Set callback for errors
    glfwSetErrorCallback(errorCallback);

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Running OpenGL on Mac", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // OpenGL initializations
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex data (4 vertices for a quad)
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // Bottom left
         1.0f, -1.0f, 0.0f, // Bottom right
         1.0f,  1.0f, 0.0f, // Top right
        -1.0f,  1.0f, 0.0f  // Top left
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Index data for two triangles forming the quad
    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Read the shader files
    char* vertexShaderSource = readShaderFile("src/shaders/vertex.glsl");
    char* fragmentShaderSource = readShaderFile("src/shaders/frag.glsl");

    if (!vertexShaderSource || !fragmentShaderSource) {
        fprintf(stderr, "Error loading shader files\n");
        return -1;
    }

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char* const*)&vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fputs(infoLog, stderr);
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char* const*)&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fputs(infoLog, stderr);
    }

    // Link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fputs(infoLog, stderr);
    }
    glUseProgram(shaderProgram);

    // Cleanup shaders (they are linked to the program, so they can be deleted)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int iTimeLocation = glGetUniformLocation(shaderProgram, "iTime");

    // Get the uniform location for iResolution
    int iResolutionLocation = glGetUniformLocation(shaderProgram, "iResolution");

    // Bind vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Get the framebuffer size and pass it to the shader
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        // width /= 2;
        // height /= 2;

        width = 640;
        height = 480;



        // Set the resolution uniform
        glUniform3f(iResolutionLocation, (float)width, (float)height, 1.0f);

        float timeValue = (float)glfwGetTime();
        glUniform1f(iTimeLocation, timeValue);  // Set iTime uniform

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw quad with indices

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
