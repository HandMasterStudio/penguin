#include<player/player.h>
#include<player/camera.h>
#include<shader/shaderCompiler.h>
#include<player/camera.h>
#include<window/windowManager.h>

//public
void Player::setup(float speed,float eye){
    this->speed = speed;
    this->eye = eye;
    camera = new Camera();
    cameraPos = camera->getCameraPosition();
    gravity = 1.0f;
}

void Player::setPosPlayer(glm::vec3 pos){
    this->playerPos = pos;
}

void Player::setEyePlayer(float eye){
    this->eye = eye;
    cameraPos.y = eye;
}

void Player::loop(float deltaTime,ShaderCompiler &shader){
    this->deltaTime = deltaTime;

    cameraPos.y = gravity;
    gravity -= 0.1;
    cameraFront = camera->getCameraFront();
    cameraUp = camera->getCameraUp();
    controllerKeyboard();
    camera->update(deltaTime,shader);
}

void Player::cleanUp(){
    delete camera;
    cout<<"Saving player position"<<endl;

}

void Player::forwardMovementMouse(float x,float y){
    camera->movementMouse(x,y);
}

glm::vec3 Player::getPosPlayer(){
    return cameraPos;
}

//private
void Player::controllerKeyboard(){
    float finalSpeed = speed*deltaTime;

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