//
// Created by Aashay shah on 26/12/2020.
//

#ifndef OPENGL_WITH_CONAN_PROGRAM_H
#define OPENGL_WITH_CONAN_PROGRAM_H

#include "bind_point.h"
#include "shader.h"
#include <GL/glew.h>
#include <map>
#include <memory>
#include <string>

namespace gl {
class program : public std::enable_shared_from_this<program> {
    using error_handler = void (*)(int err, std::string describe);

  public:
    program(std::string vertexFile, std::string fragmentFile);

    void attachShader(gl::shader &s) ;

    void on_error(error_handler &handler);

    GLint attribLocation(std::string attr) ;

    gl::bind_point::ptr attribBindPoint(std::string attr,
                                        std::vector<gl::point_type> ps);

    GLint matLocation(std::string name) ;
    /* bind_point::ptr matLocation(std::string name); */

    void use() ;

    ~program();

    GLuint get();

    std::map<std::string, gl::bind_point::ptr> binds;
    using ptr = std::shared_ptr<program>;

  private:
    gl::shader vShader;
    gl::shader fShader;
    GLuint _program;
    int error{};
    std::string err_describe;
    error_handler err_func{};
};
} // namespace gl

#endif // OPENGL_WITH_CONAN_PROGRAM_H
