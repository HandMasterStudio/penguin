#pragma once 
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"shader/shaderCompiler.h"
#include<iostream>
#include<vector>

using namespace std;

class Camera{
public:
    glm::vec3 HFront = glm::vec3(0,0,0);
    void update(float deltaTime);
    void setCameraPosition(glm::vec3 &pos);
    void setCameraFront(glm::vec3 &front);
    void setCameraUp(glm::vec3 &up);
    void movementMouse(float x,float y);
    void eulerUpdate();
    void forwardAddShaderFunction(ShaderCompiler &addShader);
    void removeTranslation();
    void cleanUp();

    glm::vec3 getCameraPosition()const;
    glm::vec3 getCameraFront()const;
    glm::vec3 getCameraUp()const;
    glm::mat4 getViewMatrix()const;
    glm::mat4 getProjMatrix()const;
private:
    void camera();

    vector<ShaderCompiler> shader;
    glm::vec3 cameraPosition = glm::vec3(0,0,0); //default will be 0,0,0
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraFront = glm::vec3(0,0,-1.0f);
    glm::vec3 cameraUp = glm::vec3(0,1,0);
    float deltaTime = 0;
    int w = 0,h = 0;
    float sensMouse = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;
};