#pragma once
#include "bitmap.hpp"

class texture2d{

private:

    GLuint texture;
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapType;
    GLenum bufferFormat;







public:

    texture2d(bitmap textureSource){

        minFilter       = GL_NEAREST;
        magFilter       = GL_NEAREST;
        wrapType        = GL_REPEAT;  //GL_CLAMP_TO_BORDER
        bufferFormat    = GL_BGR;

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


        glTexImage2D
        (
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            textureSource.getWidth(), 
            textureSource.getheight(), 
            0, 
            bufferFormat, 
            GL_UNSIGNED_BYTE, 
            textureSource.getBytes()
        );






    }


    void bind(){
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void Delete(){

        glDeleteTextures(1, &texture);
    }




};
