#ifndef HELPER_CONTEXT
#define HELPER_CONTEXT

#include "glm/fwd.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

namespace gl {
GLFWwindow *mkWindowContextCurrent(unsigned int SCR_WIDTH,
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

  // Init GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    throw "Failed to initialize GLEW\n";
  }
  return window;
}

void func_key_call (GLFWwindow* window, std::function<void(GLFWwindow*, int, int, int, int)> key_func) {
  glfwSetKeyCallback(window, *key_func.target<GLFWkeyfun>());
}

}
};
#endif
