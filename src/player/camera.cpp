#include<player/camera.h>
#include<window/windowManager.h>

void Camera::update(float deltaTime,ShaderCompiler &shader){
    w = windowManager.getWindowSizeW();
    h = windowManager.getWindowSizeH();
    this->deltaTime = deltaTime;
    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f),(float)w/(float)h,0.1f,100.0f);
    view = glm::lookAt(cameraPosition,cameraPosition+cameraFront,cameraUp);

    shader.use();
    shader.setMat4("projection",projection);
    shader.setMat4("view",view);
}

void Camera::setCameraPosition(glm::vec3 &pos){
    this->cameraPosition = pos;
}

void Camera::setCameraFront(glm::vec3 &front){
    this->cameraFront = front;
}

void Camera::setCameraUp(glm::vec3 &up){
    this->cameraUp = up;
}

void Camera::movementMouse(float x,float y){
    x*= sensMouse;
    y*= sensMouse;

    yaw += x;
    pitch += y;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    if(glfwGetKey(windowManager.getWindowID(),GLFW_KEY_ESCAPE)){
        glfwSetInputMode(windowManager.getWindowID(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }else{
        glfwSetInputMode(windowManager.getWindowID(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }


    eulerUpdate();
}

void Camera::eulerUpdate(){
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    HFront = glm::normalize(glm::vec3(front.x,0,front.z));
    cameraFront = glm::normalize(front);
}

glm::vec3 Camera::getCameraPosition()const{
    return cameraPosition;
}


glm::vec3 Camera::getCameraFront()const{
    return cameraFront;
}

glm::vec3 Camera::getCameraUp()const{
    return cameraUp;
}
