#ifndef  SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

//Shader Class derived from https://learnopengl.com/Getting-started/Shaders

class Shader
{
    public:
        unsigned int programID;
        Shader( const char* vertexPath, const char* fragmentPath);

        unsigned int create_shader(unsigned int shader_type, const char* source);
        unsigned int create_program(unsigned int vs, unsigned int fs);
        unsigned int getUniform(const char* name);
        
        void use();
        
 };



#endif