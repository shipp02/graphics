#ifndef HELPER_CONTEXT
#define HELPER_CONTEXT

#include "uv.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gl/context.h"
#include <fstream>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>

namespace gl {



void window_idler_callback(uv_idle_t *t) {
    if(glfwWindowShouldClose(static_cast<GLFWwindow*>(t->data))) {
        uv_idle_stop(t);
        uv_stop(t->loop);
    }
}
Window mkWindowContextCurrent(unsigned int SCR_WIDTH,
                                   unsigned int SCR_HEIGHT) {

    if (glfwInit() != GL_TRUE) {
        throw "Failed to initialise GLFW\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    uv_loop_init(uv_default_loop());
    uv_idle_t idler;
    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, window_idler_callback);
    idler.data = window;

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw "Failed to initialize GLEW\n";
    }
    return Window {
        .window = window,
        .loop = *uv_default_loop(),
        .__idler = idler
    };
}

void func_key_call(
    GLFWwindow *window,
    std::function<void(GLFWwindow *, int, int, int, int)> key_func) {
    glfwSetKeyCallback(window, *key_func.target<GLFWkeyfun>());
}

using std::ifstream;
using std::string;
using std::stringstream;

stringstream config_reader(const char *file) {
    ifstream infile;
    infile.open(file, std::ios::in);
    if (!infile.is_open()) {
        printf("Failed to read shader\n");
        printf("%s\n", file);
    }
    std::stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();
    return buffer;
}

struct config {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    GLfloat near;
    GLfloat far;
    GLfloat fov;
};

glm::vec3 read_vec(ifstream &infile) {
    string l1, l2, l3;
    getline(infile, l1);
    getline(infile, l2);
    getline(infile, l3);
    return glm::vec3(std::atof(l1.c_str()), std::atof(l2.c_str()),
                     std::atof(l3.c_str()));
}

GLfloat read_float(ifstream &infile) {
    string l1;
    getline(infile, l1);
    return std::atof(l1.c_str());
}

config read_config(const char *file) {
    ifstream infile;
    infile.open(file, std::ios::in);
    if (!infile.is_open()) {
        printf("Failed to read shader\n");
        printf("%s\n", file);
    }
    auto eye = read_vec(infile);
    auto center = read_vec(infile);
    auto up = read_vec(infile);
    return config{read_vec(infile),   read_vec(infile),   read_vec(infile),
                  read_float(infile), read_float(infile), read_float(infile)};
}
}; // namespace gl
#endif
