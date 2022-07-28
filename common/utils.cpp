// utils.cpp

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

GLuint create_shader(const std::string filename, const GLuint type) {

    printf("Creating shader from %s .\n", filename.c_str());

    // result
    GLuint shaderid = glCreateShader(type);

    // read in the file
    std::string source;
    std::ifstream ifs(filename, std::ios::in);
    if (ifs.is_open()) {
        std::stringstream ss;
        ss << ifs.rdbuf();
        source = ss.str();
        ifs.close();
    }
    else {
        std::cerr << "Couldn't open file " << filename << std::endl;
        getchar();
        return GL_FALSE;
    }

    GLint compile_result = GL_FALSE;
    int info_log_length;
    const char * sourceptr = source.c_str();

    glShaderSource(shaderid, 1, &sourceptr, NULL);
    glCompileShader(shaderid);

    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &compile_result);
    glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0) {
        std::vector<char> error_message(info_log_length + 1);
        glGetShaderInfoLog(shaderid, info_log_length, NULL, &error_message[0]);
        printf("Shader error message: %s\n", error_message[0]);
   }

    return shaderid;
}

GLuint link_program(GLuint vshaderid, GLuint fshaderid) {

    printf("Linking program.\n");

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vshaderid);
    glAttachShader(programID, fshaderid);

    glLinkProgram(programID);
    
    GLint link_result;
    int info_log_length;
    glGetProgramiv(programID, GL_LINK_STATUS, &link_result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0) {
        std::vector<char> error_message(info_log_length + 1);
        glGetProgramInfoLog(programID, info_log_length, NULL, &error_message[0]);
        printf("Linker error message: %s\n", error_message[0]);
        return GL_FALSE;
    }

    glDetachShader(programID, vshaderid);
    glDetachShader(programID, fshaderid);

    glDeleteShader(vshaderid);
    glDeleteShader(fshaderid);

    return programID;

}


