#pragma once 
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>

using namespace std;

class WindowManager{
public:
    void windowInit();
    void prepare();
    void cleanUp();
    
    void setWindowTitle(const char* title);
    void setWindowSize(int w,int h);
    void setColor(int x,int y,int z);
    void getWindowSizeUpdate(int &w,int &h);
    
    GLFWwindow* getWindowID()const;
    int getWindowSizeH()const;
    int getWindowSizeW()const;
    bool getIsPause()const;
    const char* getTitleString()const;

private:
    int w = 600;
    int h = 400;
    bool isPause = false;
    const char* title = "ERROR:Give title for the window by using setWindowTitle(title)";
    GLFWwindow* window;

    void statePause();
};

extern WindowManager windowManager;
