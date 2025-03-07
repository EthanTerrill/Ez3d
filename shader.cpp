#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <cassert>

class shader{

    private:

    std::string filename;
    std::string shaderSource;
    unsigned int shaderPointer;



    public:




    //void link(GLuint format, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {


        
        //glVertexAttribPointer(format, numComponents, type, GL_FALSE, stride, offset);
        //glEnableVertexAttribArray(format);


    //}


    void compile(GLuint type){

          const char* cSource = shaderSource.c_str();
          //////////////////////////////////////////////////////////////
          //	Create and compile vertex shader
          //////////////////////////////////////////////////////////
          shaderPointer = glCreateShader(type);
          glShaderSource(shaderPointer, 1, &cSource, NULL);
          glCompileShader(shaderPointer);
          
          
          
          //////////////////////////////////////////////////////////////
          //	check for vertex errors
          //////////////////////////////////////////////////////////
          int success;
          char infoLog[512];
          glGetShaderiv(shaderPointer, GL_COMPILE_STATUS, &success);

          if (!success)
          {
              glGetShaderInfoLog(shaderPointer, 512, NULL, infoLog);
              std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
              assert(false);
          }

    }


    shader(std::string fileName){

        assert(fileName != "");



        std::ifstream f;

        f.open(fileName, std::ios::binary);

        if(f.is_open()){
            shaderSource = "";
            char c = ' ';

            while(!f.eof()){    
                f.get(c);
                shaderSource += c;
            }
            shaderSource += "\n\0";

        }
        else{

            std::cerr<<"ERROR: invalid shader file: "  << fileName << "\n\n";

            exit(-1);
        }
        //printSrc();
    }

    const char* getShaderSource(){

        return shaderSource.c_str();

    }

    void printSrc(){

        assert(shaderSource != "");
        std::cout << "\n\n{SHADER SOURCE}\n\n"<<shaderSource<<"\n\n-----------------\n\n\n\n";

    }

    

    unsigned int getPointer(){
        return shaderPointer;
    }


    void attach(unsigned int shaderProgram){

        glAttachShader(shaderProgram, shaderPointer);	
    }



};
