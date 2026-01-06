#include<glad/glad.h>
#include"loader/loader.h"
#include"shader/shaderCompiler.h"
#include"window/windowManager.h"
#include"core/renderer.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"player/player.h"
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

    ShaderCompiler shader("/home/hady/penguin/shader/shader.vert",
        "/home/hady/penguin/shader/shader.frag");

    //~~~~~~~~learnOpengl.com~~~~~~~~~~
    vector<float> vertices = {
         0.5f, 0.5f, 0.5f,  0,0,1,
         0.5f,-0.5f, 0.5f,  0,0,1,
        -0.5f,-0.5f, 0.5f,  0,0,1,
        -0.5f, 0.5f, 0.5f,  0,0,1,

         0.5f, 0.5f,-0.5f,  0,0,-1,
        -0.5f, 0.5f,-0.5f,  0,0,-1,
        -0.5f,-0.5f,-0.5f,  0,0,-1,
         0.5f,-0.5f,-0.5f,  0,0,-1,

         0.5f,-0.5f, 0.5f,  -1,0,0,
         0.5f,-0.5f,-0.5f,  -1,0,0,
         0.5f, 0.5f,-0.5f,  -1,0,0,
         0.5f, 0.5f, 0.5f,  -1,0,0,

         -0.5f,-0.5f,-0.5f,  1,0,0,
         -0.5f, 0.5f,-0.5f,  1,0,0,
         -0.5f, 0.5f, 0.5f,  1,0,0,
         -0.5f,-0.5f, 0.5f,  1,0,0,

          0.5f, 0.5f, 0.5f,  0,1,0,
         -0.5f, 0.5f, 0.5f,  0,1,0,
         -0.5f, 0.5f,-0.5f,  0,1,0,
          0.5f, 0.5f,-0.5f,  0,1,0,

          0.5f,-0.5f, 0.5f,  0,-1,0,
         -0.5f,-0.5f, 0.5f,  0,-1,0,
         -0.5f,-0.5f,-0.5f,  0,-1,0,
          0.5f,-0.5f,-0.5f,  0,-1,0
    };


    vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12, 

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    //~

    Loader quad(vertices,indices,"/home/hady/penguin/res/image/test_tfdsfex.png");
    Renderer renQuad(quad.loadToVao(),quad.texture());
    Loader quad2(vertices,indices,"/home/hady/penguin/res/image/walfdasfdl.jpg");
    Renderer renQuad2(quad2.loadToVao(),quad2.texture());
    player.setup(10,2,7);
    player.setPosPlayer(glm::vec3(0,0,0));
    //model mat4
    glm::mat4 model;
    float i = 0.0f;
    //~ 
    float deltaTime = 0;
    float lastFrame = 0;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(windowManager.getWindowID())){
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        windowManager.setColor(0,0,0);
        player.loop(deltaTime);
        shader.use();
        shader.setVec3("lightPos", 1.2f, 1.0f, 2.0f);
        shader.setVec3("viewPos",player.getPosCamera());
        player.addShader(shader);

        glm::vec3 lightColor = glm::vec3(1,1,1);
        // lightColor.x = static_cast<float>(sin(glfwGetTime()*2));
        // lightColor.y = static_cast<float>(sin(glfwGetTime()*0.7f));
        // lightColor.z = static_cast<float>(sin(glfwGetTime()*1.3f));
        glm::vec3 diffColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffColor * glm::vec3(0.2f);
        shader.setVec3("light.ambient",ambientColor);
        shader.setVec3("light.diffuse",diffColor);
        shader.setVec3("light.specular",1,1,1);

        shader.setVec3("material.ambient",1,0.5f,0.31f);
        shader.setVec3("material.diffuse",1,0.5f,0.31f);
        shader.setVec3("material.specular",0.5f,0.5f,0.5f);
        shader.setFloat("material.shininess",32);
        
        //maths
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0,1,0));
        model = glm::rotate(model,glm::radians(i),glm::vec3(1,1,1));
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
    if(!windowManager.getIsPause()){
        player.forwardMovementMouse(xOffset,yOffset);
    }
}