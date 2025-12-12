#include<loader/loader.h>

Loader::Loader(vector<float> vertices, vector<unsigned int> indices,const char* tex){
    this->vertices = vertices;
    this->indices = indices;
    this->tex = tex;

    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
}

unsigned int Loader::loadToVao(){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    unbind();
    return vao;
}

unsigned int Loader::texture(){
    unsigned int texID;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(tex,&width,&height,&nrChannels,0);

    if(data){
        glGenTextures(1,&texID);
        glBindTexture(GL_TEXTURE_2D,texID);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        cout<<"ERROR:Cant load image "<<tex<<endl;
        unsigned char* error = stbi_load("/home/handdev/penguin/res/image/error_tex.png",&width,&height,&nrChannels,0);
        if(!error){
            cout<<"ERROR:Bro why you remove the error_tex? its should be on /home/handdev/penguin/res/image/error_tex.png"<<endl;
        }else{
            glGenTextures(1,&texID);
            glBindTexture(GL_TEXTURE_2D,texID);
    
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,error);
            stbi_image_free(error);
        }
    }

    stbi_image_free(data);
    return texID;
}

void Loader::cleanUp(){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);

    vertices.clear();
    indices.clear();
}

void Loader::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}