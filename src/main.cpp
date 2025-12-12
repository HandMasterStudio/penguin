#include<glad/glad.h>
#include<loader/loader.h>
#include<shader/shaderCompiler.h>
#include<window/windowManager.h>
#include<core/renderer.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<player/player.h>
#include<iostream>

using namespace std;

void mouseCallBack(GLFWwindow* window,double xPosIn,double yPosIn);

bool mouseClick = true;
float lastX = windowManager.getWindowSizeW()/2;
float lastY = windowManager.getWindowSizeH()/2;

int main(){
    windowManager.windowInit();
    glfwSetCursorPosCallback(windowManager.getWindowID(),mouseCallBack);
    windowManager.setWindowSize(500,250);
    windowManager.setWindowTitle("penguin");

    ShaderCompiler shader("/home/handdev/penguin/src/shader/shader.vert","/home/handdev/penguin/src/shader/shader.frag");

    //~~~~~~~~learnOpengl.com~~~~~~~~~~
    vector<float> vertices = {
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Right face
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Top face
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f
    };

    vector<unsigned int> indices = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Right
        8, 9, 10,
        10, 11, 8,

        // Left
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    //~

    Loader quad(vertices,indices,"/home/handdev/penguin/res/image/test_tex.png");
    Renderer renQuad(quad.loadToVao(),quad.texture());
    Loader quad2(vertices,indices,"/home/handdev/penguin/res/image/wall.jpg");
    Renderer renQuad2(quad2.loadToVao(),quad2.texture());
    player.setup(10,1);
    player.setPosPlayer(glm::vec3(0,0,0));
    player.setEyePlayer(2);
    //model mat4
    glm::mat4 model;
    float i = 0.0f;
    //~ 
    float deltaTime = 0;
    float lastFrame = 0;

    while(!glfwWindowShouldClose(windowManager.getWindowID())){
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        windowManager.setColor(0,0,0);
        player.loop(deltaTime,shader);
        shader.use();
        
        //maths
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0,1,0));
        // model = glm::rotate(model,glm::radians(i),glm::vec3(1,1,1));
        i++;
        shader.setMat4("model", model);
        renQuad.render(shader,36);
        //~

        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0,0,0));
        model = glm::scale(model,glm::vec3(20,1,20));
        shader.setMat4("model",model);
        renQuad2.render(shader,36);

        windowManager.prepare();
    }

    //cleanUp
    shader.cleanUp();
    quad.cleanUp();
    quad2.cleanUp();
    player.cleanUp();
    windowManager.cleanUp();
    //delete
    return 0;
}

void mouseCallBack(GLFWwindow* window,double xPosIn,double yPosIn){
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    if(mouseClick){
        lastX = xPos;
        lastY = yPos;
        mouseClick = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
    player.forwardMovementMouse(xOffset,yOffset);
}