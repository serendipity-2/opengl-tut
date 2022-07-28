#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

// values that stay constant for the whole mesh.
uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertexPosition, 1);   

    // the color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = vertexColor;
}

