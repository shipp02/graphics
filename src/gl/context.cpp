#ifndef HELPER_CONTEXT
#define HELPER_CONTEXT

#include "uv.h"
#include <gl/raw/opengl.h>
#include "gl/context.h"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace gl {

void window_idler_callback(uv_idle_t *t) {
    if (glfwWindowShouldClose(glfwGetCurrentContext())) {
        // GLFW closing hooks.
        glfwDestroyWindow(glfwGetCurrentContext());
        glfwTerminate();
        // libuv closing hooks
        uv_idle_stop(t);
        uv_stop(t->loop);
    }
    glfwPollEvents();
}

void uv_key_callback(uv_async_t *t) {
    auto *k =  static_cast<key_events*>(t->data);
    for(auto it = k->event->begin(); it!=k->event->end(); ++it) {
        // For now all key callbacks will be handled by this function.
        if(*it == GLFW_KEY_Q) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
        }
        k->event->pop_front();
    }
}

void key_callback(GLFWwindow *win, int key, int, int action, int modifier) {
    auto* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    auto *k =  static_cast<key_events*>(window->key_events->data);
    // Consider sending all the data to the uv_key_callback
    k->event->push_back(key);
    k->events_remaining++;
    uv_async_send(window->key_events);
}

Window mkWindowContextCurrent(int SCR_WIDTH, int SCR_HEIGHT) {

    if (glfwInit() != GL_TRUE) {
        throw gl_initialization_exception("GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    uv_loop_init(uv_default_loop());
    uv_idle_t *idler = new uv_idle_t;
    uv_idle_init(uv_default_loop(), idler);
    uv_idle_start(idler, window_idler_callback);
    uv_async_t *key_async = new uv_async_t;
    key_async->data = new key_events {
        .events_remaining = 0,
        .event = std::make_unique<std::deque<int>>()
    };
    uv_async_init(uv_default_loop(), key_async, uv_key_callback);
    glfwSetKeyCallback(window, key_callback);

    auto *win = new Window {
        .window = window,
        .loop = uv_default_loop(),
        ._idler = idler,
        .key_events = key_async
    };
    glfwSetWindowUserPointer(window, win);

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw gl_initialization_exception("GLEW");
    }
    return *win;
}

gl_initialization_exception::gl_initialization_exception(const std::string s)
    : std::runtime_error(s) {}
} // namespace gl
#endif
