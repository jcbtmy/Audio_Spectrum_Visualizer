#include "Shader.h"

unsigned int Shader::create_shader(unsigned int shader_type, const char* source)
{
    int Result = GL_FALSE;
    int InfoLogLength;
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> ShaderError(InfoLogLength + 1);
        glGetShaderInfoLog(shader, InfoLogLength, NULL, &ShaderError[0]);
        printf("%s\n", &ShaderError[0] );
    }

    return shader;
}

unsigned int Shader::create_program(unsigned int vs, unsigned int fs)
{
    int Result = GL_FALSE;
    int InfoLogLength;
    unsigned int shader_program = glCreateProgram();

    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &Result);
	glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
        std::vector<char> errMessage(InfoLogLength + 1);
		glGetProgramInfoLog(shader_program, InfoLogLength, NULL, &errMessage[0]);
        printf("%s\n", &errMessage[0]);
	}

    return shader_program;
}

Shader::Shader(const char*  vertexPath, const char* fragmentPath)
{

    unsigned int vs, fs;

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //for try except
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Error on Shader Read" << std::endl;
    }

    

    const char* vs_source = vertexCode.c_str();
    const char* fs_source = fragmentCode.c_str();

    //create vertex and fragment, compile, then create program 
    programID = this->create_program(this->create_shader(GL_VERTEX_SHADER, vs_source),
                                    this->create_shader(GL_FRAGMENT_SHADER, fs_source));

}

void Shader::use(){
     glUseProgram(programID);
}