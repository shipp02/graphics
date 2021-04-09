//
// Created by Aashay shah on 4/3/2021.
//
/* Give this a simple interface.
 * It will provide a field called arrayBuffer to hold its gl::buffer
 * program field to hold a gl::program
 * This is basically a container class for the all the various moving parts.
 * THere will also be a vector of bind_points of both types.
 */
#ifndef OPENGL_WITH_CONAN_VAO_H
#define OPENGL_WITH_CONAN_VAO_H

#include "buffer.h"
#include <gl/raw/opengl.h>
#include <string>
#include <vector>

namespace gl {

class vao {
    vao();
    ~vao();

    void addAttrib(const std::string& name, std::vector<GLfloat> &points, int shift);
  private:
    GLuint object;
//    std::vector<buffer> buffers;
    /* program p; */
    std::vector<bind_point> binds;
};
}


#endif //OPENGL_WITH_CONAN_VAO_H
