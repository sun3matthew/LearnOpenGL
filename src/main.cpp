#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <model.h>

#include <iostream>
#include <string>

static float lastX = 800, lastY = 600;
static bool firstMouse = true;

float fade = 0.2f;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool showMouse = false;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    lastX = width / 2.0f;
    lastY = height / 2.0f;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        showMouse = !showMouse;
        if(showMouse)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        fade += 0.01f;
        if(fade > 1.0f){
            fade = 1.0f;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        fade -= 0.01f;
        if(fade < 0.0f){
            fade = 0.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset, yoffset);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glViewport(0, 0, 1600, 1200); // for some reason its double the size of the window

    std::cout << "Loading model..." << std::endl;
    Model ourModel("resources/models/backpack/backpack.obj");
    std::cout << "Model loaded!" << std::endl;

    Shader modelShader("resources/shaders/model.vert", "resources/shaders/model.frag");

    glm::vec3 modelPos(0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);  

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
    };  

    // Render loop
    // input -> update -> render -> swap buffers & poll events
    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        processInput(window);

        // Rendering commands here
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourModel.Draw(modelShader);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

        modelShader.use();
        modelShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

        for(unsigned int i = 0; i < 4; i++){
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].lightingData.ambient",  0.2f, 0.2f, 0.2f);
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].lightingData.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].lightingData.specular", 1.0f, 1.0f, 1.0f); 
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].attenuation", 1.0f, 0.09f, 0.032f);
        }

        modelShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        modelShader.setFloat("material.shininess", 32.0f);

        modelShader.setMat4("view", glm::value_ptr(view));
        modelShader.setMat4("projection", glm::value_ptr(projection));

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.1f, 0.0f));
        modelShader.setMat4("model", glm::value_ptr(model));


        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
