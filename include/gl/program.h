//
// Created by Aashay shah on 26/12/2020.
//

#ifndef OPENGL_WITH_CONAN_PROGRAM_H
#define OPENGL_WITH_CONAN_PROGRAM_H

#include "bind_point.h"
#include "shader.h"
#include <gl/raw/opengl.h>
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

    // Are copy semantics desirable here.
    // If a copy gets deleted the program will also get deleted
    // which will result in undesirable behavior.
    // There will need to be a complete copy with
    // new entire shader and program objects made with opengl.
    program& operator= (const program &p);

    program(const program& p);

    std::map<std::string, gl::bind_point::ptr> binds;
    using ptr = std::shared_ptr<program>;

  private:
    // Use unique pointers to store gl::shaders
    // so that they cannot be copied
    gl::shader vShader;
    gl::shader fShader;
    // Use unique_ptr for this int to prevent copying
    GLuint _program;
    int error{};
    std::string err_describe;
    error_handler err_func{};
};
} // namespace gl

#endif // OPENGL_WITH_CONAN_PROGRAM_H
