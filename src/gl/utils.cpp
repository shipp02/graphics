//
// Created by Aashay shah on 27/12/2020.
//

#include "gl/utils.h"
#include <iostream>
#include <vector>

namespace gl {
void printErrors(std::string pos) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << " at " + pos << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }
}

void backgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void genAndBind(GLuint &gen, generator g, binder b) {
    g(1, &gen);
    b(gen);
}
} // namespace gl

namespace vertices {
std::vector<float> cube{
    -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
    0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 1.0f,
    1.0f,  1.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, 0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
    1.0f,  1.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.5f,  0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, 0.5f,  -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  1.0f};
std::vector<float> square{
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.5f,  -0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.5f,  0.5f, -0.5f, 1.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f,
    1.0f,  1.0f,  -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  1.0f, 0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f,
};
std::vector<GLfloat> normal_cube{
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
    0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
    0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
    0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
    0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
    0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};

std::vector<GLfloat> textured_cube{
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

} // namespace vertices
