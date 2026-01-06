
#include"window/windowManager.h"

void frameBufferSizeCallBack(GLFWwindow* window,int w,int h);

void WindowManager::windowInit(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(w,h,title,NULL,NULL);

    if(window==0){
        cout<<"ERROR::window is null!"<<endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallBack);
    // glfwSetCursorPosCallback(window,mouseCallBack);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
    glEnable(GL_DEPTH_TEST);
}

void WindowManager::prepare(){
    statePause();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowManager::cleanUp(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowManager::setWindowTitle(const char* _title){
    glfwSetWindowTitle(window,_title);
    title = _title;
}

void WindowManager::setWindowSize(int w,int h){
    glfwSetWindowSize(window,w,h);
}

void WindowManager::setColor(int x,int y,int z){
    glClearColor(x,y,z,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::getWindowSizeUpdate(int &w,int &h){
    this->w = w;
    this->h = h;
}

GLFWwindow* WindowManager::getWindowID()const{
    return window;
}

int WindowManager::getWindowSizeH()const{
    return h;
}

int WindowManager::getWindowSizeW()const{
    return w;
}

bool WindowManager::getIsPause()const{
    return isPause;
}

const char* WindowManager::getTitleString()const{
    return title;
}

//private
void WindowManager::statePause(){
    //enter pause mode!
    if(glfwGetKey(windowManager.getWindowID(), GLFW_KEY_ESCAPE)){
        isPause = true;
        glfwSetCursorPos(this->window, w/2, h/2);
    }

    //~

    //aut of pause mode!
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)){
        isPause = false;
    }
    // ~

  if(isPause){
        glfwSetInputMode(windowManager.getWindowID(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }else{
        glfwSetInputMode(windowManager.getWindowID(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }
}

void frameBufferSizeCallBack(GLFWwindow* window,int wV,int hV){
    glViewport(0,0,wV,hV);
    windowManager.getWindowSizeUpdate(wV,hV);
}
WindowManager windowManager;
