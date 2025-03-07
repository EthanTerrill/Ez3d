#pragma once

#include "shader.cpp"

class shaderProgram{


private:

    unsigned int shaderPointer;



public:



    shaderProgram(std::string vertexFile, std::string fragmentFile) {

        shader vertShader = shader(vertexFile);
        shader fragShader = shader(fragmentFile);




        vertShader.compile(GL_VERTEX_SHADER);
        fragShader.compile(GL_FRAGMENT_SHADER);


        
        //////////////////////////////////////////////////////////////
        //	create Shader Program
        //////////////////////////////////////////////////////////
        shaderPointer = glCreateProgram();
        
        //////////////////////////////////////////////////////////////
        //	Link vertex and fragment shaders
        //////////////////////////////////////////////////////////
        
        glAttachShader(shaderPointer, vertShader.getPointer());
        glAttachShader(shaderPointer, fragShader.getPointer());
        
        glLinkProgram(shaderPointer);
        
        
        //////////////////////////////////////////////////////////////
        //	Ensure shaders were linked correctly
        //////////////////////////////////////////////////////////
        

        
        int success;
        char infoLog[512];
        
        glGetProgramiv(shaderPointer, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderPointer, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        
        
        //////////////////////////////////////////////////////////////
        //	Free up memory
        //////////////////////////////////////////////////////////
        glDeleteShader(vertShader.getPointer());
        glDeleteShader(fragShader.getPointer());
    }



    unsigned int getShader(){

        return shaderPointer;
    }

    void Delete(){

       glDeleteProgram(shaderPointer);
    }



};
