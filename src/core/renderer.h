#pragma once 
#include<glad/glad.h>
#include<shader/shaderCompiler.h>
#include<iostream>

class Renderer{
public:
    Renderer(unsigned int _vao,unsigned int texID);
    void render(int vertexCount);
private:
    unsigned int vao;
    unsigned int texID;
};