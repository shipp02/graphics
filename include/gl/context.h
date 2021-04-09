//
// Created by Aashay shah on 20/03/2021.
//

#ifndef OPENGL_WITH_CONAN_CONTEXT_H
#define OPENGL_WITH_CONAN_CONTEXT_H

#include <gl/raw/opengl.h>
#include "uv.h"
#include <deque>
#include <stdexcept>
#include <vector>

namespace gl {

struct key_events {
    int events_remaining;
    std::unique_ptr<std::deque<int>> event;
};

struct Window {
    GLFWwindow *window;
    uv_loop_t *loop;
    uv_idle_t *_idler;
    uv_async_t *key_events;
};

class gl_initialization_exception : public std::runtime_error {
  public:
    explicit gl_initialization_exception(std::string );
};

Window mkWindowContextCurrent(int SCR_WIDTH,
                                   int SCR_HEIGHT); 

}

#endif
