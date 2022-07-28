#include <stdio.h>
#include <stdlib.h>

#include <time.h>

// always include glew before gl.h and glfw3.h
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "../common/utils.hpp"
#include "../common/controls.hpp"

const int SCR_WIDTH = 1920, SCR_HEIGHT = 1080;
const float ASPECT = (float) SCR_WIDTH / (float) SCR_HEIGHT;

GLFWwindow* window;
GLuint vertex_array_cube;
GLuint vertexbuffer_cube, colorbuffer_cube;
GLuint programID;

mat4 mvp_cube;
GLuint uniform_mvp;

bool init_window() {

    glfwWindowHint(GLFW_SAMPLES, 4);  // 4x anti-aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GL_TRUE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GL_TRUE);

    // don't want old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    // open window and create its context
    window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "Learning OpenGL", NULL, NULL);
    if (window == NULL) return false;
    return true;

}

bool init_res() {

    glGenVertexArrays(1, &vertex_array_cube);
    glBindVertexArray(vertex_array_cube);
   
    GLuint vs, fs;
	if ((vs = create_shader("./res/simple.vs", GL_VERTEX_SHADER))   == 0) return false;
	if ((fs = create_shader("./res/simple.fs", GL_FRAGMENT_SHADER)) == 0) return false;

    if ((programID = link_program(vs, fs)) == GL_FALSE) return false;

    static const GLfloat vertexbuffer_cube_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    glGenBuffers(1, &vertexbuffer_cube);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_cube);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertexbuffer_cube_data),
        vertexbuffer_cube_data,
        GL_STATIC_DRAW
    );

    static const GLfloat colorbuffer_cube_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    glGenBuffers(1, &colorbuffer_cube);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer_cube);
    glBufferData(GL_ARRAY_BUFFER, 
        sizeof(colorbuffer_cube_data),
        colorbuffer_cube_data,
        GL_STATIC_DRAW
    );
   
    uniform_mvp = glGetUniformLocation(programID, "mvp");

    return true;
}


void render() {

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    mat4 proj, view;
    compute_matrices_from_inputs(proj, view, window);

    // model matrix
    mat4 model_cube = mat4(1.0f);
    // ModelViewProjection matrix
    mvp_cube = proj * view * model_cube;

    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &mvp_cube[0][0]);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_cube);
    glVertexAttribPointer(
        0,          // attribute zero. must match layout in shader
        3,          // size
        GL_FLOAT,   // type
        GL_FALSE,   // normalized?
        0,          // stride
        (void *) 0  // array buffer offset
    );
    
    static GLfloat colorbuffer_cube_data[12 * 3 * 3];
    srand(time(NULL));
    for (int i = 0; i < 12 * 3; ++i) {
        colorbuffer_cube_data[3 * i + 0] = ((double) rand() / RAND_MAX); // red
        colorbuffer_cube_data[3 * i + 1] = ((double) rand() / RAND_MAX); // blue 
        colorbuffer_cube_data[3 * i + 2] = ((double) rand() / RAND_MAX); // green 
    }

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer_cube);
    glBufferData(GL_ARRAY_BUFFER, 
        sizeof(colorbuffer_cube_data),
        colorbuffer_cube_data,
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *) 0
    );
    
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void cleanup() {
    glDeleteBuffers(1, &vertexbuffer_cube);
    glDeleteBuffers(1, &colorbuffer_cube);
    glDeleteVertexArrays(1, &vertex_array_cube);
    glDeleteProgram(programID);
}

int main() {
    
    if (!glfwInit()) { 
        fprintf( stderr, "Failed to init GLFW\n");
        getchar();
        return EXIT_FAILURE;
    }

    if (!init_window())  {
        fprintf( stderr, "failed to create glfw window.\n" );
        getchar();
        glfwTerminate();
        return EXIT_FAILURE;
    }
 
    glfwMakeContextCurrent(window);  // init glew

    // Ensure we can capture the escape key being pressed below    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);    
    // Hide the mouse and enable unlimited mouvement    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GL_TRUE);
    glfwPollEvents();
    glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);

    glewExperimental = true;  // need for core profile
    if (glewInit() != GLEW_OK) {
        fprintf( stderr, "failed to init glew\n");
        getchar();
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // set background to dark blue.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    if (!init_res()) {
        fprintf( stderr, "failed to init resources.\n" );
        getchar();
        glfwTerminate();
        return EXIT_FAILURE;
    }

    do {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();  
    }
    while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

    printf("Cleaning up...\n");

    cleanup();
    glfwTerminate();

    printf("Exiting.\n");

    return EXIT_SUCCESS;
}
