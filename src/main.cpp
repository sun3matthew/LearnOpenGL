#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <texture.h>

#include <iostream>

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

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int VBOModel;
    glGenBuffers(1, &VBOModel);  
    glBindBuffer(GL_ARRAY_BUFFER, VBOModel);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader modelShader("resources/shaders/model.vert", "resources/shaders/model.frag");
    unsigned int VAOModel;
    glGenVertexArrays(1, &VAOModel);  
    glBindVertexArray(VAOModel);

    glBindBuffer(GL_ARRAY_BUFFER, VBOModel);
    // index, size, type, normalized, stride, pointer to the first component
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOModel);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Texture texture1("resources/textures/container2.png", true);
    Texture texture2("resources/textures/container2_specular.png", true);
    Texture texture3("resources/textures/matrix.jpg", false);


    glm::vec3 modelPos(0.0f, 0.0f, 0.0f);
    glm::vec3 lightPos(1.2f, 0.5f, -2.2f);

    glm::vec3 modelColor(1.0f, 0.5f, 0.31f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    modelShader.use();
    modelShader.setInt("material.diffuse", 0);
    modelShader.setInt("material.specular", 1);
    modelShader.setInt("material.emissive", 2);

    lightShader.use();
    lightShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

    glEnable(GL_DEPTH_TEST);  

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind(0);
        texture2.bind(1);
        texture3.bind(2);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::vec3 lightPosNew = lightPos + glm::vec3(0.0f, 0.0f, sin(glfwGetTime()) * 4.0f);
        glm::vec3 newLightColor = lightColor - glm::vec3(0.0f, 0.0f, fade);
        for(unsigned int i = 0; i < 10; i++){
            modelShader.use();
            modelShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

            modelShader.setVec3("dirLight.direction", -lightPosNew.x, -lightPosNew.y, -lightPosNew.z);
            modelShader.setVec3("dirLight.lightingData.ambient",  0.2f, 0.2f, 0.2f);
            modelShader.setVec3("dirLight.lightingData.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
            modelShader.setVec3("dirLight.lightingData.specular", 1.0f, 1.0f, 1.0f); 

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
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            modelShader.setMat4("model", glm::value_ptr(model));
            glBindVertexArray(VAOModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightShader.use();
        lightShader.setMat4("view", glm::value_ptr(view));
        lightShader.setMat4("projection", glm::value_ptr(projection));
        lightShader.setVec3("lightColor", newLightColor.x, newLightColor.y, newLightColor.z);
        glm::mat4
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosNew);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("model", glm::value_ptr(model));
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
