//
// Created by Aashay shah on 20/03/2021.
//

#ifndef OPENGL_WITH_CONAN_CONTEXT_H
#define OPENGL_WITH_CONAN_CONTEXT_H

#include "GLFW/glfw3.h"
#include "uv.h"
namespace gl {

struct Window {
    GLFWwindow *window;
    uv_loop_t loop;
    uv_idle_t __idler;
};


Window mkWindowContextCurrent(unsigned int SCR_WIDTH,
                                   unsigned int SCR_HEIGHT); 

}

#endif
