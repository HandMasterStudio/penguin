// █████▄ ▄▄▄▄▄ ▄▄  ▄▄  ▄▄▄▄ ▄▄ ▄▄ ▄▄ ▄▄  ▄▄ 
// ██▄▄█▀ ██▄▄  ███▄██ ██ ▄▄ ██ ██ ██ ███▄██ 
// ██     ██▄▄▄ ██ ▀██ ▀███▀ ▀███▀ ██ ██ ▀██                          

#include<glad/glad.h>
#include"loader/loader.h"
#include"shader/shaderCompiler.h"
#include"window/windowManager.h"
#include"core/renderer.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"player/player.h"
#include"shader/lightManager.h"
#include"skybox/skyManager.h"
#include<iostream>

using namespace std;

void mouseCallBack(GLFWwindow* window,double xPosIn,double yPosIn);

bool mouseClick = true;
float lastX = windowManager.getWindowSizeW()/2;
float lastY = windowManager.getWindowSizeH()/2;
glm::vec3 point_light = glm::vec3 (0.0f, 2.0f, 4.0f);
glm::vec3 point_light1 = glm::vec3 (0.0f, 2.0f, -4.0f);
glm::vec3 point_light2 = glm::vec3 (4.0f, 2.0f, 0.0f);
glm::vec3 point_light3 = glm::vec3 (-4.0f, 2.0f, 0.0f);

