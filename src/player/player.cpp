#include<player/player.h>
#include<player/camera.h>
#include<shader/shaderCompiler.h>
#include<player/camera.h>
#include<window/windowManager.h>

//public
void Player::setup(float speed,float eye,float airControl){
    this->speed = speed;
    this->eye = eye;
    this->airControl = airControl;
    camera = new Camera();
    cameraPos = camera->getCameraPosition();
    gravity = eye+2;
}

void Player::setPosPlayer(glm::vec3 pos){
    this->playerPos = pos;
}

void Player::loop(float deltaTime){
    this->deltaTime = deltaTime;

    cameraFront = camera->getCameraFront();
    cameraUp = camera->getCameraUp();
    //simple physics
    cameraPos.y = gravity;
    checkingGround();
    if(glfwGetKey(windowManager.getWindowID(), GLFW_KEY_R)==GLFW_PRESS){
        gravity = 4;
        return;
    }
    if(glfwGetKey(windowManager.getWindowID(), GLFW_KEY_SPACE)==GLFW_PRESS){
        jump = true;
    }else{
        jump = false;
    }
    controllerKeyboard();
    camera->update(deltaTime);
}

void Player::forwardMovementMouse(float x,float y){
    camera->movementMouse(x,y);
}

void Player::addShader(ShaderCompiler &shader){
    camera->forwardAddShaderFunction(shader);
}

void Player::cleanUp(){
    camera->cleanUp();
    delete camera;
}

glm::vec3 Player::getPosPlayer(){
    return cameraPos;
}

glm::vec3 Player::getPosCamera(){
    return cameraPos;
}

//private
void Player::checkingGround(){
    if(gravity >eye && jump == false){
        ground = false;
        gravity -= 0.2;
    }else if(gravity <= eye){
        ground = true;
        gravity = 2;
    }

    if(jump){
        ground = false;
        gravity += 0.2;
    }
}
void Player::controllerKeyboard(){
    float currentSpeed = speed;
    if(ground == false){
        currentSpeed = airControl;
    }
    float finalSpeed = currentSpeed*deltaTime;
    //input
        if (glfwGetKey(windowManager.getWindowID(),GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += finalSpeed * camera->HFront;
        if (glfwGetKey(windowManager.getWindowID(),GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= finalSpeed * camera->HFront;
        if (glfwGetKey(windowManager.getWindowID(),GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(camera->HFront, cameraUp)) * finalSpeed;
        if (glfwGetKey(windowManager.getWindowID(),GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(camera->HFront, cameraUp)) * finalSpeed;
    cameraPos = glm::vec3(cameraPos.x,cameraPos.y,cameraPos.z);
    camera->setCameraPosition(cameraPos);
    camera->setCameraFront(cameraFront);
    camera->setCameraUp(cameraUp);
}

Player player;