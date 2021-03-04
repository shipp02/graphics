//
// Created by Aashay shah on 26/12/2020.
//

#include "program.h"
#include "utils.h"

namespace gl {

program::program(std::string vertexSource, std::string fragmentSource)
    : vShader(GL_VERTEX_SHADER, vertexSource),
      fShader(GL_FRAGMENT_SHADER, fragmentSource) {
    _program = glCreateProgram();
    attachShader(vShader);
    gl::printErrors("program cons");
    gl::printErrors("program cons2");
    attachShader(fShader);
    gl::printErrors("program cons.");
    glLinkProgram(_program);
    // TODO:Better error handlng design
    glGetProgramiv(_program, GL_LINK_STATUS, &error);
    if (error != GL_TRUE) {
        err_describe += "Linking failed\n";
    }
    char proInfo[512];
    glGetProgramInfoLog(_program, 512, NULL, proInfo);
    err_describe += proInfo;
}

bind_point::ptr program::attribBindPoint(std::string attr,
                                         std::vector<point_type> ps) {
    auto ptr = std::make_shared<bind_point>(attr, attribLocation(attr), ps);
    binds.insert({attr, ptr});
    return ptr;
}

void program::attachShader(shader &s) const {
    glAttachShader(_program, s.get());
}

void program::on_error(error_handler &handler) {
    err_func = handler;
    if (error != 0) {
        handler(error, err_describe);
    }
}

GLuint program::attribLocation(std::string attr) const {
    auto pos = glGetAttribLocation(_program, attr.c_str());
    glEnableVertexAttribArray(pos);
    return pos;
}

program::~program() { glDeleteProgram(_program); }

void program::use() const { glUseProgram(_program); }

GLint program::matLocation(std::string name) const {
    return glGetUniformLocation(_program, name.c_str());
}

GLuint program::get() { return _program; }
} // namespace gl
