#pragma once 
#include<glad/glad.h>
#include"shader/shaderCompiler.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;
 
class SkyManager {
public:
    void init();
    void render(ShaderCompiler &shader);
    void cleanUp();

private:    
    unsigned int vao, vbo;
    vector<float> vertices;
    vector<string> face;
    unsigned int cubeMapFinal;

    unsigned int cubeMapTexture(vector<string> face);
};

extern SkyManager skyManager;