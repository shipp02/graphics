//
// Created by Aashay shah on 4/3/2021.
//

#include "gl/vao.h"

namespace gl {

vao::vao() {
    glGenVertexArrays(1, &object);
    glBindVertexArray(object);
}

vao::~vao() { glDeleteVertexArrays(1, &object); }
void vao::addAttrib(const std::string& name, std::vector<GLfloat> &points, int shift) {
    /* binds.push_back(attrib_bind(p.get(), name)); */
}

} // namespace gl
