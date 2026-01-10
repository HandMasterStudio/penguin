#include<core/renderer.h>
#include<shader/shaderCompiler.h>

Renderer::Renderer(unsigned int _vao,unsigned int texID){
    this->vao = _vao;
    this->texID = texID;
}
void Renderer::render(int vertexCount){
    glBindTexture(GL_TEXTURE_2D,texID);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,vertexCount,GL_UNSIGNED_INT,0);
}