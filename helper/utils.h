//
// Created by Aashay shah on 27/12/2020.
//

#ifndef OPENGL_WITH_CONAN_UTILS_H
#define OPENGL_WITH_CONAN_UTILS_H

#include <GL/glew.h>
#include <string>
#include <vector>

namespace gl {
    using binder = void (*)(GLuint array);
    using generator = void (*)(GLsizei n, GLuint *array);

    void printErrors(std::string pos);

    void backgroundColor(float r, float g, float b, float a);

    void genAndBind(GLuint &gen, generator g, binder b);

}

namespace vertices {
    extern std::vector<GLfloat> cube;
    extern std::vector<float> square;
}

#endif //OPENGL_WITH_CONAN_UTILS_H
