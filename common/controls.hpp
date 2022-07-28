#ifndef __CONTROLS_H
#define __CONTROLS_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

void compute_matrices_from_inputs(mat4&, mat4&, GLFWwindow*);

#endif
