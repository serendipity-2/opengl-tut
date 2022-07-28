// utils.hpp

#ifndef __UTILS_H
#define __UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint create_shader(const std::string, const GLuint);
GLuint link_program(GLuint, GLuint);

GLuint loadBMP_custom(const char *);

#endif 
