#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<player/camera.h>
#include<shader/shaderCompiler.h>
#include<iostream>

using namespace std;

class Player{
public:
    void setup(float speed,float eye,float airControl);
    void setPosPlayer(glm::vec3 pos);
    void loop(float deltaTime);
    void forwardMovementMouse(float x,float y);
    void addShader(ShaderCompiler &shader);
    void cleanUp();

    glm::vec3 getPosPlayer();
    glm::vec3 getPosCamera();
private:
    void checkingGround();
    void controllerKeyboard();
    void mouse();

    glm::vec3 playerPos = glm::vec3(0,0,0);
    glm::vec3 cameraPos = glm::vec3(0,0,0);
    glm::vec3 cameraFront = glm::vec3(0,0,-1.0f);
    glm::vec3 cameraUp = glm::vec3(0,1,0);
    Camera* camera;
    float speed = 2.0f;
    float deltaTime;
    float eye = 1.0f;
    float gravity = 1.0f;
    float airControl = 8.0f;
    bool ground = false;
    bool jump = false;
    
};

extern Player player;