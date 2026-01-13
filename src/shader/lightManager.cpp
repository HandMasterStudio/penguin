#include<shader/lightManager.h>
#include"loader/loader.h"
#include"core/renderer.h"

void LightManager::setup(){
    vertices = {
         0.5,-0.5, 0.0, 0,0,0, 0,0,
        -0.5,-0.5, 0.0, 0,0,0, 0,0,
         0.0, 0.5, 0.0, 0,0,0, 0,0,

         0.0,-0.5,-0.5, 0,0,0, 0,0,
         0.0,-0.5, 0.5, 0,0,0, 0,0,
         0.0, 0.5, 0.0, 0,0,0, 0,0
    };

    indices = {
        0,1,2,
        3,4,5,
    };

    triangle = new Loader(vertices,indices, "");
    cout<<"Dont worry for the ERROR::Cannot find texture file, its just light"<<endl;
    renTriangle = new Renderer(triangle->loadToVao(),triangle->texture());
}

void LightManager::createPointLight(glm::vec3 pos,glm::vec3 scale,ShaderCompiler &shader){
    model = glm::mat4(1.0f);
    model = glm::translate(model,pos);
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
    renTriangle->render(indices.size());
}

void LightManager::cleanUp(){
    triangle->cleanUp();
    vertices.clear();
    indices.clear();
    delete renTriangle;
}

LightManager lightManager;