int main(){
    windowManager.windowInit();
    glfwSetCursorPosCallback(windowManager.getWindowID(),mouseCallBack);
    windowManager.setWindowSize(500,250);
    windowManager.setWindowTitle("penguin");

    ShaderCompiler shader("/home/hady/penguin/shader/shader.vert",
        "/home/hady/penguin/shader/shader.frag");
    ShaderCompiler lightShader("/home/hady/penguin/shader/light.vert",
        "/home/hady/penguin/shader/light.frag");
    ShaderCompiler cubeMapShader("/home/hady/penguin/shader/cubeMap.vert",
        "/home/hady/penguin/shader/cubeMap.frag");

    //~~~~~~~~learnOpengl.com~~~~~~~~~~
    vector<float> vertices = {
         0.5f,  0.5f,  0.5f,   0,0,1,   1,1,
         0.5f, -0.5f,  0.5f,   0,0,1,   1,0,
        -0.5f, -0.5f,  0.5f,   0,0,1,   0,0,
        -0.5f,  0.5f,  0.5f,   0,0,1,   0,1,

         0.5f,  0.5f, -0.5f,   0,0,-1,  1,1,
        -0.5f,  0.5f, -0.5f,   0,0,-1,  0,1,
        -0.5f, -0.5f, -0.5f,   0,0,-1,  0,0,
         0.5f, -0.5f, -0.5f,   0,0,-1,  1,0,

         0.5f, -0.5f,  0.5f,   1,0,0,   0,0,
         0.5f, -0.5f, -0.5f,   1,0,0,   1,0,
         0.5f,  0.5f, -0.5f,   1,0,0,   1,1,
         0.5f,  0.5f,  0.5f,   1,0,0,   0,1,

        -0.5f, -0.5f, -0.5f,  -1,0,0,   0,0,
        -0.5f,  0.5f, -0.5f,  -1,0,0,   0,1,
        -0.5f,  0.5f,  0.5f,  -1,0,0,   1,1,
        -0.5f, -0.5f,  0.5f,  -1,0,0,   1,0,

         0.5f,  0.5f,  0.5f,   0,1,0,   1,1,
        -0.5f,  0.5f,  0.5f,   0,1,0,   0,1,
        -0.5f,  0.5f, -0.5f,   0,1,0,   0,0,
         0.5f,  0.5f, -0.5f,   0,1,0,   1,0,

         0.5f, -0.5f,  0.5f,   0,-1,0,  1,1,
        -0.5f, -0.5f,  0.5f,   0,-1,0,  0,1,
        -0.5f, -0.5f, -0.5f,   0,-1,0,  0,0,
         0.5f, -0.5f, -0.5f,   0,-1,0,  1,0
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

    Loader quad(vertices,indices,"/home/hady/penguin/res/image/test_tex.png");
    Renderer renQuad(quad.loadToVao(),quad.texture());
    Loader quad2(vertices,indices,"/home/hady/penguin/res/image/wall.jpg");
    Renderer renQuad2(quad2.loadToVao(),quad2.texture());
    player.setup(10,2,7);
    player.setPosPlayer(glm::vec3(0,0,0));
    lightManager.setup();
    skyManager.init();
    //model mat4
    glm::mat4 model;
    float i = 0.0f;
    //~ 
    float deltaTime = 0;
    float lastFrame = 0;

    cubeMapShader.use();
    cubeMapShader.setInt("skybox",0);

    shader.use();
    shader.setInt("material.diffuse",0);
    shader.setInt("material.specular",0);
    shader.setInt("lightUsed",4);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(windowManager.getWindowID())){
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        windowManager.setColor(0,0,0);
        player.loop(deltaTime);
        shader.use();
        shader.setVec3("viewPos",player.getPosCamera());
        shader.setFloat("material.shininess",32);
        player.addShader(shader);   

        // shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        // shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        // shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        // shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        
        shader.setVec3("pointLights[0].position", point_light);
        shader.setVec3("pointLights[0].ambient", 0.00f, 0.00f, 0.1f);
        shader.setVec3("pointLights[0].diffuse", 0.0f, 0.0f, 0.8f);
        shader.setVec3("pointLights[0].specular", 0.3f, 0.3f, 1.0f);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09f);
        shader.setFloat("pointLights[0].quadratic", 0.032f);

        shader.setVec3("pointLights[1].position", point_light1);
        shader.setVec3("pointLights[1].ambient", 0.1f, 0.0f, 0.0f);
        shader.setVec3("pointLights[1].diffuse", 0.8f, 0.0f, 0.0f);
        shader.setVec3("pointLights[1].specular", 1.0f, 0.2f, 0.2f);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09f);
        shader.setFloat("pointLights[1].quadratic", 0.032f);

        shader.setVec3("pointLights[2].position", point_light2);
        shader.setVec3("pointLights[2].ambient", 0.0f, 0.1f, 0.0f);
        shader.setVec3("pointLights[2].diffuse", 0.0f, 0.8f, 0.0f);
        shader.setVec3("pointLights[2].specular", 0.3f, 1.0f, 0.3f);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09f);
        shader.setFloat("pointLights[2].quadratic", 0.032f);

        shader.setVec3("pointLights[3].position", point_light3);
        shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09f);
        shader.setFloat("pointLights[3].quadratic", 0.032f);
        
        //maths
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0,1,0));
        shader.setMat4("model", model);
        renQuad.render(36);
        //~

        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0,0,0));
        model = glm::scale(model,glm::vec3(20,1,20));
        shader.setMat4("model",model);
        renQuad2.render(36);

        lightShader.use();
        player.addShader(lightShader);
        lightShader.setVec3("color", 0,0,1);
        lightManager.createPointLight(point_light, glm::vec3(0.5f,0.5f,0.5f),lightShader);

        lightShader.setVec3("color", 1,0,0);
        lightManager.createPointLight(point_light1, glm::vec3(0.5f,0.5f,0.5f),lightShader);

        lightShader.setVec3("color", 0,1,0);
        lightManager.createPointLight(point_light2, glm::vec3(0.5f,0.5f,0.5f),lightShader);

        lightShader.setVec3("color", 1,1,1);
        lightManager.createPointLight(point_light3, glm::vec3(0.5f,0.5f,0.5f),lightShader);

        //cubeMap 
        cubeMapShader.use();
        skyManager.render(cubeMapShader);

        windowManager.prepare();
    }

    //cleanUp
    shader.cleanUp();
    quad.cleanUp();
    quad2.cleanUp();
    player.cleanUp();
    windowManager.cleanUp();
    lightManager.cleanUp();
    skyManager.cleanUp();
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