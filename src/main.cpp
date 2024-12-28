#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void){
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL X.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Needed for Mac for some reason..

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glViewport(0, 0, 1600, 1200); // for some reason its double the size of the window

    Shader shader("resources/shaders/vertex.glsl", "resources/shaders/frag.glsl");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);

    float vertices[] = {    // x, y, z, r, g, b
        -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
    }; 

    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // index, size, type, normalized, stride, pointer to the first component
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    float vertices2[] = {
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // left
        0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // right
        0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");


    // Render loop
    // input -> update -> render -> swap buffers & poll events
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        // Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        shader.use();

        shader.setVec3("ourColor", 0.0f, greenValue, 0.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shader.setVec3("ourColor", greenValue, 0.0f, 0.0f);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
