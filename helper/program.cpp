//
// Created by Aashay shah on 26/12/2020.
//

#include "program.h"
#include "bind_point.h"
#include "utils.h"
#include "raw/wrappers.h"
#include <iostream>

namespace gl {

program::program(std::string vertexSource, std::string fragmentSource)
    : vShader(GL_VERTEX_SHADER, std::move(vertexSource)),
      fShader(GL_FRAGMENT_SHADER, std::move(fragmentSource)) {
    using namespace gl::raw;
    _program = CreateProgram();
    attachShader(vShader);
    attachShader(fShader);
    LinkProgram(_program);
    // TODO:Better error handlng design
    glGetProgramiv(_program, GL_LINK_STATUS, &error);
    if (error != GL_TRUE) {
        err_describe += "Linking failed\n";
    }
    // Inseted of guessing length. Get length of INFO_LOG using
    // glGetProgramiv using GL_INFO_LOG_LENGTH parameter.
    char proInfo[512];
    glGetProgramInfoLog(_program, 512, NULL, proInfo);
    err_describe += proInfo;
//    std::cout<<"Program: "<<vertexSource<<'\n'<<err_describe<<'\n';
}

bind_point::ptr program::attribBindPoint(std::string attr,
                                         std::vector<point_type> ps) {
    auto ptr = std::make_shared<bind_point>(std::move(attr), attribLocation(attr), std::move(ps));
    binds.insert({attr, ptr});
    return ptr;
}

void program::attachShader(shader &s) {
    raw::AttachShader(_program, s.get());
}

void program::on_error(error_handler &handler) {
    err_func = handler;
    if (error != 0) {
        handler(error, err_describe);
    }
}

GLint program::attribLocation(std::string attr) {
    auto pos = glGetAttribLocation(_program, attr.c_str());
    std::cout<<pos << " : position"<<std::endl;
    glEnableVertexAttribArray(pos);
    return pos;
}

program::~program() { glDeleteProgram(_program); }

void program::use() { glUseProgram(_program); }

GLint program::matLocation(std::string name) {
    return glGetUniformLocation(_program, name.c_str());
}

GLuint program::get() { return _program; }

} // namespace gl
