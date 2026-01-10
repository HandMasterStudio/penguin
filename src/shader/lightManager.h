#pragma once 
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"loader/loader.h"
#include"core/renderer.h"
#include"shader/shaderCompiler.h"
#include<vector>
#include<iostream>

using namespace std;

class LightManager{
public:
    void setup();
    void createPointLight(glm::vec3 pos,glm::vec3 scale, ShaderCompiler &shader);
    void cleanUp();
private:
    //config 
    int evnType = 0; //0~5 lighting types
    vector<float> vertices;
    vector<unsigned int> indices;
    Loader *triangle;
    Renderer *renTriangle;
    ShaderCompiler *shader;
    glm::mat4 model;
};

extern LightManager lightManager;