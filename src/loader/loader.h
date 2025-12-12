#pragma once
#include<glad/glad.h>
#include<stb_image.h>
#include<vector>
#include<iostream>

using namespace std;

class Loader{
public:
    Loader(vector<float> vertices, vector<unsigned int> indices,const char* tex);
    unsigned int loadToVao();
    unsigned int texture();
    void cleanUp();

private:
    vector<float> vertices;
    vector<unsigned int> indices;
    unsigned int vao,vbo,ebo;
    const char* tex;
    int width,height,nrChannels;
    
    void unbind();
};