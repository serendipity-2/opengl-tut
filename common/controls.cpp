#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

vec3 position = vec3( 0, 0, 5 );    
float horizontalAngle = 3.14f;    
float verticalAngle   = 0.0f;    
float initialFOV = 45.0f;    
    
float speed = 3.0f;    
float mouse_speed = 0.005f;

void compute_matrices_from_inputs(
    mat4& proj,
    mat4& view,
    GLFWwindow* window
) {

    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    printf("Cursor pos: (%f, %f)  |  Delta time: %f  |  Est. UPS: %f\n", xpos, ypos, deltaTime, 1.0f/deltaTime);

    horizontalAngle += mouse_speed * float(1920 / 2 - xpos);
    verticalAngle += mouse_speed * float(1080 / 2 - ypos);

    vec3 direction = vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    vec3 right = vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    vec3 up = cross( right, direction );

    // move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }

    // move backward 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }

    // strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }    

    // strage left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    proj = perspective(radians(initialFOV), 16.0f / 9.0f, 0.1f, 100.0f);

    view = lookAt(
        position,
        position + direction,
        up
    );

    // reset mouse position for next frame
//    glfwSetCursorPos(window, 1920 / 2, 1080 / 2);

    lastTime = currentTime;
}
