//
// Created by Aashay shah on 20/03/2021.
//

#ifndef OPENGL_WITH_CONAN_CONTEXT_H
#define OPENGL_WITH_CONAN_CONTEXT_H

#include "GLFW/glfw3.h"
namespace gl {

GLFWwindow *mkWindowContextCurrent(unsigned int SCR_WIDTH,
                                   unsigned int SCR_HEIGHT); 

}

#endif
